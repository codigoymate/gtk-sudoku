/**
 * @file board-area.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of board-view.h
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <board-area.h>

#include <sudoku.h>
#include <board.h>
#include <utils.h>

/**
 * @brief Construct a new Board Area object
 */
BoardArea::BoardArea(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder,
				SudokuApp *app) : Gtk::DrawingArea(obj), app(app) {
	signal_draw().connect(sigc::mem_fun(*this, &BoardArea::on_area_draw));
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::KEY_PRESS_MASK);
	set_can_focus(true);
	signal_button_press_event().connect(sigc::mem_fun(*this, &BoardArea::on_area_click));
	signal_key_press_event().connect(sigc::mem_fun(*this, &BoardArea::on_area_key_press));
	sel_x = sel_y = -1;
}

/**
 * @brief On board draw.
 * 
 * @param cr Cairo drawing context.
 * @return true ever.
 */
bool BoardArea::on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	int w = get_allocated_width();
	int h = get_allocated_height();

	//double s_size = double(w <= h ? w : h) / (app->get_board().get_size() == 81 ? 9.0 : 4.0);

	auto s_size = double(w <= h ? w : h);

	Utils::draw_grid(cr, app->get_board(), w, h, sel_x, sel_y, error);

	// Draw "Solved !" if board solved
	if (app->get_board() == app->get_solved() && !app->get_board().empty()) {
		cr->set_source_rgb(0, 0, 0);
		cr->select_font_face("sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
		cr->set_font_size(s_size * 0.18);
		cr->move_to(s_size * 0.1, s_size * 0.55);
		cr->text_path("Solved !");
		cr->set_line_width(4.0);
		cr->stroke();

		cr->set_source_rgb(0, 0.7, 0);
		cr->move_to(s_size * 0.1, s_size * 0.55);
		cr->show_text("Solved !");
	}

	return true;
}

/**
 * @brief On board click.
 * 
 * @param event Mouse button event.
 * @return true to leave the others handlers.
 */
bool BoardArea::on_area_click(GdkEventButton *event) {

	error = false;

	if (event->type == GDK_BUTTON_PRESS && event->button == 1) {

		sel_x = sel_y = -1;

		if (app->get_board() == app->get_solved()) return false;

		int w = get_allocated_width();
		int h = get_allocated_height();

		double s_size = double(w <= h ? w : h) / (app->get_board().get_size() == 81 ? 9.0 : 4.0);

		sel_x = std::floor(double(event->x) / s_size);
		sel_y = std::floor(double(event->y) / s_size);

		if (sel_x >= 9 || sel_y >= 9)
			sel_x = sel_y = -1;

		queue_draw();

	}

	return true;
}

/**
 * @brief On key press.
 * 
 * @param event Keyboard event.
 * @return true to leave the others handlers.
 */
bool BoardArea::on_area_key_press(GdkEventKey *event) {

	error = false;

	if (sel_x == -1 || sel_y == -1) return false;
	if (app->get_board().get(sel_x, sel_y).fixed) return false;

	if (event->type == GDK_KEY_PRESS) {

		if (app->get_board() == app->get_solved()) return false;

		int key = gdk_keyval_name(event->keyval)[0];
		if (key >= '1' && key <= '9') {
			this->chosen_a_number(key - '0');
			queue_draw();
		}

		if (event->keyval == GDK_KEY_0 ||
				event->keyval == GDK_KEY_BackSpace ||
				event->keyval == GDK_KEY_Delete) {
			app->get_board().set(sel_x, sel_y, {unsigned(0), false});
			queue_draw();
		}

		return true;
	}

	return false;
}

/**
 * @brief It is called when the user presses a number or clicks on a number button.
 * 
 * @param number chosen number. 
 */
void BoardArea::chosen_a_number(const unsigned number) {

	error = false;

	if (sel_x == -1 || sel_y == -1) return;
	if (app->get_board().get(sel_x, sel_y).fixed) return;

	if (app->get_board() == app->get_solved()) return;

	auto max = app->get_board().get_size() == 81 ? 9 : 4;

	if (number >= 1 && number <= max) {
		app->get_board().set(sel_x, sel_y, {number, false});

		if (!app->get_board().is_valid(sel_x, sel_y)) {
			select(sel_x, sel_y, true); // Select with error
		}

		// Board solved
		if (app->get_board() == app->get_solved()) {
			app->player_wins();
		}
	}

	queue_draw();
}

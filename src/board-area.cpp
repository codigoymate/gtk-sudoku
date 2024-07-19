#include <board-area.h>

#include <app.h>
#include <sudoku.h>

BoardArea::BoardArea(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder,
				SudokuApp *app) : Gtk::DrawingArea(obj), app(app) {
	signal_draw().connect(sigc::mem_fun(*this, &BoardArea::on_area_draw));
}

bool BoardArea::on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	int w = get_allocated_width();
	int h = get_allocated_height();

	for (unsigned y = 0; y < 9; y ++) {
		for (unsigned x = 0; x < 9; x ++) {

			// Draw Rectangle
			if (app->getBoard()->get(x, y).fixed) cr->set_source_rgb(0.8, 0.8, 0.8);
			else cr->set_source_rgb(1, 1, 1);

			double s_size = double(w <= h ? w : h) / 9.0;
			
			cr->rectangle(x * s_size, y * s_size, s_size, s_size);
			cr->fill();

			cr->set_source_rgb(0, 0, 0);
			cr->set_line_width(1);
			cr->rectangle(x * s_size, y * s_size, s_size, s_size);

			cr->stroke();

			// Draw number
			if (app->getBoard()->get(x, y).value) {
				cr->select_font_face("sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
				cr->set_font_size(s_size * 0.7);
				cr->move_to(x * s_size + s_size * 0.25, y * s_size + s_size * 0.8);
				cr->show_text(std::to_string(app->getBoard()->get(x, y).value));
			}
		}
	}

	return true;
}

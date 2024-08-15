#include <board-view.h>

#include <utils.h>

/**
 * @brief Construct a new BoardView
 * 
 * @param obj base object.
 * @param builder ui builder.
 * @param board Board to draw.
 */
BoardView::BoardView(const Board &board) : board{board} {
	signal_draw().connect([this](const Cairo::RefPtr<Cairo::Context> &cr) -> bool {
		return this->on_area_draw(cr);
	});
}


/**
 * @brief On board draw.
 * 
 * @param cr Cairo drawing context.
 * @return true ever.
 */
bool BoardView::on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

	auto w = this->get_allocated_width();
	auto h = this->get_allocated_height();

	Utils::draw_grid(cr, board, w, h, -1, -1, false);

	return true;
}

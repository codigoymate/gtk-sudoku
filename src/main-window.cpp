#include <main-window.h>

#include <main-menu.h>
#include <board-area.h>

MainWindow::MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::ApplicationWindow(obj), app(app) {
	builder->get_widget_derived("main-menu", main_menu, app);
	builder->get_widget_derived("board-area", board_area, app);
}

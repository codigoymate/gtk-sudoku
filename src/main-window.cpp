#include <main-window.h>

#include <main-menu.h>

MainWindow::MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::ApplicationWindow(obj), app(app) {
	builder->get_widget_derived("main-menu", main_menu, app);
}

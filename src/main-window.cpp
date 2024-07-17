#include <main-window.h>

MainWindow::MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::ApplicationWindow(obj), app(app) {

}

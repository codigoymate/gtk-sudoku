#include <welcome-window.h>

#include <sudoku.h>
#include <main-window.h>

WelcomeWindow::WelcomeWindow(BaseObjectType* obj,
		Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::Window(obj), app{app} {

	Gtk::Button *button;
	builder->get_widget("new-game-button", button);
	button->signal_clicked().connect(sigc::mem_fun(
			*this, &WelcomeWindow::new_game_button_clicked));

}

void WelcomeWindow::show(SudokuApp *app) {
	WelcomeWindow *ww;
	auto builder = Gtk::Builder::create_from_file("../ui/welcome-window.glade");
	builder->get_widget_derived("welcome-window", ww, app);

	app->add_window(*ww);

	ww->set_transient_for(*app->get_main_window());

	ww->show_all();
}

void WelcomeWindow::new_game_button_clicked() {
	app->new_game();
	this->close();
}

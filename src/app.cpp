#include <app.h>

#include <main-window.h>
#include <sudoku.h>

SudokuApp::SudokuApp(int argc, char *argv[]) :
		Gtk::Application(argc, argv, "com.codigoymate.sudoku") {
	board = std::make_shared<Board>();
	board->load("../first-boards/1 sol 01.xml");
}

void SudokuApp::on_activate() {
	MainWindow *mw;
	auto builder = Gtk::Builder::create_from_file("../ui/main-window.glade");
	builder->get_widget_derived("main-window", mw, this);

	main_window = std::shared_ptr<MainWindow>(mw);
	this->add_window(*main_window);

	main_window->show_all();
}

int main(int argc, char *argv[]) {
	SudokuApp app(argc, argv);
	return app.run();
}

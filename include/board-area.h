#pragma once

#include <gtkmm.h>
#include <cairomm/context.h>

class SudokuApp;

class BoardArea: public Gtk::DrawingArea {
public:
	BoardArea(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);
private:
	SudokuApp *app;

	bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr);
};

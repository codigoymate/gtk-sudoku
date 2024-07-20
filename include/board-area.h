#pragma once

#include <gtkmm.h>
#include <cairomm/context.h>

class SudokuApp;

class BoardArea: public Gtk::DrawingArea {
public:
	BoardArea(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

	void select(const int x, const int y) { sel_x = x; sel_y = y; }

private:
	SudokuApp *app;

	bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	bool on_area_click(GdkEventButton *event);
	bool on_area_key_press(GdkEventKey *event);

	int sel_x, sel_y;
};

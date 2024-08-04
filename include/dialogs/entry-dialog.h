/**
 * @file entry-dialog.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Shows entry text user dialog.
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

/**
 * @brief Show text entry dialog.
 * 
 */
class EntryDialog: public Gtk::Dialog {
public:
	/**
	 * @brief Construct a new Entry Dialog.
	 */
	EntryDialog(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const& builder);

	/**
	 * @brief Shows the entry dialog.
	 * @param prompt The prompt to show.
	 * 
	 * @return const std::string the text entered. or "" if the dialog is cancelled.
	 */
	static const std::string show(const std::string prompt);

private:
	Gtk::Entry *entry;
	Gtk::Label *prompt_label;
};

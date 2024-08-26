/**
 * @file entry-dialog.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of entry-dialog.h
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dialogs/entry-dialog.h>

#include <utils.h>

/**
 * @brief Construct a new Entry Dialog.
 */
EntryDialog::EntryDialog(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const& builder) :
		Gtk::Dialog(obj) {
	builder->get_widget("entry", entry);
	builder->get_widget("prompt-label", prompt_label);
}

/**
 * @brief Shows the entry dialog.
 * @param prompt The prompt to show.
 * 
 * @return const std::string the text entered. or "" if the dialog is cancelled.
 */
const std::string EntryDialog::show(const std::string prompt) {
	EntryDialog *dialog;
	auto builder = Gtk::Builder::create_from_file(Utils::locate_ui("entry-dialog.glade"));
	builder->get_widget_derived("entry-dialog", dialog);

	dialog->prompt_label->set_text(prompt);

	auto result = dialog->run();

	dialog->close();

	if (result == Gtk::RESPONSE_ACCEPT) return dialog->entry->get_text();

	return "";
}

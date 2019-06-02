#include "editor_version_control_settings.h"
#include "editor_settings.h"

Array EditorVersionControlSettings::available_vcs;
bool EditorVersionControlSettings::is_vcs_intialised;
String EditorVersionControlSettings::vcs_name;

void EditorVersionControlSettings::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_initialize_vcs"), &EditorVersionControlSettings::_initialize_vcs);
	ClassDB::bind_method(D_METHOD("_selected_a_vcs"), &EditorVersionControlSettings::_selected_a_vcs);

	ClassDB::bind_method(D_METHOD("popup_vcs_initialization_settings"), &EditorVersionControlSettings::popup_vcs_initialization_settings);
}

void EditorVersionControlSettings::_register_vcs_plugin(String p_vcs_name) {

	if (available_vcs.find(p_vcs_name) != -1) {
		available_vcs.append(p_vcs_name);
	}
}

void EditorVersionControlSettings::_initialize_vcs(String p_vcs_name) {

	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);
	vcs_name = vcs_choice_drop_down->get_text();
}

void EditorVersionControlSettings::_selected_a_vcs() {

	if (available_vcs.find(vcs_name) != -1) {
		initialize_button->set_disabled(false);
	} else {
		initialize_button->set_disabled(true);
	}
}

void EditorVersionControlSettings::popup_vcs_initialization_settings(Control * p_gui_base) {

	Size2 popup_size = Size2(450, 300);
	Size2 window_size = p_gui_base->get_viewport_rect().size;
	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	vcs_name = EditorSettings::get_singleton()->get_project_metadata("vcs", "name", "");

	if (is_vcs_intialised) {
		initialize_button->set_disabled(true);
	}

	vcs_init_dialog_holder->popup_centered(popup_size);
}

EditorVersionControlSettings::EditorVersionControlSettings(EditorData *p_data) {

	data = p_data;
	is_vcs_intialised = false;

	vcs_init_dialog_holder = memnew(AcceptDialog);
	vcs_init_dialog_holder->set_title(TTR("Set Up Version Control"));
	vcs_init_dialog_holder->set_v_size_flags(BoxContainer::SIZE_SHRINK_CENTER);
	add_child(vcs_init_dialog_holder);

	VBoxContainer * vcs_init_dialog = memnew(VBoxContainer);
	vcs_init_dialog->set_alignment(ALIGN_BEGIN);
	vcs_init_dialog_holder->add_child(vcs_init_dialog);

	vcs_init_vbc = memnew(VBoxContainer);
	vcs_init_dialog->add_child(vcs_init_vbc);
	
	vcs_init_hbc = memnew(HBoxContainer);
	vcs_init_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	vcs_init_dialog->add_child(vcs_init_hbc);

	vcs_name_label = memnew(Label);
	vcs_name_label->set_text(TTR("Version Control System"));
	vcs_init_hbc->add_child(vcs_name_label);

	vcs_choice_drop_down = memnew(OptionButton);
	vcs_choice_drop_down->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	vcs_choice_drop_down->set_text(TTR("Select an available VCS"));
	for (int i = 0; i < available_vcs.size(); i++) {
		vcs_choice_drop_down->add_item(available_vcs[i]);
	}
	vcs_choice_drop_down->connect("pressed", this, "_selected_a_vcs");
	vcs_init_hbc->add_child(vcs_choice_drop_down);

	initialize_button = memnew(Button(TTR("Initialise VCS")));
	initialize_button->set_disabled(true);
	initialize_button->connect("pressed", this, "_initialize_vcs");
	vcs_init_vbc->add_child(initialize_button);
}

EditorVersionControlSettings::~EditorVersionControlSettings() {
}

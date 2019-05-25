#include "vcs_settings_editor.h"
#include "editor_settings.h"

void VCSSettingsEditor::_initialise_vcs_plugin(String p_vcs_name) {

	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);
}

void VCSSettingsEditor::_initialise_vcs() {
	initialise_button->set_text("aha");
}

void VCSSettingsEditor::popup_vcs_settings() {

	Size2 popup_size = Size2(900, 500);
	Size2 window_size = get_viewport_rect().size;

	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	vcs_name = EditorSettings::get_singleton()->get_project_metadata("vcs", "name", "");
	if (is_vcs_intialised) {
		initialise_button->set_disabled(true);
	}

	popup_centered(popup_size);
}

VCSSettingsEditor::VCSSettingsEditor(EditorData *p_data) {
	set_title(TTR("VCS Settings"));
	set_resizable(true);
	data = p_data;
	is_vcs_intialised = false;
	
	VBoxContainer *vbc = memnew(VBoxContainer);
	vbc->set_alignment(BoxContainer::ALIGN_BEGIN);
	vbc->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	add_child(vbc);

	HBoxContainer *hbc = memnew(HBoxContainer);
	hbc->set_h_size_flags(Control::SIZE_EXPAND);
	vbc->add_child(hbc);

	vcs_name_label = memnew(Label);
	vcs_name_label->set_text(TTR("VCS Name"));
	hbc->add_child(vcs_name_label);

	vcs_choice_drop_down = memnew(OptionButton);
	vcs_choice_drop_down->set_text(TTR("Select an available VCS"));
	for (int i = 0; i < available_vcs.size(); i++) {
		vcs_choice_drop_down->add_item(available_vcs[i]);
	}
	hbc->add_child(vcs_choice_drop_down);

	initialise_button = memnew(Button(TTR("Initialise VCS")));
	initialise_button->connect("pressed", this, "_initialise_vcs");
	vbc->add_child(initialise_button);
}

VCSSettingsEditor::~VCSSettingsEditor() {
}

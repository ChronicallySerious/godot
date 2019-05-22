#include "editor_settings.h"
#include "vcs_settings_editor.h"

float VCSSettingsEditor::scale;

void VCSSettingsEditor::_initialise_vcs_plugin(String p_vcs_name) {

	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);
	scale = 2.0f;
}

void VCSSettingsEditor::popup_vcs_settings() {

	Size2 popup_size = Size2(900, 700) * editor_get_scale();
	Size2 window_size = get_viewport_rect().size;

	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);
	
	popup_centered(popup_size);
}

float VCSSettingsEditor::editor_get_scale() {
	return scale;
}

VCSSettingsEditor::VCSSettingsEditor(EditorData *p_data) {
	set_title(TTR("VCS Settings (project.godot)"));
	set_resizable(true);
	data = p_data;

	VBoxContainer *vbc = memnew(VBoxContainer);
	vbc->set_alignment(BoxContainer::ALIGN_BEGIN);
	vbc->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	add_child(vbc);

	HBoxContainer *hbc = memnew(HBoxContainer);
	hbc->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	vbc->add_child(hbc);

	label = memnew(OptionButton);
	label->set_text(TTR("Version Control Setting"));
	vbc->add_child(label);
}

VCSSettingsEditor::~VCSSettingsEditor() {
}

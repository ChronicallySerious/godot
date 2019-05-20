#include "vcs_settings_editor.h"

void VCSSettingsEditor::_initialise_vcs_plugin(String p_vcs_name) {

	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);

	
}

void VCSSettingsEditor::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_initialise_vcs_plugin"), &VCSSettingsEditor::_initialise_vcs_plugin);
}

void VCSSettingsEditor::popup_vcs_settings() {

	Rect2 saved_size = EditorSettings::get_singleton()->get_project_metadata("dialog_bounds", "vcs_settings", Rect2());
	
	if (saved_size != Rect2())
	{
		popup(saved_size);
	}
}

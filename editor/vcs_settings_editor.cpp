#include "vcs_settings_editor.h"

void VCSSettingsEditor::_vcs_select(VCSName p_vcs_name) {

	Variant vcs_name = Variant(p_vcs_name);
	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);

}

void VCSSettingsEditor::_bind_methods() {

	ClassDB::bind_method("_vcs_select", &VCSSettingsEditor::_vcs_select);

}

void VCSSettingsEditor::popup_vcs_settings() {

	Rect2 saved_size = EditorSettings::get_singleton()->get_project_metadata("dialog_bounds", "vcs_settings", Rect2());
	
	if (saved_size != Rect2())
	{
		popup(saved_size);
	}
}

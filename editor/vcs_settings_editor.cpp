#include "vcs_settings_editor.h"

void VCSSettingsEditor::_vcs_select(VCSName p_vcs_name) {

	current_vcs_name = p_vcs_name;

}

void VCSSettingsEditor::_bind_methods() {

	ClassDB::bind_method("_vcs_select", &VCSSettingsEditor::_vcs_select);

}

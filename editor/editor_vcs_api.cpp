#include "editor_vcs_api.h"
#include "vcs_settings_editor.h"

void EditorVCSAPI::register_to_editor(String p_name) {
	VCSSettingsEditor::_register_vcs_plugin(p_name);
}

void EditorVCSAPI::get_commit_dock() {
	_get_commit_dock();
}

String EditorVCSAPI::get_vcs_name() {
	return _get_vcs_name();
}

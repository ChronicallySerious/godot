#include "editor/editor_vcs_api.h"
#include "editor/plugins/version_control_editor_plugin.h"

void EditorVCS::_register_to_editor(const String &p_name) {

	if (!VersionControlEditorPlugin::get_singleton()->register_vcs(p_name)) {

		WARN_PRINT("Duplicate VCS entry trying to be registered.");
	}
}

void EditorVCS::get_commit_dock() const {
}

String EditorVCS::get_vcs_name() const {

	return vcs_name;
}

EditorVCS::EditorVCS() {
}

EditorVCS::~EditorVCS() {
}

#include "editor_vcs_interface.h"

EditorVCSInterface *EditorVCSInterface::singleton = NULL;

void EditorVCSInterface::_bind_methods() {
}

void EditorVCSInterface::set_version_control_dock(Node *p_vcs_control_dock) {

	EditorVersionControlDock *version_control_dock = VersionControlEditorPlugin::get_singleton()->get_version_control_dock();
	version_control_dock = Object::cast_to<EditorVersionControlDock>(p_vcs_control_dock);
	ERR_FAIL_NULL(version_control_dock);
}

void EditorVCSInterface::set_version_commit_dock(Node *p_vcs_commit_dock) {

	EditorVersionCommitDock *version_commit_dock = VersionControlEditorPlugin::get_singleton()->get_version_commit_dock();
	version_commit_dock = Object::cast_to<EditorVersionCommitDock>(p_vcs_commit_dock);
	ERR_FAIL_NULL(version_commit_dock);
}

void EditorVCSInterface::set_version_control_name(String p_vcs_name) {

	VersionControlEditorPlugin::get_singleton()->set_version_control_name(p_vcs_name);
}

String EditorVCSInterface::get_vcs_name() {

	WARN_PRINT("No VCS specified. Using stock responses.");
	return "";
}

EditorVCSInterface::EditorVCSInterface() {
}

EditorVCSInterface::~EditorVCSInterface() {
}

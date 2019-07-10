#include "editor_vcs_interface.h"

EditorVCSInterface *EditorVCSInterface::singleton = NULL;

void EditorVCSInterface::_bind_methods() {
}

void EditorVCSInterface::supply_editor_requirements(Node *p_vcs_control_dock, Node *p_vcs_commit_dock, String p_vcs_name) {

	EditorVersionControlDock *version_control_dock = VersionControlEditorPlugin::get_singleton()->get_version_control_dock();
	version_control_dock = Object::cast_to<EditorVersionControlDock>(p_vcs_control_dock);
	ERR_FAIL_NULL(version_control_dock);

	EditorVersionCommitDock *version_commit_dock = VersionControlEditorPlugin::get_singleton()->get_version_commit_dock();
	version_commit_dock = Object::cast_to<EditorVersionCommitDock>(p_vcs_commit_dock);
	ERR_FAIL_NULL(version_commit_dock);

	VersionControlEditorPlugin::get_singleton()->set_version_control_name(p_vcs_name);
	ERR_FAIL_COND(p_vcs_name == "");
}

String EditorVCSInterface::get_vcs_name() {

	WARN_PRINT("No VCS Interface specified. Using stock responses for VCS info getters.");
	return "";
}

Array EditorVCSInterface::get_git_remotes() {

	return Array();
}

EditorVCSInterface::EditorVCSInterface() {
}

EditorVCSInterface::~EditorVCSInterface() {
}

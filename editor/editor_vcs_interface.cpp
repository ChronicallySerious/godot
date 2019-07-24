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

bool EditorVCSInterface::initialize(String p_project_root_path) {

	// Editor shouldn't be calling this definition.
	// Using this implies that there is no VCS interaction present with the editor
	WARN_PRINT("No VCS Interface specified. Using stock responses for Version Control information.");
	return "";
}

bool EditorVCSInterface::shutdown() {

	return false;
}

String EditorVCSInterface::get_project_name() {

	return String();
}

String EditorVCSInterface::get_vcs_name() {

	return "";
}

Node *EditorVCSInterface::get_init_settings() {

	return nullptr;
}

EditorVCSInterface::EditorVCSInterface() {
}

EditorVCSInterface::~EditorVCSInterface() {
}

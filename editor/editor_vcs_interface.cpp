#include "editor/editor_vcs_interface.h"

EditorVCSInterface *EditorVCSInterface::vcs_interface;

void EditorVCSInterface::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_version_control_dock", "vcs_control_dock"), &EditorVCSInterface::set_version_control_dock);
	ClassDB::bind_method(D_METHOD("set_version_commit_dock", "version_commit_dock"), &EditorVCSInterface::set_version_commit_dock);
	ClassDB::bind_method(D_METHOD("set_version_control_name", "vcs_name"), &EditorVCSInterface::set_version_control_name);
}

String EditorVCSInterface::get_version_control_name() {

	return call("get_vcs_name");
}

void EditorVCSInterface::set_version_control_dock(Node *p_vcs_control_dock) {

	EditorVersionControlDock *vcs_control_dock = VersionControlEditorPlugin::get_singleton()->get_version_control_dock();
	vcs_control_dock = Object::cast_to<EditorVersionControlDock>(p_vcs_control_dock);

	if (!vcs_control_dock) {

		WARN_PRINT("vcs_control_dock is set to NULL");
	}
}

void EditorVCSInterface::set_version_commit_dock(Node *p_vcs_commit_dock) {

	EditorVersionCommitDock *version_commit_dock = VersionControlEditorPlugin::get_singleton()->get_version_commit_dock();
	version_commit_dock = Object::cast_to<EditorVersionCommitDock>(p_vcs_commit_dock);

	if (!version_commit_dock) {

		WARN_PRINT("version_commit_dock is set to NULL");
	}
}

void EditorVCSInterface::set_version_control_name(String p_vcs_name) {

	VersionControlEditorPlugin::get_singleton()->set_version_control_name(p_vcs_name);
}

EditorVCSInterface::EditorVCSInterface() {
}

EditorVCSInterface::~EditorVCSInterface() {
}

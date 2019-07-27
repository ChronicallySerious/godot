#include "editor_vcs_interface.h"

Node *EditorVCSInterface::singleton = NULL;

void EditorVCSInterface::_bind_methods() {

	ClassDB::bind_method(D_METHOD("initialize", "project_root_path"), &EditorVCSInterface::initialize);;
	ClassDB::bind_method(D_METHOD("get_vcs_name"), &EditorVCSInterface::get_vcs_name);
	ClassDB::bind_method(D_METHOD("shut_down"), &EditorVCSInterface::shut_down);
	ClassDB::bind_method(D_METHOD("get_project_name"), &EditorVCSInterface::get_project_name);
	ClassDB::bind_method(D_METHOD("submit_vcs_addon", "addon"), &EditorVCSInterface::submit_vcs_addon);

	BIND_VMETHOD(MethodInfo("get_initialization_settings_panel_container"));
	BIND_VMETHOD(MethodInfo("get_commit_dock_panel_container"));
}

bool EditorVCSInterface::initialize(String p_project_root_path) {

	// Editor shouldn't be calling this definition.
	// Using this implies that there is no VCS interaction present with the editor
	WARN_PRINT("No VCS Interface specified. Using stock responses for Version Control information.");
	return "";
}

Control *EditorVCSInterface::get_initialization_settings_panel_container() {

	return NULL;
}

Control *EditorVCSInterface::get_commit_dock_panel_container() {

	return NULL;
}

bool EditorVCSInterface::shut_down() {

	return false;
}

void EditorVCSInterface::submit_vcs_addon(Node *p_addon) {

	WARN_PRINT("received submit");
	singleton = p_addon;
}

String EditorVCSInterface::get_project_name() {

	return String();
}

String EditorVCSInterface::get_vcs_name() {

	return "";
}

EditorVCSInterface::EditorVCSInterface() {
}

EditorVCSInterface::~EditorVCSInterface() {
}

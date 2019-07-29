#include "editor_vcs_interface.h"

Object *EditorVCSInterface::singleton = NULL;

void EditorVCSInterface::_bind_methods() {

	ClassDB::bind_method(D_METHOD("initialize", "project_root_path"), &EditorVCSInterface::initialize);;
	ClassDB::bind_method(D_METHOD("get_vcs_name"), &EditorVCSInterface::get_vcs_name);
	ClassDB::bind_method(D_METHOD("shut_down"), &EditorVCSInterface::shut_down);
	ClassDB::bind_method(D_METHOD("get_project_name"), &EditorVCSInterface::get_project_name);

	ClassDB::bind_method(D_METHOD("get_initialization_settings_panel_container"), &EditorVCSInterface::get_initialization_settings_panel_container);
	ClassDB::bind_method(D_METHOD("get_commit_dock_panel_container"), &EditorVCSInterface::get_commit_dock_panel_container);
}

bool EditorVCSInterface::initialize(String p_project_root_path) {

	WARN_PRINT("No VCS Interface specified. Default Version Control Interface behaviour is active.");
	return "";
}

Variant EditorVCSInterface::get_initialization_settings_panel_container() {

	return NULL;
}

Variant EditorVCSInterface::get_commit_dock_panel_container() {

	return NULL;
}

bool EditorVCSInterface::shut_down() {

	return false;
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

Object *EditorVCSInterface::get_singleton() {

	if (singleton) {

		return singleton;
	}

	return singleton;
}

void EditorVCSInterface::set_singleton(Object *p_singleton) {

	singleton = p_singleton;
}

#include "editor_vcs_interface.h"

EditorVCSInterface *EditorVCSInterface::singleton = NULL;

void EditorVCSInterface::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_initialize", "project_root_path"), &EditorVCSInterface::_initialize);
	ClassDB::bind_method(D_METHOD("_get_is_vcs_intialized"), &EditorVCSInterface::_get_is_vcs_intialized);
	ClassDB::bind_method(D_METHOD("_get_vcs_name"), &EditorVCSInterface::_get_vcs_name);
	ClassDB::bind_method(D_METHOD("_shut_down"), &EditorVCSInterface::_shut_down);
	ClassDB::bind_method(D_METHOD("_get_project_name"), &EditorVCSInterface::_get_project_name);

	ClassDB::bind_method(D_METHOD("_get_initialization_settings_panel_container"), &EditorVCSInterface::_get_initialization_settings_panel_container);
	ClassDB::bind_method(D_METHOD("_get_commit_dock_panel_container"), &EditorVCSInterface::_get_commit_dock_panel_container);
}

bool EditorVCSInterface::_initialize(String p_project_root_path) {

	WARN_PRINT("Selected VCS addon does not implement an initialization function. This warning will be suppressed.")
	return true;
}

bool EditorVCSInterface::_get_is_vcs_intialized() {

	return false;
}

Variant EditorVCSInterface::_get_commit_dock_panel_container() {

	return NULL;
}

bool EditorVCSInterface::_shut_down() {

	return false;
}

String EditorVCSInterface::_get_project_name() {

	return String();
}

String EditorVCSInterface::_get_vcs_name() {

	return String();
}

Variant EditorVCSInterface::_get_initialization_settings_panel_container() {

	return NULL;
}

bool EditorVCSInterface::initialize(String p_project_root_path) {

	return call("_initialize", p_project_root_path);
}

bool EditorVCSInterface::get_is_vcs_intialized() {

	return call("_get_is_vcs_intialized");
}

PanelContainer *EditorVCSInterface::get_initialization_settings_panel_container() {

	return Object::cast_to<PanelContainer>(call("_get_initialization_settings_panel_container"));
}

PanelContainer *EditorVCSInterface::get_commit_dock_panel_container() {

	return Object::cast_to<PanelContainer>(call("_get_commit_dock_panel_container"));
}

bool EditorVCSInterface::shut_down() {

	return call("_shut_down");
}

String EditorVCSInterface::get_project_name() {

	return call("_get_project_name");
}

String EditorVCSInterface::get_vcs_name() {

	return call("_get_vcs_name");
}

EditorVCSInterface::EditorVCSInterface() {
}

EditorVCSInterface::~EditorVCSInterface() {
}

EditorVCSInterface *EditorVCSInterface::get_singleton() {

	return singleton;
}

void EditorVCSInterface::set_singleton(EditorVCSInterface *p_singleton) {

	singleton = p_singleton;
}

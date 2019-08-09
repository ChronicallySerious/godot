#include "editor_vcs_interface.h"

EditorVCSInterface *EditorVCSInterface::singleton = NULL;

void EditorVCSInterface::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_initialize", "project_root_path"), &EditorVCSInterface::_initialize);
	ClassDB::bind_method(D_METHOD("_get_is_vcs_intialized"), &EditorVCSInterface::_get_is_vcs_intialized);
	ClassDB::bind_method(D_METHOD("_get_vcs_name"), &EditorVCSInterface::_get_vcs_name);
	ClassDB::bind_method(D_METHOD("_shut_down"), &EditorVCSInterface::_shut_down);
	ClassDB::bind_method(D_METHOD("_get_project_name"), &EditorVCSInterface::_get_project_name);
	ClassDB::bind_method(D_METHOD("_get_modified_files_data"), &EditorVCSInterface::_get_modified_files_data);
	ClassDB::bind_method(D_METHOD("_get_initialization_settings_panel_container"), &EditorVCSInterface::_get_initialization_settings_panel_container);
	ClassDB::bind_method(D_METHOD("_get_commit_dock_panel_container"), &EditorVCSInterface::_get_commit_dock_panel_container);
	ClassDB::bind_method(D_METHOD("_commit", "msg"), &EditorVCSInterface::_commit);
	ClassDB::bind_method(D_METHOD("_stage_all"), &EditorVCSInterface::_stage_all);
	ClassDB::bind_method(D_METHOD("_stage_file", "file_path"), &EditorVCSInterface::_stage_file);

	ClassDB::bind_method(D_METHOD("commit", "msg"), &EditorVCSInterface::commit);
	ClassDB::bind_method(D_METHOD("stage_all"), &EditorVCSInterface::stage_all);
}

bool EditorVCSInterface::_initialize(String p_project_root_path) {

	WARN_PRINT("Selected VCS addon does not implement an initialization function. This warning will be suppressed.")
	return true;
}

bool EditorVCSInterface::_get_is_vcs_intialized() {

	return false;
}

Dictionary EditorVCSInterface::_get_modified_files_data() {

	return Dictionary();
}

void EditorVCSInterface::_stage_all() {

	return;
}

void EditorVCSInterface::_stage_file(String p_file_path) {

	return;
}

void EditorVCSInterface::_commit(String p_msg) {

	return;
}

Control *EditorVCSInterface::_get_commit_dock_panel_container() {

	return NULL;
}

bool EditorVCSInterface::_shut_down() {

	return false;
}

String EditorVCSInterface::_get_project_name() {

	return String();
}

String EditorVCSInterface::_get_vcs_name() {

	return "";
}

Control *EditorVCSInterface::_get_initialization_settings_panel_container() {

	return NULL;
}

bool EditorVCSInterface::initialize(String p_project_root_path) {

	is_initialized = call("_initialize", p_project_root_path);
	return is_initialized;
}

bool EditorVCSInterface::get_is_vcs_intialized() {

	return call("_get_is_vcs_intialized");
}

Dictionary EditorVCSInterface::get_modified_files_data() {

	return call("_get_modified_files_data");
}

void EditorVCSInterface::stage_all() {

	if (check_addon_status())
	{
		call("_stage_all");
	}
	return;
}

void EditorVCSInterface::stage_file(String p_file_path) {

	if (check_addon_status())
	{
		call("_stage_file", p_file_path);
	}
	return;
}

bool EditorVCSInterface::check_addon_status() {

	return is_initialized;
}

void EditorVCSInterface::commit(String p_msg) {

	if (check_addon_status())
	{
		call("_commit", p_msg);
	}
	return;
}

PanelContainer *EditorVCSInterface::get_initialization_settings_panel_container() {

	return Object::cast_to<PanelContainer>(call("_get_initialization_settings_panel_container").operator Control *());
}

PanelContainer *EditorVCSInterface::get_commit_dock_panel_container() {

	Object *c = call("_get_commit_dock_panel_container").operator Object *();
	return Object::cast_to<PanelContainer>(c);
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

	is_initialized = false;
}

EditorVCSInterface::~EditorVCSInterface() {
}

EditorVCSInterface *EditorVCSInterface::get_singleton() {

	return singleton;
}

void EditorVCSInterface::set_singleton(EditorVCSInterface *p_singleton) {

	singleton = p_singleton;
}

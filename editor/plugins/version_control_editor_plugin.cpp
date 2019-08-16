#include "version_control_editor_plugin.h"
#include "core/script_language.h"
#include "editor/editor_file_system.h"
#include "editor/editor_node.h"

VersionControlEditorPlugin *VersionControlEditorPlugin::singleton = NULL;

void VersionControlEditorPlugin::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_selected_a_vcs"), &VersionControlEditorPlugin::_selected_a_vcs);
	ClassDB::bind_method(D_METHOD("_initialize_vcs"), &VersionControlEditorPlugin::_initialize_vcs);
	ClassDB::bind_method(D_METHOD("_send_commit_msg"), &VersionControlEditorPlugin::_send_commit_msg);
	ClassDB::bind_method(D_METHOD("_refresh_stage_area"), &VersionControlEditorPlugin::_refresh_stage_area);
	ClassDB::bind_method(D_METHOD("_stage_all"), &VersionControlEditorPlugin::_stage_all);
	ClassDB::bind_method(D_METHOD("_stage_selected"), &VersionControlEditorPlugin::_stage_selected);
	ClassDB::bind_method(D_METHOD("_view_file_diff"), &VersionControlEditorPlugin::_view_file_diff);
	ClassDB::bind_method(D_METHOD("_refresh_file_diff"), &VersionControlEditorPlugin::_refresh_file_diff);
	ClassDB::bind_method(D_METHOD("popup_vcs_set_up_dialog"), &VersionControlEditorPlugin::popup_vcs_set_up_dialog);

	// Used to track the status of files in the staging area
	BIND_ENUM_CONSTANT(CHANGE_TYPE_NEW);
	BIND_ENUM_CONSTANT(CHANGE_TYPE_MODIFIED);
	BIND_ENUM_CONSTANT(CHANGE_TYPE_RENAMED);
	BIND_ENUM_CONSTANT(CHANGE_TYPE_DELETED);
	BIND_ENUM_CONSTANT(CHANGE_TYPE_TYPECHANGE);
}

void VersionControlEditorPlugin::_selected_a_vcs(int p_id) {

	List<StringName> available_addons = get_available_vcs_names();
	const StringName selected_vcs = set_up_choice->get_item_text(p_id);

	if (available_addons.find(selected_vcs) != NULL) {

		set_up_init_button->set_disabled(false);
	} else {

		set_up_init_button->set_disabled(true);
	}
}

void VersionControlEditorPlugin::_populate_available_vcs_names() {

	static bool called = false;

	if (!called) {

		set_up_choice->add_item("Select an available VCS");

		fetch_available_vcs_addon_names();
		List<StringName> available_addons = get_available_vcs_names();
		for (int i = 0; i < available_addons.size(); i++) {

			set_up_choice->add_item(available_addons[i]);
		}

		called = true;
	}
}

VersionControlEditorPlugin *VersionControlEditorPlugin::get_singleton() {

	return singleton ? singleton : memnew(VersionControlEditorPlugin);
}

void VersionControlEditorPlugin::popup_vcs_set_up_dialog(const Control *p_gui_base) {

	Size2 popup_size = Size2(400, 100);
	Size2 window_size = p_gui_base->get_viewport_rect().size;
	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	if (get_is_vcs_intialized()) {

		set_up_init_button->set_disabled(true);
	}

	_populate_available_vcs_names();

	set_up_dialog->set_custom_minimum_size(Size2(400, 100));
	set_up_dialog->popup_centered_clamped(popup_size * EDSCALE);
}

void VersionControlEditorPlugin::_initialize_vcs() {

	if (vcs_interface) {

		ERR_EXPLAIN(vcs_interface->get_vcs_name() + " is already active");
		return;
	}

	int id = set_up_choice->get_selected_id();
	String selected_addon = set_up_choice->get_item_text(id);

	String path = ScriptServer::get_global_class_path(selected_addon);
	Ref<Script> script = ResourceLoader::load(path);
	if (!script.is_valid()) {

		ERR_EXPLAIN("VCS Addon path is invalid");
	}

	vcs_interface = memnew(EditorVCSInterface);
	ScriptInstance *addon_script_instance = script->instance_create(vcs_interface);
	if (!addon_script_instance) {

		ERR_FAIL_NULL(addon_script_instance);
		return;
	}

	// The addon is attached as a script to the VCS interface as a proxy end-point
	vcs_interface->set_script_and_instance(script.get_ref_ptr(), addon_script_instance);

	EditorVCSInterface::set_singleton(vcs_interface);
	EditorFileSystem::get_singleton()->connect("filesystem_changed", this, "_refresh_stage_area");

	String res_dir = OS::get_singleton()->get_resource_dir();
	if (!EditorVCSInterface::get_singleton()->initialize(res_dir)) {

		ERR_EXPLAIN("VCS was not initialized");
	}

	_refresh_stage_area();
}

void VersionControlEditorPlugin::_send_commit_msg() {

	String msg = commit_message->get_text();
	if (msg == "") {

		commit_status->set_text(TTR("No commit message was provided"));
		return;
	}

	if (EditorVCSInterface::get_singleton()) {

		if (staged_files_count == 0) {

			commit_status->set_text(TTR("No files added to stage"));
			return;
		}

		EditorVCSInterface::get_singleton()->commit(msg);

		commit_message->set_text("");
		version_control_dock_button->set_pressed(false);
	} else {

		WARN_PRINT("No VCS addon is initialized. Select a Version Control Addon from Project menu");
	}

	_refresh_stage_area();
	_clear_file_diff();
	_update_commit_status();
}

void VersionControlEditorPlugin::_refresh_stage_area() {

	if (EditorVCSInterface::get_singleton()) {

		clear_stage_area();
		commit_status->set_text("");
		TreeItem *root = stage_files->get_root();

		Dictionary modified_file_paths = EditorVCSInterface::get_singleton()->get_modified_files_data();
		String file_path;
		TreeItem *attach = NULL;
		for (int i = 0; i < modified_file_paths.size(); i++) {

			file_path = modified_file_paths.get_key_at_index(i);
			TreeItem *found = stage_files->search_item_text(file_path, 0, true);
			if (!found) {

				attach = root->get_children();
				switch ((int)modified_file_paths.get_value_at_index(i)) {

					case CHANGE_TYPE_NEW:        attach = attach; break;
					case CHANGE_TYPE_MODIFIED:   attach = attach->get_next(); break;
					case CHANGE_TYPE_RENAMED:    attach = attach->get_next()->get_next(); break;
					case CHANGE_TYPE_DELETED:    attach = attach->get_next()->get_next()->get_next(); break;
					case CHANGE_TYPE_TYPECHANGE: attach = attach->get_next()->get_next()->get_next()->get_next(); break;
					default: WARN_PRINT("Invalid file change type");
				}

				TreeItem *new_item = stage_files->create_item(attach);
				new_item->set_cell_mode(0, TreeItem::CELL_MODE_CHECK);
				new_item->set_text(0, file_path);
				new_item->set_checked(0, true);
				new_item->set_editable(0, true);
			} else {

				if (found->get_text(0) == diff_file_name->get_text()) {

					_refresh_file_diff();
				}
			}
			commit_status->set_text("New changes detected");
		}
	} else {

		WARN_PRINT("No VCS addon is initialized. Select a Version Control Addon from Project menu.")
	}
}

void VersionControlEditorPlugin::_stage_selected() {

	if (!vcs_interface) {

		WARN_PRINT("No VCS addon is initialized. Select a Version Control Addon from Project menu");
		return;
	}

	TreeItem *root = stage_files->get_root();
	if (root) {

		TreeItem *change_type = root->get_children();
		while (change_type) {

			TreeItem *file_entry = change_type->get_children();
			while (file_entry) {

				if (file_entry->is_checked(0)) {

					EditorVCSInterface::get_singleton()->stage_file(file_entry->get_text(0));
					file_entry->set_icon_color(0, EditorNode::get_singleton()->get_gui_base()->get_color("success_color", "Editor"));
					staged_files_count++;
				} else {

					EditorVCSInterface::get_singleton()->unstage_file(file_entry->get_text(0));
					file_entry->set_icon_color(0, EditorNode::get_singleton()->get_gui_base()->get_color("error_color", "Editor"));
					staged_files_count--;
				}

				file_entry = file_entry->get_next();
			}

			change_type = change_type->get_next();
		}
	}

	_update_stage_status();
}

void VersionControlEditorPlugin::_stage_all() {

	if (!vcs_interface) {

		WARN_PRINT("No VCS addon is initialized. Select a Version Control Addon from Project menu");
		return;
	}

	TreeItem *root = stage_files->get_root();
	if (root) {

		TreeItem *change_type = root->get_children();
		while (change_type) {

			TreeItem *file_entry = change_type->get_children();
			while (file_entry) {

				EditorVCSInterface::get_singleton()->stage_file(file_entry->get_text(0));
				file_entry->set_icon_color(0, EditorNode::get_singleton()->get_gui_base()->get_color("success_color", "Editor"));
				staged_files_count++;

				file_entry = file_entry->get_next();
			}

			change_type = change_type->get_next();
		}
	}

	_update_stage_status();
}

void VersionControlEditorPlugin::_view_file_diff() {

	version_control_dock_button->set_pressed(true);

	String file_path = stage_files->get_selected()->get_text(0);

	_display_file_diff(file_path);
}

void VersionControlEditorPlugin::_display_file_diff(String p_file_path) {

	Array diff_content = EditorVCSInterface::get_singleton()->get_file_diff(p_file_path);

	diff_file_name->set_text(p_file_path);

	diff->clear();
	diff->push_font(EditorNode::get_singleton()->get_gui_base()->get_font("source", "EditorFonts"));
	for (int i = 0; i < diff_content.size(); i++) {

		Dictionary line_result = diff_content[i];

		if (line_result["status"] == "+") {

			diff->push_color(EditorNode::get_singleton()->get_gui_base()->get_color("success_color", "Editor"));
		} else if (line_result["status"] == "-") {

			diff->push_color(EditorNode::get_singleton()->get_gui_base()->get_color("error_color", "Editor"));
		} else {

			diff->push_color(EditorNode::get_singleton()->get_gui_base()->get_color("font_color", "Label"));
		}

		diff->add_text((String)line_result["content"]);

		diff->pop();
	}
	diff->pop();
}

void VersionControlEditorPlugin::_refresh_file_diff() {

	String open_file = diff_file_name->get_text();
	if (open_file != "") {

		_display_file_diff(diff_file_name->get_text());
	}
}

void VersionControlEditorPlugin::_clear_file_diff() {

	diff->clear();
	diff_file_name->set_text("");
	
	version_control_dock_button->set_pressed(false);
}

void VersionControlEditorPlugin::_update_stage_status() {

	String status;
	if (staged_files_count == 1) {

		status = "Stage contains 1 file";
	} else {

		status = "Stage contains " + String::num_int64(staged_files_count) + " files";
	}
	commit_status->set_text(status);
}

void VersionControlEditorPlugin::_update_commit_status() {

	String status;
	if (staged_files_count == 1) {

		status = "Committed 1 file";
	} else {

		status = "Committed " + String::num_int64(staged_files_count) + " files ";
	}
	commit_status->set_text(status);
	staged_files_count = 0;
}

void VersionControlEditorPlugin::register_editor() {

	ToolButton *vc = EditorNode::get_singleton()->add_bottom_panel_item(TTR("Version Control"), version_control_dock);
	set_tool_button(vc);
}

void VersionControlEditorPlugin::fetch_available_vcs_addon_names() {

	ScriptServer::get_global_class_list(&available_addons);
}

void VersionControlEditorPlugin::clear_stage_area() {

	TreeItem *root = stage_files->get_root();

	TreeItem *category = root->get_children();
	while (category) {

		category->clear_children();

		category = category->get_next();
	}
}

const bool VersionControlEditorPlugin::get_is_vcs_intialized() const {

	return vcs_interface ? vcs_interface->get_is_vcs_intialized() : false;
}

const String VersionControlEditorPlugin::get_vcs_name() const {

	return vcs_interface ? vcs_interface->get_vcs_name() : "";
}

VersionControlEditorPlugin::VersionControlEditorPlugin() {

	singleton = this;
	vcs_interface = NULL;
	staged_files_count = 0;

	version_control_actions = memnew(PopupMenu);
	version_control_actions->set_v_size_flags(BoxContainer::SIZE_SHRINK_CENTER);

	set_up_dialog = memnew(AcceptDialog);
	set_up_dialog->set_title(TTR("Set Up Version Control"));
	set_up_dialog->set_custom_minimum_size(Size2(400, 100));
	version_control_actions->add_child(set_up_dialog);

	set_up_ok_button = set_up_dialog->get_ok();
	set_up_ok_button->set_disabled(false);
	set_up_ok_button->set_text(TTR("Close"));

	set_up_vbc = memnew(VBoxContainer);
	set_up_vbc->set_alignment(VBoxContainer::ALIGN_CENTER);
	set_up_dialog->add_child(set_up_vbc);

	set_up_hbc = memnew(HBoxContainer);
	set_up_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_vbc->add_child(set_up_hbc);

	set_up_vcs_status = memnew(RichTextLabel);
	set_up_vcs_status->set_text(TTR("VCS Addon not initialized"));
	set_up_vbc->add_child(set_up_vcs_status);

	set_up_vcs_label = memnew(Label);
	set_up_vcs_label->set_text(TTR("Version Control System"));
	set_up_hbc->add_child(set_up_vcs_label);

	set_up_choice = memnew(OptionButton);
	set_up_choice->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_choice->connect("item_selected", this, "_selected_a_vcs");
	set_up_hbc->add_child(set_up_choice);

	set_up_init_settings = NULL;

	set_up_init_button = memnew(Button);
	set_up_init_button->set_disabled(true);
	set_up_init_button->set_text(TTR("Initialize"));
	set_up_init_button->connect("pressed", this, "_initialize_vcs");
	set_up_vbc->add_child(set_up_init_button);

	version_control_actions->set_v_size_flags(PopupMenu::SIZE_EXPAND_FILL);
	version_control_actions->set_h_size_flags(PopupMenu::SIZE_EXPAND_FILL);

	version_commit_dock = memnew(VBoxContainer);
	version_commit_dock->set_visible(false);

	commit_box_vbc = memnew(VBoxContainer);
	version_commit_dock->add_child(commit_box_vbc);

	stage_tools = memnew(HSplitContainer);
	stage_tools->set_dragger_visibility(SplitContainer::DRAGGER_HIDDEN_COLLAPSED);
	commit_box_vbc->add_child(stage_tools);

	staging_area_label = memnew(Label);
	staging_area_label->set_h_size_flags(Label::SIZE_EXPAND_FILL);
	staging_area_label->set_text(TTR("Staging area"));
	stage_tools->add_child(staging_area_label);

	refresh_button = memnew(Button);
	refresh_button->set_tooltip(TTR("Detect new changes"));
	refresh_button->set_text(TTR("Refresh"));
	refresh_button->set_icon(EditorNode::get_singleton()->get_gui_base()->get_icon("Reload", "EditorIcons"));
	refresh_button->connect("pressed", this, "_refresh_stage_area");
	stage_tools->add_child(refresh_button);

	staging_area = memnew(VBoxContainer);
	staging_area->set_custom_minimum_size(Size2(100, 300));
	staging_area->set_v_size_flags(VBoxContainer::SIZE_EXPAND_FILL);
	version_commit_dock->add_child(staging_area, true);

	stage_files = memnew(Tree);
	stage_files->set_custom_minimum_size(Size2(100, 300));
	stage_files->set_columns(1);
	stage_files->set_column_title(0, TTR("Changes"));
	stage_files->set_column_titles_visible(true);
	stage_files->set_allow_reselect(true);
	stage_files->set_allow_rmb_select(true);
	stage_files->set_select_mode(Tree::SelectMode::SELECT_MULTI);
	stage_files->set_edit_checkbox_cell_only_when_checkbox_is_pressed(true);
	stage_files->connect("cell_selected", this, "_view_file_diff");
	commit_box_vbc->add_child(stage_files);

	change_type_as_strings[CHANGE_TYPE_NEW] = TTR("New");
	change_type_as_strings[CHANGE_TYPE_MODIFIED] = TTR("Modified");
	change_type_as_strings[CHANGE_TYPE_RENAMED] = TTR("Renamed");
	change_type_as_strings[CHANGE_TYPE_DELETED] = TTR("Deleted");
	change_type_as_strings[CHANGE_TYPE_TYPECHANGE] = TTR("Typechange");

	TreeItem *root = stage_files->create_item();
	stage_files->set_hide_root(true);

	new_files = stage_files->create_item();
	new_files->set_selectable(0, false);
	new_files->set_text(0, change_type_as_strings[CHANGE_TYPE_NEW]);

	modified_files = stage_files->create_item(root);
	modified_files->set_selectable(0, false);
	modified_files->set_text(0, change_type_as_strings[CHANGE_TYPE_MODIFIED]);

	renamed_files = stage_files->create_item(root);
	renamed_files->set_selectable(0, false);
	renamed_files->set_text(0, change_type_as_strings[CHANGE_TYPE_RENAMED]);

	deleted_files = stage_files->create_item(root);
	deleted_files->set_selectable(0, false);
	deleted_files->set_text(0, change_type_as_strings[CHANGE_TYPE_DELETED]);

	typechange_files = stage_files->create_item(root);
	typechange_files->set_selectable(0, false);
	typechange_files->set_text(0, change_type_as_strings[CHANGE_TYPE_TYPECHANGE]);

	stage_buttons = memnew(HSplitContainer);
	stage_buttons->set_dragger_visibility(SplitContainer::DRAGGER_HIDDEN_COLLAPSED);
	commit_box_vbc->add_child(stage_buttons);

	stage_selected_button = memnew(Button);
	stage_selected_button->set_h_size_flags(Button::SIZE_EXPAND_FILL);
	stage_selected_button->set_text(TTR("Stage Selected"));
	stage_selected_button->connect("pressed", this, "_stage_selected");
	stage_buttons->add_child(stage_selected_button);

	stage_all_button = memnew(Button);
	stage_all_button->set_text(TTR("Stage All"));
	stage_all_button->connect("pressed", this, "_stage_all");
	stage_buttons->add_child(stage_all_button);

	commit_box_vbc->add_child(memnew(HSeparator));

	commit_message = memnew(TextEdit);
	commit_message->set_h_grow_direction(Control::GrowDirection::GROW_DIRECTION_BEGIN);
	commit_message->set_v_grow_direction(Control::GrowDirection::GROW_DIRECTION_END);
	commit_message->set_text(TTR("Add a commit message"));
	commit_message->set_custom_minimum_size(Size2(100, 70));
	commit_message->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	commit_box_vbc->add_child(commit_message);

	commit_button = memnew(Button);
	commit_button->set_text(TTR("Commit Changes"));
	commit_button->connect("pressed", this, "_send_commit_msg");
	commit_box_vbc->add_child(commit_button);

	commit_status = memnew(Label);
	commit_status->set_align(Label::ALIGN_CENTER);
	commit_box_vbc->add_child(commit_status);

	version_control_dock = memnew(PanelContainer);
	version_control_dock->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	version_control_dock->hide();

	diff_vbc = memnew(VBoxContainer);
	diff_vbc->set_custom_minimum_size(Size2(300, 250));
	diff_vbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	version_control_dock->add_child(diff_vbc);

	diff_hbc = memnew(HBoxContainer);
	diff_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	diff_vbc->add_child(diff_hbc);

	diff_heading = memnew(Label);
	diff_heading->set_text(TTR("Status"));
	diff_heading->set_tooltip(TTR("View file diffs before commiting them to the latest version"));
	diff_hbc->add_child(diff_heading);

	diff_file_name = memnew(Label);
	diff_file_name->set_text(TTR("No file diff is active"));
	diff_file_name->set_h_size_flags(Label::SIZE_EXPAND_FILL);
	diff_file_name->set_align(Label::ALIGN_RIGHT);
	diff_hbc->add_child(diff_file_name);

	diff_refresh_button = memnew(Button);
	diff_refresh_button->set_tooltip(TTR("Detect changes in file diff"));
	diff_refresh_button->set_icon(EditorNode::get_singleton()->get_gui_base()->get_icon("Reload", "EditorIcons"));
	diff_refresh_button->connect("pressed", this, "_refresh_file_diff");
	diff_hbc->add_child(diff_refresh_button);

	diff = memnew(RichTextLabel);
	diff->set_v_size_flags(TextEdit::SIZE_EXPAND_FILL);
	diff->set_selection_enabled(true);
	diff_vbc->add_child(diff);
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {

	memdelete(version_control_dock);
	memdelete(version_commit_dock);
	memdelete(version_control_actions);
}

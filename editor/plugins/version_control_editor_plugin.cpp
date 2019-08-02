#include "version_control_editor_plugin.h"
#include "core/script_language.h"
#include "editor/editor_node.h"

VersionControlEditorPlugin *VersionControlEditorPlugin::singleton = NULL;

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

		VersionControlEditorPlugin::get_singleton()->fetch_available_vcs_addon_names();
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

	Size2 popup_size = Size2(450, 300);
	Size2 window_size = p_gui_base->get_viewport_rect().size;
	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	if (get_is_vcs_intialized()) {

		set_up_init_button->set_disabled(true);
	}

	_populate_available_vcs_names();

	set_up_dialog->popup_centered_clamped(popup_size * EDSCALE);
}

void VersionControlEditorPlugin::_initialize_vcs() {

	int id = set_up_choice->get_selected_id();
	String selected_addon = set_up_choice->get_item_text(id);

	String path = ScriptServer::get_global_class_path(selected_addon);
	Ref<Script> script = ResourceLoader::load(path);
	if (!script.is_valid()) {

		ERR_EXPLAIN("VCS Addon path is invalid");
	}

	if (!vcs_interface) {

		vcs_interface = memnew(EditorVCSInterface);
	}
	ScriptInstance *addon_script_instance = script->instance_create(vcs_interface);
	if (!addon_script_instance) {

		ERR_FAIL_NULL(addon_script_instance);
		return;
	}

	// The addon is attached as a script to the VCS interface for a proxy architecture
	vcs_interface->set_script_and_instance(script.get_ref_ptr(), addon_script_instance);

	EditorVCSInterface::set_singleton(vcs_interface);

	String res_dir = OS::get_singleton()->get_resource_dir();
	if (!EditorVCSInterface::get_singleton()->initialize(res_dir)) {

		ERR_EXPLAIN("VCS was not initialized");
	}

	// Delete the already in use settings panel
	if (set_up_init_settings) {

		set_up_init_settings->queue_delete();
	}
	// Replace it with new one
	set_up_init_settings = EditorVCSInterface::get_singleton()->get_initialization_settings_panel_container();
	set_up_vbc->add_child(set_up_init_settings);
}
	
void VersionControlEditorPlugin::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_selected_a_vcs"), &VersionControlEditorPlugin::_selected_a_vcs);
	ClassDB::bind_method(D_METHOD("_initialize_vcs"), &VersionControlEditorPlugin::_initialize_vcs);

	ClassDB::bind_method(D_METHOD("popup_vcs_set_up_dialog"), &VersionControlEditorPlugin::popup_vcs_set_up_dialog);
}

void VersionControlEditorPlugin::register_editor() {

	ToolButton *vc = EditorNode::get_singleton()->add_bottom_panel_item(TTR("Version Control"), version_control_dock);
	set_tool_button(vc);
}

void VersionControlEditorPlugin::fetch_available_vcs_addon_names() {

	ScriptServer::get_global_class_list(&available_addons);
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

	version_control_actions = memnew(PopupMenu);
	version_control_actions->set_v_size_flags(BoxContainer::SIZE_SHRINK_CENTER);

	set_up_dialog = memnew(AcceptDialog);
	set_up_dialog->set_title(TTR("Set Up Version Control"));
	version_control_actions->add_child(set_up_dialog);

	set_up_ok_button = set_up_dialog->get_ok();
	set_up_ok_button->set_disabled(false);
	set_up_ok_button->set_text(TTR("Close"));

	set_up_vbc = memnew(VBoxContainer);
	set_up_dialog->add_child(set_up_vbc);

	set_up_hbc = memnew(HBoxContainer);
	set_up_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_vbc->add_child(set_up_hbc);

	set_up_vcs_label = memnew(Label);
	set_up_vcs_label->set_text(TTR("Version Control System"));
	set_up_hbc->add_child(set_up_vcs_label);

	set_up_choice = memnew(OptionButton);
	set_up_choice->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_choice->connect("item_selected", this, "_selected_a_vcs");
	set_up_hbc->add_child(set_up_choice);

	set_up_init_settings = memnew(PanelContainer);
	set_up_init_settings->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_vbc->add_child(set_up_init_settings);

	set_up_init_button = memnew(Button);
	set_up_init_button->set_disabled(true);
	set_up_init_button->set_text(TTR("Initialize"));
	set_up_init_button->connect("pressed", this, "_initialize_vcs");
	set_up_vbc->add_child(set_up_init_button);

	version_control_actions->set_v_size_flags(PopupMenu::SIZE_EXPAND_FILL);
	version_control_actions->set_h_size_flags(PopupMenu::SIZE_EXPAND_FILL);

	version_commit_dock = memnew(VBoxContainer);

	stage_button = memnew(Button);
	stage_button->set_text(TTR("Stage all"));
	version_commit_dock->add_child(stage_button);

	HSeparator *separator = memnew(HSeparator);
	version_commit_dock->add_child(separator);

	commit_box_vbc = memnew(VBoxContainer);
	version_commit_dock->add_child(commit_box_vbc);

	staging_area = memnew(ItemList);
	staging_area->set_allow_reselect(true);
	staging_area->set_same_column_width(true);
	staging_area->set_auto_height(true);
	commit_box_vbc->add_child(staging_area);

	commit_message = memnew(TextEdit);
	commit_message->set_h_grow_direction(Control::GrowDirection::GROW_DIRECTION_BEGIN);
	commit_message->set_v_grow_direction(Control::GrowDirection::GROW_DIRECTION_END);
	commit_message->set_text(TTR("Add a commit message"));
	commit_message->set_custom_minimum_size(Size2(100, 70));
	commit_message->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	commit_box_vbc->add_child(commit_message);

	commit_button = memnew(Button);
	commit_button->set_text(TTR("Commit"));
	commit_box_vbc->add_child(commit_button);

	version_control_dock = memnew(PanelContainer);
	version_control_dock->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	version_control_dock->hide();

	diff_viewer = memnew(HSplitContainer);
	version_control_dock->add_child(diff_viewer);

	left_pane = memnew(VBoxContainer);
	left_pane->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	diff_viewer->add_child(left_pane);

	left_pane_heading = memnew(Label);
	left_pane_heading->set_text("Last version");
	left_pane->add_child(left_pane_heading);

	left_diff = memnew(RichTextLabel);
	left_diff->set_v_size_flags(TextEdit::SIZE_EXPAND_FILL);
	left_pane->add_child(left_diff);

	right_pane = memnew(VBoxContainer);
	right_pane->set_alignment(BoxContainer::AlignMode::ALIGN_BEGIN);
	right_pane->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	diff_viewer->add_child(right_pane);

	right_pane_heading = memnew(Label);
	right_pane_heading->set_text("Modifications");
	right_pane->add_child(right_pane_heading);

	right_diff = memnew(RichTextLabel);
	right_diff->set_v_size_flags(TextEdit::SIZE_EXPAND_FILL);
	right_pane->add_child(right_diff);
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {

	memdelete(version_control_dock);
	memdelete(version_commit_dock);
	memdelete(version_control_actions);
}

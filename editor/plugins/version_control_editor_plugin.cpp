#include "version_control_editor_plugin.h"
#include "core/script_language.h"
#include "editor/editor_node.h"
#include "editor_vcs_interface.h"

VersionControlEditorPlugin *VersionControlEditorPlugin::singleton = NULL;

void VersionControlEditorPlugin::_selected_a_vcs(int p_id) {

	List<StringName> available_vcs_names = get_available_vcs_names();
	const StringName selected_vcs = set_up_choice->get_item_text(p_id);

	if (available_vcs_names.find(selected_vcs) != NULL) {

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
		List<StringName> available_vcs_names = get_available_vcs_names();
		for (int i = 0; i < available_vcs_names.size(); i++) {

			set_up_choice->add_item(available_vcs_names[i]);
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

	EditorVCSInterface *vcs_interface = memnew(EditorVCSInterface);
	ScriptInstance *addon_script_instance = script->instance_create(vcs_interface);
	if (!addon_script_instance) {

		ERR_FAIL_NULL(addon_script_instance);
		return;
	}

	// The addon is attached as a script to the VCS interface for a cleaner design
	vcs_interface->set_script_and_instance(script.get_ref_ptr(), addon_script_instance);

	EditorVCSInterface::set_singleton(vcs_interface);

	// Delete the already in use settings panel
	if (set_up_init_settings) {

		set_up_vbc->get_parent_control()->remove_child(set_up_init_settings);
		memdelete(set_up_init_settings);
	}
	// Replace it with new one
	set_up_init_settings = EditorVCSInterface::get_singleton()->get_initialization_settings_panel_container();
	set_up_vbc->add_child(set_up_init_settings);

	String res_dir = OS::get_singleton()->get_resource_dir();
	if (!vcs_interface->initialize(res_dir)) {

		ERR_EXPLAIN("VCS was not initialized");
	}
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

	ScriptServer::get_global_class_list(&available_vcs_names);
}

VersionControlEditorPlugin::VersionControlEditorPlugin() {

	singleton = this;

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

	set_up_init_settings = memnew(Control);
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

	commit_box = memnew(VBoxContainer);
	version_commit_dock->add_child(commit_box);

	stage = memnew(Button);
	stage->set_text(TTR("Stage files"));
	version_commit_dock->add_child(stage);

	commit_top_hbc = memnew(HBoxContainer);
	commit_top_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	version_commit_dock->add_child(commit_top_hbc);

	commit_message = memnew(TextEdit);
	commit_message->set_text(TTR("Commit messages can have multiple lines"));
	commit_message->set_custom_minimum_size(Size2(100, 70));
	commit_message->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	commit_box->add_child(commit_message);

	commit = memnew(Button);
	commit->set_text(TTR("Commit"));
	commit_box->add_child(commit);

	version_control_dock = memnew(PanelContainer);
	version_control_dock->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	version_control_dock->hide();
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {

	memdelete(version_control_actions);
	memdelete(version_control_dock);
}

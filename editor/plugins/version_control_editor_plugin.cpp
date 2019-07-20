#include "version_control_editor_plugin.h"
#include "editor/editor_node.h"

//temporary
#include "editor/plugins/vcs_addons/git/src/git_api.h"

VersionControlEditorPlugin *VersionControlEditorPlugin::singleton = NULL;

void EditorVersionControlActions::_selected_a_vcs(int p_id) {

	const Array &available_vcs_names = VersionControlEditorPlugin::get_singleton()->get_available_vcs_names();
	const String &selected_vcs = set_up_choice->get_item_text(p_id);

	if (available_vcs_names.find(selected_vcs) != -1) {

		set_up_ok_button->set_disabled(false);
	} else {

		set_up_ok_button->set_disabled(true);
	}
}

void EditorVersionControlActions::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_selected_a_vcs"), &EditorVersionControlActions::_selected_a_vcs);
	ClassDB::bind_method(D_METHOD("_initialise_vcs", "vcs_name"), &EditorVersionControlActions::_initialise_vcs);
	ClassDB::bind_method(D_METHOD("popup_vcs_set_up_dialog"), &EditorVersionControlActions::popup_vcs_set_up_dialog);
}

void EditorVersionControlActions::_append_names_to_list() {

	static bool called = false;

	if (!called) {

		set_up_choice->add_item("Select an available VCS");
		Array available_vcs_names = VersionControlEditorPlugin::get_singleton()->get_available_vcs_names();
		for (int i = 0; i < available_vcs_names.size(); i++) {

			set_up_choice->add_item(available_vcs_names[i]);
		}

		called = true;
	}
}

void EditorVersionControlActions::popup_vcs_set_up_dialog(const Control *p_gui_base) {

	Size2 popup_size = Size2(450, 300);
	Size2 window_size = p_gui_base->get_viewport_rect().size;
	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	if (VersionControlEditorPlugin::get_singleton()->get_is_vcs_intialised()) {

		set_up_ok_button->set_disabled(true);
	}

	_append_names_to_list();

	set_up_dialog->popup_centered_clamped(popup_size * EDSCALE);
}

void EditorVersionControlActions::_initialise_vcs() {

	WARN_PRINT("nit");
	String res_dir = OS::get_singleton()->get_resource_dir();
	if (!EditorVCSInterface::get_singleton()->initialise(res_dir)) {
		WARN_PRINT("VCS is not initialised");
	}
}

EditorVersionControlActions::EditorVersionControlActions() {

	set_up_dialog = memnew(AcceptDialog);
	set_up_dialog->set_title(TTR("Set Up Version Control"));
	set_v_size_flags(BoxContainer::SIZE_SHRINK_CENTER);
	add_child(set_up_dialog);

	set_up_ok_button = set_up_dialog->get_ok();
	set_up_ok_button->set_disabled(true);
	set_up_ok_button->set_text(TTR("Initialize Version Control"));

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
}

EditorVersionCommitDock::EditorVersionCommitDock() {

	set_v_size_flags(SIZE_EXPAND_FILL);
	set_h_size_flags(SIZE_EXPAND_FILL);

	commit_box = memnew(VBoxContainer);
	add_child(commit_box);

	stage = memnew(Button);
	stage->set_text(TTR("Stage files"));
	add_child(stage);

	commit_top_hbc = memnew(HBoxContainer);
	commit_top_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	add_child(commit_top_hbc);

	commit_message = memnew(TextEdit);
	commit_message->set_text(TTR("Commit messages can have multiple lines"));
	commit_message->set_custom_minimum_size(Size2(100, 70));
	commit_message->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	commit_box->add_child(commit_message);

	commit = memnew(Button);
	commit->set_text(TTR("Commit"));
	commit_box->add_child(commit);
}

EditorVersionControlActions::~EditorVersionControlActions() {
}

void EditorVersionControlDock::_bind_methods() {
}

EditorVersionControlDock::EditorVersionControlDock() {
}

EditorVersionControlDock::~EditorVersionControlDock() {
}
	
void VersionControlEditorPlugin::_bind_methods() {
}

void VersionControlEditorPlugin::register_editor() {

	ToolButton *vc = EditorNode::get_singleton()->add_bottom_panel_item(TTR("Version Control"), version_control_dock);
	version_control_dock->set_tool_button(vc);
}

bool VersionControlEditorPlugin::register_as_available_vcs(const String &p_vcs_name) {

	if (available_vcs_names.find(p_vcs_name) == -1) {

		available_vcs_names.push_back(p_vcs_name);
		return true;
	}
	
	return false;
}

VersionControlEditorPlugin::VersionControlEditorPlugin(EditorNode *p_node) {

	singleton = this;
	editor_node = p_node;

	//temporary
	EditorVCSInterface::singleton = memnew(GitAPI);

	version_actions = memnew(EditorVersionControlActions);
	version_actions->set_up_dialog->get_ok()->connect("pressed", this, "_initialise_vcs");

	version_control_dock = memnew(EditorVersionControlDock);
	version_control_dock->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	version_control_dock->hide();
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {

	memdelete(version_actions);
	memdelete(version_control_dock);
	memdelete(EditorVCSInterface::singleton);
}

EditorVersionCommitDock::~EditorVersionCommitDock() {
}

#include "version_control_editor_plugin.h"
#include "editor/editor_node.h"

EditorVersionControlDock *EditorVersionControlDock::singleton = NULL;

VersionControlEditorPlugin *VersionControlEditorPlugin::singleton = NULL;

void EditorVersionControlActions::_selected_a_vcs() {

	const Array &available_vcs = VersionControlEditorPlugin::get_singleton()->get_available_vcs();
	const String &selected_vcs = set_up_choice->get_text();

	if (available_vcs.find(selected_vcs) != -1) {

		set_up_ok_button->set_disabled(false);
	} else {

		set_up_ok_button->set_disabled(true);
	}
}

void EditorVersionControlActions::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_selected_a_vcs"), &EditorVersionControlActions::_selected_a_vcs);

	ClassDB::bind_method(D_METHOD("popup_vcs_set_up_dialog"), &EditorVersionControlActions::popup_vcs_set_up_dialog);
}

void EditorVersionControlActions::popup_vcs_set_up_dialog(const Control *p_gui_base) {

	Size2 popup_size = Size2(450, 300);
	Size2 window_size = p_gui_base->get_viewport_rect().size;
	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	if (VersionControlEditorPlugin::get_singleton()->get_is_vcs_intialised()) {

		set_up_ok_button->set_disabled(true);
	}

	Array available_vcs = VersionControlEditorPlugin::get_singleton()->get_available_vcs();
	for (int i = 0; i < available_vcs.size(); i++) {

		set_up_choice->add_item(available_vcs[i]);
	}

	set_up_dialog->popup_centered_clamped(popup_size * EDSCALE, 0.8);

}

EditorVersionControlActions::EditorVersionControlActions() {

	set_up_dialog = memnew(AcceptDialog);
	set_up_dialog->set_title(TTR("Set Up Version Control"));
	set_v_size_flags(BoxContainer::SIZE_SHRINK_CENTER);
	add_child(set_up_dialog);

	set_up_vbc = memnew(VBoxContainer);
	set_up_dialog->add_child(set_up_vbc);

	set_up_ok_button = set_up_dialog->get_ok();
	set_up_ok_button->set_disabled(true);
	set_up_ok_button->set_text(TTR("Initialize Version Control"));
	set_up_ok_button->connect("pressed", this, "_initialize_vcs");

	set_up_hbc = memnew(HBoxContainer);
	set_up_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_vbc->add_child(set_up_hbc);

	set_up_vcs_label = memnew(Label);
	set_up_vcs_label->set_text(TTR("Version Control System"));
	set_up_hbc->add_child(set_up_vcs_label);

	set_up_choice = memnew(OptionButton);
	set_up_choice->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	set_up_choice->set_text(TTR("Select an available VCS"));
	set_up_choice->connect("pressed", this, "_selected_a_vcs");
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

EditorVersionControlDock *EditorVersionControlDock::register_editor() {

	singleton = this;
	ToolButton *vc = EditorNode::get_singleton()->add_bottom_panel_item(TTR("Version Control"), singleton);
	singleton->set_tool_button(vc);

	return singleton;
}

EditorVersionControlDock::EditorVersionControlDock() {
}

EditorVersionControlDock::~EditorVersionControlDock() {
}

void VersionControlEditorPlugin::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_initialize_vcs"), &VersionControlEditorPlugin::_initialize_vcs);
}

bool VersionControlEditorPlugin::register_vcs(const String &p_vcs_name) {

	if (available_vcs.find(p_vcs_name) != -1) {

		available_vcs.append(p_vcs_name);
		return true;
	}
	return false;
}

void VersionControlEditorPlugin::_initialize_vcs(const String &p_vcs_name) {

	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);
	vcs_name = p_vcs_name;
}

VersionControlEditorPlugin::VersionControlEditorPlugin(EditorNode *p_node) {

	singleton = this;
	editor_node = p_node;

	vcs_actions = memnew(EditorVersionControlActions);

	vcs_dock = memnew(EditorVersionControlDock);
	vcs_dock->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	vcs_dock->hide();
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {

	memdelete(vcs_actions);
	memdelete(vcs_dock);
}

EditorVersionCommitDock::~EditorVersionCommitDock() {
}

#include "version_control_editor_plugin.h"
#include "editor/editor_node.h"

EditorVersionControlDock *EditorVersionControlDock::singleton = NULL;

VersionControlEditorPlugin *VersionControlEditorPlugin::singleton = NULL;

void EditorVersionControlActions::_selected_a_vcs() {

	const Array &available_vcs = VersionControlEditorPlugin::get_singleton()->get_available_vcs();
	const String &selected_vcs = vcs_choice_drop_down->get_text();

	if (available_vcs.find(selected_vcs) != -1) {

		ok_button->set_disabled(false);
	} else {

		ok_button->set_disabled(true);
	}
}

void EditorVersionControlActions::_bind_methods() {

	ClassDB::bind_method(D_METHOD("_selected_a_vcs"), &EditorVersionControlActions::_selected_a_vcs);

	ClassDB::bind_method(D_METHOD("popup_vcs_set_up_dialog"), &EditorVersionControlActions::popup_vcs_set_up_dialog);
}

void EditorVersionControlActions::popup_vcs_set_up_dialog(Control *p_gui_base) {

	Size2 popup_size = Size2(450, 300);
	Size2 window_size = p_gui_base->get_viewport_rect().size;
	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	VersionControlEditorPlugin::get_singleton()->set_vcs_name(EditorSettings::get_singleton()->get_project_metadata("vcs", "name", ""));

	bool is_vcs_initialized = VersionControlEditorPlugin::get_singleton()->get_is_vcs_intialised();

	if (is_vcs_initialized) {
		ok_button->set_disabled(true);
	}

	popup_centered(popup_size);
}

EditorVersionControlActions::EditorVersionControlActions() {
	
	set_title(TTR("Set Up Version Control"));
	set_v_size_flags(BoxContainer::SIZE_SHRINK_CENTER);

	vcs_set_up_vbc = memnew(VBoxContainer);
	add_child(vcs_set_up_vbc);

	ok_button = get_ok();
	ok_button->set_disabled(true);
	ok_button->connect("pressed", this, "_initialize_vcs");
	vcs_set_up_vbc->add_child(ok_button);

	vcs_set_up_hbc = memnew(HBoxContainer);
	vcs_set_up_hbc->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	vcs_set_up_vbc->add_child(vcs_set_up_hbc);
	
	vcs_name_label = memnew(Label);
	vcs_name_label->set_text(TTR("Version Control System"));
	vcs_set_up_hbc->add_child(vcs_name_label);

	vcs_choice_drop_down = memnew(OptionButton);
	vcs_choice_drop_down->set_h_size_flags(HBoxContainer::SIZE_EXPAND_FILL);
	vcs_choice_drop_down->set_text(TTR("Select an available VCS"));
	const Array &available_vcs = VersionControlEditorPlugin::get_singleton()->get_available_vcs();
	for (int i = 0; i < available_vcs.size(); i++) {
		vcs_choice_drop_down->add_item(available_vcs[i]);
	}
	vcs_choice_drop_down->connect("pressed", this, "_selected_a_vcs");
	vcs_set_up_hbc->add_child(vcs_choice_drop_down);
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

bool VersionControlEditorPlugin::register_vcs(String p_vcs_name) {

	if (available_vcs.find(p_vcs_name) != -1) {

		available_vcs.append(p_vcs_name);
		return true;
	}
	return false;
}

void VersionControlEditorPlugin::_initialize_vcs(String p_vcs_name) {

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

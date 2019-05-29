#include "editor_version_control.h"
#include "editor/editor_node.h"

EditorVersionControl *EditorVersionControl::register_editor() {

	EditorVersionControl *version_control = memnew(EditorVersionControl);
	EditorNode::get_singleton()->add_bottom_panel_item(TTR("Version Control"), version_control);
	return version_control;
}

void EditorVersionControl::open_layout() {

	EditorNode::get_singleton()->make_bottom_panel_item_visible(this);

	EditorNode::get_singleton()->get_undo_redo()->clear_history();
	call_deferred("_select_layout");
}

EditorVersionControl::EditorVersionControl() {

	main_hbc = memnew(HBoxContainer);
	add_child(main_hbc);

	toolbox = memnew(VBoxContainer);
	main_hbc->add_child(toolbox);

	changes = memnew(VBoxContainer);
	main_hbc->add_child(changes);
}

EditorVersionControl::~EditorVersionControl() {
}

VersionControlEditorPlugin::VersionControlEditorPlugin(EditorVersionControl *p_node) {
	version_control_container = p_node;
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {
}

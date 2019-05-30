#include "version_control_editor_plugin.h"
#include "editor/editor_node.h"

VersionControl *VersionControl::version_control = NULL;

void VersionControl::_bind_methods() {
}

VersionControl *VersionControl::register_editor() {

	version_control = memnew(VersionControl);
	ToolButton *vc = EditorNode::get_singleton()->add_bottom_panel_item(TTR("Version Control"), version_control);
	version_control->set_tool_button(vc);

	return version_control;
}

void VersionControl::set_tool_button(ToolButton * p_button) {

	tool_button = p_button;
}

VersionControl::VersionControl() {
}

VersionControl::~VersionControl() {
}

VersionControlEditorPlugin::VersionControlEditorPlugin(EditorNode *p_node) {

	editor_node = p_node;
	VersionControl *version_control = VersionControl::get_singleton();

	version_control->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	version_control->hide();
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {
}

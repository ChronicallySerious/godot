#include "editor_version_control.h"

EditorVersionControl::EditorVersionControl() {
}

EditorVersionControl::~EditorVersionControl() {
}

VersionControlEditorPlugin::VersionControlEditorPlugin(EditorVersionControl *p_node) {
	version_control_container = p_node;
}

VersionControlEditorPlugin::~VersionControlEditorPlugin() {
}

#ifndef VERSION_CONTROL_EDITOR_PLUGIN_H
#define VERSION_CONTROL_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "scene/gui/container.h"

class VersionControl : public PanelContainer {

	GDCLASS(VersionControl, PanelContainer)

	static VersionControl *version_control;

	// ADD COMMIT DOCK CHILD CLASS AND MAKE A PANEL WITH IT

	ToolButton *tool_button;

protected:
	static void _bind_methods();

public:
	static VersionControl *get_singleton() { return version_control; }
	
	static VersionControl *register_editor();

	void set_tool_button(ToolButton *p_button);

	VersionControl();
	~VersionControl();
};

class VersionControlEditorPlugin : public EditorPlugin {

	GDCLASS(VersionControlEditorPlugin, EditorPlugin)

	EditorNode *editor_node;

public:
	
	VersionControlEditorPlugin(EditorNode *p_node);
	~VersionControlEditorPlugin();
};

#endif // VERSION_CONTROL_EDITOR_PLUGIN_H

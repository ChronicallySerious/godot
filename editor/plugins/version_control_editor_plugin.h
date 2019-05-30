#ifndef VERSION_CONTROL_EDITOR_PLUGIN_H
#define VERSION_CONTROL_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "scene/gui/container.h"

class VersionControl : public PanelContainer {

	GDCLASS(VersionControl, PanelContainer)

	static VersionControl *version_control;

protected:
	static void _bind_methods();

public:
	static VersionControl *get_singleton() { return version_control; }
	
	static VersionControl *register_editor();

	void open_layout();

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

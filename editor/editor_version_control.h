#ifndef EDITOR_VERSIONING_H
#define EDITOR_VERSIONING_H

#include "editor/editor_plugin.h"
#include "scene/gui/container.h"

class EditorVersionControl : public VBoxContainer {

	GDCLASS(EditorVersionControl, VBoxContainer)

	HBoxContainer *main_hbc;
	VBoxContainer *toolbox;
	VBoxContainer *changes;

public:
	static EditorVersionControl *register_editor();

	EditorVersionControl();
	~EditorVersionControl();
};

class VersionControlEditorPlugin : public EditorPlugin {

	GDCLASS(VersionControlEditorPlugin, EditorPlugin)

	EditorVersionControl *version_control_container;

public:
	VersionControlEditorPlugin(EditorVersionControl *p_node);
	~VersionControlEditorPlugin();
};

#endif

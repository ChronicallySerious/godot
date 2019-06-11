#ifndef VERSION_CONTROL_EDITOR_PLUGIN_H
#define VERSION_CONTROL_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "scene/gui/container.h"
#include "scene/gui/text_edit.h"

class EditorVersionControlActions : public PopupMenu {

	GDCLASS(EditorVersionControlActions, PopupMenu)

	AcceptDialog *set_up_dialog;
	VBoxContainer *set_up_vbc;
	HBoxContainer *set_up_hbc;
	Label *set_up_vcs_label;
	OptionButton *set_up_choice;
	Button *set_up_ok_button;

	void _selected_a_vcs();

protected:
	static void _bind_methods();

public:
	void popup_vcs_set_up_dialog(Control *p_gui_base);

	EditorVersionControlActions();
	~EditorVersionControlActions();
};

class EditorVersionCommitDock : public VBoxContainer {

	GDCLASS(EditorVersionCommitDock, VBoxContainer)

	Button *stage;
	VBoxContainer *commit_box;
	HBoxContainer *commit_top_hbc;
	TextEdit *commit_message;
	Button *commit;

public:
	EditorVersionCommitDock();
	~EditorVersionCommitDock();
};

class EditorVersionControlDock : public PanelContainer {

	GDCLASS(EditorVersionControlDock, PanelContainer)

protected:
	static EditorVersionControlDock *singleton;

	ToolButton *tool_button;

	static void _bind_methods();

public:
	EditorVersionControlDock *register_editor();

	static EditorVersionControlDock *get_singleton() { return singleton; }

	void set_tool_button(ToolButton *p_button) { tool_button = p_button; }

	EditorVersionControlDock();
	~EditorVersionControlDock();
};

class VersionControlEditorPlugin : public EditorPlugin {

	GDCLASS(VersionControlEditorPlugin, EditorPlugin)

	static VersionControlEditorPlugin *singleton;

	Array available_vcs;
	bool is_vcs_intialised;
	String vcs_name;

	EditorVersionControlActions *vcs_actions;
	EditorVersionControlDock *vcs_dock;

	EditorNode *editor_node;

	void _initialize_vcs(String p_vcs_name);

	static void _bind_methods();

public:
	static VersionControlEditorPlugin *get_singleton() { return singleton; }

	bool register_vcs(String p_vcs_name);

	const Array &get_available_vcs() { return available_vcs; }
	const bool &get_is_vcs_intialised() { return is_vcs_intialised; }
	const String &get_vcs_name() { return vcs_name; }

	EditorVersionControlActions *get_vcs_actions_panel() { return vcs_actions; }
	EditorVersionControlDock *get_vcs_dock() { return vcs_dock; }

	void set_vcs_name(String p_vcs_name) { vcs_name = p_vcs_name; }

	VersionControlEditorPlugin(EditorNode *p_node);
	~VersionControlEditorPlugin();
};

#endif // VERSION_CONTROL_EDITOR_PLUGIN_H

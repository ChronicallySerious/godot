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
	void popup_vcs_set_up_dialog(const Control *p_gui_base);

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

	Array available_vcs_names;
	String vcs_name;

	EditorVersionControlActions *version_actions;
	EditorVersionControlDock *version_control_dock;
	EditorVersionCommitDock *version_commit_dock;

	EditorNode *editor_node;

	void _initialize_vcs(const String &p_vcs_name);

	static void _bind_methods();

	friend class EditorVCSInterface;

public:
	static VersionControlEditorPlugin *get_singleton() { return singleton; }

	bool register_as_available_vcs(const String &p_vcs_name);

	const Array &get_available_vcs_names() const { return available_vcs_names; }
	const bool get_is_vcs_intialised() const { return vcs_name == "" ? false : true; }
	const String get_vcs_name() const { return vcs_name; }

	EditorVersionControlActions *get_version_control_actions_panel() const { return version_actions; }
	EditorVersionControlDock *get_version_control_dock() const { return version_control_dock; }
	EditorVersionCommitDock *get_version_commit_dock() const { return version_commit_dock; }

	void set_version_control_name(String p_vcs_name) { vcs_name = p_vcs_name; }

	VersionControlEditorPlugin(EditorNode *p_node);
	~VersionControlEditorPlugin();
};

#endif // !VERSION_CONTROL_EDITOR_PLUGIN_H

#ifndef VERSION_CONTROL_EDITOR_PLUGIN_H
#define VERSION_CONTROL_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "scene/gui/container.h"
#include "scene/gui/text_edit.h"

class VersionControlEditorPlugin : public EditorPlugin {

	GDCLASS(VersionControlEditorPlugin, EditorPlugin)

	static VersionControlEditorPlugin *singleton;

	List<StringName> available_vcs_names;
	String vcs_name;

	PopupMenu *version_control_actions;
	AcceptDialog *set_up_dialog;
	VBoxContainer *set_up_vbc;
	HBoxContainer *set_up_hbc;
	Label *set_up_vcs_label;
	OptionButton *set_up_choice;
	Control *set_up_init_settings;
	Button *set_up_init_button;
	Button *set_up_ok_button;

	void _populate_available_vcs_names();
	void _selected_a_vcs(int p_id);
	void _initialize_vcs();

	VBoxContainer *version_commit_dock;
	Button *stage;
	VBoxContainer *commit_box;
	HBoxContainer *commit_top_hbc;
	TextEdit *commit_message;
	Button *commit;

	PanelContainer *version_control_dock;
	ToolButton *tool_button;

	friend class EditorVCSInterface;
	friend class EditorVersionControlActions;

protected:
	static void _bind_methods();

public:
	static VersionControlEditorPlugin *get_singleton();

	void popup_vcs_set_up_dialog(const Control *p_gui_base);
	void set_tool_button(ToolButton *p_button) { tool_button = p_button; }

	PopupMenu *get_version_control_actions_panel() const { return version_control_actions; }
	VBoxContainer *get_version_commit_dock() const { return version_commit_dock; }
	PanelContainer *get_version_control_dock() const { return version_control_dock; }

	void register_editor();
	void fetch_available_vcs_addon_names();

	List<StringName> get_available_vcs_names() const { return available_vcs_names; }
	const bool get_is_vcs_intialized() const { return vcs_name == "" ? false : true; }
	const String get_vcs_name() const { return vcs_name; }

	void set_version_control_name(String p_vcs_name) { vcs_name = p_vcs_name; }

	VersionControlEditorPlugin();
	~VersionControlEditorPlugin();
};

#endif // !VERSION_CONTROL_EDITOR_PLUGIN_H

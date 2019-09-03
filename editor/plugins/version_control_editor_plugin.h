#ifndef VERSION_CONTROL_EDITOR_PLUGIN_H
#define VERSION_CONTROL_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "editor/editor_vcs_interface.h"
#include "scene/gui/container.h"
#include "scene/gui/text_edit.h"

class VersionControlEditorPlugin : public EditorPlugin {

	GDCLASS(VersionControlEditorPlugin, EditorPlugin)

	static VersionControlEditorPlugin *singleton;
	EditorVCSInterface *vcs_interface;

	List<StringName> available_addons;

	PopupMenu *version_control_actions;
	AcceptDialog *set_up_dialog;
	VBoxContainer *set_up_vbc;
	HBoxContainer *set_up_hbc;
	Label *set_up_vcs_label;
	OptionButton *set_up_choice;
	PanelContainer *set_up_init_settings;
	Button *set_up_init_button;
	Button *set_up_ok_button;

	void _populate_available_vcs_names();
	void _selected_a_vcs(int p_id);
	void _initialize_vcs();

	VBoxContainer *version_commit_dock;
	Button *stage_button;
	VBoxContainer *commit_box_vbc;
	ItemList *staging_area;
	TextEdit *commit_message;
	Button *commit_button;

	PanelContainer *version_control_dock;
	ToolButton *tool_button;
	HSplitContainer *diff_viewer;
	VBoxContainer *left_pane;
	Label *left_pane_heading;
	TextEdit *left_diff;
	VBoxContainer *right_pane;
	Label *right_pane_heading;
	TextEdit *right_diff;

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

	List<StringName> get_available_vcs_names() const { return available_addons; }
	const bool get_is_vcs_intialized() const;
	const String get_vcs_name() const;

	VersionControlEditorPlugin();
	~VersionControlEditorPlugin();
};

#endif // !VERSION_CONTROL_EDITOR_PLUGIN_H

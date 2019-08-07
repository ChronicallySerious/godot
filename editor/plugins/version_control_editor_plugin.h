#ifndef VERSION_CONTROL_EDITOR_PLUGIN_H
#define VERSION_CONTROL_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "editor/editor_vcs_interface.h"
#include "scene/gui/container.h"
#include "scene/gui/rich_text_label.h"
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
	RichTextLabel *set_up_vcs_status;
	Button *set_up_ok_button;

	VBoxContainer *version_commit_dock;
	VBoxContainer *commit_box_vbc;
	HSplitContainer *stage_tools;
	VBoxContainer *staging_area;
	Label *staging_area_label;
	HSplitContainer *stage_buttons;
	Button *stage_all_button;
	Button *stage_selected_button;
	Button *refresh_button;
	TextEdit *commit_message;
	Button *commit_button;

	PanelContainer *version_control_dock;
	ToolButton *tool_button;
	HSplitContainer *diff_viewer;
	VBoxContainer *left_pane;
	Label *left_pane_heading;
	RichTextLabel *left_diff;
	VBoxContainer *right_pane;
	Label *right_pane_heading;
	RichTextLabel *right_diff;

	void _populate_available_vcs_names();
	void _selected_a_vcs(int p_id);
	void _initialize_vcs();
	void _send_commit_msg();

	friend class EditorVCSInterface;

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

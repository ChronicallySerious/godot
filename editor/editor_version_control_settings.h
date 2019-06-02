#ifndef EDITOR_VERSION_CONTROL_SETTINGS_H
#define EDITOR_VERSION_CONTROL_SETTINGS_H

#include "core/array.h"
#include "editor/editor_data.h"
#include "editor/editor_vcs_api.h"
#include "scene/gui/dialogs.h"

class EditorVersionControlSettings : public VBoxContainer {

	GDCLASS(EditorVersionControlSettings, VBoxContainer);

	static Array available_vcs;
	static bool is_vcs_intialised;
	static String vcs_name;

	EditorData *data;

	AcceptDialog *vcs_init_dialog_holder;
	VBoxContainer *vcs_init_vbc;
	HBoxContainer *vcs_init_hbc;
	Label *vcs_name_label;
	OptionButton *vcs_choice_drop_down;
	Button *initialize_button;

	static void _bind_methods();
	static void _register_vcs_plugin(String p_vcs_name);

	void _initialize_vcs(String p_vcs_name);
	void _selected_a_vcs();

	friend class EditorVCSAPI;

public:
	void popup_vcs_initialization_settings(Control *p_gui_base);

	static String get_vcs_name() { return vcs_name; }
	static bool get_is_vcs_intialised() { return is_vcs_intialised; }

	static void set_vcs_name(String p_vcs_name) { vcs_name = p_vcs_name; }

	EditorVersionControlSettings(EditorData *p_data);
	~EditorVersionControlSettings();
};

#endif

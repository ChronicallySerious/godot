#ifndef VERSION_CONTROL_SETTINGS_EDITOR_H
#define VERSION_CONTROL_SETTINGS_EDITOR_H

#include "core/array.h"
#include "editor/editor_data.h"
#include "scene/gui/dialogs.h"
#include "editor/editor_vcs_api.h"

class VCSSettingsEditor : public AcceptDialog {
	GDCLASS(VCSSettingsEditor, AcceptDialog);

	String vcs_name;
	bool is_vcs_intialised;
	static Array available_vcs;
	EditorData *data;

	Label *vcs_name_label;
	OptionButton *vcs_choice_drop_down;
	Button *initialise_button;

	static void _bind_methods();
	static void register_vcs_plugin(String p_vcs_name);

	void _initialise_vcs(String p_vcs_name);
	void _selected_a_vcs();

	friend class EditorVCSAPI;

public:
	void popup_vcs_settings();

	String get_vcs_name() { return vcs_name; }

	VCSSettingsEditor(EditorData *p_data);
	~VCSSettingsEditor();
};

#endif

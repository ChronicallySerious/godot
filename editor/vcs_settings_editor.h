#ifndef VERSION_CONTROL_SETTINGS_EDITOR_H
#define VERSION_CONTROL_SETTINGS_EDITOR_H

#include "core/array.h"
#include "editor/editor_data.h"
#include "scene/gui/dialogs.h"

class VCSSettingsEditor : public AcceptDialog {
	GDCLASS(VCSSettingsEditor, AcceptDialog);

	String vcs_name;
	EditorData *data;

	OptionButton *label;

	static float scale;

	static void _initialise_vcs_plugin(String p_vcs_name);

	public:
	void popup_vcs_settings();

	float editor_get_scale();
	String get_vcs_name() { return vcs_name; }

	VCSSettingsEditor(EditorData *p_data);
	~VCSSettingsEditor();
};

#endif

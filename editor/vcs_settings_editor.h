#ifndef VERSION_CONTROL_SETTINGS_EDITOR_H
#define VERSION_CONTROL_SETTINGS_EDITOR_H

#include "core/array.h"
#include "scene/gui/dialogs.h"
#include "editor_settings.h"

class VCSSettingsEditor : public AcceptDialog {
	GDCLASS(VCSSettingsEditor, AcceptDialog);

	Array available_vcs_plugins_names;
	String selected_vcs;

	static void _initialise_vcs_plugin(String p_vcs_name);

	protected:
	static void _bind_methods();

	public:
	void popup_vcs_settings();

	String get_vcs_type() { return selected_vcs; }
};

#endif

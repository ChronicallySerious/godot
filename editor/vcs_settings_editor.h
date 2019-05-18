#ifndef VERSION_CONTROL_SETTINGS_EDITOR_H
#define VERSION_CONTROL_SETTINGS_EDITOR_H

#include "scene/gui/dialogs.h"
#include "editor_settings.h"

enum VCSName {
	Git
};

class VCSSettingsEditor : public AcceptDialog {

	GDCLASS(VCSSettingsEditor, AcceptDialog);

	VCSName current_vcs_name;

	void _vcs_select(VCSName p_vcs_name);

	protected:
	static void _bind_methods();

	public:
	void popup_vcs_settings();

	VCSName get_vcs_type() { return current_vcs_name; }
};

#endif

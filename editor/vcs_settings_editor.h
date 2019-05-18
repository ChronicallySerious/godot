#ifndef VERSION_CONTROL_SETTINGS_EDITOR_H
#define VERSION_CONTROL_SETTINGS_EDITOR_H

#include "scene/gui/dialogs.h"

class VCSSettingsEditor : public AcceptDialog {

	GDCLASS(VCSSettingsEditor, AcceptDialog);

	enum class VCSName {
		GIT
	};

	VCSName current_vcs_name;

	void _vcs_select(VCSName p_vcs_name);

	protected:
	static void _bind_methods();

	public:
	VCSName get_vcs_type() { return current_vcs_name; }
};

#endif

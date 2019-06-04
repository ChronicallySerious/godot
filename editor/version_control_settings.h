#ifndef VERSION_CONTROL_SETTINGS_H
#define VERSION_CONTROL_SETTINGS_H

#include "core/array.h"
#include "editor/editor_data.h"
#include "editor/editor_vcs_api.h"
#include "editor/plugins/version_control_editor_plugin.h"
#include "scene/gui/dialogs.h"

class VersionControlSettings : public VBoxContainer {

	GDCLASS(VersionControlSettings, VBoxContainer);

	static void _bind_methods();

	friend class EditorVCSAPI;

public:
	static String get_vcs_name() { return VersionControlEditorPlugin::get_singleton()->get_vcs_name(); }
	static Array get_available_vcs() { return VersionControlEditorPlugin::get_singleton()->get_available_vcs(); }
	static bool get_is_vcs_intialised() { return VersionControlEditorPlugin::get_singleton()->get_is_vcs_intialised(); }

	static void set_vcs_name(String p_vcs_name) { VersionControlEditorPlugin::get_singleton()->set_vcs_name(p_vcs_name); }

	VersionControlSettings(EditorData *p_data);
	~VersionControlSettings();
};

#endif // VERSION_CONTROL_SETTINGS_H

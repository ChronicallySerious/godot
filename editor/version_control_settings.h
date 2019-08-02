#ifndef VERSION_CONTROL_SETTINGS_H
#define VERSION_CONTROL_SETTINGS_H

#include "core/array.h"
#include "editor/editor_data.h"
#include "editor/editor_vcs_interface.h"
#include "editor/plugins/version_control_editor_plugin.h"
#include "scene/gui/dialogs.h"

class VersionControlSettings : public VBoxContainer {

	GDCLASS(VersionControlSettings, VBoxContainer);

	static void _bind_methods();

	friend class EditorVCSInterface;

public:
	static String get_vcs_name() { return VersionControlEditorPlugin::get_singleton()->get_vcs_name(); }
	static List<StringName> get_available_vcs_names() { return VersionControlEditorPlugin::get_singleton()->get_available_vcs_names(); }
	static bool get_is_vcs_intialized() { return VersionControlEditorPlugin::get_singleton()->get_is_vcs_intialized(); }

	VersionControlSettings(EditorData *p_data);
	~VersionControlSettings();
};

#endif // VERSION_CONTROL_SETTINGS_H

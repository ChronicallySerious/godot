#ifndef EDITOR_VCS_INTERFACE_H
#define EDITOR_VCS_INTERFACE_H

#include "core/ustring.h"
#include "core/object.h"
#include "scene/main/node.h"

class EditorVCSInterface : public Object {

protected:
	static Object *singleton;

	static void _bind_methods();

	friend class VersionControlEditorPlugin;


public:
	static Object *get_singleton();
	static void set_singleton(Object *p_singleton);

	// Exposing these functions to the editor for use, and for the GDNative addons to implement
	virtual bool initialize(String p_project_root_path);
	virtual Variant get_initialization_settings_panel_container();
	virtual Variant get_commit_dock_panel_container();
	virtual bool shut_down();
	virtual String get_project_name();
	virtual String get_vcs_name();

	EditorVCSInterface();
	virtual ~EditorVCSInterface();
};

#endif // !EDITOR_VCS_INTERFACE_H

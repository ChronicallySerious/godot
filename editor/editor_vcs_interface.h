#ifndef EDITOR_VCS_INTERFACE_H
#define EDITOR_VCS_INTERFACE_H

#include "core/ustring.h"
#include "core/object.h"
#include "scene/gui/panel_container.h"

class EditorVCSInterface : public Object {

	GDCLASS(EditorVCSInterface, Object)

protected:
	static EditorVCSInterface *singleton;

	static void _bind_methods();

	friend class VersionControlEditorPlugin;

	// Implemented by addons as end points for the proxy functions
	bool _initialize(String p_project_root_path);
	bool _get_is_vcs_intialized();
	Variant _get_initialization_settings_panel_container();
	Variant _get_commit_dock_panel_container();
	bool _shut_down();
	String _get_project_name();
	String _get_vcs_name();

public:
	static EditorVCSInterface *get_singleton();
	static void set_singleton(EditorVCSInterface *p_singleton);

	// Proxy functions to the editor for use
	virtual bool initialize(String p_project_root_path);
	virtual bool get_is_vcs_intialized();
	virtual PanelContainer *get_initialization_settings_panel_container();
	virtual PanelContainer *get_commit_dock_panel_container();
	virtual bool shut_down();
	virtual String get_project_name();
	virtual String get_vcs_name();

	EditorVCSInterface();
	virtual ~EditorVCSInterface();
};

#endif // !EDITOR_VCS_INTERFACE_H

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

	// Implemented by addons as end points for the proxy functions
	bool _initialize(String p_project_root_path);
	bool _get_is_vcs_intialized();
	Dictionary _get_untracked_files_data();
	void _stage_all();
	void _commit(String p_msg);
	Control *_get_initialization_settings_panel_container();
	Control *_get_commit_dock_panel_container();
	bool _shut_down();
	String _get_project_name();
	String _get_vcs_name();

public:
	static EditorVCSInterface *get_singleton();
	static void set_singleton(EditorVCSInterface *p_singleton);

	// Proxy functions to the editor for use
	bool initialize(String p_project_root_path);
	bool get_is_vcs_intialized();
	Dictionary get_untracked_files_data();
	void stage_all();
	void commit(String p_msg);
	PanelContainer *get_initialization_settings_panel_container();
	PanelContainer *get_commit_dock_panel_container();
	bool shut_down();
	String get_project_name();
	String get_vcs_name();

	EditorVCSInterface();
	virtual ~EditorVCSInterface();
};

#endif // !EDITOR_VCS_INTERFACE_H

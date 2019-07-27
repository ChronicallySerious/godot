#ifndef EDITOR_VCS_INTERFACE_H
#define EDITOR_VCS_INTERFACE_H

#include "core/ustring.h"
#include "core/object.h"
#include "scene/main/node.h"

class EditorVCSInterface : public Node {

	GDCLASS(EditorVCSInterface, Node)

protected:
	static Node *singleton;

	static void _bind_methods();

	friend class VersionControlEditorPlugin;

	EditorVCSInterface();
	virtual ~EditorVCSInterface();

public:
	static Node *get_singleton() { return singleton; }
	
	// Exposing these functions to the editor for use, and for the GDNative addons to implement
	virtual bool initialize(String p_project_root_path);
	virtual Control *get_initialization_settings_panel_container();
	virtual Control *get_commit_dock_panel_container();
	virtual bool shut_down();
	virtual void submit_vcs_addon(Node *p_addon);
	virtual String get_project_name();
	virtual String get_vcs_name();
};

#endif // !EDITOR_VCS_INTERFACE_H

#ifndef EDITOR_VCS_INTERFACE_H
#define EDITOR_VCS_INTERFACE_H

#include "core/ustring.h"
#include "core/object.h"
#include "editor/plugins/version_control_editor_plugin.h"

class EditorVCSInterface : public Object {

	GDCLASS(EditorVCSInterface, Object)

protected:
	static EditorVCSInterface *singleton;

	static void _bind_methods();

	friend class VersionControlEditorPlugin;

public:
	static EditorVCSInterface *get_singleton() { return singleton; }
	static bool register_vcs_addon(EditorVCSInterface * p_implementation, String p_vcs_name);

	void set_version_control_dock(Node *p_vcs_control_dock);
	void set_version_commit_dock(Node *p_vcs_commit_dock);
	void set_version_control_name(String p_vcs_name);

	// Exposed VCS access functions to editor
	virtual String get_vcs_name();
	
	EditorVCSInterface();
	virtual ~EditorVCSInterface();
};

#endif // !EDITOR_VCS_INTERFACE_H

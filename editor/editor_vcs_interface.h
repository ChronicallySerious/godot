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

	void supply_editor_requirements(Node *p_vcs_control_dock, Node *p_vcs_commit_dock, String p_vcs_name);

	// Exposed VCS access functions to editor
	virtual String get_vcs_name();
	
	EditorVCSInterface();
	virtual ~EditorVCSInterface();
};

#endif // !EDITOR_VCS_INTERFACE_H

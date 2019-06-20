#ifndef EDITOR_VCS_API_H
#define EDITOR_VCS_API_H

#include "core/ustring.h"
#include "core/object.h"
#include "editor/plugins/version_control_editor_plugin.h"

class EditorVCS {

	String vcs_name;

	EditorVersionControlActions *vcs_actions;
    EditorVersionControlDock *vcs_control_dock;
    EditorVersionCommitDock *vcs_commit_dock;

	static void _register_to_editor(const EditorVCS &p_vcs);

public:
	EditorVersionControlActions *get_actions_menu() const { return vcs_actions; }
	EditorVersionCommitDock *get_commit_dock() const { return vcs_commit_dock; }
	String get_vcs_name() const { return vcs_name; }

	void set_version_control_dock(EditorVersionCommitDock *p_vcs_dock);
	void set_vcs_commit_dock(EditorVersionCommitDock *p_vcs_commit_dock);

	EditorVCS(String p_vcs_name);
	virtual ~EditorVCS();

protected:

};

#endif

#ifndef EDITOR_VCS_API_H
#define EDITOR_VCS_API_H

#include "core/ustring.h"
#include "core/object.h"
#include "editor/plugins/version_control_editor_plugin.h"

class EditorVCS : public Object {

	GDCLASS(EditorVCS, Object)

	String vcs_name;

	EditorVersionControlActions *vcs_actions;
    EditorVersionControlDock *vcs_control_dock;
    EditorVersionCommitDock *vcs_commit_dock;

	static EditorVCS *vcs_singleton;

	static void _register_to_editor(const EditorVCS &p_singleton);

protected:
	static void _bind_methods();

public:
	static EditorVCS *get_singleton() { return vcs_singleton; }

	EditorVersionControlActions *get_actions_menu() const { return vcs_actions; }
	EditorVersionCommitDock *get_commit_dock() const { return vcs_commit_dock; }
	String get_vcs_name() const { return vcs_name; }

	void set_version_control_dock(EditorVersionControlDock *p_vcs_commit_dock) { vcs_control_dock = p_vcs_commit_dock; }
	void set_version_commit_dock(EditorVersionCommitDock *p_vcs_commit_dock) { vcs_commit_dock = p_vcs_commit_dock; }
	void set_version_control_name(String p_vcs_name) { vcs_name = p_vcs_name; }

	void replace_singleton(EditorVCS *p_vcs_singleton) { vcs_singleton = p_vcs_singleton; }

	EditorVCS();
	EditorVCS(String p_vcs_name);
	virtual ~EditorVCS();

};

#endif

#ifndef EDITOR_VCS_API_H
#define EDITOR_VCS_API_H

#include "core/ustring.h"
#include "core/object.h"

class EditorVCSAPI {

private:
	String vcs_name;

	static void register_to_editor(String vcs_name);

	String _get_vcs_name();
	String _get_commit_dock();

public:
	void get_commit_dock();
	String get_vcs_name();

	EditorVCSAPI(String p_vcs_name);
	virtual ~EditorVCSAPI();
};

#endif

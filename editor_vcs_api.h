#ifndef EDITOR_VCS_API_H
#define EDITOR_VCS_API_H

#include "core/ustring.h"
#include "core/object.h"

class EditorVCSAPI {

private:
	String vcs_name;

	String _get_vcs_name();
	String _display_commit_dock();

public:
	void display_commit_dock();
	void get_vcs_name();
};

#endif

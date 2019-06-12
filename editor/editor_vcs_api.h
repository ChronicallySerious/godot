#ifndef EDITOR_VCS_API_H
#define EDITOR_VCS_API_H

#include "core/ustring.h"
#include "core/object.h"

class EditorVCS {

private:
	String vcs_name;

	static void _register_to_editor(const String &vcs_name);

public:
	virtual void get_commit_dock() const = 0;
	virtual String get_vcs_name() const = 0;

	EditorVCS();
	virtual ~EditorVCS();
};

#endif

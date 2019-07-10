#ifndef GIT_API_H
#define GIT_API_H

#include "editor/editor_vcs_interface.h"

extern "C" {

#include "editor/plugins/vcs_addons/git/libgit2/include/git2.h"
}

class GitAPI : public EditorVCSInterface {

	GDCLASS(GitAPI, EditorVCSInterface)

protected:
	friend class EditorVersionControlPlugin;

public:
	String get_vcs_name() override;

	GitAPI();
	~GitAPI();
};

#endif // !GIT_API_H

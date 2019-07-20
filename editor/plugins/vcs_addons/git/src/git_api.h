#ifndef GIT_API_H
#define GIT_API_H

#include "editor/editor_vcs_interface.h"

#include "thirdparty/libgit2/include/git2.h"

#define GIT2_CALL(m_libgit2_function, m_fail_return) {     \
	int res = m_libgit2_function;           \
	if (res < 0) {                          \
		const git_error *e = giterr_last(); \
		WARN_PRINT(e->message);             \
        return m_fail_return;               \
    }                                       \
}

class GitAPI : public EditorVCSInterface {

	GDCLASS(GitAPI, EditorVCSInterface)

	git_repository *repo;
	git_revwalk *walker;

protected:
	friend class EditorVersionControlPlugin;

public:
	bool initialise(String p_git_path) override;
	bool shutdown() override;
	String get_project_name() override;
	String get_vcs_name() override;

	GitAPI();
	~GitAPI();
};

#endif // !GIT_API_H

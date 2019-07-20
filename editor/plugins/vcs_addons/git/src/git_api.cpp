#include "git_api.h"
#include "editor/editor_vcs_interface.h"

bool GitAPI::initialise(String p_git_path) {

	ERR_FAIL_COND_V(p_git_path == "", false);

	GIT2_CALL(git_repository_open(&repo, p_git_path.ascii()), false);
	GIT2_CALL(git_repository_init(&repo, p_git_path.ascii(), false), false);
	WARN_PRINT("intiialised");
	return true;
}

bool GitAPI::shutdown() {

	return git_libgit2_shutdown() == 0;
}

String GitAPI::get_project_name() {

	return String();
}

String GitAPI::get_vcs_name() {

	return "Git";
}

GitAPI::GitAPI() {

	EditorVCSInterface::singleton = this;
	repo = NULL;
	walker = NULL;

	VersionControlEditorPlugin::get_singleton()->register_as_available_vcs(get_vcs_name());

	if (git_libgit2_init() > 1) {

		WARN_PRINT("Multiple Git APIs are active");
	}
}

GitAPI::~GitAPI() {
}

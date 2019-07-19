#include "git_api.h"
#include "editor/editor_vcs_interface.h"

//temporary

String GitAPI::get_vcs_name() {

	return "Git";
}

GitAPI::GitAPI() {

	EditorVCSInterface::singleton = this;
	VersionControlEditorPlugin::get_singleton()->register_as_available_vcs(get_vcs_name());
	git_libgit2_init();
}

GitAPI::~GitAPI() {
}

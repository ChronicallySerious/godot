#include "vcs_addon_git_api.h"

String GitAPI::get_vcs_name() {

	return "Git";
}

GitAPI::GitAPI() {

	EditorVCSInterface::singleton = this;
	VersionControlEditorPlugin::get_singleton()->register_as_available_vcs(get_vcs_name());
}

GitAPI::~GitAPI() {
}

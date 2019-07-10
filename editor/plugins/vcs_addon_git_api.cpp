#include "vcs_addon_git_api.h"

String GitAPI::get_vcs_name() {

	return "Git";
}

GitAPI::GitAPI() {

	EditorVCSInterface::register_vcs_addon(this, get_vcs_name());
}

GitAPI::~GitAPI() {
}

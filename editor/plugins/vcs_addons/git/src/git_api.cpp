#include "git_api.h"
#include "editor/editor_vcs_interface.h"

bool GitAPI::initialize(String p_git_path) {

	ERR_FAIL_COND_V(p_git_path == "", false);

	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	opts.flags |= GIT_REPOSITORY_INIT_NO_REINIT;
	GIT2_CALL(git_repository_init_ext(&repo, p_git_path.ascii(), &opts), false);

	GIT2_CALL(git_repository_open(&repo, p_git_path.ascii()), false);

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

Node *GitAPI::get_init_settings() {

	return init_settings;
}

void GitAPI::_construct_init_ui() {

	init_settings = memnew(VBoxContainer);

	init_settings_hbc = memnew(HBoxContainer);
	init_settings_hbc->set_h_size_flags(VBoxContainer::SIZE_EXPAND);
	init_settings->add_child(init_settings_hbc);

	init_settings_git_ignore = memnew(CheckButton);
	init_settings_hbc->add_child(init_settings_git_ignore);
}

GitAPI::GitAPI() {

	EditorVCSInterface::singleton = this;
	repo = NULL;
	walker = NULL;

	_construct_init_ui();

	VersionControlEditorPlugin::get_singleton()->register_as_available_vcs(get_vcs_name());

	if (git_libgit2_init() > 1) {

		WARN_PRINT("Multiple Git APIs are active");
	}
}

GitAPI::~GitAPI() {

	memdelete(init_settings);
}

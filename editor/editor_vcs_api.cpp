#include "editor/editor_vcs_api.h"

void EditorVCS::_register_to_editor(const EditorVCS &p_singleton) {
}

void EditorVCS::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_version_control_dock"), &EditorVCS::set_version_control_dock);
	ClassDB::bind_method(D_METHOD("set_version_commit_dock"), &EditorVCS::set_version_commit_dock);
	ClassDB::bind_method(D_METHOD("set_version_control_name"), &EditorVCS::set_version_control_name);
	ClassDB::bind_method(D_METHOD("replace_singleton"), &EditorVCS::replace_singleton);
}

EditorVCS::EditorVCS() :
		vcs_name("") {
}

EditorVCS::EditorVCS(String p_vcs_name) :
		vcs_name(p_vcs_name) {
}

EditorVCS::~EditorVCS() {
}

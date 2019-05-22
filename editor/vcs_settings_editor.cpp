#include "editor_settings.h"
#include "vcs_settings_editor.h"

float VCSSettingsEditor::scale;

void VCSSettingsEditor::_initialise_vcs_plugin(String p_vcs_name) {

	EditorSettings::get_singleton()->set_project_metadata("vcs", "name", p_vcs_name);
	scale = 2.0f;
}

void VCSSettingsEditor::popup_vcs_settings() {

	Size2 popup_size = Size2(900, 700) * editor_get_scale();
	Size2 window_size = get_viewport_rect().size;

	popup_size.x = MIN(window_size.x * 0.5, popup_size.x);
	popup_size.y = MIN(window_size.y * 0.5, popup_size.y);

	popup_centered(popup_size);

	
}

float VCSSettingsEditor::editor_get_scale() {
	return scale;
}

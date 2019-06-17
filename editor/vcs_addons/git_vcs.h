#ifndef GIT_VCS_H
#define GIT_VCS_H

#include "editor/editor_vcs_api.h"
#include "editor/version_control_settings.h"

class GitVCS : public EditorVCS {
    
    GDCLASS(GitVCS, EditorVCS)
    
protected:
    static void _bind_methods();

public:
    void get_commit_dock() const override;
    void String get_vcs_name() const override;

    GitVCS();
    ~GitVCS();
}

#endif // GIT_VCS_H

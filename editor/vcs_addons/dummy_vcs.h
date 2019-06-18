#ifndef GIT_VCS_H
#define GIT_VCS_H

#include "editor/editor_vcs_api.h"
#include "editor/version_control_settings.h"

class DummyVCS : public EditorVCS {

    GDCLASS(DummyVCS, EditorVCS)

protected:
    static void _bind_methods();

public:
    void get_commit_dock() const override;
    void String get_vcs_name() const override;

    DummyVCS();
    ~DummyVCS();
}

#endif // GIT_VCS_H

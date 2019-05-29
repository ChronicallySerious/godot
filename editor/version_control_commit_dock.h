#ifndef VERSION_CONTROL_COMMIT_DOCK_H
#define VERSION_CONTROL_COMMIT_DOCK_H

#include "scene/gui/control.h"

class VersionControlCommitDock : public Control {

	GDCLASS(VersionControlCommitDock, Control)

protected:
	static void _bind_methods();

public:
	VersionControlCommitDock();
	~VersionControlCommitDock();
};

#endif // VERSION_CONTROL_COMMIT_DOCK_H

#include "steamVR.h"
#include <string>
#include <algorithm>

bool setActiveJSON(std::string relativeFilePath)
{
	vr::EVRInputError iError = vr::VRInputError_None;
	std::string fullManifestPath;
	bool retVal = true;

	//----
	// Gets the current exe path, strips the file name and
	// adds the relative file path
	//----
	char tPath[MAX_PATH];
	int bytes = GetModuleFileName(NULL, tPath, MAX_PATH);
	if (bytes == 0) {
		retVal = false;
	}
	else {
		std::string exePath(tPath);
		std::replace(exePath.begin(), exePath.end(), '\\', '/');
		int pos = exePath.rfind('/') + 1;
		if (pos > -1) {
			exePath.erase(pos);
			fullManifestPath = exePath + relativeFilePath;
			if (GetFileAttributes(fullManifestPath.c_str()) == INVALID_FILE_ATTRIBUTES) {
				retVal = false;
			}
		}
		else {
			retVal = false;
		}
	}

	if (retVal) {
		if (fullManifestPath.length() > 0) {
			iError = vr::VRInput()->SetActionManifestPath(fullManifestPath.c_str());
		}
	}
	return retVal;
}

bool setActionHandlesGame(inputController* input)
{
	vr::EVRInputError iError = vr::VRInputError_None;

	iError = vr::VRInput()->GetActionSetHandle("/actions/game", &input->game.setHandle);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/movement", &input->game.movement);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/rotate", &input->game.rotate);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/lefthand", &input->game.lefthand);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/lefthandpalm", &input->game.lefthandpalm);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/righthand", &input->game.righthand);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/righthandpalm", &input->game.righthandpalm);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/button_y", &input->game.button_y);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/button_x", &input->game.button_x);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/button_a", &input->game.button_a);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/button_b", &input->game.button_b);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/left_trigger", &input->game.left_trigger);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/left_bumper", &input->game.left_bumper);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/left_stick_click", &input->game.left_stick_click);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/left_anim", &input->game.left_anim);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/right_trigger", &input->game.right_trigger);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/right_bumper", &input->game.right_bumper);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/right_stick_click", &input->game.right_stick_click);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/right_anim", &input->game.right_anim);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/menu_start", &input->game.menu_start);
	iError = vr::VRInput()->GetActionHandle("/actions/game/in/menu_select", &input->game.menu_select);
	iError = vr::VRInput()->GetActionHandle("/actions/game/out/haptic_left", &input->game.haptic_left);
	iError = vr::VRInput()->GetActionHandle("/actions/game/out/haptic_right", &input->game.haptic_right);

	return true;
}

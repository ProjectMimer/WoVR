#pragma once
#pragma once

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <openvr.h>

struct inputActionGame
{
	vr::VRActionSetHandle_t setHandle;

	vr::VRActionHandle_t movement;
	vr::VRActionHandle_t rotate;
	vr::VRActionHandle_t lefthand;
	vr::VRActionHandle_t lefthandpalm;
	vr::VRActionHandle_t righthand;
	vr::VRActionHandle_t righthandpalm;
	vr::VRActionHandle_t button_y;
	vr::VRActionHandle_t button_x;
	vr::VRActionHandle_t button_a;
	vr::VRActionHandle_t button_b;
	vr::VRActionHandle_t left_trigger;
	vr::VRActionHandle_t left_bumper;
	vr::VRActionHandle_t left_stick_click;
	vr::VRActionHandle_t left_anim;
	vr::VRActionHandle_t right_trigger;
	vr::VRActionHandle_t right_bumper;
	vr::VRActionHandle_t right_stick_click;
	vr::VRActionHandle_t right_anim;
	vr::VRActionHandle_t menu_start;
	vr::VRActionHandle_t menu_select;
	vr::VRActionHandle_t haptic_left;
	vr::VRActionHandle_t haptic_right;
};


struct inputController
{
	struct inputActionGame game;
};


bool setActiveJSON(std::string relativeFilePath);
bool setActionHandlesGame(inputController* input);

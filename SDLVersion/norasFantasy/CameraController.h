#pragma once
#ifndef CAMERACONTROLLER // prevents from files being recompiled twice if they were added to multiple header files
#define CAMERACONTROLLER

#include "globals.h"
#include "entity.h"

using namespace std;

class CameraController
{
public:
	Entity* target = NULL;
	float lerp = 2.6f;

	void update();

	CameraController(); // added interpolation stuff

};
#endif


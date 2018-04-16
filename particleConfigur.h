#pragma once

#include "SFMLHeader.h"

struct ConfigueStruct
{
	ConfigueStruct(Vector2f pPos, int pChange = NO_CHANGE, int pStrategy = NO_S, float pA = 0, float pB = 0)
	{
		cPos = pPos;
		cChangeType = pChange;
		cStrategyType = pStrategy;
		cA = pA;
		cB = pB;
	}

	Vector2f cPos;
	int cChangeType;
	int cStrategyType;
	float cA;
	float cB;
};

const ConfigueStruct _ConfigueArray[17] = {
	ConfigueStruct(Vector2f(1200,750)),
	ConfigueStruct(Vector2f(1200,500)),ConfigueStruct(Vector2f(800,1000)),ConfigueStruct(Vector2f(1600,1000)),
	ConfigueStruct(Vector2f(800,750),CHANGE_V,LINEAR_S,2,200),ConfigueStruct(Vector2f(1600,750),CHANGE_V,LINEAR_S,200,-198),
	ConfigueStruct(Vector2f(800,750),CHANGE_S,LINEAR_S,1,3),ConfigueStruct(Vector2f(1600,750),CHANGE_S,LINEAR_S,4,-3),
	ConfigueStruct(Vector2f(1200,500),CHANGE_V,EASE_IN_S,2,200),ConfigueStruct(Vector2f(800,1000),CHANGE_V,EASE_OUT_S,200,-198),ConfigueStruct(Vector2f(1600,1000),CHANGE_V,SIN_S,2,200),
	ConfigueStruct(Vector2f(1200,500),CHANGE_S,EASE_IN_S,1,3),ConfigueStruct(Vector2f(800,1000),CHANGE_S,EASE_OUT_S,4,-3),ConfigueStruct(Vector2f(1600,1000),CHANGE_S,SIN_S,1,3),
	ConfigueStruct(Vector2f(1200,500),CHANGE_R,EASE_IN_S,0,1080),ConfigueStruct(Vector2f(800,1000),CHANGE_R,EASE_OUT_S,0,-1080),ConfigueStruct(Vector2f(1600,1000),CHANGE_R,SIN_S,0,1080),
};

const int _SceneStartIndex[SCENE_SIZE] = { 0,1,4,6,8,11,14 };
const int _SceneLength[SCENE_SIZE] = { 1,3,2,2,3,3,3 };

const string _SceneTip[SCENE_SIZE] = { "Simple Particle System", "Multiple Particle Systems",
"Velocity Linearly Grow / Shrink", "Size Linearly Grow / Shirnk",
"Easing In / Easing Out / Sin Curves to Control Velocity",
"Easing In / Easing Out / Sin Curves to Control Size",
"Easing In / Easing Out / Sin Curves to Control Rotation" };

const string _Scene_0_Tip = "Current Particle Number: ";
#pragma once
#include"Math.h"
class Camera2D;
class CameraBehavior {
public:
	virtual~CameraBehavior() = default;
	virtual void Update(Camera2D* camera) = 0;
};
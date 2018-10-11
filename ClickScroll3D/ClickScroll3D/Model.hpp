#pragma once
#include "Parameter.hpp"
#include "DxLib.h"
#include "Input.hpp"

class Model
{
private:
	int modelHandle;

	int mouseX, mouseY;
	int preMouseX, preMouseY;

	Vector2 modelUp, modelDown;
	VECTOR modelVecUp, modelVecDown;

	bool modelFlag;

	bool modelXMoveTouch;
	bool modelZMoveTouch;


public:
	Model(VECTOR t_modelVecUp, VECTOR t_modelVecDown);
	~Model();

	void Process(int t_mouseX, int t_mouseY);
	void Draw();

	void SelectCheck(int mouseX, int mouseY);
	void SetTouchFlase();
	bool GetModelFlag();
};


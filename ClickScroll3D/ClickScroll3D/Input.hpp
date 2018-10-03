#pragma once
#include "DxLib.h"

enum class CLICK { LEFT, RIGHT };

class MouseData
{
private:
	static int m_Mouse[3];
	static int MouseInput;

public:
	MouseData();
	~MouseData();

	static void Mouse_UpDate(); //�}�E�X�̃N���b�N�̏�Ԃ��X�V����
	static int GetClick(int MouseCode); //�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
};


class MouseWheelData
{
private:
	static int m_MouseWheel;
	static int old_MouseWheel;

public:
	MouseWheelData();
	~MouseWheelData();

	static void MouseWheel_Update(); //�}�E�X�̃z�C�[���̏�Ԃ��X�V
	static int GetMouseWheel(int MouseWheelCode); //�}�E�X�z�C�[���̏�Ԃ�Ԃ�
};
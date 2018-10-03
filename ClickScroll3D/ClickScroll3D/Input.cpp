#include "Input.hpp"


//////////////////////////////////////////////�}�E�X�֘A////////////////////////////////////////////////////

MouseData::MouseData()
{

}

MouseData::~MouseData()
{

}

int MouseData::m_Mouse[3];
int MouseData::MouseInput;

void MouseData::Mouse_UpDate()
{
	MouseInput = GetMouseInput();    //�}�E�X�̉�������Ԏ擾
	for (int i = 0; i < 3; i++)
	{
		if ((MouseInput & 1 << i) != 0)
		{
			m_Mouse[i]++;   //������Ă�����J�E���g�A�b�v
		}
		else
		{
			m_Mouse[i] = 0; //������ĂȂ�������0
		}
	}
}

int MouseData::GetClick(int MouseCode)
{
	return m_Mouse[MouseCode];
}

//////////////////////////////////////////////�}�E�X�z�C�[���֘A////////////////////////////////////////////////////
MouseWheelData::MouseWheelData()
{

}

MouseWheelData::~MouseWheelData()
{

}

int MouseWheelData::m_MouseWheel;
int MouseWheelData::old_MouseWheel;

void MouseWheelData::MouseWheel_Update()
{
	old_MouseWheel = m_MouseWheel;
	if (old_MouseWheel - m_MouseWheel > 0)
	{
		m_MouseWheel++;
	}
	else if (old_MouseWheel - m_MouseWheel < 0)
	{
		m_MouseWheel--;
	}
	else
	{
		m_MouseWheel = 0;
	}
}

int MouseWheelData::GetMouseWheel(int MouseWheelCode)
{
	return m_MouseWheel += MouseWheelCode;
}
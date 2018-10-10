#include "Camera.hpp"


// �R���X�g���N�^
Camera::Camera()
{
	cameraArea = VGet(0, 350, 0);

	circleArea = Vector2(0.0f, 100.0f);

	speed = DX_PI_F / 90;
	angle = 0.0f;

	SetCameraNearFar(10.0f, 10000.0f);	// �J�����̕`��͈͂��w��

	// �������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(cameraArea, VAdd(cameraArea, VGet(circleArea.x, 0.0f, circleArea.y)));
}

// �f�X�g���N�^
Camera::~Camera()
{
}

const VECTOR Camera::GetArea() const
{
	return cameraArea;
}


// ���C���v���Z�X
void Camera::Process(int mouseX, int mouseY)
{
	// �E�N���b�N�������Ă�����
	if (MouseData::GetClick(1) >= 1)
	{
		// ���ɉ�]��
		if (premouseX < mouseX)
		{
			double xd = circleArea.x * cos(DX_PI_F / 180) - circleArea.y * sin(DX_PI_F / 180);
			double yd = circleArea.x * sin(DX_PI_F / 180) + circleArea.y * cos(DX_PI_F / 180);
			circleArea.x = xd;
			circleArea.y = yd;
			angle += speed * 2;
		}
		// �E�ɉ�]��
		if (premouseX > mouseX)
		{
			double xd = circleArea.x * cos(-DX_PI_F / 180) - circleArea.y * sin(-DX_PI_F / 180);
			double yd = circleArea.x * sin(-DX_PI_F / 180) + circleArea.y * cos(-DX_PI_F / 180);
			circleArea.x = xd;
			circleArea.y = yd;
			angle -= speed * 2;
		}

		if (KeyData::Get(KEY_INPUT_A) >= 1)
		{
			cameraArea.x += cosf(-angle) * 5.0f;
			cameraArea.z += sinf(-angle) * 5.0f;
		}

		if (KeyData::Get(KEY_INPUT_D) >= 1)
		{
			cameraArea.x += cosf(-angle) * -5.0f;
			cameraArea.z += sinf(-angle) * -5.0f;
		}

		if (KeyData::Get(KEY_INPUT_W) >= 1)
		{
			cameraArea.x += sinf(angle) * -5.0f;
			cameraArea.z += cosf(angle) * -5.0f;
		}

		if (KeyData::Get(KEY_INPUT_S) >= 1)
		{
			cameraArea.x += sinf(angle) * 5.0f;
			cameraArea.z += cosf(angle) * 5.0f;
		}
	}


	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) >= 1)
	{
		cameraArea.x += sinf(angle) * -5.0f;
		cameraArea.z += cosf(angle) * -5.0f;
	}

	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) <= -1)
	{
		cameraArea.x += sinf(angle) * 5.0f;
		cameraArea.z += cosf(angle) * 5.0f;
	}
	

	premouseX = mouseX;
	premouseY = mouseY;

	DrawFormatString(0, 0, 255, "%f\t%f\t%f\n", cameraArea.x, cameraArea.y, cameraArea.z);

	SetCameraPositionAndTarget_UpVecY(cameraArea, VAdd(cameraArea, VGet(circleArea.x, 0.0f, circleArea.y)));
}


// ang�p��]����
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
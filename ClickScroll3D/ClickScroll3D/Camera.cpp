#include "Camera.hpp"


// �R���X�g���N�^
Camera::Camera()
{
	cameraArea = VGet(0, 350, 500);
	viewArea = VGet(0, 150, 0);

	speed = DX_PI_F / 90;

	SetCameraNearFar(100.0f, 10000.0f);	// �J�����̕`��͈͂��w��

	// �������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VAdd(cameraArea, VGet(0.0f, 0.0f, 0.0f)), VAdd(viewArea, VGet(0.0f, 0.0f, 0.0f)));
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
void Camera::Process()
{
	GetMousePoint(&mouseX, &mouseY);

	// ���ɉ�]��
	if (premouseX < mouseX)
	{
		RLrotate(speed, cameraArea);	// ��]����
	}
	// �E�ɉ�]��
	if (premouseX > mouseX)
	{
		RLrotate(-speed, cameraArea);	// ��]����
	}


	premouseX = mouseX;
	premouseY = mouseY;

	SetCameraPositionAndTarget_UpVecY(VAdd(cameraArea, VGet(0.0f, 0.0f, 0.0f)), VAdd(viewArea, VGet(0.0f, 0.0f, 0.0f)));
}


// ang�p��]����
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
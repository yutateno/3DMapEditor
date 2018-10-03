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
	// ���ɉ�]��
	if (CheckHitKey(KEY_INPUT_LEFT) >= 1)
	{
		RLrotate(speed, cameraArea);	// ��]����
	}
	// �E�ɉ�]��
	if (CheckHitKey(KEY_INPUT_RIGHT) >= 1)
	{
		RLrotate(-speed, cameraArea);	// ��]����
	}

	//// ��L�[��������Ă����牺���猩�グ��
	//if (KeyData::Get(KEY_INPUT_UP) >= 1
	//	|| InputPad::GetPadThumbData(controllNumber, STICK_RIGHT_Y) > 0)
	//{
	//	// ����
	//	if (TestPosition.y > 240)
	//	{
	//		TestPosition = VAdd(TestPosition, VScale(VNorm(TestPosition), -10));	// �P�ʃx�N�g�������ă}�C�i�X�����ē�������Ɍ��炷
	//	}
	//}

	//// ���L�[��������Ă�����ォ�猩���낷
	//if (KeyData::Get(KEY_INPUT_DOWN) >= 1
	//	|| ::InputPad::GetPadThumbData(controllNumber, STICK_RIGHT_Y) < 0)
	//{
	//	// ����
	//	if (TestPosition.y < 400)
	//	{
	//		TestPosition = VAdd(TestPosition, VScale(VNorm(TestPosition), 10));	// VScale����Ȃ�
	//	}
	//}

#ifdef _CAMERA_DEBG
	printfDx("%d\n", HitNum);
	//DrawCapsule3D(VAdd(cameraArea, charaArea), VAdd(viewArea, charaArea), 5.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// �ʔ���
	DrawCapsule3D(VAdd(cameraArea, charaArea), charaArea, 5.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// �����蔻����m�F�p�̕\���e�X�g
#endif // !_CAMERA_DEBG

}


// ang�p��]����
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
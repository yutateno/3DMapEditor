#pragma once
#include "DxLib.h"
#include <math.h>
#include "InputKey.hpp"


class Camera
{
private:
	VECTOR cameraArea;		// �J�����̈ʒu
	VECTOR viewArea;		// �����������


	int stageHandle;		// �����蔻��p�X�e�[�W


	float speed;					// ��]�X�s�[�h
	void RLrotate(const float speed, VECTOR& p_cameraArea);	// ��]���s���֐�


	int mouseX, mouseY, premouseX, premouseY;


public:
	Camera();				// �L�����̈ʒu�������Ɏ�����R���X�g���N�^
	~Camera();													// �f�X�g���N�^


	void Process();		// �L�����̈ʒu�������Ɏ�����v���Z�X


	const VECTOR GetArea() const;				// �L�����N�^�[�̃A���O��
};
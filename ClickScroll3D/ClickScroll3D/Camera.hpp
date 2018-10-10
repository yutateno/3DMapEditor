#pragma once
#include "DxLib.h"
#include <math.h>
#include "InputKey.hpp"
#include "Input.hpp"
#include "Parameter.hpp"


class Camera
{
private:
	VECTOR cameraArea;		// �J�����̈ʒu
	Vector2 circleArea;


	int stageHandle;		// �����蔻��p�X�e�[�W


	float speed;					// ��]�X�s�[�h
	void RLrotate(const float speed, VECTOR& p_cameraArea);	// ��]���s���֐�


	int premouseX, premouseY;

	float angle;


public:
	Camera();				// �L�����̈ʒu�������Ɏ�����R���X�g���N�^
	~Camera();													// �f�X�g���N�^


	void Process(int mouseX, int mouseY);		// �L�����̈ʒu�������Ɏ�����v���Z�X


	const VECTOR GetArea() const;				// �L�����N�^�[�̃A���O��
};
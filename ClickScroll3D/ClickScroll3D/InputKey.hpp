#pragma once
#include "DxLib.h"


class KeyData
{
private:
	static int key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
	static char tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����


public:
	KeyData() {};
	~KeyData() {};

	static void UpDate();			// �L�[���͂̏�ԍX�V
	static const int Get(const int KeyCode);	// �L�[���͏�Ԏ擾
	static bool CheckEnd();			// �����I��
};
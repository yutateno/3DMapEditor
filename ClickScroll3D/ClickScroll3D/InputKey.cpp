#include "InputKey.hpp"

int KeyData::key[256];
char KeyData::tmpKey[256];

void KeyData::UpDate()
{
	KeyData::tmpKey[256];			// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(KeyData::tmpKey);	// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++)
	{
		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;   // ���Z
		}
		// �L�[�������ꂽ�u��
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1; // -1�ɂ���
		}
		// ����ȊO
		else
		{
			KeyData::key[i] = 0; // 0�ɂ���
		}
	}
}

bool KeyData::CheckEnd()
{
	return { KeyData::key[KEY_INPUT_ESCAPE] <= 0 };
}

const int KeyData::Get(const int KeyCode)
{
	return KeyData::key[KeyCode];
}
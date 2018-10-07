#include "InputKey.hpp"

int KeyData::key[256];
char KeyData::tmpKey[256];

void KeyData::UpDate()
{
	KeyData::tmpKey[256];			// 現在のキーの入力状態を格納する
	GetHitKeyStateAll(KeyData::tmpKey);	// 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++)
	{
		// i番のキーコードに対応するキーが押されていたら
		if (KeyData::tmpKey[i] != 0)
		{
			KeyData::key[i]++;   // 加算
		}
		// キーが離された瞬間
		else if (KeyData::key[i] > 0)
		{
			KeyData::key[i] = -1; // -1にする
		}
		// それ以外
		else
		{
			KeyData::key[i] = 0; // 0にする
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
#pragma once
#include "DxLib.h"


class KeyData
{
private:
	static int key[256];		// キーの入力状態格納用変数
	static char tmpKey[256];	// 現在のキーの入力状態を格納する


public:
	KeyData() {};
	~KeyData() {};

	static void UpDate();			// キー入力の状態更新
	static const int Get(const int KeyCode);	// キー入力状態取得
	static bool CheckEnd();			// 強制終了
};
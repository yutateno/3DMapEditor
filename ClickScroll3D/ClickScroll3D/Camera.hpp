#pragma once
#include "DxLib.h"
#include <math.h>
#include "InputKey.hpp"


class Camera
{
private:
	VECTOR cameraArea;		// カメラの位置
	VECTOR viewArea;		// 注視する方向


	int stageHandle;		// 当たり判定用ステージ


	float speed;					// 回転スピード
	void RLrotate(const float speed, VECTOR& p_cameraArea);	// 回転を行う関数


	int mouseX, mouseY, premouseX, premouseY;


public:
	Camera();				// キャラの位置を引数に取ったコンストラクタ
	~Camera();													// デストラクタ


	void Process();		// キャラの位置を引数に取ったプロセス


	const VECTOR GetArea() const;				// キャラクターのアングル
};
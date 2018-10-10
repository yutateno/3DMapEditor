#pragma once
#include "DxLib.h"
#include <math.h>
#include "InputKey.hpp"
#include "Input.hpp"
#include "Parameter.hpp"


class Camera
{
private:
	VECTOR cameraArea;		// カメラの位置
	Vector2 circleArea;


	int stageHandle;		// 当たり判定用ステージ


	float speed;					// 回転スピード
	void RLrotate(const float speed, VECTOR& p_cameraArea);	// 回転を行う関数


	int premouseX, premouseY;

	float angle;


public:
	Camera();				// キャラの位置を引数に取ったコンストラクタ
	~Camera();													// デストラクタ


	void Process(int mouseX, int mouseY);		// キャラの位置を引数に取ったプロセス


	const VECTOR GetArea() const;				// キャラクターのアングル
};
#include "Camera.hpp"


// コンストラクタ
Camera::Camera()
{
	cameraArea = VGet(0, 350, 500);
	viewArea = VGet(0, 150, 0);

	speed = DX_PI_F / 90;

	SetCameraNearFar(100.0f, 10000.0f);	// カメラの描画範囲を指定

	// 第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VAdd(cameraArea, VGet(0.0f, 0.0f, 0.0f)), VAdd(viewArea, VGet(0.0f, 0.0f, 0.0f)));
}

// デストラクタ
Camera::~Camera()
{
}

const VECTOR Camera::GetArea() const
{
	return cameraArea;
}


// メインプロセス
void Camera::Process()
{
	GetMousePoint(&mouseX, &mouseY);

	// 左に回転中
	if (premouseX < mouseX)
	{
		RLrotate(speed, cameraArea);	// 回転処理
	}
	// 右に回転中
	if (premouseX > mouseX)
	{
		RLrotate(-speed, cameraArea);	// 回転処理
	}


	premouseX = mouseX;
	premouseY = mouseY;

	SetCameraPositionAndTarget_UpVecY(VAdd(cameraArea, VGet(0.0f, 0.0f, 0.0f)), VAdd(viewArea, VGet(0.0f, 0.0f, 0.0f)));
}


// ang角回転する
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
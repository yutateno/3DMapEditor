#include "Camera.hpp"


// コンストラクタ
Camera::Camera()
{
	cameraArea = VGet(0, 350, 0);

	circleArea = Vector2(0.0f, 100.0f);

	speed = DX_PI_F / 180;
	angle = 0.0f;

	SetCameraNearFar(1.0f, 5000.0f);	// カメラの描画範囲を指定

	// 第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(cameraArea, VAdd(cameraArea, VGet(circleArea.x, -200.0f, circleArea.y)));
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
void Camera::Process(int mouseX, int mouseY)
{
	// 右クリックを押していたら
	if (MouseData::GetClick(1) >= 1)
	{
		// 左に回転中
		if (premouseX < mouseX)
		{
			float circle = DX_PI_F / 180;
			float xd = circleArea.x * cosf(circle) - circleArea.y * sinf(circle);
			float yd = circleArea.x * sinf(circle) + circleArea.y * cosf(circle);
			circleArea.x = xd;
			circleArea.y = yd;
			angle -= circle;
		}
		// 右に回転中
		if (premouseX > mouseX)
		{
			float circle = -DX_PI_F / 180;
			float xd = circleArea.x * cosf(circle) - circleArea.y * sinf(circle);
			float yd = circleArea.x * sinf(circle) + circleArea.y * cosf(circle);
			circleArea.x = xd;
			circleArea.y = yd;
			angle -= circle;
		}

		if (KeyData::Get(KEY_INPUT_A) >= 1)
		{
			cameraArea.x += cosf(-angle) * -5.0f;
			cameraArea.z += sinf(-angle) * -5.0f;
		}

		if (KeyData::Get(KEY_INPUT_D) >= 1)
		{
			cameraArea.x += cosf(-angle) * 5.0f;
			cameraArea.z += sinf(-angle) * 5.0f;
		}

		if (KeyData::Get(KEY_INPUT_W) >= 1)
		{
			cameraArea.x += sinf(angle) * 5.0f;
			cameraArea.z += cosf(angle) * 5.0f;
		}

		if (KeyData::Get(KEY_INPUT_S) >= 1)
		{
			cameraArea.x += sinf(angle) * -5.0f;
			cameraArea.z += cosf(angle) * -5.0f;
		}
	}


	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) >= 1)
	{
		cameraArea.x += sinf(angle) * -5.0f;
		cameraArea.z += cosf(angle) * -5.0f;
	}

	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) <= -1)
	{
		cameraArea.x += sinf(angle) * 5.0f;
		cameraArea.z += cosf(angle) * 5.0f;
	}
	

	premouseX = mouseX;
	premouseY = mouseY;

	SetCameraPositionAndTarget_UpVecY(cameraArea, VAdd(cameraArea, VGet(circleArea.x, 0.0f, circleArea.y + 50.0f)));
}


// ang角回転する
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
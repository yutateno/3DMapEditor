#include "Camera.hpp"


// コンストラクタ
Camera::Camera()
{
	cameraArea = VGet(0, 350, 500);
	viewArea = VGet(0, 150, 0);
	pointArea = VGet(0.0f, 0.0f, 0.0f);

	speed = DX_PI_F / 90;
	angle = 0.0f;

	SetCameraNearFar(100.0f, 10000.0f);	// カメラの描画範囲を指定

	// 第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VAdd(cameraArea, pointArea), VAdd(viewArea, pointArea));
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
			RLrotate(speed * 2, cameraArea);	// 回転処理
			RLrotate(speed * 2, viewArea);	// 回転処理
			RLrotate(speed * 2, pointArea);	// 回転処理
			angle += speed * 2;
		}
		// 右に回転中
		if (premouseX > mouseX)
		{
			RLrotate(-speed * 2, cameraArea);	// 回転処理
			RLrotate(-speed * 2, viewArea);	// 回転処理
			RLrotate(-speed * 2, pointArea);	// 回転処理
			angle -= speed * 2;
		}

		if (KeyData::Get(KEY_INPUT_A) >= 1)
		{
			cameraArea.x += cosf(-angle) * 5.0f;
			cameraArea.z += sinf(-angle) * 5.0f;
			viewArea.x += cosf(-angle) * 5.0f;
			viewArea.z += sinf(-angle) * 5.0f;
		}

		if (KeyData::Get(KEY_INPUT_D) >= 1)
		{
			cameraArea.x += cosf(-angle) * -5.0f;
			cameraArea.z += sinf(-angle) * -5.0f;
			viewArea.x += cosf(-angle) * -5.0f;
			viewArea.z += sinf(-angle) * -5.0f;
		}

		if (KeyData::Get(KEY_INPUT_W) >= 1)
		{
			cameraArea.x += sinf(angle) * -5.0f;
			cameraArea.z += cosf(angle) * -5.0f;
			viewArea.x += sinf(angle) * -5.0f;
			viewArea.z += cosf(angle) * -5.0f;
			//pointArea.x += sinf(angle) * -5.0f;
			////pointArea.z += cosf(angle) * -5.0f;
		}

		if (KeyData::Get(KEY_INPUT_S) >= 1)
		{
			cameraArea.x += sinf(angle) * 5.0f;
			cameraArea.z += cosf(angle) * 5.0f;
			viewArea.x += sinf(angle) * 5.0f;
			viewArea.z += cosf(angle) * 5.0f;
			//pointArea.x += sinf(angle) * 5.0f;
			//pointArea.z += cosf(angle) * 5.0f;
		}
	}


	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) >= 1)
	{
		cameraArea.x += sinf(angle) * -5.0f;
		cameraArea.z += cosf(angle) * -5.0f;
		viewArea.x += sinf(angle) * -5.0f;
		viewArea.z += cosf(angle) * -5.0f;
		//pointArea.x += sinf(angle) * -5.0f;
		////pointArea.z += cosf(angle) * -5.0f;
	}

	if (MouseWheelData::GetMouseWheel(GetMouseWheelRotVol()) <= -1)
	{
		cameraArea.x += sinf(angle) * 5.0f;
		cameraArea.z += cosf(angle) * 5.0f;
		viewArea.x += sinf(angle) * 5.0f;
		viewArea.z += cosf(angle) * 5.0f;
		//pointArea.x += sinf(angle) * 5.0f;
		//pointArea.z += cosf(angle) * 5.0f;
	}
	

	premouseX = mouseX;
	premouseY = mouseY;

	DrawFormatString(0, 0, 255, "%f\t%f\t%f\n%f\t%f\t%f\n%f\t%f\t%f\n", cameraArea.x, cameraArea.y, cameraArea.z, viewArea.x, viewArea.y, viewArea.z, pointArea.x, pointArea.y, pointArea.z);

	SetCameraPositionAndTarget_UpVecY(VAdd(cameraArea, pointArea), VAdd(viewArea, pointArea));
}


// ang角回転する
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
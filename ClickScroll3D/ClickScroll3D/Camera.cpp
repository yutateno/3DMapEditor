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
	// 左に回転中
	if (CheckHitKey(KEY_INPUT_LEFT) >= 1)
	{
		RLrotate(speed, cameraArea);	// 回転処理
	}
	// 右に回転中
	if (CheckHitKey(KEY_INPUT_RIGHT) >= 1)
	{
		RLrotate(-speed, cameraArea);	// 回転処理
	}

	//// 上キーが押されていたら下から見上げる
	//if (KeyData::Get(KEY_INPUT_UP) >= 1
	//	|| InputPad::GetPadThumbData(controllNumber, STICK_RIGHT_Y) > 0)
	//{
	//	// 制限
	//	if (TestPosition.y > 240)
	//	{
	//		TestPosition = VAdd(TestPosition, VScale(VNorm(TestPosition), -10));	// 単位ベクトル化してマイナスかけて同一方向に減らす
	//	}
	//}

	//// 下キーが押されていたら上から見下ろす
	//if (KeyData::Get(KEY_INPUT_DOWN) >= 1
	//	|| ::InputPad::GetPadThumbData(controllNumber, STICK_RIGHT_Y) < 0)
	//{
	//	// 制限
	//	if (TestPosition.y < 400)
	//	{
	//		TestPosition = VAdd(TestPosition, VScale(VNorm(TestPosition), 10));	// VScaleいらない
	//	}
	//}

#ifdef _CAMERA_DEBG
	printfDx("%d\n", HitNum);
	//DrawCapsule3D(VAdd(cameraArea, charaArea), VAdd(viewArea, charaArea), 5.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// 面白い
	DrawCapsule3D(VAdd(cameraArea, charaArea), charaArea, 5.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// 当たり判定を確認用の表示テスト
#endif // !_CAMERA_DEBG

}


// ang角回転する
void Camera::RLrotate(const float speed, VECTOR& p_cameraArea)
{
	float tempX = p_cameraArea.x;
	p_cameraArea.x = tempX * cosf(speed) + p_cameraArea.z *sinf(speed);
	p_cameraArea.z = -tempX * sinf(speed) + p_cameraArea.z * cosf(speed);
}
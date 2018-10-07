#include "Input.hpp"
#include "InputKey.hpp"
#include "Camera.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	SetBackgroundColor(100, 100, 100);
	SetGraphMode(1920, 1080, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	SetDragFileValidFlag(TRUE);

	SetMouseDispFlag(TRUE);

	int windowX, windowY, colorBit;
	GetDefaultState(&windowX, &windowY, &colorBit);
	SetWindowSize(windowX, windowY);


	int mac = MV1LoadModel("“§‰ß–³‘o\\“§‰ß–³‘o\\tkms_Blender.mv1");
	int mac2 = MV1LoadModel("“§‰ß–³‘o\\“§‰ß–³‘o\\tkms_Blender.mv1");


	Camera* camera = new Camera();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2))
	{
		KeyData::UpDate();
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();

		camera->Process();

		MV1DrawModel(mac);
		MV1SetPosition(mac, VGet(0.0f, 0.0f, 0.0f));
		MV1DrawModel(mac2);
		MV1SetPosition(mac2, VGet(100.0f, 0.0f, 100.0f));

		// ConvWorldPosToScreenPos
	}


	MV1DeleteModel(mac2);
	MV1DeleteModel(mac);


	delete camera;


	DxLib_End();
	return 0;
}
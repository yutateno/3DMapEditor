#include "Input.hpp"
#include "InputKey.hpp"
#include "Camera.hpp"
#include "Model.hpp"

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

	Camera* camera = new Camera();


	int mouseX, mouseY;

	VECTOR model1VecUp = VGet(0.0f, 160.0f, 0.0f);
	VECTOR model1VecDown = VGet(0.0f, 0.0f, 0.0f);

	VECTOR model2VecUp = VGet(100.0f, 160.0f, 100.0f);
	VECTOR model2VecDown = VGet(100.0f, 0.0f, 100.0f);

	VECTOR model3VecUp = VGet(200.0f, 160.0f, 200.0f);
	VECTOR model3VecDown = VGet(200.0f, 0.0f, 200.0f);

	Model* model[Parameter::modelNum];
	model[0] = new Model(model1VecUp, model1VecDown);
	model[1] = new Model(model2VecUp, model2VecDown);
	model[2] = new Model(model3VecUp, model3VecDown);

	bool flag[Parameter::modelNum];
	flag[0] = false;
	flag[1] = false;
	flag[2] = false;


	int i;
	VECTOR Pos1;
	VECTOR Pos2;

	float LINE_AREA_SIZE = 10000.0f;
	int LINE_NUM = 500;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2))
	{
		SetUseZBufferFlag(TRUE);

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.x += LINE_AREA_SIZE / LINE_NUM;
			Pos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.z += LINE_AREA_SIZE / LINE_NUM;
			Pos2.z += LINE_AREA_SIZE / LINE_NUM;
		}

		SetUseZBufferFlag(FALSE);

		KeyData::UpDate();
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		GetMousePoint(&mouseX, &mouseY);

		camera->Process(mouseX, mouseY);

		for (int i = 0; i != Parameter::modelNum; ++i)
		{
			model[i]->Draw();

			model[i]->Process(mouseX, mouseY);
		}


		for (int i = 0; i != Parameter::modelNum; ++i)
		{
			if (MouseData::GetClick(0) == 1)
			{
				if (!flag[i])
				{
					model[i]->SelectCheck(mouseX, mouseY);

					if (model[i]->GetModelFlag())
					{
						for (int j = 0; j != Parameter::modelNum; ++j)
						{
							flag[j] = false;
							model[j]->SetTouchFlase();
						}
						model[i]->SelectCheck(mouseX, mouseY);
						flag[i] = true;
					}
				}
			}
		}
	}


	for (int i = 0; i != 2; i++)
	{
		_POINTER_RELEASE(model[i]);
	}

	_POINTER_RELEASE(camera);


	DxLib_End();
	return 0;
}
#include "Input.hpp"
#include "InputKey.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include <vector>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

inline void SaveData(std::vector<Model*> t_v_model);

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

	std::string str = "透過無双\\透過無双\\tkms_metaseq.mv1";

	std::vector<Model*> v_model;
	v_model.push_back(new Model(model1VecUp, model1VecDown, str));
	v_model.push_back(new Model(model2VecUp, model2VecDown, str));
	v_model.push_back(new Model(model3VecUp, model3VecDown, str));

	bool flag[Parameter::modelNum];
	flag[0] = false;
	flag[1] = false;
	flag[2] = false;


	int i;
	VECTOR Pos1;
	VECTOR Pos2;

	float LINE_AREA_SIZE = 10000.0f;
	int LINE_NUM = 50;

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

		for (int i = 0; i != v_model.size(); ++i)
		{
			if (!CheckCameraViewClip(v_model[i]->GetArea()))
			{
				v_model[i]->Draw();

				v_model[i]->Process(mouseX, mouseY);

				if (v_model[i]->GetModelFlag())
				{
					DrawFormatString(0, 0, GetColor(255, 255, 255), "Number : %d", i);
				}
			}
		}


		for (int i = 0; i != v_model.size(); ++i)
		{
			if (!CheckCameraViewClip(v_model[i]->GetArea()))
			{
				if (MouseData::GetClick(0) == 1)
				{
					if (!flag[i])
					{
						v_model[i]->SelectCheck(mouseX, mouseY);

						if (v_model[i]->GetModelFlag())
						{
							for (int j = 0; j != v_model.size(); ++j)
							{
								flag[j] = false;
								v_model[j]->SetTouchFlase();
							}
							v_model[i]->SelectCheck(mouseX, mouseY);
							flag[i] = true;
						}
					}
				}
			}
		}

		if (KeyData::Get(KEY_INPUT_Z) == 1)
		{
			SaveData(v_model);
			DrawFormatString(255, 255, 255, "セーブしました。\n");
		}
	}


	for (int i = 0; i != 2; i++)
	{
		_POINTER_RELEASE(v_model[i]);
	}
	_VECTOR_RELEASE(v_model);

	_POINTER_RELEASE(camera);


	DxLib_End();
	return 0;
}

inline void SaveData(std::vector<Model*> t_v_model)
{
	std::ofstream saveFile;
	saveFile.open("Save.csv");		// ファイルオープン

	if (saveFile.fail()) {	// ファイル読み込み失敗
		DrawFormatString(0, 0, GetColor(0, 0, 0), "SaveError");
	}
	else {
		// 読み込み成功
		saveFile << "番号" << "," << "X" << "," << "Y" << "," << "Z";
		saveFile << std::endl;
		for (int i = 0, n = static_cast<int>(t_v_model.size()); i < n; i++) {
			saveFile << i << "," << t_v_model[i]->GetArea().x << "," << t_v_model[i]->GetArea().y << "," << t_v_model[i]->GetArea().z;
			saveFile << std::endl;
		}
	}

	// ファイルを閉じる
	saveFile.close();
}

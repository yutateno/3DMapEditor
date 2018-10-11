#include "Model.hpp"


Model::Model(VECTOR t_modelVecUp, VECTOR t_modelVecDown, std::string str)
{
	modelVecUp	 = t_modelVecUp;
	modelVecDown = t_modelVecDown;

	modelUp		 = Vector2(ConvWorldPosToScreenPos(modelVecUp).x - 5.0f		, ConvWorldPosToScreenPos(modelVecUp).y);
	modelDown	 = Vector2(ConvWorldPosToScreenPos(modelVecDown).x + 5.0f	, ConvWorldPosToScreenPos(modelVecDown).y);

	modelFlag = false;

	modelXMoveTouch = false;
	modelZMoveTouch = false;

	modelHandle = MV1LoadModel(str.c_str());

	MV1SetPosition(modelHandle, modelVecDown);
}

Model::~Model()
{
	_MODEL_RELEASE(modelHandle);
}

void Model::Process(int mouseX, int mouseY)
{
	modelUp = Vector2(ConvWorldPosToScreenPos(modelVecUp).x - 5.0f		, ConvWorldPosToScreenPos(modelVecUp).y);
	modelDown = Vector2(ConvWorldPosToScreenPos(modelVecDown).x + 5.0f	, ConvWorldPosToScreenPos(modelVecDown).y);


	if (modelFlag)
	{
		if (!modelZMoveTouch)
		{
			if ((ConvWorldPosToScreenPos(VGet(modelVecUp.x					, (modelVecUp.y - (modelVecDown.y)) / 2.0f	, modelVecUp.z)).x <= mouseX
				&& ConvWorldPosToScreenPos(VGet(modelVecUp.x + 100.0f		, (modelVecUp.y - (modelVecDown.y)) / 2.0f	, modelVecUp.z)).x >= mouseX)
				|| (ConvWorldPosToScreenPos(VGet(modelVecUp.x				, (modelVecUp.y - (modelVecDown.y)) / 2.0f	, modelVecUp.z)).x >= mouseX
					&& ConvWorldPosToScreenPos(VGet(modelVecUp.x + 100.0f	, (modelVecUp.y - (modelVecDown.y)) / 2.0f	, modelVecUp.z)).x <= mouseX))
			{
				if (MouseData::GetClick(0) >= 1)
				{
					modelXMoveTouch = true;
				}
			}
			if (modelXMoveTouch)
			{
				if (preMouseX > mouseX)
				{
					modelVecUp.x -= preMouseX - mouseX;
					modelVecDown.x -= preMouseX - mouseX;
				}
				if (preMouseX < mouseX)
				{
					modelVecUp.x += mouseX - preMouseX;
					modelVecDown.x += mouseX - preMouseX;
				}
			}
			if (MouseData::GetClick(0) == 0)
			{
				modelXMoveTouch = false;
			}
		}

		if (!modelXMoveTouch)
		{
			if ((ConvWorldPosToScreenPos(VGet(modelVecUp.x		, (modelVecUp.y - (modelVecDown.y)) / 2.0f, modelVecUp.z)).x			 <= mouseX
				&& ConvWorldPosToScreenPos(VGet(modelVecUp.x	, (modelVecUp.y - (modelVecDown.y)) / 2.0f, modelVecUp.z + 100.0f)).x	 >= mouseX)
				|| (ConvWorldPosToScreenPos(VGet(modelVecUp.x	, (modelVecUp.y - (modelVecDown.y)) / 2.0f, modelVecUp.z)).x			 >= mouseX
					&& ConvWorldPosToScreenPos(VGet(modelVecUp.x, (modelVecUp.y - (modelVecDown.y)) / 2.0f, modelVecUp.z + 100.0f)).x	 <= mouseX))
			{
				if (MouseData::GetClick(0) >= 1)
				{
					modelZMoveTouch = true;
				}
			}
			if (modelZMoveTouch)
			{
				if (preMouseX > mouseX)
				{
					modelVecUp.z += preMouseX - mouseX;
					modelVecDown.z += preMouseX - mouseX;
				}
				if (preMouseX < mouseX)
				{
					modelVecUp.z -= mouseX - preMouseX;
					modelVecDown.z -= mouseX - preMouseX;
				}
			}
			if (MouseData::GetClick(0) == 0)
			{
				modelZMoveTouch = false;
			}
		}
	}


	MV1SetPosition(modelHandle, modelVecDown);


	preMouseX = mouseX;
	preMouseY = mouseY;
}

void Model::Draw()
{
	MV1DrawModel(modelHandle);

	if (modelFlag)
	{
		// X軸方向に関して
		for (int i = 0; i != 10; ++i)
		{
			DrawLine(static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x			, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z)).x)
				, static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x			, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z)).y)
				, static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x + 100.0f	, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z)).x)
				, static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x + 100.0f	, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z)).y)
				, GetColor(255, 0, 255));
		}

		// Z軸方向に関して
		for (int i = 0; i != 10; ++i)
		{
			DrawLine(static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x		, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z)).x)
				, static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x		, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z)).y)
				, static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x		, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z + 100.0f)).x)
				, static_cast<int>(ConvWorldPosToScreenPos(VGet(modelVecUp.x		, (modelVecUp.y + i - (modelVecDown.y - i)) / 2.0f, modelVecUp.z + 100.0f)).y)
				, GetColor(0, 255, 255));
		}

		DrawCapsule3D(modelVecUp, modelVecDown, 50.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// 当たり判定を確認用の表示テスト
	}

	DrawBox(static_cast<int>(modelUp.x), static_cast<int>(modelUp.y), static_cast<int>(modelDown.x), static_cast<int>(modelDown.y), GetColor(0, 255, 0), false);
}

void Model::SelectCheck(int mouseX, int mouseY)
{
	if (!modelFlag)
	{
		if ((modelUp.x <= mouseX && modelDown.x >= mouseX)
			|| (modelUp.x >= mouseX && modelDown.x <= mouseX))
		{
			modelFlag = true;
		}
	}
}

void Model::SetTouchFlase()
{
	modelFlag = false;
}

bool Model::GetModelFlag()
{
	return modelFlag;
}

VECTOR Model::GetArea()
{
	return modelVecDown;
}

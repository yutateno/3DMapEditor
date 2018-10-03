#pragma once
#include "DxLib.h"

enum class CLICK { LEFT, RIGHT };

class MouseData
{
private:
	static int m_Mouse[3];
	static int MouseInput;

public:
	MouseData();
	~MouseData();

	static void Mouse_UpDate(); //マウスのクリックの状態を更新する
	static int GetClick(int MouseCode); //マウスのクリックの状態を返す
};


class MouseWheelData
{
private:
	static int m_MouseWheel;
	static int old_MouseWheel;

public:
	MouseWheelData();
	~MouseWheelData();

	static void MouseWheel_Update(); //マウスのホイールの状態を更新
	static int GetMouseWheel(int MouseWheelCode); //マウスホイールの状態を返す
};
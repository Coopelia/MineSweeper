#pragma once
#include"Def.h"
#include"Button.h"
#include"Menu.h"
#include"Grid.h"
#include"MyClock.h"

class StartScene
{
	friend class Game;
public:
	Menu menu_setting;
	Music bgm;
	String LV;
	Sprite sBack_log, sSkin;
	Button bt_Setting, bt_Ok, bt_Cancel;
	Texture tSkin, tBack_log;
	bool isRunning;
	bool isOnExitLog;
	bool isOnMenu;
	StartScene();
	void gameStart();
private:
	Sprite sBack;
	Button bt_Enter, bt_Exit;
	Texture tBack;
	RenderWindow* app;
	void Initial(RenderWindow* app);
	void Updata();
	void DrawBack();
	void DrawMenu();
	void DrawExitLog();
	void scene_close();
};

class GameScene:public StartScene
{
	friend class Game;
public:
	int width, heigth;
	int dt_x, dt_y;
	int gridSizeX, gridSizeY;
	int mineCounter;
	MyClock myTimer;
	Grid grid[36][36];
	GameScene();
	void Initial(RenderWindow* app);
	void Updata();
	void ReStart();
	void DrawBack();
	void DrawExitLog();
	void DrawMenu();
	void DrawGrid();
	void TimeShow();
	void CounterShow();
	void LvShow();
	void scene_close();
private:
	Sprite sBack, sTime, sCount, sLv;
	Button bt_Setting, bt_Back;
	Texture tBack, tTime, tCount, tLv;
	Font font;
	Text time, count, lv;
	RenderWindow* app;
};
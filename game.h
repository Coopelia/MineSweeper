#pragma once
#include"Def.h"
#include"scene.h"

class Game
{
public:
	RenderWindow* app;
	StartScene start_scene;
	GameScene game_scene;
	bool OnStartScene;
	bool OnPlayScene;
	bool isOvered;//游戏是否已结束
	bool isDebug;//debug
	State de_back[40][40];
	int mine_num; //雷总数
	int mine_rest; //显示的剩余雷数
	int mine_counter;//被正确标为红旗的雷数
	int px, py;//第一次点击的位置
	int mouse_timer;//鼠标双击计时器
	int gameOver;//0未结算，1胜利，2失败
	int MineState;//0未开始布雷，1正在布雷，2布雷完毕
	Clock mouseClock;
	Button bt_ok, bt_restart;
	Texture tOver, tSkin[6],tBack[7];
	Sprite sOver;
	Game();
	~Game();
	void SetMine(); //布雷
	void Update(); //更新
	void UpdateGrid();//格子Logic
	void GameOver(); //游戏结束
	void Run(); //主控函数
	void (Game::* Input)(Event&);//输入函数指针
	void (Game::* Draw)();//绘制函数指针
	void Input_start_scene(Event& e);
	void Input_game_scene(Event& e);
	void draw_start_scene();
	void draw_game_scene();
	void Debug();
};
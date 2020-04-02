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
	bool isOvered;
	int mine_num;
	int mine_rest;
	int mine_counter;
	int px, py;
	int mouse_timer;
	int gameOver;//0未结算，1胜利，2失败
	int MineState;//0未开始布雷，1正在布雷，2布雷完毕
	Clock mouseClock;
	Button bt_ok, bt_restart;
	Texture tOver, tSkin[6],tBack[7];
	Sprite sOver;
	Sound sBoom, sPass;
	SoundBuffer sbBoom, sbPass;
	Game(RenderWindow* app);
	void SetMine();
	void Updata();
	void UpdataGrid(Event& e);
	void GameOver();
	void Run();
	void (Game::* Input)(Event&);
	void (Game::* Draw)();
	void Input_start_scene(Event& e);
	void Input_game_scene(Event& e);
	void draw_start_scene();
	void draw_game_scene();
};
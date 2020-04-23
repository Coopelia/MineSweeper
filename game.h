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
	bool isOvered;//��Ϸ�Ƿ��ѽ���
	bool isDebug;//debug
	State de_back[40][40];
	int mine_num; //������
	int mine_rest; //��ʾ��ʣ������
	int mine_counter;//����ȷ��Ϊ���������
	int px, py;//��һ�ε����λ��
	int mouse_timer;//���˫����ʱ��
	int gameOver;//0δ���㣬1ʤ����2ʧ��
	int MineState;//0δ��ʼ���ף�1���ڲ��ף�2�������
	Clock mouseClock;
	Button bt_ok, bt_restart;
	Texture tOver, tSkin[6],tBack[7];
	Sprite sOver;
	Game();
	~Game();
	void SetMine(); //����
	void Update(); //����
	void UpdateGrid();//����Logic
	void GameOver(); //��Ϸ����
	void Run(); //���غ���
	void (Game::* Input)(Event&);//���뺯��ָ��
	void (Game::* Draw)();//���ƺ���ָ��
	void Input_start_scene(Event& e);
	void Input_game_scene(Event& e);
	void draw_start_scene();
	void draw_game_scene();
	void Debug();
};
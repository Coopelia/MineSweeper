#pragma once
#include"Def.h"

class Button
{
	friend class Game;
	friend class StartScene;
	friend class GameScene;
	friend class Menu;
public:
	Button():app(NULL),PreBehRel(false) {};
	bool PreBehRel;   //��ֹ����ڰ�ť���水סȻ���Ƶ���ť���ɿ���������¼�
	void setTextrue(String s);
	void setPosition(int x, int y);
	void setScale(float x, float y);
	void show();
	bool onClick(Event& e);
	Sprite s;
private:
	Texture t;
	RenderWindow* app;
};
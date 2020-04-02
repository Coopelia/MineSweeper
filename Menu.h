#pragma once
#include"Button.h"

class Menu
{
	friend class StartScene;
	friend class GameScene;
	friend class Game;
public:
	Menu();
	void setPosition(int x, int y);
	void setBack(String s);
	void addButton(String s, int posX, int posY, float scaleX, float scaleY);
	void addText(String s, int posX, int posY, int size, Color color);
	void show();
private:
	int posX, posY;
	int num_button;
	int num_text;
	Button button[10];
	Text text[20];
	Sprite sBack;
	Texture tBack;
	Font font;
	RenderWindow* app;
};


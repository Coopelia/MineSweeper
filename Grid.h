#pragma once
#include"Def.h"

class Grid
{
	//friend class Game;
	friend class GameScene;
public:
	Grid();
	void Init_texture(Texture t);
	void setPosition(int x, int y);
	void show();
	void setTextureID(int id);
	bool LeftPreBehRel;
	bool RightPreBehRel;
	bool DLeftPreBehRel;
	bool isMineSetted;
	bool isClickOnce;
	bool onClickLeft(Event& e);
	bool onClickRight(Event& e);
	bool onClickDouble(Event& e);
	State sta;
	int texture_id;
private:
	Sprite s;
	Texture t;
	int sizeX, sizeY;
	int posX, posY;
	RenderWindow* app;
};
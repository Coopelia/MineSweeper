#include"scene.h"

StartScene::StartScene()
{
	this->app = NULL;
	isRunning = false;
	isOnExitLog = false;
	isOnMenu = false;
	this->LV = " ";
	tBack.loadFromFile("data/images/BK01.jpg");
	sBack.setTexture(tBack);
	tBack_log.loadFromFile("data/images/Menu/back3.png");
	sBack_log.setTexture(tBack_log);
	bt_Enter.setTextrue("data/images/start_btn0.png");
	bt_Exit.setTextrue("data/images/leave_btn0.png");
	bt_Setting.setTextrue("data/images/hall_setting_btn0.png");
	bt_Ok.setTextrue("data/images/Menu/ok.png");
	bt_Cancel.setTextrue("data/images/Menu/cancel.png");
	bgm.openFromFile("data/Audios/BGM01.ogg");
	bgm.setLoop(true);
}

void StartScene::Initial(RenderWindow* app)
{
	this->app = app;
	this->bt_Enter.app = app;
	this->bt_Exit.app = app;
	this->bt_Setting.app = app;
	this->bt_Ok.app = app;
	this->bt_Cancel.app = app;
	this->menu_setting.app = app;

	this->menu_setting.setBack("data/images/Menu/back1.png");
	this->menu_setting.setPosition(287, 66);

	this->menu_setting.addText(L"音量:", 310, 80, 40, Color::White);
	this->menu_setting.addButton("data/images/Menu/left.png", 410, 90, 0.4, 0.4);
	this->menu_setting.addText(std::to_string(vol), 460, 82, 36, Color::Yellow);
	this->menu_setting.addButton("data/images/Menu/right.png", 520, 90, 0.4, 0.4);

	this->menu_setting.addText(L"难度:", 310, 150, 40, Color::White);
	this->menu_setting.addButton("data/images/Menu/left.png", 410, 160, 0.4, 0.4);
	this->menu_setting.addText(this->LV, 457, 152, 36, Color::Yellow);
	this->menu_setting.addButton("data/images/Menu/right.png", 520, 160, 0.4, 0.4);

	this->menu_setting.addText(L"皮肤:", 310, 270, 40, Color::White);
	this->menu_setting.addButton("data/images/Menu/up.png", 470, 250, 0.3, 0.3);
	this->menu_setting.addText(this->LV, 457, 152, 36, Color::Yellow);
	this->menu_setting.addButton("data/images/Menu/down.png", 470, 323, 0.3, 0.3);

	this->menu_setting.addButton("data/images/Menu/ok.png", 400, 420, 0.5, 0.5);
}

void StartScene::Update()
{
	this->bgm.setVolume(vol);
}

void StartScene::DrawBack()
{
	sBack.setPosition(0, 0);
	bt_Setting.setPosition(720, 10);
	bt_Exit.setPosition(790, 10);
	bt_Enter.setPosition(324, 500);
	(*app).draw(sBack);
	bt_Setting.show();
	bt_Exit.show();
	bt_Enter.show();
}

void StartScene::DrawMenu()
{
	menu_setting.text[1].setString(std::to_string(vol));
	menu_setting.text[3].setString(LV);
	menu_setting.show();
	sSkin.setTexture(tSkin);
	sSkin.setTextureRect(IntRect(25, 0, 275, 25));
	sSkin.setScale(0.7, 0.7);
	sSkin.setPosition(385, 290);
	(*app).draw(sSkin);

}

void StartScene::gameStart()
{
	bgm.setVolume(vol);
	bgm.play();
	isRunning = true;
}

void StartScene::scene_close()
{
	bgm.stop();
	isRunning = false;
}

void StartScene::DrawExitLog()
{
	sBack_log.setPosition(125, 103);
	bt_Ok.setPosition(220, 350);
	bt_Cancel.setPosition(480, 350);
	(*app).draw(sBack_log);
	bt_Ok.show();
	bt_Cancel.show();
}

GameScene::GameScene()
{
	this->app = NULL;
	this->LV = L"简单";
	this->width = 10;
	this->heigth = 10;
	this->gridSizeX = 25;
	this->gridSizeY = 25;
	this->mineCounter = 0;
	this->dt_x = 0;
	this->dt_y = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigth; j++)
		{
			this->grid[i][j].sizeX = this->gridSizeX;
			this->grid[i][j].sizeY = this->gridSizeY;
			this->grid[i][j].Init_texture(tSkin);
		}
	}
	isRunning = false;
	tBack_log.loadFromFile("data/images/Menu/back2.png");
	sBack_log.setTexture(tBack_log);
	bt_Ok.setTextrue("data/images/Menu/ok.png");
	bt_Cancel.setTextrue("data/images/Menu/cancel.png");
	tBack.loadFromFile("data/images/BK02.jpg");
	sBack.setTexture(tBack);
	tTime.loadFromFile("data/images/jishiqi.jpg");
	sTime.setTexture(tTime);
	tCount.loadFromFile("data/images/jishuqi.jpg");
	sCount.setTexture(tCount);
	tLv.loadFromFile("data/images/head_bg.png");
	sLv.setTexture(tLv);
	bt_Back.setTextrue("data/images/btn_back0.png");
	bt_Setting.setTextrue("data/images/hall_setting_btn0.png");
	sbBoom.loadFromFile("data/Audios/bomb.wav");
	sbPass.loadFromFile("data/Audios/pass.wav");
	sBoom.setBuffer(sbBoom);
	sBoom.setVolume(vol);
	sBoom.setLoop(false);
	sPass.setBuffer(sbPass);
	sPass.setVolume(vol);
	sPass.setLoop(false);
	bgm.openFromFile("data/Audios/BGM02.ogg");
	font.loadFromFile("data/font/oil.ttf");
	bgm.setLoop(true);
}

void GameScene::Initial(RenderWindow* app)
{
	this->app = app;
	this->bt_Back.app = app;
	this->bt_Setting.app = app;
	this->menu_setting.app = app;
	this->bt_Ok.app = app;
	this->bt_Cancel.app = app;
	for (int i = 0; i < 36; i++)
		for (int j = 0; j < 36; j++)
			this->grid[i][j].app = this->app;

	this->menu_setting.setBack("data/images/Menu/back1.png");
	this->menu_setting.setPosition(287, 66);

	this->menu_setting.addText(L"音量:", 310, 80, 40, Color::White);
	this->menu_setting.addButton("data/images/Menu/left.png", 410, 90, 0.4, 0.4);
	this->menu_setting.addText(std::to_string(vol), 460, 82, 36, Color::Yellow);
	this->menu_setting.addButton("data/images/Menu/right.png", 520, 90, 0.4, 0.4);

	this->menu_setting.addText(L"难度:", 310, 150, 40, Color::White);
	this->menu_setting.addText(this->LV, 457, 152, 36, Color::Yellow);
	this->menu_setting.addText(L"(需要在主\n 菜单变更)", 520, 158, 16, Color::Blue);

	this->menu_setting.addText(L"皮肤:", 310, 270, 40, Color::White);
	this->menu_setting.addButton("data/images/Menu/up.png", 470, 250, 0.3, 0.3);
	this->menu_setting.addButton("data/images/Menu/down.png", 470, 323, 0.3, 0.3);

	this->menu_setting.addText(L"背景:", 310, 367, 40, Color::White);
	this->menu_setting.addButton("data/images/Menu/left.png", 400, 380, 0.4, 0.4);
	this->menu_setting.addButton("data/images/Menu/right.png", 535, 380, 0.4, 0.4);

	this->menu_setting.addButton("data/images/Menu/re.png", 330, 460, 0.5, 0.4);
	this->menu_setting.addButton("data/images/Menu/ok.png", 480, 460, 0.5, 0.4);
}

void GameScene::Update()
{
	this->dt_x = 430 - (this->width * this->gridSizeX) / 2;
	this->dt_y = 300 - (this->heigth * this->gridSizeY) / 2;
	this->myTimer.update();
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigth; j++)
		{
			this->grid[i][j].sizeX = this->gridSizeX;
			this->grid[i][j].sizeY = this->gridSizeY;
			this->grid[i][j].Init_texture(tSkin);
		}
	}
	this->sPass.setVolume(vol);
	this->sBoom.setVolume(vol);
	this->bgm.setVolume(vol);
}

void GameScene::scene_close()
{
	mineCounter = 0;
	myTimer.stop();
	bgm.stop();
	isRunning = false;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigth; j++)
		{
			grid[i][j].sta = REV;
			grid[i][j].texture_id = 0;
		}
	}
}

void GameScene::DrawBack()
{
	sBack.setPosition(0, 0);
	sBack.setScale(1, 1);
	bt_Setting.setPosition(735, 8);
	bt_Back.setPosition(790, 10);
	(*app).draw(sBack);
	bt_Back.show();
	bt_Setting.show();
}

void GameScene::DrawExitLog()
{
	sBack_log.setPosition(125, 103);
	bt_Ok.setPosition(220, 350);
	bt_Cancel.setPosition(480, 350);
	(*app).draw(sBack_log);
	bt_Ok.show();
	bt_Cancel.show();
}

void GameScene::DrawMenu()
{
	menu_setting.text[1].setString(std::to_string(vol));
	menu_setting.text[3].setString(LV);
	menu_setting.show();
	sSkin.setTexture(tSkin);
	sSkin.setTextureRect(IntRect(25, 0, 275, 25));
	sSkin.setScale(0.7, 0.7);
	sSkin.setPosition(385, 290);
	sBack.setTexture(tBack);
	sBack.setPosition(442, 365);
	sBack.setScale(0.1, 0.1);
	(*app).draw(sSkin);
	(*app).draw(sBack);

}

void GameScene::DrawGrid()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigth; j++)
		{
			this->grid[i][j].setPosition(i * grid[i][j].sizeX + dt_x, j * grid[i][j].sizeY + dt_y);
			this->grid[i][j].show();
		}
	}
}

void GameScene::TimeShow()
{
	this->sTime.setPosition(0, 550);
	this->time.setFont(this->font);
	this->time.setString(std::to_string(myTimer.hour / 10) + (std::to_string(myTimer.hour % 10)) + ":" + std::to_string(myTimer.minute / 10) + std::to_string(myTimer.minute % 10) + ":" + std::to_string(myTimer.second / 10) + std::to_string(myTimer.second % 10));
	this->time.setCharacterSize(25);
	this->time.setFillColor(Color::Yellow);
	this->time.setPosition(100, 558);
	(*this->app).draw(this->sTime);
	(*this->app).draw(this->time);
}

void GameScene::CounterShow()
{
	this->sCount.setPosition(640, 550);
	this->count.setFont(font);
	this->count.setString(std::to_string(mineCounter));
	this->count.setCharacterSize(30);
	this->count.setFillColor(Color::Green);
	this->count.setPosition(800, 552);
	(*this->app).draw(this->sCount);
	(*this->app).draw(this->count);
}

void GameScene::LvShow()
{
	this->sLv.setPosition(402, 555);
	this->sLv.setScale(1, 0.5);
	this->lv.setFont(font);
	this->lv.setString(LV);
	this->lv.setCharacterSize(31);
	this->lv.setFillColor(Color::White);
	this->lv.setPosition(422, 557);
	(*this->app).draw(this->sLv);
	(*this->app).draw(this->lv);
}
#include"game.h"

Game::Game()
{
	this->mine_num = 10;
	this->mine_rest = 10;
	this->mine_counter = 0;
	this->px = -1;
	this->py = -1;
	this->mouse_timer = 0;
	this->app = new RenderWindow(VideoMode(win_width, win_height), "MineSweeper", Uint32(5));
	this->bt_ok.app = app;
	this->bt_restart.app = app;
	this->game_scene.Initial(app);
	this->start_scene.Initial(app);
	this->OnStartScene = true;
	this->OnPlayScene = false;
	this->isOvered = false;
	this->isDebug = false;
	this->gameOver = 0;
	this->MineState = 0;
	tSkin[0].loadFromFile("data/images/Game1.jpg");
	tSkin[1].loadFromFile("data/images/Game2.jpg");
	tSkin[2].loadFromFile("data/images/Game3.jpg");
	tSkin[3].loadFromFile("data/images/Game4.jpg");
	tSkin[4].loadFromFile("data/images/Game5.jpg");
	tSkin[5].loadFromFile("data/images/Game6.jpg");
	tBack[0].loadFromFile("data/images/BK02.jpg");
	tBack[1].loadFromFile("data/images/BK03.jpg");
	tBack[2].loadFromFile("data/images/BK04.jpg");
	tBack[3].loadFromFile("data/images/BK05.jpg");
	tBack[4].loadFromFile("data/images/BK06.jpg");
	tBack[5].loadFromFile("data/images/BK07.jpg");
	tBack[6].loadFromFile("data/images/BK01.jpg");
	tOver.loadFromFile("data/images/gameover.jpg");
	bt_ok.setTextrue("data/images/Menu/ok.png");
	bt_restart.setTextrue("data/images/Menu/re.png");
	Input = &Game::Input_start_scene;
	Draw = &Game::draw_start_scene;
	(*app).setFramerateLimit(60);
}

Game::~Game()
{
	delete this->app;
}

void Game::UpdateGrid()
{
	if (this->MineState == 2)
	{
		for (int i = 0; i < game_scene.width; i++)
		{
			for (int j = 0; j < game_scene.heigth; j++)
			{
				if (this->game_scene.grid[i][j].texture_id == 0 && this->game_scene.grid[i][j].sta == FRO)
				{
					for (int ii = i - 1; ii <= i + 1; ii++)
					{
						for (int jj = j - 1; jj <= j + 1; jj++)
						{
							if (ii >= 0 && ii < game_scene.width && jj >= 0 && jj < game_scene.heigth && game_scene.grid[ii][jj].sta == REV)
								game_scene.grid[ii][jj].sta = FRO;
						}
					}
				}
			}
		}
	}

	if (gameOver == 0)
	{
		mine_counter = 0;
		for (int i = 0; i < game_scene.width; i++)
		{
			for (int j = 0; j < game_scene.heigth; j++)
			{
				if (game_scene.grid[i][j].sta == FRO && game_scene.grid[i][j].texture_id == 9)
				{
					game_scene.grid[i][j].texture_id = 12;
					gameOver = 2;
					i = game_scene.width;
					break;
				}
				if (game_scene.grid[i][j].sta == FLA && game_scene.grid[i][j].texture_id == 9)
					mine_counter++;
			}
		}
		if (mine_counter == mine_num)
			gameOver = 1;
	}

	if (gameOver == 2)
	{
		for (int i = 0; i < game_scene.width; i++)
		{
			for (int j = 0; j < game_scene.heigth; j++)
			{
				if (game_scene.grid[i][j].sta != FLA && game_scene.grid[i][j].texture_id == 9)
					game_scene.grid[i][j].sta = FRO;
			}
		}
	}
}

void Game::Debug()
{
	isDebug = !isDebug;
	if (isDebug)
	{
		for (int i = 0; i < game_scene.width; i++)
		{
			for (int j = 0; j < game_scene.heigth; j++)
			{
				de_back[i][j] = game_scene.grid[i][j].sta;
				game_scene.grid[i][j].sta = FRO;
			}
		}
	}
	else
	{
		for (int i = 0; i < game_scene.width; i++)
		{
			for (int j = 0; j < game_scene.heigth; j++)
			{
				game_scene.grid[i][j].sta = de_back[i][j];
			}
		}
	}
}

void Game::GameOver()
{
	game_scene.myTimer.isRun = false;
	sOver.setTexture(tOver);
	if (gameOver == 1)
	{
		if (!isOvered)
		{
			game_scene.sPass.play();
			game_scene.bgm.stop();
			isOvered = true;
		}
		sOver.setTextureRect(IntRect(0, 0, 200, 122));
	}
	if (gameOver == 2)
	{
		if (!isOvered)
		{
			game_scene.sBoom.play();
			game_scene.bgm.stop();
			isOvered = true;
		}
		sOver.setTextureRect(IntRect(200, 0, 200, 122));
	}
	sOver.setPosition(330, 259);
	bt_restart.setPosition(338, 400);
	bt_restart.setScale(0.5, 0.5);
	bt_ok.setPosition(438, 400);
	bt_ok.setScale(0.5, 0.5);
	(*app).draw(sOver);
	bt_restart.show();
	bt_ok.show();
}

void Game::Update()
{
	if (OnStartScene)
	{
		switch (rank)
		{
		case 0:
			game_scene.width = 10;
			game_scene.heigth = 10;
			mine_num = 10;
			game_scene.LV = L"简单";
			start_scene.LV = L"简单";
			break;
		case 1:
			game_scene.width = 24;
			game_scene.heigth = 16;
			mine_num = 50;
			game_scene.LV = L"中等";
			start_scene.LV = L"中等";
			break;
		case 2:
			game_scene.width = 32;
			game_scene.heigth = 18;
			mine_num = 100;
			game_scene.LV = L"困难";
			start_scene.LV = L"困难";
			break;
		default:
			break;
		}
		mine_rest = mine_num;
		start_scene.tSkin = tSkin[skin_id];
		start_scene.Update();
	}
	game_scene.tSkin = tSkin[skin_id];
	game_scene.tBack = tBack[back_id];
	game_scene.Update();
	game_scene.mineCounter = mine_rest;
}

void Game::SetMine()
{
	if (this->MineState == 1)
	{
		int count = 0;
		int i, j;
		srand(time(0));
		while (count != this->mine_num)
		{
			i = rand() % this->game_scene.width;
			j = rand() % this->game_scene.heigth;
			if ((i - this->px) * (i - this->px) + (j - this->py) * (j - this->py) <= 2)
				continue;
			else
			{
				this->game_scene.grid[i][j].setTextureID(9);
				this->game_scene.grid[i][j].isMineSetted = true;
				count++;
			}
		}

		for (int i = 0; i < this->game_scene.width; i++)
		{
			for (int j = 0; j < this->game_scene.heigth; j++)
			{
				if (this->game_scene.grid[i][j].texture_id == 9)
				{
					if (i != 0)
					{
						if (j != 0)
							this->game_scene.grid[i - 1][j - 1].texture_id = this->game_scene.grid[i - 1][j - 1].texture_id != 9 ? (this->game_scene.grid[i - 1][j - 1].texture_id + 1) : 9;
						this->game_scene.grid[i - 1][j].texture_id = this->game_scene.grid[i - 1][j].texture_id != 9 ? (this->game_scene.grid[i - 1][j].texture_id + 1) : 9;
						this->game_scene.grid[i - 1][j + 1].texture_id = this->game_scene.grid[i - 1][j + 1].texture_id != 9 ? (this->game_scene.grid[i - 1][j + 1].texture_id + 1) : 9;
					}
					if (j != 0)
					{
						this->game_scene.grid[i][j - 1].texture_id = this->game_scene.grid[i][j - 1].texture_id != 9 ? (this->game_scene.grid[i][j - 1].texture_id + 1) : 9;
						this->game_scene.grid[i + 1][j - 1].texture_id = this->game_scene.grid[i + 1][j - 1].texture_id != 9 ? (this->game_scene.grid[i + 1][j - 1].texture_id + 1) : 9;
					}
					this->game_scene.grid[i + 1][j].texture_id = this->game_scene.grid[i + 1][j].texture_id != 9 ? (this->game_scene.grid[i + 1][j].texture_id + 1) : 9;
					this->game_scene.grid[i][j + 1].texture_id = this->game_scene.grid[i][j + 1].texture_id != 9 ? (this->game_scene.grid[i][j + 1].texture_id + 1) : 9;
					this->game_scene.grid[i + 1][j + 1].texture_id = this->game_scene.grid[i + 1][j + 1].texture_id != 9 ? (this->game_scene.grid[i + 1][j + 1].texture_id + 1) : 9;
				}
				else
					continue;
			}
		}
		this->MineState = 2;
	}
	else
		return;
}

void Game::Input_start_scene(Event& e)
{
	if (!start_scene.isOnExitLog && !start_scene.isOnMenu)
	{
		if (start_scene.bt_Enter.onClick(e))
		{
			OnStartScene = false;
			OnPlayScene = true;
		}
		if (start_scene.bt_Exit.onClick(e))
			start_scene.isOnExitLog = true;
		if (start_scene.bt_Setting.onClick(e))
			start_scene.isOnMenu = true;
	}
	if (start_scene.isOnExitLog)
	{
		if (start_scene.bt_Ok.onClick(e))
			(*app).close();
		if (start_scene.bt_Cancel.onClick(e))
			start_scene.isOnExitLog = false;
	}
	if (start_scene.isOnMenu)
	{
		if (start_scene.menu_setting.button[start_scene.menu_setting.num_button - 1].onClick(e))
			start_scene.isOnMenu = false;
		if (start_scene.menu_setting.button[0].onClick(e) && vol >= 10)
			vol -= 10;
		if (start_scene.menu_setting.button[1].onClick(e) && vol <= 90)
			vol += 10;
		if (start_scene.menu_setting.button[2].onClick(e) && rank >= 1)
			rank--;
		if (start_scene.menu_setting.button[3].onClick(e) && rank <= 1)
			rank++;
		if (start_scene.menu_setting.button[4].onClick(e))
		{
			skin_id--;
			if (skin_id < 0)
				skin_id = 5;
		}
		if (start_scene.menu_setting.button[5].onClick(e))
		{
			skin_id++;
			if (skin_id > 5)
				skin_id = 0;
		}
	}
	e.type = Event::Count;
}

void Game::Input_game_scene(Event& e)
{
	if (!game_scene.isOnExitLog && !game_scene.isOnMenu && !gameOver)
	{
		if (game_scene.bt_Back.onClick(e))
			game_scene.isOnExitLog = true;
		if (game_scene.bt_Setting.onClick(e))
			game_scene.isOnMenu = true;
		if (e.type == Event::EventType::KeyReleased && e.key.code == Keyboard::T)
		{
			std::cout << "debug!!!!!!!\n";
			Debug();
		}
		if (!isDebug)
		{
			for (int i = 0; i < game_scene.width; i++)
			{
				for (int j = 0; j < game_scene.heigth; j++)
				{
					game_scene.grid[i][j].isReadyToShow = false;
					int num = 0;
					for (int m = i - 1; m <= i + 1; m++)
					{
						if (m < 0 || m>game_scene.width - 1)
							continue;
						for (int n = j - 1; n <= j + 1; n++)
						{
							if (n < 0 || n>game_scene.heigth - 1 || (m == i && n == j))
								continue;
							if (game_scene.grid[m][n].isPressLR && game_scene.grid[i][j].sta == REV)
								game_scene.grid[i][j].isReadyToShow = true;
							if (game_scene.grid[m][n].sta == FLA || game_scene.grid[m][n].sta == WEN)
								num++;
						}
					}
					if (game_scene.grid[i][j].onCLickLR(e))
					{
						if (!game_scene.myTimer.isRun)
							game_scene.myTimer.start();
						if (num == game_scene.grid[i][j].texture_id && game_scene.grid[i][j].sta == FRO)
						{
							for (int m = i - 1; m <= i + 1; m++)
							{
								if (m < 0 || m>game_scene.width - 1)
									continue;
								for (int n = j - 1; n <= j + 1; n++)
								{
									if (n < 0 || n>game_scene.heigth - 1)
										continue;
									if (game_scene.grid[m][n].sta == REV)
										game_scene.grid[m][n].sta = FRO;
								}
							}
						}
					}
					else if (game_scene.grid[i][j].onClickLeft(e) && game_scene.grid[i][j].sta != FLA && !game_scene.grid[i][j].isClickOnce)
					{
						if (!game_scene.myTimer.isRun)
							game_scene.myTimer.start();
						game_scene.grid[i][j].isClickOnce = true;
						this->mouseClock.restart();
					}
					else if (game_scene.grid[i][j].isClickOnce)
					{
						this->mouse_timer += this->mouseClock.getElapsedTime().asMilliseconds();
						if (this->mouse_timer >= 500)
						{
							this->mouse_timer = 0;
							game_scene.grid[i][j].sta = FRO;
							game_scene.grid[i][j].isClickOnce = false;
							if (this->MineState == 0)
							{
								this->px = i;
								this->py = j;
								this->MineState = 1;
							}
						}
						else if (game_scene.grid[i][j].onClickDouble(e))
						{
							if (game_scene.grid[i][j].texture_id < 9 && game_scene.grid[i][j].sta == FRO)
							{
								for (int m = i - 1; m <= i + 1; m++)
								{
									if (m < 0 || m>game_scene.width - 1)
										continue;
									for (int n = j - 1; n <= j + 1; n++)
									{
										if (n < 0 || n>game_scene.heigth - 1)
											continue;
										if (game_scene.grid[m][n].sta == REV)
											game_scene.grid[m][n].sta = FRO;
									}
								}
							}
							game_scene.grid[i][j].isClickOnce = false;
							this->mouse_timer = 0;
						}
					}
					else if (game_scene.grid[i][j].onClickRight(e))
					{
						if (!game_scene.myTimer.isRun)
							game_scene.myTimer.start();
						if (game_scene.grid[i][j].sta == REV && mine_rest > 0)
						{
							game_scene.grid[i][j].sta = FLA;
							this->mine_rest--;
						}
						else if (game_scene.grid[i][j].sta == FLA)
						{
							game_scene.grid[i][j].sta = WEN;
							this->mine_rest++;
						}
						else if (game_scene.grid[i][j].sta == WEN)
							game_scene.grid[i][j].sta = REV;
					}
				}
			}
		}
	}
	if (game_scene.isOnExitLog)
	{
		if (game_scene.bt_Ok.onClick(e))
		{
			OnStartScene = true;;
			OnPlayScene = false;
			game_scene.isOnExitLog = false;
		}
		if (game_scene.bt_Cancel.onClick(e))
			game_scene.isOnExitLog = false;
	}
	if (game_scene.isOnMenu)
	{
		if (game_scene.menu_setting.button[game_scene.menu_setting.num_button - 1].onClick(e))
			game_scene.isOnMenu = false;
		if (game_scene.menu_setting.button[game_scene.menu_setting.num_button - 2].onClick(e))
		{
			game_scene.isOnMenu = false;
			game_scene.scene_close();
		}
		if (game_scene.menu_setting.button[0].onClick(e) && vol >= 10)
			vol -= 10;
		if (game_scene.menu_setting.button[1].onClick(e) && vol <= 90)
			vol += 10;
		if (game_scene.menu_setting.button[2].onClick(e))
		{
			skin_id--;
			if (skin_id < 0)
				skin_id = 5;
		}
		if (game_scene.menu_setting.button[3].onClick(e))
		{
			skin_id++;
			if (skin_id > 5)
				skin_id = 0;
		}
		if (game_scene.menu_setting.button[4].onClick(e))
		{
			back_id--;
			if (back_id < 0)
				back_id = 6;
		}
		if (game_scene.menu_setting.button[5].onClick(e))
		{
			back_id++;
			if (back_id > 6)
				back_id = 0;
		}
	}
	if (gameOver)
	{
		if (bt_ok.onClick(e))
		{
			OnPlayScene = false;
			OnStartScene = true;
			isOvered = false;
			gameOver = false;
		}
		if (bt_restart.onClick(e))
		{
			isOvered = false;
			gameOver = false;
			game_scene.scene_close();
		}
	}
	e.type = Event::Count;
}

void Game::draw_start_scene()
{
	start_scene.DrawBack();
	if (start_scene.isOnMenu)
		start_scene.DrawMenu();
	if (start_scene.isOnExitLog)
		start_scene.DrawExitLog();
}

void Game::draw_game_scene()
{
	game_scene.DrawBack();
	game_scene.DrawGrid();
	game_scene.TimeShow();
	game_scene.CounterShow();
	game_scene.LvShow();
	if (game_scene.isOnMenu)
		game_scene.DrawMenu();
	if (game_scene.isOnExitLog)
		game_scene.DrawExitLog();
	if (gameOver != 0)
		GameOver();
}

void Game::Run()
{
	while ((*app).isOpen())
	{
		Update();
		Event e;
		while ((*app).pollEvent(e))
		{
			if (e.type == Event::Closed)
				(*app).close();
		}
		if (OnStartScene)
		{
			if (!start_scene.isRunning)
			{
				game_scene.scene_close();
				start_scene.gameStart();
				Input = &Game::Input_start_scene;
				Draw = &Game::draw_start_scene;
			}
		}
		else if (OnPlayScene)
		{
			if (!game_scene.isRunning)
			{
				MineState = 0;
				mine_rest = mine_num;
				isDebug = false;
				start_scene.scene_close();
				game_scene.gameStart();
				Input = &Game::Input_game_scene;
				Draw = &Game::draw_game_scene;
			}
			if (!isDebug)
			{
				SetMine();
				UpdateGrid();
			}
		}
		(this->*Draw)();
		(this->*Input)(e);
		(*app).display();
	}
}
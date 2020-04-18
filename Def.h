#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<time.h>
#include<windows.h>
#include<iostream>
using namespace sf;

extern int rank;
extern int vol;
extern int skin_id;
extern int back_id;
extern int win_width;
extern int win_height;
extern int win_posX;
extern int win_posY;
extern class MyClock;
extern class Grid;
extern class Button;
extern class Menu;
extern class StartScene;
extern class GameScene;
extern class Game;
enum State{REV = 0,FRO,FLA,WEN};

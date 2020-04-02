#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<time.h>
#include<windows.h>
using namespace sf;

extern int rank;
extern int vol;
extern int skin_id;
extern int back_id;
extern class MyClock;
extern class Grid;
extern class Button;
extern class Menu;
extern class StartScene;
extern class GameScene;
extern class Game;
enum State{REV = 0,FRO,FLA};

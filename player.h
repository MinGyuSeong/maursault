#ifndef MAURSAULT_PLAYER_H
#define MAURSAULT_PLAYER_H

#include <iostream>
#include "raylib.h"
#include "Base_infomation.h"
#include"attack.h"
enum Player_Direction;

class Player
{
private:
	int hp ;
	int mp ;
	int atk ;
	int def ;
	int exp ;
	int level;

	int pos_x;
	int pos_y;

	int size_x;
	int size_y;
	Player_Direction p_direc;

	void Input_Direction();
	void Input_Attack();
public:
	Player();
	void update();
	void Draw();
	void getdamage(int damage);
};
#endif // !defined(MAURSAULT_PLAYER_H)
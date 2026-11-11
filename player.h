#ifndef MAURSAULT_PLAYER_H
#define MAURSAULT_PLAYER_H

#include <iostream>
#include "raylib.h"
#include "Base_information.h"
#include"Attack.h"
enum Player_Direction
{
	LEFT,
	RIGHT
};

class Player
{
public:
	Player();
private:
	int hp ;
	int mp ;
	int atk ;
	int def ;
	int exp ;
	int level;

	Vector2 pos;

	int size_x;
	int size_y;
	Player_Direction p_direc;

	void Input_Direction();
	void Input_Attack();
public:
	Vector2 Return_Pos();

	///

	void Update();
	void Draw();
	void Get_Damage(int damage);
};


//class Attak
//{
//public:
//	Attak();
//	~Attak();
//
//private:
//
//public:
//	virtual void Attack_Before(Player& player);
//	virtual void Attack_Motion(Player& player);
//	virtual void Attack_collision(Player& player);
//};
#endif // !defined(MAURSAULT_PLAYER_H)
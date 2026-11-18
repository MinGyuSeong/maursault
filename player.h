#ifndef MAURSAULT_PLAYER_H
#define MAURSAULT_PLAYER_H


#include "Base_information.h"
#include"Attack.h"

enum Player_Animation_State
{
	idle,
	ChangeDirection
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

	float anime_size_x;
	float anime_size_y;
	double anime_time;

	Direction p_direc;
	Texture2D Texture_player = LoadTexture("player.png");


	Player_Animation_State anme_state;

	void Input_Direction();
	void Input_Attack();

	void Anmation_AD();
public:
	Vector2 Return_Pos();
	Rectangle Return_Rect();

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
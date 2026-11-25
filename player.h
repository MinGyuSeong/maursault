#ifndef MAURSAULT_PLAYER_H
#define MAURSAULT_PLAYER_H
#include "Base_information.h"
#include"Attack.h"
class Attack;
class Base_Attack;

enum Player_Animation_State
{
	idle,
	blink,
	attack_mortar,
};

void LoadPlayer_Image();

class Player
{
public:
	Player();
private:
	int hp ;
	int maxhp;
	int mp ;
	int atk ;
	int def ;
	int exp ;
	int level;

	Vector2 pos;
	Vector2 size;

	bool ChangeDirection;

	Vector2 anime_pos;
	Vector2 anime_size;

	double anime_time;
	double anime_direc_time;

	Direction p_direc;
	Texture2D Texture_player;

	Attack* attack;
	Attack* attack_null;
	Base_Attack* base_attack;

	Player_Animation_State anme_state;

	void Input_Direction();
	void Input_Attack();
	void Input_Select_Weapon();

	void Anmation_AD();
	void Animation_Idle();
	void Animation_Blink();

	void Animation_Change_state(Player_Animation_State state);
	void Player_Ui();
public:
	Vector2 Return_Pos();
	Rectangle Return_Rect();
	Direction Return_Direc();

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
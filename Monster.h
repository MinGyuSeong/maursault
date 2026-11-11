#pragma once
#include "Base_information.h"
#include "Player.h"

enum Monster_Direction {
    LEFT,
    RIGHT
};

class Monster
{
public:
    Monster();
	~Monster();
private:
	int max_hp;
	int hp;
	int atk;

	int speed;

	Vector2 pos;
	Monster_Direction m_direc;

	int size_x;
	int size_y;
public:
	Vector2 Return_Pos();
	void Update();
	void Draw();
	
	void Get_Damage(int damage);
};


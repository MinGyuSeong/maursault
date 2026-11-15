#pragma once
#include "Base_information.h"
#include "Player.h"

class Player;


enum Monster_State;

class Monster
{
public:
    Monster(Vector2 position, Direction direction);
	~Monster();
protected:
	int max_hp;
	int hp;
	int atk;

	float speed;

	float attack_range;
	double attack_coolTime;
	double attack_timer;

	Vector2 pos;
	Direction m_direc;
	Monster_State m_state;

	int size_x;
	int size_y;
public:
	Rectangle Return_Rect();
	Vector2 Return_Pos();

	void Update(Player& player);
	void Draw();

	virtual void MoveState(Player& player);
	virtual void Attack_State(Player& player);
	virtual void Die_State(Player& player);

	virtual void Attack_Player(Player& player);

	void Get_Damage(int damage);
};

class Monster_Robot : public Monster {
public:
	Monster_Robot(Vector2 position,Direction direction);
	~Monster_Robot();
private:
	virtual void MoveState(Player& player) override;
	virtual void Attack_State(Player& player) override;
	virtual void Die_State(Player& player) override;

	virtual void Attack_Player(Player& player) override;
};

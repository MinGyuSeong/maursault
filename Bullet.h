#pragma once
#include "Base_information.h"
#include "Monster.h"

class Monster;

void draw_bullets();
void update_bullets();
void collision_bullets(Monster& monster);

struct Vector2_double
{
	double x;
	double y;
};

class Bullet
{
public:
	Bullet(Vector2 pos, Vector2 direction);
	~Bullet();
protected:
	int atk;
	float speed;

	Vector2 pos;
	Vector2 direction;
	Vector2_double direction_unit;

	int size_x;
	int size_y;

	std::map<Monster*, double> checkcol;
	double atk_cooltime;

	Vector2_double Unit_Vector(Vector2& direction);
public:
	virtual void Move();//총알이 낭아가는 경로 함수
	virtual void collision(Monster& monster);//몬스터와의 충돌 체크 미완

	void Update();//
	void Draw();
};


class Bullet_Mortar :public Bullet
{
public:
	Bullet_Mortar(Vector2 pos, Vector2 direction);
	~Bullet_Mortar();
private:
	float speed_y;
	float gravity;
public:
	virtual void Move() override;
	virtual void collision(Monster& monster) override;
};


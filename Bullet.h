#pragma once
#include "Base_information.h"
#include "Monster.h"

class Monster;

void draw_bullets();
void update_bullets();

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

	Vector2_double Unit_Vector(Vector2& direction);
public:
	virtual void Move();
	virtual void collision(Monster& monster);

	void Update();
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


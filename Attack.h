#ifndef MAURSAULT_ATTACK_H
#define MAURSAULT_ATTACK_H
#include "Base_information.h"
#include "Player.h"
#include "Bullet.h"

//class Player;

class Player;

class Attack
{
public:
	Attack(){}
	~Attack(){}
private:

public:
	virtual void Attack_Before(Player& player);//공격하기전 보여주는 ui 공격 마크
	virtual void Attack_(Player& player);//플레이어에서 인풋시 실행 공격 (불렛 생성)
	virtual void Attack_collision(Player& player);//만들어 놓고 안씀 왜만들었지?
	
	void update(Player& player);
	void draw();//만들어 놓고 안씀 쓸데가 없음
};
///////////////
class Base_Attack : public Attack {
public:
	Base_Attack(){}
	~Base_Attack(){}
private:
public:
	virtual void Attack_Before(Player& player) override;
	virtual void Attack_(Player& player) override;
	virtual void Attack_collision(Player& player) override;
};

class Push_Attack : public Attack {
public:
	Push_Attack() {}
	~Push_Attack() {}
private:
public:
	virtual void Attack_Before(Player& player) override;
	virtual void Attack_(Player& player) override;
	virtual void Attack_collision(Player& player) override;
};

#endif
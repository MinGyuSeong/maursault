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
	virtual void Attack_Before(Player& player);
	virtual void Attack_(Player& player);
	virtual void Attack_collision(Player& player);
	
	void update(Player& player) {
		Attack_Before(player);
		Attack_(player);
		Attack_collision(player);
	}
	void draw();
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

#endif
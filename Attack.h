#ifndef MAURSAULT_ATTACK_H
#define MAURSAULT_ATTACK_H
#include "Base_information.h"
#include "Player.h"




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
	virtual void Attack_Motion(Player& player);
	virtual void Attack_collision(Player& player);
	
	void update(Player& player) {
		Attack_Before(player);
		Attack_Motion(player);
		Attack_collision(player);
	}
	virtual void draw() {

	}
};
///////////////

class Base_Attack : public Attack {
public:
	Base_Attack(){}
	~Base_Attack(){}
private:
public:
	virtual void Attack_Before(Player& player) override;
	virtual void Attack_Motion(Player& player) override;
	virtual void Attack_collision(Player& player) override;
	virtual void draw()override;
};




#endif
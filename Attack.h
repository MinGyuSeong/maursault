#pragma once//header guard
//https://gdngy.tistory.com/177 상속 개념 한번 볼것 
//이해안되면 묻고

#include <iostream>
#include "raylib.h"
#include <vector>
#include <math.h>

#include"player.h"


class Attack
{
private:
	int atk;
	int atk_cooltime;


	bool atk_state;
public:
	Attack();

	void draw();
	void update();
};


class Base_Attack :Attack {
private:
	
public:
	Base_Attack();
	void draw();
	void update();
};




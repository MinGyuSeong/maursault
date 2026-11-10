#include <iostream>
#include "raylib.h"
#include "Player.h"
enum Player_Direction
{
	right,
	left
};


Player::Player()
	:hp(100), mp(100), atk(10), def(0), exp(0), level(0), p_direc(Player_Direction::right)
	,pos_x(100), pos_y(100),size_x(100),size_y(100) {

}


void Player::Input_Direction() {
	if (IsKeyPressed(KEY_A)) {
		p_direc = Player_Direction::right;
	}
	else if (IsKeyPressed(KEY_B)) {
		p_direc = Player_Direction::left;
	}
}

void Player::Atack(){

}



void Player::update() {
	p_direc = Player_Direction::right;
}

void Player::Draw() {
	DrawRectangle(pos_x,pos_y, size_x, size_y,BLACK);
	//DrawTexturePro();
}

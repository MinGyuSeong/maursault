#include "Player.h"

enum Player_Direction
{
	right,
	left
};

Player::Player()
	:hp(100), mp(100), atk(10), def(0), exp(0), level(0), p_direc(Player_Direction::right)
	, pos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 +200}), size_x(100), size_y(100) {
}


void Player::Input_Direction() {
	if (IsKeyPressed(KEY_A)) {
		p_direc = Player_Direction::right;
	}
	else if (IsKeyPressed(KEY_B)) {
		p_direc = Player_Direction::left;
	}
}
//
Vector2 Player::Return_Pos() {
	return pos;
}



//

void Player::Update() {
	Base_Attack attack;
	attack.Attack_Before(*this);
	p_direc = Player_Direction::right;
}

void Player::Draw() {
	DrawRectangle(pos.x,pos.y, size_x, size_y,BLACK);
	//DrawTexturePro();
}


void Player::Get_Damage(int damage) {
	hp -= damage;
	if (hp < 0) {
		hp = 0;
	}
}

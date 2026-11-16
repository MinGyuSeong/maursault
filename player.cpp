#include "Player.h"


Player::Player()
	:hp(100), mp(100), atk(10), def(0), exp(0), level(0), p_direc(Direction::RIGHT)
	, pos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 +200}), size_x(100), size_y(100) {
}


void Player::Input_Direction() {
	if (IsKeyPressed(KEY_A)) {
		p_direc = Direction::RIGHT;
	}
	else if (IsKeyPressed(KEY_B)) {
		p_direc = Direction::LEFT;
	}
}

void Player::Input_Attack() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Base_Attack attack;
		attack.Attack_(*this);
	}//공격 실행 attack을 실행
}

//
Vector2 Player::Return_Pos() {
	return pos;
}
Rectangle Player::Return_Rect() {
	return { pos.x, pos.y, (float)size_x, (float)size_y };
}


//
void Player::Update() {
	Base_Attack attack;
	attack.Attack_Before(*this);
	Input_Attack();//에택 다양한 무기로 공격할 예정
	//기초 미완
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

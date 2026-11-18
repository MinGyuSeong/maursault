#include "Player.h"

Player::Player()
	:hp(100), mp(100), atk(10), def(0), exp(0), level(0), p_direc(Direction::RIGHT)
	, pos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 +200}), size_x(300), size_y(300) {
	//Texture_player = Load_Texture_player;
	anime_size_x = size_x;
	anime_size_y = size_y;
	anime_time = 0;
}

void Player::Input_Direction() {
	if (IsKeyPressed(KEY_A)) {
		p_direc = Direction::RIGHT;
		anme_state = ChangeDirection;
	}
	else if (IsKeyPressed(KEY_D)) {
		p_direc = Direction::LEFT;
		anme_state = ChangeDirection;
	}
}
void Player::Input_Select_Weapon() {
	if (IsKeyPressed(KEY_KP_1)) {
		attack = base_attack;
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
	return { pos.x - (float)size_x/2, pos.y- (float)size_y ,
		(float)size_x, (float)size_y };
}


//
void Player::Update() {
	Input_Direction();
	Base_Attack attack;
	attack.Attack_Before(*this);
	Input_Attack();//에택 다양한 무기로 공격할 예정
	//기초 미완
}

void Player::Get_Damage(int damage) {
	hp -= damage;
	if (hp < 0) {
		hp = 0;
	}	
}
/////////////////////////////////


void Player::Anmation_AD() {
	double time = 0.3f;
	if (anme_state != ChangeDirection) {
		return;
		std::cout << "A" << std::endl;
	}
	if (anime_time < time) {
		anime_time += GetFrameTime();
		std::cout << anime_time<<"B" << std::endl;
	}
	else
	{
		anime_size_y = size_y;
		anime_time = 0;
		anme_state = idle;
		std::cout << "C" << std::endl;
	}

	std::cout << "anime" << std::endl;
	if (anime_time < 0.1) {
		anime_size_y -= 50 * GetFrameTime();
	}
	else if (anime_time < 0.2) {
		anime_size_y -= 100 * GetFrameTime();
	}
	else if (anime_time < 0.3) {
		anime_size_y += 110 * GetFrameTime();
	}
}

void Player::Draw() {
	//DrawRectangle(pos.x, pos.y, size_x, size_y, BLACK);
	Anmation_AD();
	//DrawTexturePro();
	
	int direction = 1;
	if (p_direc == Direction::LEFT)
		direction = -1;
	else
		direction = 1;

	DrawTexturePro(Texture_player,
		{ 0,0,768.0f * direction,768 },
		{ pos.x,pos.y,(float)anime_size_y,(float)anime_size_y },
		{ (float)size_x / 2 ,(float)size_y }, 0.0f, WHITE);
}

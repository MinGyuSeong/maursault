#include "Player.h"

Texture2D Texture_playeridle;
Texture2D Texture_playerattack_motar;
Texture2D Texture_playerattack_blink;

void LoadPlayer_Image() {
	Texture_playeridle = LoadTexture("player.png");
	Texture_playerattack_motar = LoadTexture("player_motar.png");
	Texture_playerattack_blink = LoadTexture("blink.png");
}

Player::Player()
	:hp(100), maxhp(100), mp(100), atk(10), def(0), exp(0), level(0), p_direc(Direction::RIGHT)
	, pos({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 +200}),
	size{300,300},
	Texture_player(Texture_playerattack_blink){
	//Texture_player = Load_Texture_player;

	anime_size = size;
	anime_time = 0;

	this->attack = new Attack();
	this->base_attack = new Base_Attack();
	this->attack_null = new Attack();
	this->hp = maxhp;
	ChangeDirection = false;
}

void Player::Input_Direction() {
	if (IsKeyPressed(KEY_A)) {
		p_direc = Direction::RIGHT;
		ChangeDirection=true;
	}
	else if (IsKeyPressed(KEY_D)) {
		p_direc = Direction::LEFT;
		ChangeDirection = true;
	}
}
void Player::Input_Select_Weapon() {
	if (IsKeyPressed(KEY_ONE)) {
		Texture_player =Texture_playerattack_motar;
		attack = base_attack;
		Animation_Change_state(attack_mortar);
	}
	if (IsKeyPressed(KEY_ZERO)) {
		Texture_player = Texture_playerattack_blink;
		attack = attack_null;
		Animation_Change_state(idle);
	}
}

void Player::Input_Attack() {   
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		attack->Attack_(*this);
	}//공격 실행 attack을 실행
}

//
Vector2 Player::Return_Pos() {
	return pos;
}
Direction Player::Return_Direc() {
	return p_direc;
}
Rectangle Player::Return_Rect() {
	//DrawRectangle(pos.x - (float)size_x / 2, pos.y - (float)size_y,
	//	(float)size_x, (float)size_y,RED);

	return { pos.x - (float)size.x/2, pos.y- (float)size.y ,
		(float)size.x, (float)size.y};
}


//
void Player::Update() {
	Input_Direction();
	attack->Attack_Before(*this);
	Input_Select_Weapon();
	Player_Ui();
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
	if (!ChangeDirection) {
		return;
		//std::cout << "A" << std::endl;
	}
	if (anime_direc_time < time) {
		anime_direc_time += GetFrameTime();
	}
	else
	{
		anime_size = size;
		anime_direc_time = 0;
		ChangeDirection = false;
	}

	std::cout << "anime" << std::endl;
	if (anime_direc_time < 0.1) {
		anime_size.x -= 5 * GetFrameTime();
		anime_size.y -= 100 * GetFrameTime();
	}
	else if (anime_direc_time < 0.2) {
		anime_size.x -= 10 * GetFrameTime();
		anime_size.y -= 150 * GetFrameTime();
	}
	else if (anime_direc_time < 0.3) {
		anime_size.x += 30 * GetFrameTime();
		anime_size.y += 200 * GetFrameTime();
	}
}

void Player::Animation_Idle() {
	if (anme_state != idle) {
		return;
	}
	if (anime_time>5.0f) {
		Animation_Change_state(blink);
	}
	anime_time += GetFrameTime();
	anime_pos.x = 0;
	anime_pos.y = 0;
}
void Player::Animation_Blink() {
	if (anme_state != blink) {
		return;
	}
	Texture_player = Texture_playerattack_blink;
	anime_pos.x = 0;
	anime_pos.y = 0;

	if (anime_time < 0.1f) {
		anime_pos.x = 768;//1
	}
	else if (anime_time < 0.2f) {
		anime_pos.x = 768+768;//2
	}
	else if (anime_time < 0.3f)
	{
		anime_pos.x += 768 + 768 + 768;//3
	}
	else if (anime_time < 0.4f) {
		anime_pos.x += 768 + 768 + 768 + 768;//4
	}
	else if (anime_time < 0.6f) {
		anime_pos.x += 768 + 768 + 768 + 768 + 768;//5
	}
	else if (anime_time < 0.7f) {
		anime_pos.x += 768 + 768 + 768 + 768;//4
	}
	else if (anime_time < 0.8f)
	{
		anime_pos.x += 768 + 768 + 768;//3
	}
	else if (anime_time < 0.9f) {
		anime_pos.x = 768 + 768;//2
	}
	else if (anime_time < 1.0f) {
		anime_pos.x = 768;//1
	}
	else if (anime_time < 1.1f) {
		Animation_Change_state(idle);//1
	}
	anime_time += GetFrameTime();
}

void Player::Animation_Change_state(Player_Animation_State state) {
	anime_pos.x = 0;
	anime_pos.y = 0;
	anime_time = 0;

	anme_state = state;
}

void Player::Draw() {
	//DrawRectangle(pos.x, pos.y, size_x, size_y, BLACK);
	Anmation_AD();
	Animation_Idle();
	Animation_Blink();
	//DrawTexturePro();
	
	int direction = 1;
	if (p_direc == Direction::LEFT)
		direction = -1;
	else
		direction = 1;

	DrawTexturePro(Texture_player,
		{ anime_pos.x,anime_pos.y,
		768.0f * direction,768 },
		{ pos.x,pos.y,(float)anime_size.x,(float)anime_size.y },
		{ (float)anime_size.x / 2 ,(float)anime_size.y }, 0.0f, WHITE);
	if (Get_Draw_Collider()) {
		std::cout << "Draw_Collider player" << std::endl;
		DrawRectangleLinesEx(
			{
				pos.x - (float)anime_size.x / 2,
				pos.y - (float)anime_size.y ,
				(float)anime_size.x,(float)anime_size.y
			},3,RED
		);
		DrawCircle(
			pos.x,
			pos.y,
			10,RED);
	}

}

void Player::Player_Ui() {
	//full hp
	DrawRectanglePro(
		{ 70, 70, 500 , 50 },
		{ 0, 0 }, 0, GRAY
	);

	//current hp
	DrawRectanglePro(
		{ 70, 70, (float)hp / maxhp * 500 , 50 },
		{ 0, 0 }, 0, RED
	);
}
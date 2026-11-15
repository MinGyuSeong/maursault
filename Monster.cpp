#include "Monster.h"

//enum Monster_Direction 
//{
//	RIGHT,
//	LEFT
//};
enum Monster_State
{
	MOVE,
	ATTACK,
	DIE
};

Monster::Monster(Vector2 position, Direction direction) : max_hp(100), hp(100), atk(10),
speed(5.0f), attack_range(5.0f), pos(position), m_direc(direction) {

}
Monster::~Monster() {}

void Monster::MoveState(Player& player) {}
void Monster::Attack_State(Player& player) {}
void Monster::Die_State(Player& player) {}


void Monster::Attack_Player(Player& player) {}

Rectangle Monster::Return_Rect() {
	return { pos.x, pos.y, (float)size_x, (float)size_y };
}

void Monster::Update(Player& player) {
	MoveState(player);
	Attack_State(player);
	Die_State(player);
}
void Monster::Draw() {
	if (Monster_State::DIE == m_state) {
		return;
	}
	DrawRectangle(pos.x, pos.y, size_x, size_y, RED);
}

void Monster::Get_Damage(int damage) {
	hp -= damage;
	if (hp < 0) {
		hp = 0;
	}
}

#pragma region Monster_Robot
/// 
Monster_Robot::Monster_Robot(Vector2 position, Direction direction)
	:Monster(position, direction) {
	this->max_hp = 100;
	this->atk = 10;
	this->speed = 5;

	this->attack_range = 110;
	this->attack_coolTime = 4;

	this->size_x = 100;
	this->size_y = 100;

	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->m_direc = direction;
	this->m_state = MOVE;
}

Monster_Robot::~Monster_Robot() {}

void Monster_Robot::MoveState(Player& player) {
	if (m_state != MOVE)
	{
		return;
	}
	if(m_direc == RIGHT) {
		pos.x += speed;
	} else {
		pos.x -= speed;
	}
	if (player.Return_Pos().x <= pos.x + attack_range||
		player.Return_Pos().x >= pos.x - attack_range) {
		m_state = ATTACK;
		attack_timer = attack_coolTime/2;//선 공격 쿨타임
	}
}
void Monster_Robot::Attack_State(Player& player) {
	if (m_state != ATTACK)
	{
		return;
	}
	if (player.Return_Pos().x > pos.x + attack_range ||
		player.Return_Pos().x < pos.x - attack_range) {
		m_state = MOVE;
		return;
	}
	if (attack_timer >= attack_coolTime) {
		//std::cout << "Getcool" << std::endl;
		attack_timer = 0;
		Attack_Player(player);
		return;
	}
	attack_timer += GetFrameTime();
}
void Monster_Robot::Die_State(Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Robot::Attack_Player(Player& player) {
	Rectangle player_rect = player.Return_Rect();
	Rectangle monster_rect = Return_Rect();
	if (CheckCollisionRecs(player_rect, monster_rect)) {
		player.Get_Damage(atk);
		//std::cout << "Monster Attack Player" << std::endl;
		return;
	}
	//std::cout << "Try Attack" << std::endl;
	return;
}
#pragma endregion

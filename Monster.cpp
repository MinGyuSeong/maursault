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

/*
move 스테이트가 아닐때 실행안함
방향에 따라 한쪽으로 계속 움직임 
사정거리안에 플레이어가 있으면
Attack_State변경
*/
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

/*
attack state가 아닐때 실행안함
거리가 멀어지면 movestate로 변경 
쿨타임 제기 시작
쿨이 돌때마다 플레이어 공격

거리가 멀어지면 movestate로 변경 
*/
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
//주금
void Monster_Robot::Die_State(Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

/*플레이어 공격로직
플레이어 사각형 가져오기 
몬스터 사각형 가져오기 
퉁돌이면 데미지

인데 "몬스터 사각형 가져오기"이걸 
공격 collision 을 따로 만드는 방식으로 바꿀거임
*/

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

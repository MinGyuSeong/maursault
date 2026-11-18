#include "Monster.h"


//enum Monster_Direction 
//{
//	RIGHT,
//	LEFT
//};
Texture2D Texture_monsters;
void LoadMonster_Image() {
	Texture_monsters = LoadTexture("monster.png");
}

std::vector<Monster*> monsters;
void draw_monsters() {
	for (auto monster : monsters) {
		monster->Draw();
	}
}
void update_monsters(Player& player) {
	for (auto monster : monsters) {
		monster->Update(player);
	}
}
void spawn_monster() {
	monsters.push_back(new Monster_Robot({ 0, WINDOW_HEIGHT / 2 + 200 },
		Direction::RIGHT));
	monsters.push_back(new Monster_Robot({ 1980, WINDOW_HEIGHT / 2 + 200 },
		Direction::LEFT));
}

std::vector<Monster*> return_monsters() {
	return monsters;
}

enum Monster_State
{
	MOVE,
	ATTACK,
	DIE
};

Monster::Monster(Vector2 position, Direction direction) :
	max_hp(100), hp(100), atk(10),
speed(5.0f), attack_range(5.0f), 
pos(position), m_direc(direction),
Texture_monster(Texture_monsters),
size({100,100}),
anime_size({ 100,100 })
{

}
Monster::~Monster() {}

void Monster::MoveState(Player& player) {}
void Monster::Attack_State(Player& player) {}
void Monster::Die_State(Player& player) {}

void Monster::Attack_Player(Player& player) {}

void Monster::Draw_anime() {}
Rectangle Monster::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
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
	Draw_anime();
	//DrawRectangle(pos.x, pos.y, size_x, size_y, RED);
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

	this->size={ 196 / 2, 486 / 2 };


	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;

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
	if (m_direc == RIGHT) {
		pos.x += speed;
	}
	else {
		pos.x -= speed;
	}
	if (player.Return_Pos().x <= pos.x + attack_range ||
		player.Return_Pos().x >= pos.x - attack_range) {
		m_state = ATTACK;
		attack_timer = attack_coolTime / 2;//선 공격 쿨타임
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

Rectangle Monster_Robot::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
}

void Monster_Robot::Draw_anime() {
	int direction = 1;
	if (m_direc == RIGHT) {
		direction = -1;
	}

	if (m_state) {
		anime_rotate = 0;
		anime_timer = 0;
	}
	else {
		if (anime_timer < 0.3) {
			anime_rotate = -5;
		}
		else if (anime_timer < 0.6) {
			anime_rotate = 5;
		}
		else if (anime_timer > 0.8)
		{
			anime_timer = 0;
		}

		if (anime_timer > 0.2 && anime_timer <= 0.2999) {
			std::cout << anime_timer << "a" << std::endl;
			anime_size.x -= 50 * GetFrameTime();
			anime_size.y -= 300 * GetFrameTime();
		}
		else if (anime_timer > 0.32 && anime_timer<0.4){
			std::cout << anime_timer << "b" << std::endl;
			anime_size.x = size.x;
			anime_size.y = size.y;
		}
		else if(anime_timer > 0.5 && anime_timer <= 0.5999) {
			std::cout << anime_timer << "c" << std::endl;
			anime_size.x -= 50 * GetFrameTime();
			anime_size.y -= 300 * GetFrameTime();
		}
		else if (anime_timer > 0.62 && anime_timer <0.7 ) {
			std::cout << anime_timer << "d" << std::endl;
			anime_size.x = size.x;
			anime_size.y = size.y;
		}
		
	}
	
	DrawTexturePro(Texture_monster,
		{ 291 ,711,
		(float)196 * direction,486 },
		{ pos.x, pos.y, anime_size.x, anime_size.y },
		{ 196 / 4,486 / 2 }, anime_rotate, WHITE);


	anime_timer += GetFrameTime();
}


#pragma endregion
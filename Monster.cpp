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
enum Monster_type
{
	FISH
};

struct Monster_spawn
{
	Monster_type type;
	Vector2 pos;
	Direction dir;
};
static std::vector<Monster_spawn> monster_spawn;

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

	monsters.push_back(new Monster_Wizard({ 1980, WINDOW_HEIGHT / 2 + 200 },
		Direction::LEFT));

	//monsters.push_back(new Monster_Fish({ 0, WINDOW_HEIGHT / 2 + 200 },
	//	Direction::RIGHT));
	//monsters.push_back(new Monster_Fish({ 1980, WINDOW_HEIGHT / 2 + 200 },
	//	Direction::LEFT));

	monsters.push_back(new Monster_Dog({ 0, WINDOW_HEIGHT / 2 + 200 },
		Direction::RIGHT));
	monsters.push_back(new Monster_Dog({ 1980, WINDOW_HEIGHT / 2 + 200 },
		Direction::LEFT));


	if (!monster_spawn.empty()) {
		Monster_spawn monster =monster_spawn.back();
		monster_spawn.pop_back();
		monsters.push_back(new Monster_Fish(monster.pos, monster.dir));
	}
}

void spawn_fish(Vector2 pos_ ,Direction direc) {

	monsters.push_back(new Monster_Fish(pos_ , direc));
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
	size({ 100,100 }),
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

	this->size = { 196 / 2, 486 / 2 };


	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;
	this->anime_rotate = 0;

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
	player.Get_Damage(atk);
	std::cout << "Monster Attack Player" << std::endl;
	return;
	//std::cout << "Try Attack" << std::endl;
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
			anime_size.x -= 50 * GetFrameTime();
			anime_size.y -= 300 * GetFrameTime();
		}
		else if (anime_timer > 0.32 && anime_timer < 0.4) {
			anime_size.x = size.x;
			anime_size.y = size.y;
		}
		else if (anime_timer > 0.5 && anime_timer <= 0.5999) {
			anime_size.x -= 50 * GetFrameTime();
			anime_size.y -= 300 * GetFrameTime();
		}
		else if (anime_timer > 0.62 && anime_timer < 0.7) {
			anime_size.x = size.x;
			anime_size.y = size.y;
		}
	}

	DrawTexturePro(Texture_monster,
		{ 291 ,711,
		(float)196 * direction,486 },
		{ pos.x, pos.y + 95, anime_size.x, anime_size.y },
		{ 196 / 4,486 / 2 }, anime_rotate, WHITE);


	anime_timer += GetFrameTime();
}


#pragma endregion

#pragma region Monster_Wizard
/// 
Monster_Wizard::Monster_Wizard(Vector2 position, Direction direction)
	:Monster(position, direction) {
	this->max_hp = 90;
	this->atk = 18;
	this->speed = 8;

	this->attack_range = 380;
	this->attack_coolTime = 4;

	this->size = { 159 / 2, 220 / 2 };

	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;
	this->anime_rotate = 0;
	this->m_direc = direction;
	this->m_state = MOVE;
	this->attack = false;
}

Monster_Wizard::~Monster_Wizard() {}

void Monster_Wizard::MoveState(Player& player) {
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

void Monster_Wizard::Attack_State(Player& player) {
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
void Monster_Wizard::Die_State(Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Wizard::Attack_Player(Player& player) {
	monster_spawn.push_back(Monster_spawn(FISH, pos, m_direc));

	std::cout << "Monster Attack Player Get Fish " << std::endl;
	return;
	//std::cout << "Try Attack" << std::endl;
}

Rectangle Monster_Wizard::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
}

void Monster_Wizard::Draw_anime() {
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
			anime_size.x -= 50 * GetFrameTime();
			anime_size.y -= 300 * GetFrameTime();
		}
		else if (anime_timer > 0.32 && anime_timer < 0.4) {
			anime_size.x = size.x;
			anime_size.y = size.y;
		}
		else if (anime_timer > 0.5 && anime_timer <= 0.5999) {
			anime_size.x -= 50 * GetFrameTime();
			anime_size.y -= 300 * GetFrameTime();
		}
		else if (anime_timer > 0.62 && anime_timer < 0.7) {
			anime_size.x = size.x;
			anime_size.y = size.y;
		}

	}

	if (m_state == ATTACK) {
		attack = false;
	}
	else {
		attack = true;
	}


	if (attack == true) {
		DrawTexturePro(Texture_monster,
			{ 1271, 1139,
			(float)159 * direction,224 },
			{ pos.x, pos.y + 120, anime_size.x, anime_size.y },
			{ 196 / 4,486 / 2 }, anime_rotate, WHITE);
		anime_timer += GetFrameTime();
	}
	else if (attack == false) {
		DrawTexturePro(Texture_monster,
			{ 830, 1153,
			(float)381 * direction,216 },
			{ pos.x, pos.y + 120, anime_size.x, anime_size.y },
			{ 196 / 4,486 / 2 }, anime_rotate, WHITE);
		anime_timer += GetFrameTime();
	}
}

#pragma endregion

#pragma region Monster_Fish
/// 
Monster_Fish::Monster_Fish(Vector2 position, Direction direction)
	:Monster(position, direction) {
	this->max_hp = 20;
	this->atk = 30;
	this->speed = 12;

	this->attack_range = 0;
	this->attack_coolTime = 2;

	this->size = { 225 / 2, 84 / 2 };


	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;

	this->m_direc = direction;
	this->m_state = ATTACK;
}

Monster_Fish::~Monster_Fish() {}

void Monster_Fish::MoveState(Player& player) {
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

void Monster_Fish::Attack_State(Player& player) {
	if (m_state != ATTACK) {
		return;
	}	
	std::cout << "Monster Attack Player Fish s" << std::endl;
	//std::cout << "Monster Attack Player Fish sadafda" << std::endl;
	if (m_direc == RIGHT) {
		pos.x += speed;
	}
	else {
		pos.x -= speed;
	}

	if (player.Return_Pos().x < pos.x + 4 &&
		player.Return_Pos().x > pos.x - 4) {
		player.Get_Damage(atk);
	}
	return;
}
void Monster_Fish::Die_State(Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Fish::Attack_Player(Player& player) {

	return;
}

Rectangle Monster_Fish::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
}

void Monster_Fish::Draw_anime() {
	int direction = 1;
	if (m_direc == RIGHT) {
		direction = -1;
	}

	DrawTexturePro(Texture_monster,
		{ 391 ,1293,
		(float)225 * direction,84 },
		{ pos.x, pos.y-100 , anime_size.x, anime_size.y },
		{ 0 ,0 }, 0, WHITE);

	anime_timer += GetFrameTime();
}
#pragma endregion

#pragma region Monster_Dog
Monster_Dog::Monster_Dog(Vector2 position, Direction direction)
	:Monster(position, direction) {
	this->max_hp = 180;
	this->atk = 13;
	this->speed = 4;

	this->attack_range = 100;
	this->attack_coolTime = 5;

	this->size = { 484 / 3.8, 241 / 3.8 };


	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;

	this->m_direc = direction;
	this->m_state = MOVE;
}

Monster_Dog::~Monster_Dog() {}

void Monster_Dog::MoveState(Player& player) {
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

void Monster_Dog::Attack_State(Player& player) {
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
void Monster_Dog::Die_State(Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Dog::Attack_Player(Player& player) {
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

Rectangle Monster_Dog::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
}

void Monster_Dog::Draw_anime() {
	int direction = 1;
#pragma region anime
	if (m_direc == RIGHT) {
		direction = -1;
	}

	if (m_state) {
		//anime_rotate = 0;
		anime_timer = 0;
	}
	else {
		if (anime_timer < 0.4) {
			if (anime_rotate == 12) {
				anime_size.x = size.x;
				anime_size.y = size.y;
			}
			anime_rotate = -2;
		}
		else if (anime_timer < 0.8) {
			if (anime_rotate == -2) {
				anime_size.x = size.x;
				anime_size.y = size.y;
			}
			anime_rotate = 12;
		}
		else{
			anime_timer = 0;
		}

		if (anime_timer > 0.35 && anime_timer < 0.4){
			anime_size.y -= 100 * GetFrameTime();
		}
		if (anime_timer > 0.75 && anime_timer < 0.8) {
			anime_size.y -= 100 * GetFrameTime();
		}

	}
#pragma endregion

	DrawTexturePro(Texture_monster,
		{ 616, 726,
		(float)484 * direction, 241},
		{ pos.x, pos.y, 
		anime_size.x, anime_size.y },
		{ anime_size.x / 2, anime_size.y },
		anime_rotate, WHITE);

	if (Get_Draw_Collider()) {
		std::cout << "Draw_Collider player" << std::endl;
		DrawRectangleLinesEx(
			{
				pos.x - anime_size.x / 2,
				pos.y - anime_size.y ,
				anime_size.x,
				anime_size.y
			}, 3, RED
		);
		DrawCircle(
			pos.x,
			pos.y,
			10, RED);
	}

	anime_timer += GetFrameTime();
}
#pragma endregion
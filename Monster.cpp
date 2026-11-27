#include "Monster.h"

//enum Monster_Direction 
//{
//	RIGHT,
//	LEFT
//};
Texture2D Texture_monsters;

Texture2D Texture_monster_Dog;
Texture2D Texture_monster_Wizard;
Texture2D Texture_monster_Golam;
void LoadMonster_Image() {
	Texture_monsters = LoadTexture("monster.png");
	Texture_monster_Dog = LoadTexture("dog.png");
	Texture_monster_Wizard = LoadTexture("wizard.png");
	Texture_monster_Golam = LoadTexture("golam.png");
}

std::vector<Monster*> monsters;
enum Monster_type
{
	FISH
};

enum Monster_State
{
	MOVE,
	ATTACK,
	DIE
};

struct Monster_spawn
{
	Monster_type type;
	Vector2 pos;
	Direction dir;
};

static std::vector<Monster_spawn> monster_spawn;

void draw_monsters(float dt) {
	for (auto monster : monsters) {
		monster->Draw( dt);
	}
}
void update_monsters(float dt, Player& player) {
	for (auto monster : monsters) {
		monster->Update(dt,player);
	}
}
void Monster::Get_Force(Vector2 add_force) {
	get_force = add_force;
}
void Monster::Update_Force(float dt) {
	if ((abs(get_force.x) < 3 && abs(get_force.y) < 3)) {
		get_force.x = 0;
		get_force.y = 0;
		return;
	}

	pos.x += get_force.x *dt;
	pos.y += get_force.y *dt;

	if (get_force.x > 0) {
		get_force.x -= get_force.x / 100;
	}
	else
	{
		get_force.x += get_force.x / 100;
	}

	if (get_force.y > 0) {
		get_force.y -= get_force.y / 100;
	}
	else
	{
		get_force.y += get_force.y / 100;
	}
}
void spawn_monster() {
	monsters.push_back(new Monster_Golam({ 0, WINDOW_HEIGHT / 2 + 200 },
		Direction::RIGHT));

	monsters.push_back(new Monster_Golam({ 1980, WINDOW_HEIGHT / 2 + 200 },
		Direction::LEFT));

	monsters.push_back(new Monster_Wizard({ 1980, WINDOW_HEIGHT / 2 + 200 },
		Direction::LEFT));
	//monsters.push_back(new Monster_Wizard({ 0, WINDOW_HEIGHT / 2 + 200 },
	//	Direction::RIGHT));

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

std::vector<Monster*> return_monsters() {
	return monsters;
}

Monster::Monster(Vector2 position, Direction direction) :
	max_hp(100), hp(100), atk(10),
	speed(5.0f), attack_range(5.0f),
	pos(position), m_direc(direction),
	Texture_monster(Texture_monsters),
	size({ 100,100 }),
	anime_size({ 100,100 }) {}
Monster::~Monster() {}

void Monster::MoveState(float dt, Player& player) {}
void Monster::Attack_State(float dt, Player& player) {}
void Monster::Die_State(float dt, Player& player) {}

void Monster::Attack_Player(float dt, Player& player) {}

void Monster::Draw_anime(float dt) {}
Rectangle Monster::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
}

void Monster::Update(float dt, Player& player) {
	MoveState(dt,player);
	Attack_State(dt,player);
	Die_State(dt,player);

	//
	Update_Force(dt);
}
void Monster::Draw(float dt) {
	if (Monster_State::DIE == m_state) {
		return;
	}
	Draw_anime(dt);
	//DrawRectangle(pos.x, pos.y, size_x, size_y, RED);
}

void Monster::Get_Damage(int damage) {
	hp -= damage;

	if (hp < 0) {
		hp = 0;
	}
}

#pragma region Monster_Golam
/// 
Monster_Golam::Monster_Golam(Vector2 position, Direction direction)
	:Monster(position, direction) {
	this->max_hp = 100;
	this->atk = 10;
	this->speed = 5;

	this->attack_range = 110;
	this->attack_coolTime = 4;

	this->size = { 191 *1.2 / 2, 285 *1.2 / 2 };

	this->Texture_monster = Texture_monster_Golam;

	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;
	this->anime_rotate = 0;

	this->m_direc = direction;
	this->m_state = MOVE;
}

Monster_Golam::~Monster_Golam() {}
/*
move 스테이트가 아닐때 실행안함
방향에 따라 한쪽으로 계속 움직임
사정거리안에 플레이어가 있으면
Attack_State변경
*/
void Monster_Golam::MoveState(float dt, Player& player) {
	if (m_state != MOVE)
	{
		return;
	}
	if (m_direc == RIGHT) {
		pos.x += speed*dt;
	}
	else {
		pos.x -= speed*dt;
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
void Monster_Golam::Attack_State(float dt, Player& player) {
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
		Attack_Player(dt,player);
		return;
	}
	attack_timer += GetFrameTime();
}
//주금
void Monster_Golam::Die_State(float dt, Player& player) {
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

void Monster_Golam::Attack_Player(float dt, Player& player) {
	player.Get_Damage(atk);
	std::cout << "Monster Attack Player" << std::endl;
	return;
	//std::cout << "Try Attack" << std::endl;
}

Rectangle Monster_Golam::Return_Rect() {
	return { pos.x-size.x/2, pos.y-size.y, size.x, size.y };
}

void Monster_Golam::Draw_anime(float dt) {
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
			anime_rotate = -10;
		}
		else if (anime_timer < 0.8) {
			if (anime_rotate == -2) {
				anime_size.x = size.x;
				anime_size.y = size.y;
			}
			anime_rotate = 10;
		}
		else {
			anime_timer = 0;
		}

		if (anime_timer > 0.35 && anime_timer < 0.4) {
			anime_size.y -= 100 * dt;
		}
		if (anime_timer > 0.75 && anime_timer < 0.8) {
			anime_size.y -= 100 * dt;
		}
	}
#pragma endregion
	DrawTexturePro(Texture_monster,
		{ 0, 0,
		(float)191 * direction, 285},
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
			}, 3, BLUE
		);
		DrawRectangleLinesEx(
			Return_Rect(), 1, RED
		);
		DrawCircle(pos.x, pos.y,
			10, RED);
	}
	anime_timer += dt;
}


#pragma endregion

#pragma region Monster_Wizard
/// 
Monster_Wizard::Monster_Wizard(Vector2 position, Direction direction)
	:Monster(position, direction) {
	this->max_hp = 90;
	this->atk = 18;
	this->speed = 3;

	this->attack_range = 480;
	this->attack_coolTime = 4;

	this->Texture_monster = Texture_monster_Wizard;

	this->idle_img = { 10,7,151,223 };
	this->attack_ready_img = { 230,21,383, 207 };
	this->zoom = 0.8f;

	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_cut = idle_img;
	this->size = { anime_cut.width * zoom, anime_cut.height * zoom }
	;
	this->anime_size = size;
	this->anime_rotate = 0;


	this->m_direc = direction;
	this->m_state = MOVE;
	this->attack = false;
}

Monster_Wizard::~Monster_Wizard() {}

void Monster_Wizard::MoveState(float dt, Player& player) {
	if (m_state != MOVE)
	{
		return;
	}
	if (m_direc == RIGHT) {
		pos.x += speed*dt;
	}
	else {
		pos.x -= speed*dt;
	}
	if (player.Return_Pos().x < pos.x + attack_range &&
		player.Return_Pos().x > pos.x - attack_range) {
		m_state = ATTACK;
		attack_timer = attack_coolTime / 2;//선 공격 쿨타임

		anime_cut = attack_ready_img;
		size = { anime_cut.width * zoom, anime_cut.height * zoom };
		anime_size = size;
	}
}

void Monster_Wizard::Attack_State(float dt, Player& player) {
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
		Attack_Player(dt,player);
		return;
	}
	attack_timer += dt;
}
//주금
void Monster_Wizard::Die_State(float dt,Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Wizard::Attack_Player(float dt, Player& player) {
	monster_spawn.push_back(Monster_spawn(FISH, pos, m_direc));

	std::cout << "Monster Attack Player Get Fish " << std::endl;
	return;
	//std::cout << "Try Attack" << std::endl;
}

Rectangle Monster_Wizard::Return_Rect() {
	return { pos.x-size.x/2, pos.y -size.y, size.x, size.y };
}

void Monster_Wizard::Draw_anime(float dt) {
	int direction = 1;
#pragma region anime
	if (m_direc == RIGHT) {
		direction = -1;
	}

	if (m_state == ATTACK) {
		//anime_rotate = 0;
		anime_timer = 0;
		anime_rotate = 0;

		if (attack_coolTime - 0.1 < attack_timer) {
			anime_size.y -= 200 * dt;
		}
		else if (attack_timer < 0.1) {
			anime_size.y += 200 * dt;
		}
		else {
			anime_size.y = size.y;
		}
	}
	else {
		if (anime_timer < 0.4) {
			if (anime_rotate == 12) {
				anime_size.x = size.x;
				anime_size.y = size.y;
			}
			anime_rotate = -5;
		}
		else if (anime_timer < 0.8) {
			if (anime_rotate == -2) {
				anime_size.x = size.x;
				anime_size.y = size.y;
			}
			anime_rotate = 5;
		}
		else {
			anime_timer = 0;
		}

		if (anime_timer > 0.35 && anime_timer < 0.4) {
			anime_size.y -= 100 * dt;
		}
		if (anime_timer > 0.75 && anime_timer < 0.8) {
			anime_size.y -= 100 * dt;
		}
	}
#pragma endregion
	DrawTexturePro(Texture_monster,
		{
			anime_cut.x * direction,
			anime_cut.y,
			anime_cut.width,
			anime_cut.height
		},
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
			}, 3, BLUE
		);
		DrawRectangleLinesEx(
			Return_Rect(), 1, RED
		);
		DrawCircle(pos.x, pos.y,
			10, RED);
	}
	anime_timer += dt;
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


	this->Texture_monster = Texture_monster_Wizard;
	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;

	this->m_direc = direction;
	this->m_state = ATTACK;
}

Monster_Fish::~Monster_Fish() {}

void Monster_Fish::MoveState(float dt, Player& player) {
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

void Monster_Fish::Attack_State(float dt, Player& player) {
	if (m_state != ATTACK) {
		return;
	}	
	std::cout << "Monster Attack Player Fish s" << std::endl;
	//std::cout << "Monster Attack Player Fish sadafda" << std::endl;
	if (m_direc == RIGHT) {
		pos.x += speed*dt;
	}
	else {
		pos.x -= speed*dt;
	}

	if (player.Return_Pos().x < pos.x + 4 &&
		player.Return_Pos().x > pos.x - 4) {
		player.Get_Damage(atk);
	}
	return;
}
void Monster_Fish::Die_State(float dt, Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Fish::Attack_Player(float dt, Player& player) {
	return;
}

Rectangle Monster_Fish::Return_Rect() {
	return { pos.x, pos.y, size.x, size.y };
}

void Monster_Fish::Draw_anime(float dt) {
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

	this->size = { 484 / 2.2, 241 / 2.2 };

	this->Texture_monster = Texture_monster_Dog;

	////////////
	this->hp = max_hp;
	this->attack_timer = 0;
	this->pos = position;
	this->anime_size = size;

	this->m_direc = direction;
	this->m_state = MOVE;
}

Monster_Dog::~Monster_Dog() {}

void Monster_Dog::MoveState(float dt, Player& player) {
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

void Monster_Dog::Attack_State(float dt, Player& player) {
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
		Attack_Player(dt,player);
		return;
	}
	attack_timer +=dt ;
}
//주금
void Monster_Dog::Die_State(float dt, Player& player) {
	if (hp <= 0) {
		m_state = DIE;
	}
}

void Monster_Dog::Attack_Player(float dt, Player& player) {
	Rectangle player_rect = player.Return_Rect();
	Rectangle monster_rect = Return_Rect();

	

	if (CheckCollisionRecs(player_rect, monster_rect)) {
		player.Get_Damage(atk);
		//std::cout << "Dog Monster Attack Player" << std::endl;
		return;
	}
	attack_timer = 0;
	//std::cout << "Dog Try Attack" << std::endl;
	return;
}

Rectangle Monster_Dog::Return_Rect() {
	return { pos.x - size.x / 2
		, pos.y - size.y, size.x, size.y };
}

void Monster_Dog::Draw_anime(float dt) {
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
			anime_size.y -= 100 * dt;
		}
		if (anime_timer > 0.75 && anime_timer < 0.8) {
			anime_size.y -= 100 * dt;
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
			}, 3, BLUE
		);
		DrawRectangleLinesEx(
			Return_Rect(), 1, RED
		);
		DrawCircle(pos.x,pos.y,
			10, RED);
	}

	anime_timer += dt;
}
#pragma endregion
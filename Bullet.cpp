#include "Bullet.h"


Bullet::Bullet(Vector2 pos, Vector2 direction)
	: pos(pos), direction(direction), speed(5.0f), size_x(10), size_y(10) {
	direction_unit = {
		direction.x / sqrt(direction.x * direction.x + direction.y * direction.y),
		direction.y / sqrt(direction.x * direction.x + direction.y * direction.y)
	};
}


Bullet::~Bullet() {}

void Bullet::Move() {

}
void Bullet::collision(Monster& monster) {

}
void Bullet::Update() {
	Move();

	//https://life-with-coding.tistory.com/305
	for (auto mon : checkcol) {
		if (mon.first == nullptr) {
			checkcol.erase(mon.first);
			continue;
		}

		mon.second -= GetFrameTime();
		if (mon.second <= 0) {
			checkcol.erase(mon.first);
		}
		//std::cout << "why " << std::endl;
	}//몬스터와 충돌시 쿨타임을 줌
}
void Bullet::Draw() {
	DrawRectangle(pos.x, pos.y, size_x, size_y, BLACK);
}

Vector2_double Bullet::Unit_Vector(Vector2& direction) {
	double unit = sqrt(direction.x * direction.x + direction.y * direction.y);
	return { (double)direction.x / unit, (double)direction.y / unit };
}

Bullet_Mortar::Bullet_Mortar(Vector2 pos, Vector2 direction):
	Bullet(pos, direction) {
	this->pos = pos;
	this->atk = 10;

	this->speed = 2;
	this->speed_y = 20;
	this->gravity = 2;
	this->direction = direction;
	this->size_x = 20;
	this->size_y = 20;
}

Bullet_Mortar::~Bullet_Mortar() {

}
//https://www.omnicalculator.com/physics/trajectory-projectile-motion
//https://www.reddit.com/r/gamedev/comments/vb47cp/formula_for_an_arching_trajectory_for_2d_game/
void Bullet_Mortar::Move() {
	pos.x += direction.x * speed * GetFrameTime() * 4;
	pos.y -= direction.y * speed_y * GetFrameTime() *4;
	pos.y += direction.y * gravity/2 * GetFrameTime() * 4;
	gravity += gravity * GetFrameTime() * 4;
	if (gravity > 200) {
		gravity = 200;
	}

	//총알 움직임 박격포 움직임 패치 예정
}

//https://jgcoding.tistory.com/11
void Bullet_Mortar::collision(Monster& monster) {

	//if (checkcol.find(&monster) != checkcol.end())
	//{
	//	return;
	//}

	//checkcol.insert({&monster, 10.0f});

	Rectangle bullet_rect = { pos.x, pos.y, (float)size_x, (float)size_y };
	Rectangle monster_rect = monster.Return_Rect();

	if (CheckCollisionRecs(bullet_rect, monster_rect)) {
		if (checkcol.find(&monster) != checkcol.end())
		{
			std::cout << "Bullet Attack Monster CoolTime" << std::endl;
			return;
		}
		
		checkcol.insert({ &monster, 0.1f });
		monster.Get_Damage(atk);
		std::cout << "Bullet Attack Monster" << std::endl;
	}
}
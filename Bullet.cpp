#include "Bullet.h"


Bullet::Bullet(Vector2 pos ,Vector2 direction )
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

	this->speed = 1.6;
	this->speed_y = 14;
	this->gravity = 1;
	this->direction = direction;
	this->size_x = 20;
	this->size_y = 20;
}

Bullet_Mortar::~Bullet_Mortar() {

}
//https://www.omnicalculator.com/physics/trajectory-projectile-motion
//https://www.reddit.com/r/gamedev/comments/vb47cp/formula_for_an_arching_trajectory_for_2d_game/
void Bullet_Mortar::Move() {

	pos.x += direction.x * speed * GetFrameTime() *4;
	pos.y -= direction.y * speed_y * GetFrameTime() * 4;
	pos.y += direction.y * gravity/2 * GetFrameTime() * 4;
	gravity += gravity * GetFrameTime() * 4;
	//총알 움직임 박격포 움직임 패치 예정
}

void Bullet_Mortar::collision(Monster& monster) {
	Rectangle bullet_rect = { pos.x, pos.y, (float)size_x, (float)size_y };
	Rectangle monster_rect = monster.Return_Rect();

	if (CheckCollisionRecs(bullet_rect, monster_rect)) {
		monster.Get_Damage(atk);
	}//충돌 체크 함수실행을 안함
}
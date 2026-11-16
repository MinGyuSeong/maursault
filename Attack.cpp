#include "Attack.h"

std::vector<Bullet*> bullets;
void draw_bullets() {
	for (auto bullet : bullets) {
		bullet->Draw();
	}
}
void update_bullets() {
	for (auto bullet : bullets) {
		bullet->Update();
	}
}
///main에서 실행됨  


void Attack::Attack_Before(Player& player) {

}
void Attack::Attack_(Player& player) {

}
void Attack::Attack_collision(Player& player) {

}
void Attack::draw() {

}

//https://rhksgml78.tistory.com/272
void Base_Attack::Attack_Before(Player& player) {
	Vector2 mouse = {GetMouseX(),  player.Return_Pos().y};
	Vector2 player_pos = player.Return_Pos();
	//Vector2 middle = { (player_pos.x + mouse.x) / 2, 0 };//p1
	Vector2 direction = {1,1};
	direction.x = (mouse.x - player_pos.x)/8;
	direction.y = 40 - abs(direction.x);
	if (direction.y > 20) {
		direction.y = 20;
	}
	if (direction.y < 10) {
		direction.y = 10;
	}
	
	Vector2 pos = player_pos;
	float speed = 1;
	float speed_y = 10;
	float gravity = 1;

	for (int i = 0; i < 100; i++) {
		pos.x += direction.x * speed;
		pos.y -= direction.y * speed_y;
		pos.y += direction.y * gravity / 2;
		gravity += gravity;

		if (pos.y > player_pos.y+100) {
			break;
		}
		DrawCircle(pos.x, pos.y, 5, RED);
	}
	// 공격전 공격 경로를 보여주는 함수 
	// 공을 던지고 그경로를 보여줌 미완 
#pragma region trash



	//std::vector<Vector2> bazier;
	//int length = 50;
	//Vector2 bazier_1;
	//Vector2 bazier_2;
	//Vector2 bazier_3;
	//for (size_t i = 0; i < length; i++)
	//{
	//	double t = (float)i / length;
	//	
	//	bazier_1.x = player_pos.x + (middle.x - player_pos.x) * t;
	//	bazier_1.y = player_pos.y + (middle.y - player_pos.y) * t;

	//	bazier_2.x = middle.x + (mouse.x - middle.x) * t;
	//	bazier_2.y = middle.y + (mouse.y - middle.y) * t;
	//	
	//	bazier_3.x = bazier_1.x + (bazier_2.x - bazier_1.x) * t;
	//	bazier_3.y = bazier_1.y + (bazier_2.y - bazier_1.y) * t;


	//	bazier.push_back(bazier_3);
	//}
	//for (size_t i = 1; i < length; i++)
	//{
	//	DrawLine(bazier[i-1].x, bazier[i-1].y, bazier[i].x, bazier[i].y,RED);
	//	//DrawCircle(bazier[i].x, bazier[i].y, 10, RED)
	//}
#pragma endregion 
	//실패작
}

void Base_Attack::Attack_(Player& player) {
	Vector2 mouse = { GetMouseX(),  player.Return_Pos().y };
	Vector2 player_pos = player.Return_Pos();
	//Vector2 middle = { (player_pos.x + mouse.x) / 2, 0 };//p1
	Vector2 direction = { 1,1 };
	direction.x = (mouse.x - player_pos.x) / 8;
	direction.y = 40 - abs(direction.x);
	if (direction.y > 20) {
		direction.y = 20;
	}
	if (direction.y < 10) {
		direction.y = 10;
	}//경로 설정

	bullets.push_back(new Bullet_Mortar({ player_pos.x, player_pos.y }, direction));
	//총알 생성

	//총알 생성
	//총알을 만들때 총알이 생성되는 위치랑 날아가는 경로를 설졍해야함 
	//생성한 총알을 bullets 벡터 리스트에 넣어야지 실행됨
}

void Base_Attack::Attack_collision(Player& player) {}
//충돌 체크 

#include "Attack.h"

std::vector<Bullet*> bullets;
void draw_bullets() {
	for (auto bullet : bullets) {
		bullet->Draw();
	}
}

void update_bullets(float dt) {
	for (auto bullet : bullets) {
		bullet->Update(dt);
	}
}

void collision_bullets(Monster& monster) {
	for (auto bullet : bullets) {
		bullet->collision(monster);
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
void Attack::update(Player& player) {
	Attack_Before(player);
	Attack_(player);
	Attack_collision(player);
}



//https://rhksgml78.tistory.com/272
void Base_Attack::Attack_Before(Player& player) {
	Vector2 mouse = {GetMouseX(),  player.Return_Pos().y};
	Vector2 player_pos = player.Return_Pos();
	//Vector2 middle = { (player_pos.x + mouse.x) / 2, 0 };//p1
	Vector2 direction = {1,1};
	direction.x = (mouse.x - player_pos.x)/10;
	direction.y = 13;
	int direc_int = 1;
	if (player.Return_Direc() == LEFT) {
		direc_int = -1;
	}
	
	Vector2 pos = { player_pos.x - (100 * direc_int) ,player_pos.y - 120 };
	float speed = 2;
	float speed_y = 20;
	float gravity = 2;
	std::vector<Vector2> points = {};
	for (int i = 0; i < 300; i++) {
		pos.x += direction.x * speed * 1/ SET_FrameRate * 4;
		pos.y -= direction.y * speed_y* 1/ SET_FrameRate * 4;
		pos.y += direction.y * gravity / 2 * 1/ SET_FrameRate * 4;
		gravity += gravity * 1/ SET_FrameRate * 4;
		if(gravity > 200) {
			gravity = 200;
		}
		if (pos.y > player_pos.y+100) {
			break;
		}
		points.push_back(pos);
	}
	for (int i = 0; i < points.size() - 1; i++) {
		DrawLine(points[i].x, points[i].y , points[i+1].x, points[i+1].y, RED);
	}


	// 공격전 공격 경로를 보여주는 함수 
	// 공을 던지고 그경로를 보여줌 미완 
#pragma region trash

	//std::vector<Vector2> bazier;
	//Vector2 middle = { (pos.x + mouse.x) / 2 ,10 };
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
	int direc_int = 1;
	if (player.Return_Direc() == LEFT) {
		direc_int = -1;
	}
	Vector2 pos = { player_pos.x - (100 * direc_int) ,player_pos.y - 120 };

	Vector2 direction = { 1,1 };
	direction.x = (mouse.x - player_pos.x) / 10;
	direction.y = 13;//경로 설정
	
	bullets.push_back(new Bullet_Mortar({ pos.x, pos.y }, direction));
	//총알 생성

	//총알 생성
	//총알을 만들때 총알이 생성되는 위치랑 날아가는 경로를 설졍해야함 
	//생성한 총알을 bullets 벡터 리스트에 넣어야지 실행됨
}

void Base_Attack::Attack_collision(Player& player) {}

//충돌 체크 

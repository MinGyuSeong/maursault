#include "Attack.h"

void Attack::Attack_Before(Player& player) {

}
void Attack::Attack_Motion(Player& player) {

}
void Attack::Attack_collision(Player& player) {

}




//https://rhksgml78.tistory.com/272
void Base_Attack::Attack_Before(Player& player) {
	Vector2 mouse = {GetMouseX(),  player.Return_Pos().y};
	Vector2 player_pos = player.Return_Pos();
	Vector2 middle = { (player_pos.x + mouse.x) / 2, 0 };//p1

	std::vector<Vector2> bazier;
	int length = 50;
	Vector2 bazier_1;
	Vector2 bazier_2;
	Vector2 bazier_3;
	for (size_t i = 0; i < length; i++)
	{
		double t = (float)i / length;
		
		bazier_1.x = player_pos.x + (middle.x - player_pos.x) * t;
		bazier_1.y = player_pos.y + (middle.y - player_pos.y) * t;

		bazier_2.x = middle.x + (mouse.x - middle.x) * t;
		bazier_2.y = middle.y + (mouse.y - middle.y) * t;
		
		bazier_3.x = bazier_1.x + (bazier_2.x - bazier_1.x) * t;
		bazier_3.y = bazier_1.y + (bazier_2.y - bazier_1.y) * t;


		bazier.push_back(bazier_3);
	}
	std::cout << "aaaa " << std::endl;
	for (size_t i = 1; i < length; i++)
	{
		DrawLine(bazier[i-1].x, bazier[i-1].y, bazier[i].x, bazier[i].y,RED);
		//DrawCircle(bazier[i].x, bazier[i].y, 10, RED);
	}
}
void Base_Attack::Attack_Motion(Player& player) {
	Vector2 mouse = { GetMouseX(),  player.Return_Pos().y };
	Vector2 player_pos = player.Return_Pos();
	Vector2 middle = { (player_pos.x + mouse.x) / 2, 0 };//p1

	std::vector<Vector2> bazier;
	int length = 100;
	Vector2 bazier_1;
	Vector2 bazier_2;
	Vector2 bazier_3;
	for (size_t i = 0; i < length; i++)
	{
		double t = (float)i / length;

		bazier_1.x = player_pos.x + (middle.x - player_pos.x) * t;
		bazier_1.y = player_pos.y + (middle.y - player_pos.y) * t;

		bazier_2.x = middle.x + (mouse.x - middle.x) * t;
		bazier_2.y = middle.y + (mouse.y - middle.y) * t;

		bazier_3.x = bazier_1.x + (bazier_2.x - bazier_1.x) * t;
		bazier_3.y = bazier_1.y + (bazier_2.y - bazier_1.y) * t;

		bazier.push_back(bazier_3);
	}
	std::cout << "aaaa " << std::endl;
	for (size_t i = 1; i < length; i++)
	{
		DrawLine(bazier[i - 1].x, bazier[i - 1].y, bazier[i].x, bazier[i].y, RED);
	}
}

void Base_Attack::Attack_collision(Player& player) {}
void Base_Attack::draw(){}
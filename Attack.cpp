#include "Attack.h"


Attack::Attack()
	:atk(10), atk_cooltime(0), atk_state(false) {
}

void Attack::draw() {
	DrawRectangle(100, 100, 50, 50, RED);
}

void Attack::update() {
	// Update attack logic
}

///////////////////


Base_Attack::Base_Attack()
	:Attack() {
}
void Base_Attack::draw(){
	DrawRectangle(100, 100, 50, 50, RED);
}
void Base_Attack::update() {
	// Update attack logic
}




















#ifndef MAURSAULT_PLAYER_H
#define MAURSAULT_PLAYER_H


enum Player_Direction;

class Player
{
private:
	int hp ;
	int mp ;
	int atk ;
	int def ;
	int exp ;
	int level;

	int pos_x;
	int pos_y;


	int size_x;
	int size_y;
	Player_Direction p_direc;


	void Input_Direction();
	void Atack();

public:
	Player();
	void update();
	void Draw();
};

#endif // !defined(MAURSAULT_PLAYER_H)
#pragma once
#include "Base_information.h"
#include "Player.h"

class Player;

void draw_monsters(float dt);
void update_monsters(float dt, Player& player);
void spawn_monster();
void spawn_monster2();
void LoadMonster_Image();

enum Monster_State;

class Monster
{
public:
	Monster(Vector2 position, Direction direction);
	~Monster();
protected:
	int max_hp;
	int hp;
	int atk;

	float speed;

	float attack_range;
	double attack_coolTime;//공격 쿨타임
	double attack_timer;//공격 타이머

	double anime_timer = 0;

	Texture2D Texture_monster;

	Vector2 pos;
	Direction m_direc;//오른쪽에서 올지 왼쪽애서 올지
	Monster_State m_state;//스테이트 행동 결정

	Vector2 size;
	Vector2 anime_size;

	Vector2 get_force;
public:
	virtual Rectangle Return_Rect();
	Vector2 Return_Pos();
	void Get_Force(Vector2 add_foce);

	void Update(float dt, Player& player);
	void Draw(float dt);

	virtual void MoveState(float dt,Player& player);//움직임 플레이어에게 다가감
	virtual void Attack_State(float dt, Player& player);//사정거리에 들어오면 공격함 
	virtual void Die_State(float dt, Player& player);//hp<0 아무 행동도 하지 않음

	virtual void Attack_Player(float dt, Player& player);//Attack_State 플레이어를 공격

	virtual void Draw_anime(float dt);

	void Get_Damage(int damage);
private:
	void Update_Force(float dt);
};
//------------
/*
	대부분의 클래스 bullet attack monster등을 상속으로 만들거임

	원하는 자식 클래스(Monster_Robot)를 만든뒤  이름뒤에 :public 부모 클래스(Monster)이런 식으로 적으면
	자식 클래스(Monster_Robot)는 부모 클래스(Monster) 에서 만든 함수나 변수를 선언 없이 그대로 쓸수 있음
	자식 클래스랑 부모 클래스는 상속받은 클래스 상속된 클래스를 의미함

	예시로 밑에 Monster_Robot을 보면 getdamage나 다른 변수는 없지만 cpp파일에서 정상 작동하는 걸 볼수 있음

	이제 니들이 해야할것
	앞에 virtual이라고 적힌애들은 다시 만들어서 쓰겠다는 말임
	뒤에 override라고 적힌 부분은 다시 만들겠다라는 말이고
	그래서 이부분은 선언 해준다음 cpp에서 기능 구현을 새롭게 해줘야함

	하지만  virtual이라고 적힌 부분을 실행하는 함수는 부모클래스가 가지고 있기 떄문에
	기능구현만 하고 클래스 만들고 vector에 넣기만 하면 바로 실행 될거임 "아마", "몇개 빼고"

	또한 c++ 에서 헤더 파일 관리를 안배웠는데 c랑 똑같은데 다른점은
	기능 구현할떄
	void (클래스명)::(햠수명)(매계변수){
		//기능 구현
	}
	꼴로 만들어야함

	나름 깔끔하게 보일려고 class랑 헤더파일 써봤는데 이거 때매 더 복잡아진것 같기도 하고 잘모르겠음 ㄷㄷ
*/

class Monster_Dog : public Monster {
public:
	Monster_Dog(Vector2 position, Direction direction);
	~Monster_Dog();
private:
	Rectangle anime_cut;

	Rectangle idle_img;
	Rectangle attack_1_img;
	Rectangle attack_2_img;

	float zoom;
	int anime_rotate;
	//virtual funition
	virtual Rectangle Return_Rect() override;

	virtual void MoveState(float dt, Player& player) override;
	virtual void Attack_State(float dt, Player& player) override;
	virtual void Die_State(float dt, Player& player) override;

	virtual void Attack_Player(float dt, Player& player) override;

	virtual void Draw_anime(float dt) override;
};

class Monster_Wizard : public Monster {
public:
	Monster_Wizard(Vector2 position, Direction direction);
	~Monster_Wizard();
private:
	int anime_rotate;
	bool attack;

	Rectangle anime_cut;

	Rectangle idle_img;
	Rectangle attack_ready_img;
	float zoom;

	//virtual funition
	virtual Rectangle Return_Rect() override;

	virtual void MoveState(float dt, Player& player) override;
	virtual void Attack_State(float dt, Player& player) override;
	virtual void Die_State(float dt, Player& player) override;

	virtual void Attack_Player(float dt, Player& player) override;

	virtual void Draw_anime(float dt) override;
};

class Monster_Fish : public Monster {
public:
	Monster_Fish(Vector2 position, Direction direction);
	~Monster_Fish();
private:

	//virtual funition
	virtual Rectangle Return_Rect() override;

	virtual void MoveState(float dt, Player& player) override;
	virtual void Attack_State(float dt, Player& player) override;
	virtual void Die_State(float dt, Player& player) override;

	virtual void Attack_Player(float dt, Player& player) override;

	virtual void Draw_anime(float dt) override;
};

class Monster_Golam : public Monster {
public:
	Monster_Golam(Vector2 position, Direction direction);
	~Monster_Golam();
private:
	int anime_rotate;

	//
	//virtual funition
	virtual Rectangle Return_Rect() override;

	virtual void MoveState(float dt, Player& player) override;
	virtual void Attack_State(float dt, Player& player) override;
	virtual void Die_State(float dt, Player& player) override;

	virtual void Attack_Player(float dt, Player& player) override;

	virtual void Draw_anime(float dt) override;
};

std::vector<Monster*> return_monsters();

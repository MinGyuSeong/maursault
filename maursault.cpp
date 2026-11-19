// maursault.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Player.h"
#include "Attack.h"
#include "Monster.h"
#include "Bullet.h"
#include "Base_information.h"
//#include <windows.h>


int main()
{
    //SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    //SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
    // 
    //https://www.raylib.com/examples/core/loader.html?name=core_window_flags
    //윈도우 사이즈
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Game");
    //Load_image();
    //ToggleFullscreen();
	LoadPlayer_Image();
	LoadMonster_Image();

	Player player;

    SetTargetFPS(SET_FrameRate);

    double timer = 0;

    while (!WindowShouldClose())
    {
        timer += GetFrameTime();
		if (timer >=3) {
            //monsters.push_back(new Monster_Robot({ 0, WINDOW_HEIGHT / 2 + 200 },
            //    Direction::RIGHT));
            //monsters.push_back(new Monster_Robot({ 1980, WINDOW_HEIGHT / 2 + 200 },
            //    Direction::LEFT));
            spawn_monster();
            timer = 0;
		}//생성

        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.Draw();
        player.Update();//플레이어

        //for (auto monster : monsters) {
        //    monster->Draw();
        //    monster->Update(player);
        //}//몬스터
        draw_monsters();
        update_monsters(player);

        for (auto monster : return_monsters()) {
            collision_bullets(*monster);
        }

        draw_bullets();
        update_bullets();//총알
        DrawRectangle(0, WINDOW_HEIGHT / 3*2, WINDOW_WIDTH, WINDOW_HEIGHT / 5*4, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

// 프로그램 실행: Ctrl+F5 또는 디버그 > 디버깅하지 않고 시작 메뉴
// 프로그램 디버그: F5 키 또는 디버그 > 디버깅 시작 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

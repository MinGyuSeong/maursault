#pragma once
#include "raylib.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <map>
/// <summary>
/// 기본 정보가 있는 파일 
/// 윈도우 사이즈랑 디렉션 enum 같은 모두가 쓰는 정보가드감
/// 각종 헤더파일도
/// </summary>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define SET_FrameRate 60
enum Direction {
	RIGHT,
	LEFT
};
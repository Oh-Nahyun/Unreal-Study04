/////

#pragma once

#define WINSIZEX			800
#define WINSIZEY			800
#define RGB_VALUE			RGB(255, 0, 255)
#define ENEMY_MAX			50

///// 이미지 파일 인덱스, 8개의 이미지 파일
enum {
	IMG_BACK,
	IMG_ALPHA,
	IMG_MAP,
	IMG_DDONG,
	IMG_PLAYER,
	IMG_PLAYER_LEFTRUN,
	IMG_PLAYER_RIGHTRUN,
	IMG_PLAYER_DEATH
};

///// 플레이어 행동 인덱스, 4가지 상태
enum {
	ACTION_STAND = 4,
	ACTION_LEFT_RUN,
	ACTION_RIGHT_RUN,
	ACTION_DEATH
};


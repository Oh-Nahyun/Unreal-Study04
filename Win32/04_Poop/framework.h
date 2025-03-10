// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

///// Lib Include
#pragma comment(lib, "msimg32.lib")		///// TransparantBlt 사용을 위해 포함

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>						/////
#include <assert.h>						/////

///// STL
#include <vector>						/////

///// MyGame Include
#include "Define.h"						///// 기본적인 데이터
#include "Structure.h"					///// 이미지 구조체, 싱글톤 구조

#include "GameManager.h"				///// 이미지, 플레이어, 적, 플레이 등등 게임 관련 매니저 클래스
#include "Image.h"						///// 이미지 클래스
#include "Object.h"						///// 오브젝트 클래스 (물리 처리할 구조체)
#include "Player.h"						///// 플레이어 클래스
#include "Enemy.h"						///// 적 클래스

#include "Global.h"						///// 전역 (시스템)


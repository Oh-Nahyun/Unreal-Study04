/////

#pragma once

#include "Image.h"
#include "Player.h"
#include "Enemy.h"

class CGameManager
{
private:
	CImageManager	m_Image;
	CPlayer			m_Player;
	CEnemyManager	m_Enemy;

	DWORD			m_FrameTime;
	DWORD			m_FrameTimeLimit;

public:
	CGameManager();
	virtual ~CGameManager();
	
	bool Init();
	bool Update();
	bool Render();
	
	void ScoreCheck();
	void Collision();
	
	void RenderInterface();
};


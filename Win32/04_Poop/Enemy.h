/////

#pragma once

#include "Object.h"

class CEnemy : public CObject
{
private:
	RECT	m_rcErasePos;
	POINT	m_ptPos;

public:
	CEnemy();
	virtual ~CEnemy();

	void Init();
	void Update();
	void Render();
	void Draw(HDC hdc);
	void Move();
	void RefreshRect();

	void SetAllData(int PosX, int PosY);
};

///// 적 매니저
class CEnemyManager
{
private:
	CEnemy* m_pEnemy;
	INT		m_iScore;
	bool	m_bScoreCheck;

public:
	CEnemyManager();
	virtual ~CEnemyManager();

	bool Init();
	void Render();
	void Draw(HDC hdc);

	void Update();
	void Release();

	int GetScore() { return m_iScore; }
	void SetScoreCheck(bool Flag) { m_bScoreCheck = Flag; }

	CEnemy& operator[](int Index) { return m_pEnemy[Index]; }
};


/////

#include "framework.h"

CEnemy::CEnemy()
{
	m_iLiveFlag = false;
	PhysicsSetup(vector_3d(0, -200, 0), 30.0f, 30.0f);
}

CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
}

void CEnemy::Draw(HDC hdc)
{
	Ellipse(hdc, m_rcPos.left, m_rcPos.top, m_rcPos.right, m_rcPos.bottom);
}

void CEnemy::Render()
{
	S_IMAGE[IMG_DDONG]->Render(S_IMAGE.GetBack(), m_rcPos.left, m_rcPos.top, true, 0, 0);
}

void CEnemy::Update()
{
	ForceSetup();

	PhysicsUpdate();

	RefreshRect();
}

void CEnemy::RefreshRect()
{
	SetRect(&m_rcPos,	   (int)m_vPos.x - 10, (int)m_vPos.y - 9,  (int)m_vPos.x + 10, (int)m_vPos.y + 9);
	SetRect(&m_rcErasePos, (int)m_vPos.x - 12, (int)m_vPos.y - 12, (int)m_vPos.x + 12, (int)m_vPos.y + 12);
}

void CEnemy::Move()
{
}

void CEnemy::SetAllData(int PosX, int PosY)
{
	PhysicsReset();

	m_vPos.x = (float)PosX;
	m_vPos.y = (float)PosY;
	m_iLiveFlag = true;

	SetRect(&m_rcPos, (int)m_vPos.x - 10, (int)m_vPos.y - 9, (int)m_vPos.x + 10, (int)m_vPos.y + 9);

	PhysicsSetup(vector_3d(0, -200, 0), 30.0f, 30.0f);
}

///// ==============================
///// CEnemyManager (적 매니저 클래스)

CEnemyManager::CEnemyManager()
{
	m_pEnemy = NULL;
	m_iScore = 0;
	m_bScoreCheck = true;
}

CEnemyManager::~CEnemyManager()
{
	if (m_pEnemy)
		delete[] m_pEnemy;
}

bool CEnemyManager::Init()
{
	m_pEnemy = new CEnemy[ENEMY_MAX];

	if (!m_pEnemy)
		return false;

	return true;
}

void CEnemyManager::Render()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!m_pEnemy[i].GetLiveFlag())
			continue;
		
		m_pEnemy[i].Render();
	}
}

void CEnemyManager::Draw(HDC hdc)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!m_pEnemy[i].GetLiveFlag())
			continue;

		m_pEnemy[i].Draw(hdc);
	}
}

void CEnemyManager::Update()
{
	///// 출력
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!m_pEnemy[i].GetLiveFlag())
			continue;

		m_pEnemy[i].Update();

		///// ddong 이 바닥에 떨어졌을 경우
		if (m_pEnemy[i].GetPos().y >= 790)
		{
			m_pEnemy[i].SetLiveFlag(false);
			m_pEnemy[i].PhysicsReset();

			if (m_bScoreCheck == true)
				m_iScore++;
		}
	}

	///// ddong 부활
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (m_pEnemy[i].GetLiveFlag())
			continue;

		int Rvalue = rand() % 300;
		if (Rvalue == 0)
		{
			m_pEnemy[i].SetAllData(rand() % 590 + 10, 300);
		}
	}
}

void CEnemyManager::Release()
{
	if (m_pEnemy)
	{
		delete[] m_pEnemy;
		m_pEnemy = NULL;
		m_iScore = 0;
		m_bScoreCheck = true;
	}
}


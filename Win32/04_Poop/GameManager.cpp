///// ★ ★ ★

#include "framework.h"

CGameManager::CGameManager()
{
	m_FrameTimeLimit = 0;
}

CGameManager::~CGameManager()
{
}

bool CGameManager::Init()
{
	///// 이미지 초기화
	if (!m_Image.Init())
		return false;		///// 에러 발생 시 확실히 알림!!

	///// 플레이어 초기화
	m_Player.Init();

	///// 적(똥) 초기화
	m_Enemy.Init();

	return true;
}

bool CGameManager::Update()
{
	///// 프레임 고정
	m_FrameTime = GetTickCount();
	if (m_FrameTimeLimit > m_FrameTime)
		return true;
	m_FrameTimeLimit = m_FrameTime + 1000 / 66;

	///// 캐릭터 업데이트
	m_Player.Update();

	///// 적 업데이트
	m_Enemy.Update();

	///// 충돌 체크
	Collision();

	///// 점수 체크
	ScoreCheck();

	///// 재시작 검사 (죽었을 때 = 스페이스키 누르면 재시작)
	if (!m_Player.GetLiveFlag())
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			m_Player.Init();
			m_Enemy.Release();
			m_Enemy.Init();
		}
	}

	return true;
}

bool CGameManager::Render()
{
	///// 화면 초기화 (hBack)
	m_Image[IMG_MAP]->Render(m_Image.GetBack(), 0, 0);

	///// 캐릭터 렌더링
	m_Player.Render();

	///// 적 렌더링
	m_Enemy.Render();

	///// 화면 인터페이스 출력
	RenderInterface();

	///// 백서페이스 출력 (hBack -> hDc)
	m_Image[IMG_BACK]->Render(m_Image.GetHdc(), 0, 0);

	return true;
}

void CGameManager::RenderInterface()
{
	///// 세로선 그리기
	MoveToEx(m_Image.GetBack(), 600, 0, NULL);
	LineTo(m_Image.GetBack(), 600, 820);

	///// 스코어 (폰트 초기화)
	TCHAR szBuf[128] = { 0, };
	wsprintf(szBuf, TEXT("Score"));

	HFONT hFont, OldFont;
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, _T("나눔바른고딕"));
	OldFont = (HFONT)SelectObject(m_Image.GetBack(), hFont);

	///// 스코어 글자 출력
	TextOut(m_Image.GetBack(), 625, 100, szBuf, lstrlen(szBuf));

	///// 스코어 점수 출력
	wmemset(szBuf, 0, lstrlen(szBuf));
	wsprintf(szBuf, TEXT("%d"), m_Enemy.GetScore());

	///// 우측 정렬을 위해...
	int size = lstrlen(szBuf);
	TextOut(m_Image.GetBack(), 700 - size * 15, 200, szBuf, lstrlen(szBuf));

	///// HP 출력
	wmemset(szBuf, 0, lstrlen(szBuf));
	wsprintf(szBuf, TEXT("Life"));
	TextOut(m_Image.GetBack(), 627, 300, szBuf, lstrlen(szBuf));

	///// 박스 그리기
	RECT rcLife;
	int LifeCount = m_Player.GetHP();

	Rectangle(m_Image.GetBack(), 615, 400, 775, 420);

	HBRUSH MyBrush, OldBrush;	///// 브러쉬

	MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
	OldBrush = (HBRUSH)SelectObject(m_Image.GetBack(), MyBrush);

	SetRect(&rcLife, 615, 400, 615 + 16 * LifeCount, 420);
	Rectangle(m_Image.GetBack(), rcLife.left, rcLife.top, rcLife.right, rcLife.bottom);

	///// 색 변경 복구하기
	SelectObject(m_Image.GetBack(), OldBrush);
	DeleteObject(MyBrush);
	DeleteObject(OldBrush);

	///// 지우기
	SelectObject(m_Image.GetBack(), OldFont);
	DeleteObject(hFont);
	DeleteObject(OldFont);
}

void CGameManager::ScoreCheck()
{
	if (!m_Player.GetLiveFlag())
		m_Enemy.SetScoreCheck(false);
}

void CGameManager::Collision()
{
	///// 플레이어의 생사 여부
	if (!m_Player.GetLiveFlag())
		return;

	///// 플레이어와 적(똥)과의 충돌
	RECT rcTemp;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!m_Enemy[i].GetLiveFlag())
			continue;

		if (IntersectRect(&rcTemp, m_Player.GetRectPos(), m_Enemy[i].GetRectPos()))		///// (((사각형 교집합 함수를 이용한다.)))
		{
			m_Player.SetDamage(1);
			m_Enemy[i].SetLiveFlag(false);
		}
	}
}


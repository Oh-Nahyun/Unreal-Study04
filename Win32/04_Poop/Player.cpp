/////

#include "framework.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_vPos.x = 293;
	/////m_vPos.y = 770;
	m_vPos.y = 700;
	m_iHp = 10;
	m_fSpeed = 0.0f;
	m_iLiveFlag = true;

	RefreshRect();

	ActionSetup(ACTION_STAND, 0, 2, 10);
}

void CPlayer::Update()
{
	///// 생사 여부 판단
	if (m_iLiveFlag == false)
		return;

	///// 액션 업데이트
	if (++m_FrameInfo.FrameCount % m_FrameInfo.FrameCountSpeed == 0)
	{
		if (m_FrameInfo.FrameX++ >= m_FrameInfo.FrameMax)
		{
			ActionChange(m_FrameInfo.ActionState);
		}
	}

	///// 키보드 업데이트 > GetKeyState() 버전
	static bool KeyInput = false;
	KeyInput = false;

	if (GetKeyState(VK_LEFT) & 0x8000) ///// (((VK_LEFT가 down 된 경우를 의미한다.)))
	{
		KeyInput = true;

		if (m_fSpeed > 0)
			m_fSpeed -= 0.4f;
		else
			m_fSpeed -= 0.3f;

		if (m_FrameInfo.ActionState != ACTION_LEFT_RUN)
			ActionChange(ACTION_LEFT_RUN);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		KeyInput = true;

		if (m_fSpeed < 0)
			m_fSpeed += 0.4f;
		else
			m_fSpeed += 0.3f;

		if (m_FrameInfo.ActionState != ACTION_RIGHT_RUN)
			ActionChange(ACTION_RIGHT_RUN);
	}
	if (KeyInput == false)
	{
		if (m_fSpeed < 0)
			m_fSpeed += 0.3f;
		else if(m_fSpeed > 0)
			m_fSpeed -= 0.3f;
		
		if (m_fSpeed >= -0.2f && m_fSpeed <= 0.2f)
			m_fSpeed = 0.0f;

		m_FrameInfo.ActionState = ACTION_STAND;
	}

	///// 이동
	Move();

	///// 생사 여부 판단 (HP)
	if (m_iHp <= 0)
	{
		m_iLiveFlag = false;
		ActionChange(ACTION_DEATH);
	}
}

void CPlayer::Render()
{
	S_IMAGE[m_FrameInfo.ActionState]->Render(S_IMAGE.GetBack(), m_rcPos.left, m_rcPos.top, true, m_FrameInfo.FrameX, 0);
}

void CPlayer::Move()
{
	///// 화면 밖으로 나가는 경우 (Left)
	if (m_vPos.x - 7 + m_fSpeed <= 0)		///// ※ 스프라이트에 따라 다른 코드	///// if (m_vPos.x - 16 + m_fSpeed <= 0)
	{
		m_vPos.x = 7;						///// ※ 스프라이트에 따라 다른 코드	///// 16
		m_fSpeed = 0.0f;
	}

	///// 화면 밖으로 나가는 경우 (Right)
	if (m_vPos.x + 8 + m_fSpeed >= 600)		///// ※ 스프라이트에 따라 다른 코드	///// if (m_vPos.x + 16 + m_fSpeed >= 600)
	{
		m_vPos.x = 600 - 8;					///// ※ 스프라이트에 따라 다른 코드	///// 600 - 16
		m_fSpeed = 0.0f;
	}

	m_vPos.x += m_fSpeed;
	RefreshRect();
}

void CPlayer::RefreshRect()
{
	SetRect(&m_rcPos, m_vPos.x - 7, m_vPos.y - 11, m_vPos.x + 8, m_vPos.y + 12);	///// ※ 스프라이트에 따라 다른 코드
																					///// SetRect(&m_rcPos, m_vPos.x - 16, m_vPos.y - 16, m_vPos.x + 16, m_vPos.y + 16);
}

void CPlayer::ActionChange(int action)
{
	switch (action)
	{
	case ACTION_STAND:
		ActionSetup(action, 0, 2, 10);		///// ※ 스프라이트에 따라 다른 코드	///// 0, 3, 10 (프레임 수 : 4개여서 3)
		break;
	case ACTION_LEFT_RUN:
		ActionSetup(action, 0, 2, 2);		///// ※ 스프라이트에 따라 다른 코드	///// 0, 3, 2
		break;
	case ACTION_RIGHT_RUN:
		ActionSetup(action, 0, 2, 2);		///// ※ 스프라이트에 따라 다른 코드	///// 0, 3, 2
		break;
	case ACTION_DEATH:
		ActionSetup(action, 0, 0, 10);
		break;
	}
}


/////

#include "framework.h"

CObject::CObject()
{
	ZeroMemory(&m_PhysicsInfo, sizeof(m_PhysicsInfo));
	ZeroMemory(&m_FrameInfo, sizeof(m_FrameInfo));

	m_vPos = vector_3d(0.0f, 0.0f, 0.0f);
}

CObject::~CObject()
{
}

// 물리 적용.
void CObject::PhysicsUpdate(scalar changeInTime)
{
	// 질량이 0인지 검사.
	assert(m_PhysicsInfo.fMass != 0);

	// linearAcceleration(가속도) = sumForces(힘) / fMass(질량)
	m_PhysicsInfo.linearAcceleration = m_PhysicsInfo.sumForces / m_PhysicsInfo.fMass;

	// linearVelocity(선형속도) += linearAcceleration(가속도) * changeInTime(시간)
	m_PhysicsInfo.linearVelocity += m_PhysicsInfo.linearAcceleration * changeInTime;

	// centerOfMassLocation(이동위치) += linearVelocity(선형속도) * changeInTime(시간 : m/s)
	m_PhysicsInfo.centerOfMassLocation += m_PhysicsInfo.linearVelocity * changeInTime;

	// 오브젝트의 위치에 이동한 위치 값을 적용해 준다.
	// 1. 이전 프레임에서 이동한 값을 빼서 초기 위치 값을 구한다.
	// 2. 새로 구한 이동값을 더해 준다.

	m_PhysicsInfo.centerOfMassLocation.GetXYZ(m_PhysicsInfo.vPrevPos.x, m_PhysicsInfo.vPrevPos.y, m_PhysicsInfo.vPrevPos.z);
	vector_3d vPos = m_PhysicsInfo.vPrevPos - m_PhysicsInfo.vSavePos;

	m_vPos += vPos;
	m_PhysicsInfo.vSavePos = m_PhysicsInfo.vPrevPos;
}

// 힘 세팅(적용)
void CObject::ForceSetup()
{
	if (m_PhysicsInfo.bForceApplied == false)
	{
		// 오브젝트에 가해진 힘은 단 한번만 적용된다.
		Force(vector_3d(m_PhysicsInfo.vForce.x, m_PhysicsInfo.vForce.y, m_PhysicsInfo.vForce.z));
		m_PhysicsInfo.bForceApplied = true;
	}
	else
	{
		Force(vector_3d(0.0, 0.0, 0.0));
	}

	GravityUpdate();
}

void CObject::GravityUpdate()
{
	if (m_PhysicsInfo.bGravity)
	{
		// 지면에 충돌이 안되었다면 중력 가속.
		m_PhysicsInfo.templinearForces += CalculationFreefallmotion(m_PhysicsInfo.fMass) / 10000;
		m_PhysicsInfo.vForce = vector_3d(
			m_PhysicsInfo.templinearForces.X(),
			m_PhysicsInfo.templinearForces.Y(),
			m_PhysicsInfo.templinearForces.Z());
		m_PhysicsInfo.bForceApplied = false;
	}
}

// 물리 리셋
void CObject::PhysicsReset()
{
	m_PhysicsInfo.centerOfMassLocation.SetXYZ(0, 0, 0);
	m_PhysicsInfo.linearVelocity.SetXYZ(0, 0, 0);
	m_PhysicsInfo.linearAcceleration.SetXYZ(0, 0, 0);
	m_PhysicsInfo.sumForces.SetXYZ(0, 0, 0);
	m_PhysicsInfo.templinearForces.SetXYZ(0, 0, 0);
	m_PhysicsInfo.vPrevPos = vector_3d(0, 0, 0);
	m_PhysicsInfo.vSavePos = vector_3d(0, 0, 0);
}

// 물리 셋업
void CObject::PhysicsSetup(vector_3d _Force, float _Mass, float _GravityAccel)
{
	ZeroMemory(&m_PhysicsInfo, sizeof(m_PhysicsInfo));

	m_PhysicsInfo.vForce = _Force;						// 힘
	m_PhysicsInfo.fMass = _Mass;						// 질량
	m_PhysicsInfo.fGravityAcceleration = _GravityAccel;	// 중력가속
	m_PhysicsInfo.bGravity = true;						// 중력적용
	m_PhysicsInfo.bForceApplied = false;
}

// vector_3d 관련 함수
void CObject::Mass(scalar massValue)
{
	assert(massValue > 0.0);

	m_PhysicsInfo.fMass = massValue;
}
scalar CObject::Mass()
{
	return (m_PhysicsInfo.fMass);
}



void CObject::Location(vector_3d locationCenterOfMass)
{
	m_PhysicsInfo.centerOfMassLocation = locationCenterOfMass;
}
vector_3d CObject::Location()
{
	return (m_PhysicsInfo.centerOfMassLocation);
}

void CObject::LinearVelocity(vector_3d newVelocity)
{
	m_PhysicsInfo.linearVelocity = newVelocity;
}
vector_3d CObject::LinearVelocity()
{
	return (m_PhysicsInfo.linearVelocity);
}

void CObject::LinearAcceleration(vector_3d newAcceleration)
{
	m_PhysicsInfo.linearAcceleration = newAcceleration;
}
vector_3d CObject::LinearAcceleration()
{
	return (m_PhysicsInfo.linearAcceleration);
}

void CObject::Force(vector_3d sumExternalForces)
{
	m_PhysicsInfo.sumForces = sumExternalForces;
}
vector_3d CObject::Force()
{
	return (m_PhysicsInfo.sumForces);
}

// 중력 가속 관련 함수.
vector_3d* CObject::Gravitymotion(vector_3d* pOut, scalar mass)
{
	scalar fy = mass * m_PhysicsInfo.fGravityAcceleration;
	pOut->SetXYZ(0.0f, fy, 0.0f);

	return pOut;
}

vector_3d CObject::CalculationFreefallmotion(scalar mass)
{
	vector_3d FreefallmotionVec;
	Gravitymotion(&FreefallmotionVec, mass);

	return FreefallmotionVec;
}

void CObject::ActionSetup(int _Action, int _Start, int _Last, int _Speed)
{
	ZeroMemory(&m_FrameInfo, sizeof(m_FrameInfo));		// 메모리 초기화
	m_FrameInfo.ActionState = _Action;					// 행동 상태
	m_FrameInfo.FrameStart = _Start;					// 시작 프레임
	m_FrameInfo.FrameX = 0;
	m_FrameInfo.FrameMax = _Last - _Start;				// 맥스 프레임
	m_FrameInfo.FrameCount = 0;
	m_FrameInfo.FrameCountSpeed = _Speed;				// 카운트 초기화.
}

// 사용 안함.
vector_3d* CObject::Projection(vector_3d* pOut, vector_3d* p1, vector_3d* p2)
{
	return nullptr;
}
void CObject::ActionSetup(int _Action, int _Start, int _Last, int _Speed, int _ErNextAction, int _ArNextAction)
{
}


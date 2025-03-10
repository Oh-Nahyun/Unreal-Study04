///////////////

#pragma once

#include "PMMathLib.h"

///// 비트맵의 정보를 저장하는 구조체
typedef struct tagFrameInfo
{
	int ActionState;					///// 취하고 있는 행동
	int FrameX;							///// X축 프레임
	int FrameStart;						///// 시작
	int FrameMax;						///// 최대
	int FrameCount;						///// 카운트
	int FrameCountSpeed;				///// 카운트 속도
}FRAMEINFO, *LPFRAMEINFO;

///// 물리 처리할 구조체 (힘, 중력, 가속도)
typedef struct tagPhysicsInfo
{
	vector_3d	centerOfMassLocation;	//	이동 값.
	vector_3d	linearVelocity;			//	속도
	vector_3d	linearAcceleration;		//	가속도
	vector_3d	sumForces;				//	오브젝트에 가할 힘.
	vector_3d	templinearForces;

	vector_3d	vForce;					//	힘
	vector_3d	vPrevPos;
	vector_3d	vSavePos;

	scalar		fMass;					//	질량
	scalar		fGravityAcceleration;	//	중력 가속도

	bool		bForceApplied;			//	최초의 힘이 가해졌는지 여부
	bool		bCollisionEarth;		//	지면에 닿았는지 여부
	bool		bGravity;				//	중력 적용 여부.
}PHYSICSINFO, * LPPHYSICSINFO;

// 오브젝트 클래스. (공통적으로 사용되는 기능)
class CObject
{
protected:
	PHYSICSINFO		m_PhysicsInfo;		//	물리 정보
	FRAMEINFO		m_FrameInfo;		//	애니메이션 프레임 정보

	vector_3d		m_vPos;
	RECT			m_rcPos;
	INT				m_iMoveFlag;
	INT				m_iLiveFlag;

public:
	CObject();
	virtual ~CObject();

	// 정보 입출력
	vector_3d GetPos() { return m_vPos; }
	RECT* GetRectPos() { return &m_rcPos; }
	void SetLiveFlag(int Flag) { m_iLiveFlag = Flag; }
	int GetLiveFlag() { return m_iLiveFlag; }

	// 물리 관련
	void ForceSetup();
	void GravityUpdate();
	void PhysicsReset();
	void PhysicsUpdate(scalar changeInTime = 1);
	void PhysicsSetup(vector_3d _Force, float _Mass, float _GravityAccel);

	// vector_3d 관련 함수
	void Mass(scalar massValue);
	void Location(vector_3d locationCenterOfMass);
	void LinearVelocity(vector_3d newVelocity);
	void LinearAcceleration(vector_3d newAcceleration);
	void Force(vector_3d sumExternalForces);

	// vector_3d 관련 함수
	scalar Mass();
	vector_3d* Projection(vector_3d* pOut, vector_3d* p1, vector_3d* p2);	// 사용안함.
	vector_3d Location();
	vector_3d LinearVelocity();
	vector_3d LinearAcceleration();
	vector_3d Force();

	vector_3d* Gravitymotion(vector_3d* pOut, scalar mass);
	vector_3d CalculationFreefallmotion(scalar mass);

	// 행동 관련
	void ActionSetup(int _Action, int _Start, int _Last, int _Speed);
	void ActionSetup(int _Action, int _Start, int _Last, int _Speed, int _ErNextAction, int _ArNextAction = 0);	// 사용안함.

	// 가상 함수
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Move() = 0;
};


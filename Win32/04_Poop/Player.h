/////

#pragma once

#include "Object.h"

class CPlayer : public CObject
{
private:
	INT		m_iHp;
	INT		m_iAction;
	FLOAT	m_fSpeed;

public:
	CPlayer();
	virtual ~CPlayer();

	void Init();
	void Update();
	void Render();
	void Move();

	int GetHP() { return m_iHp; }
	float GetSpeed() { return m_fSpeed; }

	void RefreshRect();
	void SetDamage(int Damage) { m_iHp -= Damage; }
	void ActionChange(int action);
};


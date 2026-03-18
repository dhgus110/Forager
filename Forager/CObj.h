#pragma once

#include "Define.h"
#include "BaseStruct.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()	PURE;
	virtual int	 Update()		PURE;
	virtual void Late_Update()  PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	void		Update_Rect();
	//void		Move_Frame();

public:
	const RECT* Get_Rect() const { return &m_tRect; }
	const INFO* Get_Info() const { return &m_tInfo; }
	const bool&	Get_Dead() const { return &m_bDead; }


public:
	void		Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void		Set_Dead() { m_bDead = true; }


protected:
	bool		m_bDead;

	INFO		m_tInfo;
	RECT		m_tRect;

	

};


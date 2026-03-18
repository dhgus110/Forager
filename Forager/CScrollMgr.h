#pragma once
#include "Extension.h"

class CScrollMgr
{
private:
	CScrollMgr();
	CScrollMgr(const CScrollMgr& rhs) = delete;
	CScrollMgr& operator=(CScrollMgr& rScr) = delete;
	~CScrollMgr();

public:
	static CScrollMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance != nullptr) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Late_Update();

public:
	const float	Get_ScrollX() const{ return m_fScrollX; }
	const float	Get_ScrollY() const { return m_fScrollY; }
	const float	Get_TempScrollX() const { return m_fTempScrollX; }
	const float	Get_TempScrollY() const { return m_fTempScrollY; }

	void		Set_ScrollX(float fX) { m_fScrollX += fX; }
	void		Set_ScrollY(float fY) { m_fScrollY += fY; }

	void		Set_TempScrollX(float fX) { m_fTempScrollX += fX; }
	void		Set_TempScrollY(float fY) { m_fTempScrollY += fY; }

	void		Set_OriginalScroll()
	{
		m_fScrollX -= m_fTempScrollX;
		m_fScrollY -= m_fTempScrollY;

		m_fTempScrollX = 0.f;
		m_fTempScrollY = 0.f;
	}

	void		OnEarthquake() { m_bCheckEarthquake = true; m_dwTime = (DWORD)GetTickCount64();}

private:
	void		Update_Earthquake();

private:
	static CScrollMgr* m_pInstance;

	float m_fScrollX, m_fScrollY;
	
	float m_fTempScrollX, m_fTempScrollY;

	DWORD m_dwTime;
	bool  m_bCheckEarthquake;
	int m_iDX[8] = { 2,2,-2,-2,-2,-2,2,2 };
	int m_iDY[8] = { -1, -2,2,1,1,2,-2,-1 };
	int m_iDir;

};


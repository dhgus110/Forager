#include "pch.h"
#include "CScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() :m_fScrollX(0.f), m_fScrollY(0.f), m_iDir(0)
{
	m_fTempScrollX = 0.f;
	m_fTempScrollY = 0.f;

	m_dwTime = (DWORD)GetTickCount64();
	m_bCheckEarthquake =false;
	//ZeroMemory(&m_iDX, sizeof(m_iDX));
	//ZeroMemory(&m_iDY, sizeof(m_iDY));
}				

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Late_Update()
{
	Update_Earthquake();
}

void CScrollMgr::Update_Earthquake()
{
	if (!m_bCheckEarthquake) return;
	
	if (m_dwTime + 30 < (DWORD)GetTickCount64())
	{
	
		m_fScrollX += m_iDX[m_iDir];
		m_fScrollY += m_iDY[m_iDir];
		++m_iDir;
		if (m_iDir >= 7)
		{
			m_bCheckEarthquake = false;
			m_iDir = 0;
		}
		m_dwTime = (DWORD)GetTickCount64();
	}

}



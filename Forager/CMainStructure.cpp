#include "pch.h"
#include "CMainStructure.h"
#include "CManager.h"

CMainStructure::CMainStructure() : m_eId(ST_END)
{
}

CMainStructure::~CMainStructure()
{
	Release();
}

void CMainStructure::Initialize()
{
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 60.f;

}

int CMainStructure::Update()
{
	__super::Update_Position();
	__super::Update_Pulse();
	__super::Update_Rect();
	return UI_NOEVENT;
}

void CMainStructure::Late_Update()
{
}

void CMainStructure::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX),
		static_cast<int>(m_tInfo.fY),
		static_cast<int>(m_tInfo.fCX),
		static_cast<int>(m_tInfo.fCY),
		hMemDC,
		0,
		0,
		250,
		80,
		RGB(255, 0, 255));
}

void CMainStructure::Release()
{
}

void CMainStructure::Setting(MAIN_STRUCTURE_TYPE _id)
{
	m_pFrameKey = enumTotchar_Structure(static_cast<int>(_id));

}

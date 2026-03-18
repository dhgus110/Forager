#include "pch.h"
#include "CFlag.h"
#include "CManager.h"
CFlag::CFlag() :m_iCost(0)
{
}

CFlag::~CFlag()
{
    Release();
}

void CFlag::Initialize()
{
    m_tInfo.fCX = 250.f;
    m_tInfo.fCY = 250.f;

    __super::Start_Pulse(m_tInfo.fCX, m_tInfo.fCY, 1.2f, 1.0f, 0.2f, true);
}

int CFlag::Update()
{
	if (!CManager::UI()->Get_IslandFlag())return 0;
	if (CManager::User()->Get_IsBuyIsland(m_iIslandId)) return UI_DEAD;
    __super::Update_Pulse();
    return 0;
}

void CFlag::Late_Update()
{
}

void CFlag::Render(HDC hDC)
{
	if (!CManager::UI()->Get_IslandFlag()) return;

	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Flag");

	int iScrollX = CManager::Scroll()->Get_ScrollX();
	int iScrollY = CManager::Scroll()->Get_ScrollY();


	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX ) + iScrollX ,
		static_cast<int>(m_tInfo.fY ) + iScrollY ,
		static_cast<int>(m_tInfo.fCX) ,
		static_cast<int>(m_tInfo.fCY) ,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	float fTemp(0);
	CManager::UI()->NumberRender(m_iCost, 40, 80, m_tInfo.fX +30, m_tInfo.fY + 270, &fTemp, true, hDC, false);

	// 각 깃발의 ID와 좌표를 화면에 직접 표시
	//TCHAR szInfo[100];
	//wsprintf(szInfo, L"Flag %d: (%d, %d)", m_iIslandId, (int)m_tInfo.fX, (int)m_tInfo.fY);
	//TextOut(hDC,
	//	static_cast<int>(m_tInfo.fX) + iScrollX,
	//	static_cast<int>(m_tInfo.fY) + iScrollY - 20,
	//	szInfo, lstrlen(szInfo));
}

void CFlag::Release()
{
}

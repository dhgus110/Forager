#include "pch.h"
#include "CSubMenuButton.h"
#include "CManager.h"
#include "Data.h"

CSubMenuButton::CSubMenuButton()
{
	m_bInactive=false;

	m_iCurMenu = 1;
	m_iCursor = 5;
	m_pFrameKey2 = nullptr;
}

CSubMenuButton::~CSubMenuButton()
{
	Release();
}

void CSubMenuButton::Initialize()
{
	m_tInfo.fCX = 74.8f;
	m_tInfo.fCY = 86.f;

}

int CSubMenuButton::Update()
{
	if (m_bDead) return UI_DEAD;


	__super::Update_Pulse();
	//__super::Update_Rect();
	return UI_NOEVENT;
}

void CSubMenuButton::Late_Update()
{
	if (m_iCurMenu == 0) m_pFrameKey = L"MenuTap_active_Equip";
	if (m_iCurMenu == 1) m_pFrameKey = L"MenuTap_active_Item";
	if (m_iCurMenu == 2) m_pFrameKey = L"MenuTap_active_Construct";
	if (m_iCurMenu == 3) m_pFrameKey = L"MenuTap_active_Island";
	if (m_iCurMenu == 4) m_pFrameKey = L"MenuTap_active_Setting";

	if (m_iCursor == 0) m_pFrameKey2 = L"MenuTap_Inactive_Equip";
	if (m_iCursor == 1) m_pFrameKey2 = L"MenuTap_Inactive_Item";
	if (m_iCursor == 2) m_pFrameKey2 = L"MenuTap_Inactive_Construct";
	if (m_iCursor == 3) m_pFrameKey2 = L"MenuTap_Inactive_Island";
	if (m_iCursor == 4) m_pFrameKey2 = L"MenuTap_Inactive_Setting";

}

void CSubMenuButton::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);
	GdiTransparentBlt(hDC,
		(int)UIPos::SubMenu(m_iCurMenu).x,
		(int)CManager::UI()->Get_ObjectBack(UI_MENU_TAP)->Get_Info()->fY -4,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		78,
		86,
		RGB(255, 0, 255));

	Inactive_Render(hDC);
}

void CSubMenuButton::Release()
{
}

void CSubMenuButton::Inactive_Render(HDC hDC)
{
	if ( m_iCurMenu == m_iCursor || !m_bInactive) return;

	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey2);
	GdiTransparentBlt(hDC,
		(int)UIPos::SubMenu(m_iCursor).x,
		(int)CManager::UI()->Get_ObjectBack(UI_MENU_TAP)->Get_Info()->fY -4,
		74,
		86,
		//(int)m_tInfo.fCX-10,
		//(int)m_tInfo.fCY-10,
		hMemDC,
		0,
		0,
		(int)UIPos::SubMenuIconSize(m_iCursor).x,
		(int)UIPos::SubMenuIconSize(m_iCursor).y,
		RGB(255, 0, 255));
}

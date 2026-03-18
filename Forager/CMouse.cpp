#include "pch.h"
#include "CMouse.h"
#include "CManager.h"


CMouse::CMouse(): m_ptMouse{0,0}, m_Offset(false)
{
	ZeroMemory(&m_tEffectFrame, sizeof(FRAME));
	m_bEffect = false;
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 20.f;
    m_tInfo.fCY = 20.f;
    m_fMoveSpeed= 8.0f;
    CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Cursor.bmp", L"Cursor");

	m_tEffectFrame = { 0,2,0,40,(DWORD)GetTickCount64() };

}

int CMouse::Update()
{

	GetCursorPos(&m_ptMouse);

	ScreenToClient(g_hWnd, &m_ptMouse);


	m_tInfo.fX = (float)m_ptMouse.x ;
	m_tInfo.fY = (float)m_ptMouse.y ;

	__super::Update_Rect();

	ShowCursor(FALSE);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
    if (CManager::UI()->Get_IslandFlag())
	{
		int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
		int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

		if (100.f > m_tInfo.fX ) {
			CManager::Scroll()->Set_TempScrollX(m_fMoveSpeed);
			CManager::Scroll()->Set_ScrollX(m_fMoveSpeed);
		}
		if (950.f < m_tInfo.fX ) {
			CManager::Scroll()->Set_TempScrollX(-m_fMoveSpeed);
			CManager::Scroll()->Set_ScrollX(-m_fMoveSpeed);
		}
		if (50.f > m_tInfo.fY ) {
			CManager::Scroll()->Set_TempScrollY(m_fMoveSpeed);
			CManager::Scroll()->Set_ScrollY(m_fMoveSpeed);

		}
		if (550.f < m_tInfo.fY ) {
			CManager::Scroll()->Set_TempScrollY(-m_fMoveSpeed);
			CManager::Scroll()->Set_ScrollY(-m_fMoveSpeed);
		}
    }

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_bEffect = true;
	}
	Move_EffectFrame();

}

void CMouse::Render(HDC hDC)
{

	// int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
	 //int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Cursor");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left,
		(int)m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		15,
		15,
		RGB(255, 0, 255));

	if (m_bEffect) {
		hMemDC = CManager::Bmp()->Find_Img(L"Effect_Pick");
		GdiTransparentBlt(hDC,
			(int)m_tRect.left -25,
			(int)m_tRect.top-25,
			60,
			60,
			hMemDC,
			76 * m_tEffectFrame.iStart,
			0,
			76,
			76,
			RGB(255, 0, 255));
	}


	//TCHAR szMousePos[100];
	//wsprintf(szMousePos, L"Mouse: (%d, %d) | Scroll: (%d, %d)",
	//	m_ptMouse.x, m_ptMouse.y,
	//	(int)CManager::Scroll()->Get_ScrollX(),
	//	(int)CManager::Scroll()->Get_ScrollY());

	//SetBkMode(hDC, TRANSPARENT);  // 텍스트 배경 투명하게
	//SetTextColor(hDC, RGB(255, 255, 0));  // 노란색 텍스트
	//TextOut(hDC, 100, 100, szMousePos, lstrlen(szMousePos));
}

void CMouse::Release()
{
}

void CMouse::Offset()
{
}

void CMouse::Move_EffectFrame()
{
	if (!m_bEffect) return;
	if (m_tEffectFrame.dwTime + m_tEffectFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tEffectFrame.iStart;

		if (m_tEffectFrame.iStart > m_tEffectFrame.iEnd)
		{
			m_tEffectFrame.iStart = 0;
			m_bEffect = false;
		}

		m_tEffectFrame.dwTime = (DWORD)GetTickCount64();

	}
}
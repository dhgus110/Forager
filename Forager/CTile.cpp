#include "pch.h"
#include "CTile.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CManager.h"

CTile::CTile() : m_iDrawID(12), m_iOption(0), m_pFrameKey(nullptr)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_tFrame = { 13,16,0,400,(DWORD)GetTickCount64() };
	

}

int CTile::Update()
{

	CObj::Update_Rect();
	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
	if (m_iOption == 2) Move_Frame();
}

void CTile::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Tile");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_iOption == 2)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX ,
			(int)m_tInfo.fCY ,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{
		BitBlt(hDC,
			m_tRect.left + iScrollX ,
			m_tRect.top  + iScrollY ,
			TILECX,
			TILECY,
			hMemDC,
			TILECX * m_iDrawID,
			0,
			SRCCOPY);
	}

}

void CTile::Release()
{
}

void CTile::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tFrame.iStart;

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 13;

		m_tFrame.dwTime = (DWORD)GetTickCount64();

	}
}


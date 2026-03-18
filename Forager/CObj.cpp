#include "pch.h"
#include "CObj.h"
#include "CManager.h"

CObj::CObj() :m_bDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));

}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = static_cast<LONG>(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

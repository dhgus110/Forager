#include "pch.h"
#include "CSkillButton.h"
#include "CManager.h"

CSkillButton::CSkillButton()
{
}

CSkillButton::~CSkillButton()
{
    Release();
}

void CSkillButton::Initialize()
{
	m_tInfo.fCX = 140.f;
	m_tInfo.fCY = 62.f;

}

int CSkillButton::Update()
{

    __super::Update_Pulse();
    __super::Update_Rect();
	return UI_NOEVENT;
}

void CSkillButton::Late_Update()
{
}

void CSkillButton::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Skill_Btn");

    GdiTransparentBlt(hDC,
        static_cast<int>(m_tInfo.fX),
        static_cast<int>(m_tInfo.fY),
        static_cast<int>(m_tInfo.fCX),
        static_cast<int>(m_tInfo.fCY),
        hMemDC,
        0,
        0,
        140,
        62,
        RGB(255, 0, 255));
}


void CSkillButton::Release()
{
}

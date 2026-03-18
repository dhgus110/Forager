#include "pch.h"
#include "CSkillButtons.h"
#include "Extension.h"
#include "CManager.h"

CSkillButtons::CSkillButtons() :m_pFramekey(nullptr), m_iMotion(0), m_bEffect(false), m_dwTime(0), m_iEffectMotion(0), m_iEffectTime(0)
, m_eID(SK_END)
{
}

CSkillButtons::~CSkillButtons()
{
	Release();
}

void CSkillButtons::Initialize()
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 56.f;

}

int CSkillButtons::Update()
{
	if (m_bEffect)
		Move_Frame();

	__super::Update_Pulse();
	__super::Update_Rect();
	return UI_NOEVENT;
}

void CSkillButtons::Late_Update()
{
}

void CSkillButtons::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX),
		static_cast<int>(m_tInfo.fY),
		static_cast<int>(m_tInfo.fCX),
		static_cast<int>(m_tInfo.fCY),
		hMemDC,
		0 + m_iMotion * 56,
		0,
		56,
		56,
		RGB(255, 0, 255));

	if (m_bEffect) {
		hMemDC = CManager::Bmp()->Find_Img(L"Skill_Effect");

		GdiTransparentBlt(hDC,
			static_cast<int>(m_tInfo.fX) - 170,
			static_cast<int>(m_tInfo.fY) - 170,
			400,
			400,
			hMemDC,
			0 + m_iEffectMotion * 224,
			0,
			224,
			224,
			RGB(255, 0, 255));
	}

}

void CSkillButtons::Release()
{
}

void CSkillButtons::Setting(SKILLID _id)
{
	m_eID = _id;

	int iX = _id % 8;
	int iY = _id / 8;
	int iIndex = iY * 8 + iX;
	//산업
	if (0 <= iX && iX <= 3 && 0 <= iY && iY <= 3)
	{
		m_pFrameKey = L"Skill_I_Inactive";
		m_iMotion = enumToint_Skill(iIndex);
	}
	//경제
	if (4 <= iX && iX <= 7 && 0 <= iY && iY <= 3)
	{
		m_pFrameKey = L"Skill_E_Inactive";
		m_iMotion = enumToint_Skill(iIndex);

	}
	//수확
	if (0 <= iX && iX <= 3 && 4 <= iY && iY <= 7)
	{
		m_pFrameKey = L"Skill_H_Inactive";
		m_iMotion = enumToint_Skill(iIndex);

	}
	//마법
	if (4 <= iX && iX <= 7 && 4 <= iY && iY <= 7)
	{
		m_pFrameKey = L"Skill_M_Inactive";
		m_iMotion = enumToint_Skill(iIndex);

	}


}

void CSkillButtons::Move_Frame()
{
	if (m_dwTime + 20 < (DWORD)GetTickCount64())
	{
		++m_iEffectMotion;

		if (m_iEffectMotion > 8)
			m_iEffectMotion = 0;

		++m_iEffectTime;

		if (m_iEffectTime > 80)
			m_bEffect = false;

		m_dwTime = (DWORD)GetTickCount64();

	}

}

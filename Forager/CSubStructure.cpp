#include "pch.h"
#include "CSubStructure.h"
#include "CManager.h"

CSubStructure::CSubStructure() : m_eId(SST_END)
{
}

CSubStructure::~CSubStructure()
{
	Release();
}

void CSubStructure::Initialize()
{
	m_tInfo.fCX = 220.f;
	m_tInfo.fCY = 40.f;
}

int CSubStructure::Update()
{
	__super::Update_Position();
	__super::Update_Pulse();
	__super::Update_Rect();
	return 0;
}

void CSubStructure::Late_Update()
{
}

void CSubStructure::Render(HDC hDC)
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
		220,
		50,
		RGB(255, 0, 255));
}

void CSubStructure::Release()
{
}

void CSubStructure::Setting(MAIN_STRUCTURE_TYPE _type, SUB_STRUCTURE_TYPE _id)
{
	m_pFrameKey = enumTotchar_Sub_Structure(static_cast<int>(_type) ,static_cast<int>(_id));
}

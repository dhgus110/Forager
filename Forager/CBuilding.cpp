#include "pch.h"
#include "CBuilding.h"
#include "Extension.h"
#include "CManager.h"

CBuilding::CBuilding()
{
    m_eId = SI_END;
    m_iRepeatBuildingCnt = 0;
    m_pFrameKey = nullptr;
    ZeroMemory(&m_tFrame, sizeof(FRAME));
    m_dwTime = 0;
	m_bInteraction = false;

}

CBuilding::~CBuilding()
{
    Release();
}

void CBuilding::Initialize()
{
}

int CBuilding::Update()
{
    return 0;
}

void CBuilding::Late_Update()
{
}

void CBuilding::Render(HDC hDC)
{
}



void CBuilding::Release()
{
}

//void CBuilding::Setting(STRUCTURE_ITEM_ID _id, float _fX, float _fY)
//{
//    m_eId = _id;
//    m_tInfo.fX = _fX;
//    m_tInfo.fY = _fY;
//
//    m_pPrimeKey = enumTotchar_BuildingIcon(static_cast<int>(_id));
//
//}

void CBuilding::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tFrame.iStart;
		
		if (m_tFrame.iStart > m_tFrame.iEnd)
		{
			m_tFrame.iStart = 0;
			if (m_iRepeatBuildingCnt > 0) --m_iRepeatBuildingCnt;
		}

		m_tFrame.dwTime = (DWORD)GetTickCount64();

	}
}



void CBuilding::View_Interaction( HDC hDC, bool _bScroll)
{
	if (!m_bInteraction) return;
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Interacter");

	if (!_bScroll)
		GdiTransparentBlt(hDC,
			static_cast<int>(m_tInfo.fX) - 40.f,
			static_cast<int>(m_tInfo.fY) - 15.f,
			40,
			40,
			hMemDC,
			0, 0,
			56, 56,
			RGB(255, 0, 255));
	else
	{
		int iScrollX = static_cast<int>(CManager::Scroll()->Get_ScrollX());
		int iScrollY = static_cast<int>(CManager::Scroll()->Get_ScrollY());
		GdiTransparentBlt(hDC,
			static_cast<int>(m_tInfo.fX) - 40.f + iScrollX,
			static_cast<int>(m_tInfo.fY) - 15.f + iScrollY,
			40,
			40,
			hMemDC,
			0, 0,
			56, 56,
			RGB(255, 0, 255));
	}


}
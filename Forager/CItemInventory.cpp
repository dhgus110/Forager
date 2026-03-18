#include "pch.h"
#include "CItemInventory.h"
#include "CManager.h"
#include "Data.h"

CItemInventory::CItemInventory() : m_iItemSelect(0)
{
	ZeroMemory(&m_tInfos, sizeof(m_tInfos));
    //ZeroMemory(&m_eIDs, sizeof(m_eIDs));

}
CItemInventory::~CItemInventory()
{
	Release();
}

void CItemInventory::Initialize()
{
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 72.f;
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 8; ++x) {
			m_tInfos[x + y * 8].fX = UIPos::Item_Slot(x + y * 8).x;
			m_tInfos[x + y * 8].fY = UIPos::Item_Slot(x + y * 8).y;

		}
	}
	

}

int CItemInventory::Update()
{
	Update_Slot_Position();
    Update_Pulse();
	return 0;
}

void CItemInventory::Late_Update()
{
}

void CItemInventory::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Item_Inventory_Slot");
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 8; ++x) {
            if (m_bIsPulsing && x + y * 8 == m_iItemSelect)
                GdiTransparentBlt(hDC,
                    static_cast<int>(m_tInfos[x + y * 8].fX),
                    static_cast<int>(m_tInfos[x + y * 8].fY),
                    static_cast<int>(m_tInfo.fCX),
                    static_cast<int>(m_tInfo.fCY),
                    hMemDC,
                    0,
                    0,
                    88,
                    88,
                    RGB(255, 0, 255));
            else 
                  GdiTransparentBlt(hDC,
                    static_cast<int>(m_tInfos[x + y * 8].fX),
                    static_cast<int>(m_tInfos[x + y * 8].fY),
                    72,
                    72,
                    hMemDC,
                    0,
                    0,
                    88,
                    88,
                    RGB(255, 0, 255));
		}
	}



}

void CItemInventory::Release()
{
}


void CItemInventory::MoveToSlot(float fSpeed, float fOffsetX, float fOffsetY)
{
	m_bIsMoving = true;
	m_fGoalX = fOffsetX; //여기서는 fOffsetX 만큼 움직이겠다라 사용하겠음
	m_fGoalY = fOffsetY; 
	m_fMoveSpeed = fSpeed;
}


void CItemInventory::Update_Slot_Position( )
{
    if (!m_bIsMoving)
        return;

    bool allArrived = true;

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 8; ++x) {
            int index = x + y * 8;

            float targetX = UIPos::Item_Slot(index).x + m_fGoalX;
            float targetY = UIPos::Item_Slot(index).y + m_fGoalY;
            float fDiffX = targetX - m_tInfos[index].fX;
            float fDiffY = targetY - m_tInfos[index].fY;

            // 도착 판정  allArrived = true 상태로 다음 거 돌기
            if (abs(fDiffX) < 1.0f && abs(fDiffY) < 1.0f) {
                m_tInfos[index].fX = targetX;
                m_tInfos[index].fY = targetY;
                continue; 
            }

            allArrived = false;


            float fDistance = sqrt(fDiffX * fDiffX + fDiffY * fDiffY);

            // 0으로 나누기 방지
            if (fDistance < 0.001f) {
                m_tInfos[index].fX = targetX;
                m_tInfos[index].fY = targetY;
                continue;
            }

            float fNormalizedX = fDiffX / fDistance;
            float fNormalizedY = fDiffY / fDistance;

            // 이동 거리가 남은 거리보다 크면 바로 도착
            if (m_fMoveSpeed >= fDistance) {
                m_tInfos[index].fX = targetX;
                m_tInfos[index].fY = targetY;
            }
            else {
                // 이동 적용
                m_tInfos[index].fX += fNormalizedX * m_fMoveSpeed;
                m_tInfos[index].fY += fNormalizedY * m_fMoveSpeed;
            }
        }
    }

    // 모든 슬롯이 도착했는지 확인
    if (allArrived) {
        m_bIsMoving = false;
    }
}

void CItemInventory::ReturnToOriginalSlotPos(float fSpeed)
{
	MoveToSlot(fSpeed ,0.f,0.f);
}

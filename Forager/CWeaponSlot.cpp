#include "pch.h"
#include "CWeaponSlot.h"
#include "CManager.h"

CWeaponSlot::CWeaponSlot()
{
}

CWeaponSlot::~CWeaponSlot()
{
	Release();
}

void CWeaponSlot::Initialize()
{
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 72.f;

}

int CWeaponSlot::Update()
{
	Update_Pulse();
	return 0;
}

void CWeaponSlot::Late_Update()
{
}

void CWeaponSlot::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Weapon_Slot");

    GdiTransparentBlt(hDC,
        static_cast<int>(m_tInfo.fX),
        static_cast<int>(m_tInfo.fY),
        static_cast<int>(m_tInfo.fCX),
        static_cast<int>(m_tInfo.fCY),
        hMemDC,
        0,
        0,
        72,
        72,
        RGB(255, 0, 255));
}

void CWeaponSlot::Release()
{
}


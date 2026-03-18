#include "pch.h"
#include "CWeaponInventory.h"
#include "CManager.h"

CWeaponInventory::CWeaponInventory()
{
}

CWeaponInventory::~CWeaponInventory()
{
	Release();
}

void CWeaponInventory::Initialize()
{

	m_tInfo.fCX = 582.f;
	m_tInfo.fCY = 102.f;

}

int CWeaponInventory::Update()
{
	__super::Update_Rect();
	return 0;
}

void CWeaponInventory::Late_Update()
{
}

void CWeaponInventory::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Weapon_Inven");

    GdiTransparentBlt(hDC,
        static_cast<int>(m_tInfo.fX),
        static_cast<int>(m_tInfo.fY),
        static_cast<int>(m_tInfo.fCX),
        static_cast<int>(m_tInfo.fCY),
        hMemDC,
        0,
        0,
        static_cast<int>(m_tInfo.fCX),
        static_cast<int>(m_tInfo.fCY),
        RGB(255, 0, 255));

    hMemDC = CManager::Bmp()->Find_Img(L"Word_Weapon");

    GdiTransparentBlt(hDC,
        static_cast<int>(m_tInfo.fX + m_tInfo.fCX * 0.45f), 
        static_cast<int>(m_tInfo.fY) - 25,
        80,20,
        hMemDC,
        0,
        0,
        80, 20,
        RGB(255, 0, 255));
}

void CWeaponInventory::Release()
{
}

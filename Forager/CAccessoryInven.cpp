#include "pch.h"
#include "CAccessoryInven.h"
#include "CManager.h"

CAccessoryInven::CAccessoryInven()
{
}

CAccessoryInven::~CAccessoryInven()
{
	Release();
}

void CAccessoryInven::Initialize()
{
	m_tInfo.fCX = 170.f;
	m_tInfo.fCY = 240.f;

}

int CAccessoryInven::Update()
{
	return 0;
}

void CAccessoryInven::Late_Update()
{
}

void CAccessoryInven::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Accessory_Inven");

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
}

void CAccessoryInven::Release()
{
}

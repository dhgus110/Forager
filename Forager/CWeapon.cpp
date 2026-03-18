#include "pch.h"
#include "CWeapon.h"
#include "CManager.h"
#include "CMouse.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "CSoundMgr.h"


CWeapon::CWeapon(): m_pFrameKey(nullptr) , m_eState(CWeapon::IDLE), m_ePreState(CWeapon::END),m_dwSwingSpeed(0)
, pTargetResource(nullptr), pTargetMonster(nullptr), m_fAttackDamage(0.f)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));

}

CWeapon::~CWeapon()
{
	Release();
}

void CWeapon::Initialize()
{
	m_tInfo.fCX = 85.f;
	m_tInfo.fCY = 70.f;
	m_tInfo.fX = CManager::Obj()->Get_ObjectBack(OBJ_PLAYER)->Get_Info()->fX;
	m_tInfo.fY = CManager::Obj()->Get_ObjectBack(OBJ_PLAYER)->Get_Info()->fY;

	CManager::Bmp()->Insert_Bmp(L"../Image/Item/Pickax1_Ani.bmp", L"Pickax1_Ani");
	CManager::Bmp()->Insert_Bmp(L"../Image/Item/Pickax1.bmp", L"Pickax1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Item/Pickax2_Ani.bmp", L"Pickax2_Ani");
	CManager::Bmp()->Insert_Bmp(L"../Image/Item/Pickax2.bmp", L"Pickax2");


	m_dwSwingSpeed = 140;
	m_tFrame = { 0, 0, 0,m_dwSwingSpeed, (DWORD)GetTickCount64() };
	m_pFrameKey = L"Pickax1_Ani";

	m_fAttackDamage = dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Get_AttackDamage();
}

int CWeapon::Update()
{
	if (m_bDead) return OBJ_DEAD;

	Follow_Player();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CWeapon::Late_Update()
{
	Motion_Change();
	Look_Cursor();
	Swing_One_Frame();
}

void CWeapon::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left ,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CWeapon::Release()
{
}

void CWeapon::Weapon_Change()
{
	m_pFrameKey = L"Pickax2_Ani";
	m_fAttackDamage = 10.f;
	dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Set_AttackDamage(10.f);
}

void CWeapon::Follow_Player()
{
	float	fScrollX = CManager::Scroll()->Get_ScrollX();
	float	fScrollY = CManager::Scroll()->Get_ScrollY();

	m_tInfo.fX = CManager::Obj()->Get_ObjectBack(OBJ_PLAYER)->Get_Info()->fX + fScrollX;
	m_tInfo.fY = CManager::Obj()->Get_ObjectBack(OBJ_PLAYER)->Get_Info()->fY + fScrollY;

}


void CWeapon::Motion_Change()
{
	if (m_eState != m_ePreState) {
		switch (m_eState)
		{
		case CWeapon::IDLE:
			m_tFrame = { 0, 0, 0,m_dwSwingSpeed, (DWORD)GetTickCount64() };
			break;
		case CWeapon::SWING:
			//사운드
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Swing.mp3", SOUND_EFFECT, 0.7f);

			m_tFrame = { 0, 2, 0,m_dwSwingSpeed, (DWORD)GetTickCount64() };
			break;
		case CWeapon::END:
			break;

		}

		m_ePreState = m_eState;
	}
}

void CWeapon::Look_Cursor()
{
	POINT mouse = dynamic_cast<CMouse*>(CManager::UI()->Get_ObjectBack(UI_MOUSE))->Get_Mouse();
	if (m_tInfo.fX < static_cast<float>(mouse.x)) 
		m_tFrame.iMotion = 0;
	else 
		m_tFrame.iMotion = 1;
}


void CWeapon::Swing_One_Frame()
{
	if (m_eState == CWeapon::SWING) {
		if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
		{
			++m_tFrame.iStart;
			//공격중이고 , 모션 중간일 때 
			if (dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Get_IsAttack()&& m_tFrame.iStart == m_tFrame.iEnd * 0.5)
			{
				// 자원 타겟이 잡혀있으면 히트처리
				if (pTargetResource != nullptr) {
					try {
						CResources* pRes = dynamic_cast<CResources*>(pTargetResource);
						if (pRes) {
							pRes->Set_Hit();
						}
					}
					catch (...) {
						// 예외 발생 시 처리
						//OutputDebugString(L"Resource Hit Error\n");
					}

					pTargetResource = nullptr;
				}

				//보스 타겟이 잡혀있으면 히트 처리 
				if (pTargetMonster != nullptr) {
					dynamic_cast<CBoss*>(pTargetMonster)->Set_Damaged(m_fAttackDamage,m_tInfo.fX);
					pTargetMonster = nullptr;


					CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
					CSoundMgr::Get_Instance()->PlaySound(L"Player_Hit.mp3", SOUND_PLAYER, 0.7f);

				}
			
			}

			if (m_tFrame.iStart > m_tFrame.iEnd) {

				m_tFrame.iStart = 0;
				m_eState = CWeapon::IDLE;
				dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Set_IsAttack(false);
			}
			m_tFrame.dwTime = (DWORD)GetTickCount64();
		}
	}
}
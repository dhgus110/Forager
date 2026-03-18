#include "pch.h"
#include "CResources.h"
#include "CManager.h"
#include "CCommonHpBar.h"
#include "CPlayer.h"
#include "CSoundMgr.h"

CResources::CResources() :m_iHp(0), m_eId(RE_END), m_pFrameKey(nullptr), m_iRandomDir(0)
{
	m_iTileIndex = 0;
	m_eCurState = CResources::IDLE;
	m_ePreState = CResources::END;
	m_pHpBar = nullptr;
	 ZeroMemory( &m_tFrame,sizeof(FRAME)); 
	 ZeroMemory(&m_tEffectFrame, sizeof(FRAME));
	 m_bEffect = false;

}

CResources::~CResources()
{
	Release();
}

void CResources::Initialize()
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 56.f;

	m_iRandomDir = Random::GetInt(0, 1);
	m_tEffectFrame = { 0,8,0,50,(DWORD)GetTickCount64() };
}

int CResources::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

    return OBJ_NOEVENT;
}

void CResources::Late_Update()
{
	Move_Frame();
	Motion_Change();
	Move_EffectFrame();
}

void CResources::Render(HDC hDC)
{
	int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
	int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

	HDC hMemDC = CManager::Bmp()->Find_Img(L"Effect_DigSmoke");
	if (m_bEffect)
		if (m_eId == RE_TREE)
			GdiTransparentBlt(hDC,
				(int)m_tRect.left + iScrollX - 37,
				(int)m_tRect.top + iScrollY + 15,
				130,
				130,
				hMemDC,
				300 * m_tEffectFrame.iStart,
				0,
				300,
				300,
				RGB(255, 0, 255));
		else
			GdiTransparentBlt(hDC,
				(int)m_tRect.left + iScrollX - 37,
				(int)m_tRect.top + iScrollY - 20,
				130,
				130,
				hMemDC,
				300 * m_tEffectFrame.iStart,
				0,
				300,
				300,
				RGB(255, 0, 255));


	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);
	if (m_eId == RE_TREE)
		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScrollX,
			(int)m_tRect.top + iScrollY - TILECY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

	else
		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScrollX,
			(int)m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));


}

void CResources::Release()
{
	CManager::Spawner()->Set_ResourceCount(-1);
	CManager::Scroll()->OnEarthquake();

	if(m_pHpBar !=nullptr)
		m_pHpBar->Set_Dead();
}


void CResources::Set_ResourceId(RESOURCEID _id, int _iIndex)
{
	m_eId = _id;
	m_iHp = CManager::User()->Get_ResourceHp(_id);
	//Motion_Change();

	switch (_id)
	{
	case RE_BERRY:
		m_pFrameKey = L"Berry";
		break;
	case RE_COAL:
		m_pFrameKey = L"Coal";
		break;
	case RE_GOLD:
		m_pFrameKey = L"Gold_Ore";
		break;
	case RE_IRON:
		m_pFrameKey = L"Iron_Ore";
		break;
	case RE_STONE:
		m_pFrameKey = L"Stone";
		break;
	case RE_TREE:
		m_pFrameKey = L"Tree";
		m_tInfo.fCY = 168.f;
		break;
	}

}

void CResources::Move_Frame()
{
	if (m_eId == RE_END)
		return;
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tFrame.iStart;

		if (m_tFrame.iStart > m_tFrame.iEnd)
		{
			if (m_eCurState == CResources::HIT)
			{
				m_eCurState = CResources::IDLE;
				m_iHp -= (int)dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Get_AttackDamage();
				if (m_iHp <= 0)
					m_bDead = true;
			}

			m_tFrame.iStart = 0;
		}

		m_tFrame.dwTime = (DWORD)GetTickCount64();

	}
}
void CResources::Move_EffectFrame()
{
	if (!m_bEffect) return; 
	if (m_tEffectFrame.dwTime + m_tEffectFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tEffectFrame.iStart;

		if (m_tEffectFrame.iStart > m_tEffectFrame.iEnd)
		{
			m_tEffectFrame.iStart = 0;
			m_bEffect = false;
		}

		m_tEffectFrame.dwTime = (DWORD)GetTickCount64();

	}
}

void CResources::Motion_Change()
{
	if (m_eCurState != m_ePreState) {
		if (m_eCurState == CResources::IDLE) {
			switch (m_eId)
			{
			case RE_BERRY:
				m_tFrame = { 0, 3, 0, 250,(DWORD)GetTickCount64() };
				break;
			case RE_COAL:
				m_tFrame = { 0, 0, m_iRandomDir, 10000,(DWORD)GetTickCount64() };
				break;
			case RE_GOLD:
				m_tFrame = { 0, 0, m_iRandomDir, 10000,(DWORD)GetTickCount64() };
				break;
			case RE_IRON:
				m_tFrame = { 0, 0, m_iRandomDir, 10000,(DWORD)GetTickCount64() };
				break;
			case RE_STONE:
				m_tFrame = { 0, 0, 0, 10000,(DWORD)GetTickCount64() };
				break;
			case RE_TREE:
				m_tFrame = { 0, 0, 0, 10000,(DWORD)GetTickCount64() };
				break;
			}
		}
		else if (m_eCurState == CResources::HIT) {
			switch (m_eId)
			{
			case RE_BERRY:
				m_tFrame = { 0, 1, 1, 120,(DWORD)GetTickCount64() };
				CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_Berry.wav", SOUND_RESOURCE, 0.7f);
				break;

			case RE_COAL:
				m_tFrame = { 0, 1, m_iRandomDir, 120,(DWORD)GetTickCount64() };
				CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_Mineral.mp3", SOUND_RESOURCE, 0.7f);
				break;

			case RE_GOLD:
				m_tFrame = { 0, 1, m_iRandomDir, 120,(DWORD)GetTickCount64() };
				CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_Mineral.mp3", SOUND_RESOURCE, 0.7f);
				break;

			case RE_IRON:
				m_tFrame = { 0, 1, m_iRandomDir, 120,(DWORD)GetTickCount64() };
				CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_Mineral.mp3", SOUND_RESOURCE, 0.7f);
				break;

			case RE_STONE:
				m_tFrame = { 0, 1, 0, 120,(DWORD)GetTickCount64() };
				CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_Rock.wav", SOUND_RESOURCE, 0.7f);
				break;

			case RE_TREE:
				m_tFrame = { 0, 4, 0, 24,(DWORD)GetTickCount64() };
				CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_Wood.wav", SOUND_RESOURCE, 0.7f);
				break;
			}

			if(m_pHpBar!= nullptr)
				dynamic_cast<CCommonHpBar*>(m_pHpBar)->DecreaseHp
				(dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Get_AttackDamage());

		
		}

		m_ePreState = m_eCurState;
	}
}


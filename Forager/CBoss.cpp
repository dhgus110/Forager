#include "pch.h"
#include "CBoss.h"
#include "CManager.h"
#include "CBossHpBar.h"
#include "CSoundMgr.h"

CBoss::CBoss()
{
	m_iDamagedDir = 0;
	m_bCheckDamagedAnimation = false;
	m_bDeadAnimation = false;
	m_bAttackEffect = false;
	m_bAttack = false;
	m_bEnableAttack = false;
	m_dwTime = 0;
	m_dwCheckAttackTime = 0;
	m_fTargetPosX = 0.f;
	m_fTargetPosY = 0.f;

	m_iImageSizeY = 0;

	m_eState = MO_IDLE;
	m_ePreState = MO_END;

	m_fMoveSpeed = 0.f;
	m_fHp = 0.f;
	m_fAttackSpeed = 0.f;
	m_iAttackDamage = 0;

	m_fJumpTime = 0.f;
	m_fJumpSpeed = 0.f;

	m_pFrameKey = nullptr;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	ZeroMemory(&m_tEffectFrame, sizeof(FRAME));
	ZeroMemory(&m_tDamagedFrame, sizeof(FRAME)); 


	m_pHpBar = nullptr;

}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 112.f;
	m_tInfo.fCY = 112.f;

	m_fMoveSpeed = 2.f;
	m_fHp = 100.f;
	m_fAttackSpeed = 10.f;
	m_iAttackDamage = 10;

	m_fJumpSpeed = 4.f;

	m_pFrameKey = L"Boss";
	m_tFrame = { 0,7,0,200,(DWORD)GetTickCount64() };
	m_iImageSizeY = 112;

	m_tEffectFrame = { 0,7,0,100, (DWORD)GetTickCount64() };
	m_tDamagedFrame = { 0,13,0,20,(DWORD)GetTickCount64() };
}

int CBoss::Update()
{
	if (m_bDead) return OBJ_DEAD;

	Update_State();
	Effect_Frame();
	Damaged_Frame();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{

	Move_Frame();
	Motion_Change();

	if (m_fHp <= 0) m_eState = MO_DEAD;
}

void CBoss::Render(HDC hDC)
{
	int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
	int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX,
		(int)m_tRect.top - (m_iImageSizeY- 112) + iScrollY,
		(int)m_tInfo.fCX,
		m_iImageSizeY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		112,
		m_iImageSizeY,
		RGB(255, 0, 255));

	if (m_bAttackEffect)
	{
		hMemDC = CManager::Bmp()->Find_Img(L"Effect_Boss_Jump");

		GdiTransparentBlt(hDC,
			(int)m_tRect.left - 20 + iScrollX,
			(int)m_tRect.top + 60 + iScrollY ,
			200,
			200,
			hMemDC,
			92 * m_tEffectFrame.iStart,
			92 * m_tEffectFrame.iMotion,
			92,
			92,
			RGB(255, 0, 255));
	}

	if (m_bCheckDamagedAnimation && !m_bDeadAnimation)
	{
		hMemDC = CManager::Bmp()->Find_Img(L"Boss_Dead"); //보스죽는 이펙트를 작게 처리해서 피격 이펙트처럼
		GdiTransparentBlt(hDC,
			m_iDamagedDir + iScrollX ,
			(int)m_tRect.top  + iScrollY + 30,
			40,
			40,
			hMemDC,
			112 * m_tDamagedFrame.iStart,
			112 * m_tDamagedFrame.iMotion,
			112,
			112,
			RGB(255, 0, 255));
	}
}

void CBoss::Release()
{

}


void CBoss::Update_State()
{
	switch (m_eState)
	{
	case MO_IDLE:
		Update_Idle();
		break;

	case MO_RUN:
		break;

	case MO_ATTACK:
		Update_Attack_Jump();
		break;

	case MO_DAMAGED:
		break;

	case MO_DEAD:
		m_bDeadAnimation = true;
		break;

	case MO_END:
		break;


	}
}

void CBoss::Update_Idle()
{
	if (m_bAttack && m_bEnableAttack) return;

	if (m_dwTime + 3500 < (DWORD)GetTickCount64())
	{
		m_bEnableAttack = true;
	}

}

void CBoss::Set_Damaged(float _fDamage, float _fPlayerX)
{
	m_fHp -= _fDamage;
	if(m_pHpBar != nullptr)
		dynamic_cast<CBossHpBar*>(m_pHpBar)->DecreaseHp(_fDamage);

	if (!m_bCheckDamagedAnimation)
	{
		m_bCheckDamagedAnimation = true;
		int ScrollX = CManager::Scroll()->Get_ScrollX();
		if (m_tInfo.fX > _fPlayerX - ScrollX)
			m_iDamagedDir = (int)(m_tInfo.fX - 60.f);

		else
			m_iDamagedDir = (int)(m_tInfo.fX + 30.f);
	}

}

void CBoss::Setting_Attack(float _fPlayerX, float _fPlayerY)
{
	if (!m_bEnableAttack) return;

	m_bAttack = true;
	m_fTargetPosX = _fPlayerX;
	m_fTargetPosY = _fPlayerY;

	m_bAttack = true;
	m_bEnableAttack = false;
	m_eState = MO_ATTACK;

	m_dwCheckAttackTime = (DWORD)GetTickCount64();
}

void CBoss::Update_Attack_Jump()
{
	if (!m_bAttack) return;

	float		fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);
	fWidth = m_fTargetPosX - m_tInfo.fX;
	fHeight = m_fTargetPosY - m_tInfo.fY;

	//도착 판정
	if (abs(fWidth) < 1.0f && abs(fHeight) < 1.0f)
	{
		m_tInfo.fX = m_fTargetPosX;

		m_eState = MO_IDLE;
		m_bAttack = false;
		m_dwTime = (DWORD)GetTickCount64();
		m_bAttackEffect = true;

		CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
		CSoundMgr::Get_Instance()->PlaySound(L"SlimeLand.wav", SOUND_BOSS, 0.7f);

		return;
	}
	//공격 시간 지나도 여기 있으면 빠져 나옴
	if(m_dwCheckAttackTime + 1800 <(DWORD)GetTickCount64())
	{
		m_tInfo.fX = m_fTargetPosX;

		m_eState = MO_IDLE;
		m_bAttack = false;
		m_dwTime = (DWORD)GetTickCount64();
		m_bAttackEffect = true;
		return;
	}
	// Angle 구하기
	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	fRadian = acosf(fWidth / fDiagonal);  

	float fAngle = fRadian * (180 / PI);
	if (float(m_fTargetPosY) > m_tInfo.fY) fAngle *= -1.f;


	//목적지로 이동하기
	m_tInfo.fX += cosf(fAngle * (PI / 180)) * m_fMoveSpeed;
	m_tInfo.fY -= sinf(fAngle * (PI / 180)) * m_fMoveSpeed;



}


void CBoss::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tFrame.iStart;

		if (m_tFrame.iStart > m_tFrame.iEnd)
		{
			m_tFrame.iStart = 0;
			if (m_bDeadAnimation) m_bDead = true;
		}
		m_tFrame.dwTime = (DWORD)GetTickCount64();

	}
}

void CBoss::Effect_Frame()
{
	if (!m_bAttackEffect) return;

	if (m_tEffectFrame.dwTime + m_tEffectFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tEffectFrame.iStart;

		if (m_tEffectFrame.iStart > m_tEffectFrame.iEnd)
		{
			m_tEffectFrame.iStart = 0;

			m_bAttackEffect = false;
		}
		m_tEffectFrame.dwTime = (DWORD)GetTickCount64();

	}
}

void CBoss::Damaged_Frame()
{
	if (!m_bCheckDamagedAnimation) return;

	if (m_tDamagedFrame.dwTime + m_tDamagedFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tDamagedFrame.iStart;
		if (m_tDamagedFrame.iStart > m_tDamagedFrame.iEnd)
		{
			m_tDamagedFrame.iStart = 0;
			m_bCheckDamagedAnimation = false;
		}
		m_tDamagedFrame.dwTime = (DWORD)GetTickCount64();
	}
}

void CBoss::Motion_Change()
{
	if (m_eState != m_ePreState) {
		switch (m_eState)
		{
		case MO_IDLE:
			m_pFrameKey = L"Boss";
			m_tFrame = { 0,7,0,200,(DWORD)GetTickCount64() };
			m_iImageSizeY = 112;
			break;
		case MO_RUN:
			break;
		case MO_ATTACK:
			m_pFrameKey = L"Boss_Jump";
			m_tFrame = { 0,7,0,100,(DWORD)GetTickCount64() };
			m_iImageSizeY = 448;


			CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"SlimeJump.wav", SOUND_BOSS, 0.7f);
		
			break;
		case MO_DAMAGED:
			//m_pFrameKey = L"Boss_Dead";
			//m_tDamagedFrame = { 0,13,0,20,(DWORD)GetTickCount64() };
			break;
		case MO_DEAD:
			m_pFrameKey = L"Boss_Dead";
			m_tFrame = { 0,13,0,40,(DWORD)GetTickCount64() };
			m_iImageSizeY = 112;
			break;
		case MO_END:
			break;
		default:
			break;
		}
	}

	m_ePreState = m_eState;
}


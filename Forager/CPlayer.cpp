#include "pch.h"
#include "CPlayer.h"
#include "CManager.h"
#include "CMouse.h"
#include "CWeapon.h"
#include "CSoundMgr.h"
CPlayer::CPlayer()
{
	m_bIsAttack = false;
	m_eState = PL_IDLE;
	m_ePreState = PL_END;
	m_eDir = DIR_END;
	m_fMoveSpeed = 0.f;
	m_fHp = 0.f;
	m_fSwingSpeed = 0.f;
	m_fAttackDamage = 0.f;
	m_iCurIsland = 0;

	m_dwInvincibleTime = 0;
	m_bInvincible = false;

	m_pFrameKey = nullptr;

	m_dwStepSoundTime = 0;

	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 56.f;

	m_fMoveSpeed = 5.f;
	m_fHp = 300.f;
	m_fSwingSpeed = 10.f;
	m_fAttackDamage = 1.f;


	CManager::Bmp()->Insert_Bmp(L"../Image/Player/Player_Idle.bmp", L"Player_Idle");
	CManager::Bmp()->Insert_Bmp(L"../Image/Player/Player_Run.bmp", L"Player_Run");
	CManager::Bmp()->Insert_Bmp(L"../Image/Player/Player_Damaged.bmp", L"Player_Damaged");


	m_tFrame = { 0, 2, 0,150, (DWORD)GetTickCount64() };
	m_pFrameKey = L"Player_Idle";

}

int CPlayer::Update()
{
	if (m_bDead) return OBJ_DEAD;

	Key_Input();
	Update_Invincible();
	Update_Controller();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	Move_Frame();
	Motion_Change();
	Look_Cursor();
	Offset();
}

void CPlayer::Render(HDC hDC)
{
	int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
	int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

	HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX ,
		(int)m_tInfo.fCY ,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX, 
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));




}

void CPlayer::Release()
{
}


void CPlayer::Look_Cursor()
{
	int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();

	POINT mouse = dynamic_cast<CMouse*>(CManager::UI()->Get_ObjectBack(UI_MOUSE))->Get_Mouse();
	if (m_tInfo.fX < static_cast<float>(mouse.x) - iScrollX)
		m_tFrame.iMotion = 0;
	else
		m_tFrame.iMotion = 1;


}

void CPlayer::Key_Input()
{
	if (CManager::Key()->Key_Pressing('W'))
	{
		m_eDir = DIR_U;
		m_eState = PL_RUN;
		if (CManager::Key()->Key_Pressing('A')) m_eDir = DIR_LU;
		if (CManager::Key()->Key_Pressing('D')) m_eDir = DIR_RU;

	}
	else if (CManager::Key()->Key_Pressing('S')) {
		m_eDir = DIR_D;
		m_eState = PL_RUN;
		if (CManager::Key()->Key_Pressing('A')) m_eDir = DIR_LD;
		if (CManager::Key()->Key_Pressing('D')) m_eDir = DIR_RD;
	}
	else if (CManager::Key()->Key_Pressing('A'))
	{
		m_eDir = DIR_L;
		m_eState = PL_RUN;
	}
	else if (CManager::Key()->Key_Pressing('D')) {
		m_eDir = DIR_R;
		m_eState = PL_RUN;
	}
	else {
		m_eDir = DIR_END;
		if(m_eState != PL_DAMAGED)
			m_eState = PL_IDLE;
	}

	if (CManager::Key()->Key_Down(VK_LBUTTON)) {
		m_eDir = DIR_END;
		m_eState = PL_ATTACK;
	}



}

void CPlayer::Update_Controller()
{
	switch (m_eState)
	{
	case PL_IDLE:
		m_pFrameKey = L"Player_Idle";
		break;
	case PL_RUN:
		Update_Move();
		break;

	case PL_ATTACK:
		Update_Attack();
		break;
		
	case PL_DAMAGED:
		Update_Damaged();
		break;

	case PL_MINE:
		Update_Mine();
		break;

	case PL_DEAD:
		break;

	case PL_END:
		break;
	}
}


void CPlayer::Update_Move()
{
	m_pFrameKey = L"Player_Run";

	switch (m_eDir)
	{
	case DIR_L:
		m_tInfo.fX -= m_fMoveSpeed;
		break;
	case DIR_R:
		m_tInfo.fX += m_fMoveSpeed;
		break;
	case DIR_U:
		m_tInfo.fY -= m_fMoveSpeed;
		break;
	case DIR_D:
		m_tInfo.fY += m_fMoveSpeed;
		break;
	case DIR_LU:
		m_tInfo.fX -= m_fMoveSpeed / sqrtf(2.f);
		m_tInfo.fY -= m_fMoveSpeed / sqrtf(2.f);
		break;
	case DIR_LD:
		m_tInfo.fX -= m_fMoveSpeed / sqrtf(2.f);
		m_tInfo.fY += m_fMoveSpeed / sqrtf(2.f);
		break;
	case DIR_RU:
		m_tInfo.fX += m_fMoveSpeed / sqrtf(2.f);
		m_tInfo.fY -= m_fMoveSpeed / sqrtf(2.f);
		break;
	case DIR_RD:
		m_tInfo.fX += m_fMoveSpeed / sqrtf(2.f);
		m_tInfo.fY += m_fMoveSpeed / sqrtf(2.f);
		break;
	}


	for (int i = 0; i < 9; ++i) {
		ISLAND pos = CManager::User()->Get_Island()[i];
		if (pos.iMinX * BASE_SIZE <= m_tInfo.fX
			&& m_tInfo.fX <= pos.iMaxX * BASE_SIZE 
			&& pos.iMinY * BASE_SIZE <= m_tInfo.fY
			&& m_tInfo.fY <= pos.iMaxY * BASE_SIZE)
		{
			m_iCurIsland = i;
			break;
		}
	}


	//사운드
	if (m_dwStepSoundTime + 300 < (DWORD)GetTickCount64())
	{
		int rand = Random::GetInt(0, 1);
	
		CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER_STEP);
		if(rand == 0) CSoundMgr::Get_Instance()->PlaySound(L"Player_Step1.wav", SOUND_PLAYER_STEP, 0.7f);
		else  CSoundMgr::Get_Instance()->PlaySound(L"Player_Step2.wav", SOUND_PLAYER_STEP, 0.7f);
	
		m_dwStepSoundTime = (DWORD)GetTickCount64();
	}

}

void CPlayer::Update_Attack()
{
	m_pFrameKey = L"Player_Idle";
	dynamic_cast<CWeapon*>(CManager::Obj()->Get_ObjectBack(OBJ_EQUIP))->Set_Swing();


}

void CPlayer::Update_Damaged()
{
	m_pFrameKey = L"Player_Damaged";

}

void CPlayer::Update_Mine()
{
	m_pFrameKey = L"Player_Idle";

}

void CPlayer::Update_Death()
{
}

void CPlayer::Update_Invincible()
{
	if (!m_bInvincible) return;

	if (m_dwInvincibleTime + 500 < (DWORD)GetTickCount64())
	{
		m_bInvincible = false;
	}
}

void CPlayer::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
	{
		++m_tFrame.iStart;

		if (m_tFrame.iStart > m_tFrame.iEnd){
			m_tFrame.iStart = 0;
			if (m_eState == PL_DAMAGED) m_eState = PL_IDLE;
		}
		

		m_tFrame.dwTime = (DWORD)GetTickCount64();

	}
}

void CPlayer::Motion_Change()
{
	if (m_eState != m_ePreState)
	{
		switch (m_eState)
		{
		case PL_IDLE:
			m_tFrame = { 0, 2, 0,150, (DWORD)GetTickCount64() };
			break;
		case PL_RUN:
			m_tFrame = { 0, 3, 0,150, (DWORD)GetTickCount64() };
			break;
		case PL_ATTACK:
			m_tFrame = { 0, 2, 0,150, (DWORD)GetTickCount64() };
			break;
		case PL_DAMAGED:
			m_tFrame = { 0, 11, 0,150, (DWORD)GetTickCount64() };
			//사운드
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Attacked.mp3", SOUND_PLAYER, 0.7f);

			break;
		case PL_MINE:
			m_tFrame = { 0, 2, 0, 150,(DWORD)GetTickCount64() };
			break;
		case PL_DEAD:
			
			break;
		case PL_END:
			break;

		}

		m_ePreState = m_eState;
	}
}


void CPlayer::Offset()
{
	if (CManager::UI()->Get_IslandFlag()) return;

	int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
	int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

	if (OFFSET_MIN_X > m_tInfo.fX + iScrollX)
		CManager::Scroll()->Set_ScrollX(m_fMoveSpeed);

	if (OFFSET_MAX_X < m_tInfo.fX + iScrollX)
		CManager::Scroll()->Set_ScrollX(-m_fMoveSpeed);

	if (OFFSET_MIN_Y > m_tInfo.fY + iScrollY)
		CManager::Scroll()->Set_ScrollY(m_fMoveSpeed);

	if (OFFSET_MAX_Y < m_tInfo.fY + iScrollY)
		CManager::Scroll()->Set_ScrollY(-m_fMoveSpeed);
}
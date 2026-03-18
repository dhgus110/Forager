#pragma once
#include "Define.h"
#include "baseStruct.h"

// 1. 고정된 위치에 UI가 있을 것 인가?
// 2. 무언갈 따라다니는 UI 인가?


class CUI
{
public:
	CUI();
	virtual ~CUI() {}

public:
	virtual void	Initialize() PURE;
	virtual int		Update() PURE;
	virtual void	Late_Update() PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release() PURE;

public:
	const bool& Get_Dead() const { return m_bDead; }
	const INFO* Get_Info() const { return &m_tInfo; }

public:
	void Set_Dead() { m_bDead = true; }
	void Set_Info(INFO _info) { m_tInfo = _info; }
	void Set_FollowTarget(INFO* _pTarget) { m_pTarget = _pTarget; }
	void Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX; m_tInfo.fY = _fY;
		int a = 0;
	}
	void Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	//랜더링 숨기기
	void Set_ShowRender(bool _b) { m_bShowRender = _b; }  

	// UI 이동 함수
public:
	void MoveToPosition(float fGoalX, float fGoalY, float fSpeed = 10.0f);
	void Update_Position();
	void SetOriginalPos(float fX, float fY) { m_fOriginalX = fX; m_fOriginalY = fY; }
	void ReturnToOriginalPos(float fSpeed = 10.0f);
	const bool Get_IsMoving() const { return m_bIsMoving; }

	// Scale Pulsing 함수
public:
	//현재 사이즈 x , 현재 사이즈 y , 최대크기 , 최소크기, 속도, 반복유무
	void Start_Pulse(float fsizeX,float fsizeY,float fMaxVal = 1.2f, float fMinVal = 1.0f, float fSpeed = 1.0f, bool repeat = false );
	void Update_Pulse();
	void Stop_Pulse();
	const bool Get_IsPulse() { return m_bIsPulsing; }
	
	


protected:
	void			Update_Rect();

protected:
	bool m_bDead;
	bool m_bShowRender;
	bool m_bFollowTarget; // UI가 따라다니는 타겟이 있는지

	//이동 함수 관련 변수
	bool  m_bIsMoving;     // 현재 이동 중인지 여부
	float m_fGoalX;     // 목표 X 좌표
	float m_fGoalY;     // 목표 Y 좌쵸
	float m_fMoveSpeed;   // 이동 속도
	float m_fOriginalX;   // 원래 X 좌표
	float m_fOriginalY;   // 원래 Y 좌표

	//Scale Pulsing
	bool  m_bIsPulsing;			// 시작할거임?
	bool  m_bPulseRefeat;			// 반복할거임?
	bool  m_bPulseReverse;		// 스케일 반대로 곱하기
	float m_fOriginalSizeX;		// 원래 X 사이즈
	float m_fOriginalSizeY;		// 원래 Y 사이즈
	float m_fPulseMaxValue;		// 최대크기
	float m_fPulseMinValue;		// 최소크기
	float m_fPulseCurRate;		// 현재 비율
	float m_fPulseSpeed;		// 스피드


	const INFO* m_pTarget; //타겟 좌표

	INFO m_tInfo;
	RECT m_tRect;

	const TCHAR* m_pFrameKey;

	FRAME m_tFrame;

};


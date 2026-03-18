#pragma once
#include "CScene.h"

class CStage : public CScene
{
public:
	CStage();
	~CStage();

public:
	void Initailize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const int Get_CurScreen() const { return m_iCurScreen; }

public:
	void Set_CurScreen(int _i) { m_iCurScreen = _i; }
	void Set_MenuDarkLight(bool _b) { m_bJoinMenuDarkLight = _b; }

private:
	void Key_Input();
	void RenderLighting(HDC hDC, bool bPlayer);
	void AllDayCycle(); //낮 밤 시간 조절

private:
	 
	//화면 알파값 넣을 건지 안 넣을건지
	bool m_bJoinMenuDarkLight;

	DWORD m_dwResourceRespawnTime; //자원 리스폰 시간
	int  m_iResourceCnt; 

	DWORD m_dwDayTime; //낮밤 시간 조절
	bool  m_bDay; //낮이면 true , 밤이면 false
	bool  m_bNightChange; //서서히 어두워졌다가 정점 찍고 서서히 밝아지도록
	int	  m_iAlphaValue; //투명도 값
	int   m_iDayCnt; //낮 시간 가는거 저장하는 변수

	// 0 : 게임화면
	// 1 : 메뉴 탭 화면
	// 2 : 스킬 창 화면
	int m_iCurScreen;

	//test
	int		m_iTest;
};


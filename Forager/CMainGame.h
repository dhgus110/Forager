#pragma once
#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render();
	void	Release();

private:
	void	ViewFPS();

private:
	int				m_iFPS;
	DWORD			m_dwTime;
	TCHAR			m_szFPS[32];

	HDC		m_DC;

};


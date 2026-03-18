#pragma once
#include "CScene.h"
class CEdit :  public CScene
{
public:
	CEdit();
	~CEdit();

public:
	void Initailize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void	Key_Input();

private:
	const TCHAR* m_pFrameKey;
	int		m_iDrawID;
	int		m_iOption;

	TCHAR m_szTest[32];
};


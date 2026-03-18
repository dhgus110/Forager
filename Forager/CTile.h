#pragma once
#include "CObj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	const int& Get_DrawID() { return m_iDrawID; }
	void	Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }

	const int& Get_Option() { return m_iOption; }
	void	Set_Option(int iOption) { m_iOption = iOption; }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;


private:
	void	Move_Frame();

private:

	int		m_iDrawID;

	// 옵션
	// 0. 이동 가능 , 짓기 가능,  	// 다리 건설 시  0번으로 변경 / 이동 가능!  짓기 가능/ 타일 옵션 바꿔주자
	// 1. 이동 불가능 (물)
	// 2. 애니 메이션 (절벽)( 이동 불가능)
	// 3. 나머지 건물 건설 / 이동 불가 ! / 타일 옵션 바꿔주자 

	int		m_iOption;

	const TCHAR* m_pFrameKey;
	FRAME		 m_tFrame;
};


#pragma once
#include "CObj.h"
#include "CSoundMgr.h"

class CBuilding : public CObj
{
public:
	CBuilding();
	~CBuilding();

public:
	void Initialize() override;
	int	 Update()	 override;
	void Late_Update()   override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const STRUCTURE_ITEM_ID& Get_Id() const { return m_eId; }
	const bool Get_Interaction() const { return m_bInteraction; }

public:
	void Set_Interaction(bool _b) {
		m_bInteraction = _b;
		if (!m_bInteraction&& _b)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_STRUCTURE);
			CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_STRUCTURE, 0.7f);
		}
	}


protected:
	void Move_Frame();
	void View_Interaction(HDC hDC, bool _bScroll);

protected:
	STRUCTURE_ITEM_ID	m_eId;

	int					m_iRepeatBuildingCnt;
	bool				m_bInteraction;

	const TCHAR*		m_pFrameKey;
	FRAME				m_tFrame;

	DWORD				m_dwTime;
};


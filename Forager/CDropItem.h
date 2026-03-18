#pragma once
#include "CObj.h"
#include "Enum.h"

class CDropItem : public CObj
{
public:
	CDropItem();
	~CDropItem();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const bool Get_IsLand() const { return m_bIsLand; }
	const ITEMID& Get_ItemId() const {return m_eId;}

	//무슨 아이템인지 결정해주기
public:
	void DropResourceItem(RESOURCEID _id, int _iOption);
	void DropFishTrap(); //Resourceid 에 통발 추가하면 안돼서,,

	//todo
	void Drop_Furnance(ITEMID _id);


private:
	void One_Jump();
	void Move_Frame();



private:
	bool m_bJump;
	bool m_bIsLand;
	float m_fRandomDropX;
	float m_fRandJumpLimitTime;
	float m_fJumpTime;
	float m_fJumpSpeed;
	int m_iCount; // 합쳐진 drop아이템 수량

	ITEMID m_eId;

	const TCHAR* m_pFrameKey1;

	DWORD	m_dwTime;
	FRAME		 m_tFrame;
};


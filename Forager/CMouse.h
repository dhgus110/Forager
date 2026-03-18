#pragma once
#include "CUI.h"
class CMouse : public CUI
{
public:
    CMouse();
    ~CMouse();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    const POINT& Get_Mouse() const { return m_ptMouse; }
    const bool Get_Offset() const { return m_Offset; }

public:
    void Set_Offset(bool _b) { m_Offset = _b; }
private:
    void Offset();

    void Move_EffectFrame();

private:
    POINT	m_ptMouse;
    bool    m_Offset;

    FRAME		 m_tEffectFrame;
    bool		m_bEffect;
};


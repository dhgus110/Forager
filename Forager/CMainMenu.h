#pragma once
#include "CScene.h"
class CMainMenu : public CScene
{
public:
    CMainMenu();
    ~CMainMenu();

public:
    void Initailize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

};


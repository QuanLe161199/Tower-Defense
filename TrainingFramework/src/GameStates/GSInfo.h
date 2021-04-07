#pragma once
#include "GSMenu.h"
#include "GameStateBase.h"
#include "Text.h"

class GSInfo :
	public GameStateBase
{
public:
	GSInfo();
	~GSInfo();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void HandleMouseMoveEvent(int x, int y);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_infoLink;
	std::shared_ptr<Sprite2D> m_frame;
	std::shared_ptr<GameButton>	m_button;
	std::list<std::shared_ptr<Text>> m_textInfo;
	float m_time = 0.f;
};
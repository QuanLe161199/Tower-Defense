#pragma once 
#include "Sprite2D.h"

class Tower;

enum TowerStates
{
	NOT_ACTIVED = 0,
	OPTIONS,
	LEVEL_1,
	UPDATE,
	LEVEL_2,
};

class GameButton : public Sprite2D
{
public:
	GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	SetOnClick(TowerStates nextState, void	(*pBtClick)(TowerStates state));
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();

private:
	void	(*m_pBtClick)();
	bool	m_isHandle;

};

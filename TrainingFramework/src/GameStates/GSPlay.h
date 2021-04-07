#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Animation.h"
#include "Enemy.h"
#include "Tower.h"
#include "map.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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


	void SetNewPostionForBullet();

private:
	float m_currentTime = 0.f;
	float m_latency = 0.f;
	bool m_stop = false;
	float m_time = 0.f;
	float m_startEvaluate;
	std::shared_ptr<Text> m_textMoney;

	std::shared_ptr<Animation> m_backGround;
	std::shared_ptr<Map> m_map;
	std::list<std::shared_ptr<GameButton>> m_listButton;
	std::vector<std::shared_ptr<Enemy>> m_listEnemy;
	std::list<std::shared_ptr<Tower>> m_listTower;
	std::shared_ptr<Sprite2D> m_frameMoney;
	std::shared_ptr<Sprite2D> m_evaluate;
	std::shared_ptr<Sprite2D> m_evaluateRank;
};


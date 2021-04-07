#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameObject/Animation.h"
#include "WinUser.h"

#include <stdio.h>
#include <Windows.h>
#include <math.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int m_music;
extern int m_musicPrevious;
extern int m_sound;
extern float m_money;
extern int m_round;

int numEnemies;
bool m_pause = false;
bool endGame = false;

GSPlay::GSPlay()
{

}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//backgound
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	m_backGround = std::make_shared<Animation>(model, shader, texture, 5.f, 0.f, 0.f, 0.2f, 0.f, 1.0f);
	m_backGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_backGround->SetSize(screenWidth, screenHeight);

	//pause button
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 25, 25);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		if (m_pause)
		{
			m_pause = false;
		}
		else
		{
			m_pause = true;
		}
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		});
	m_listButton.push_back(button);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_reduction");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(25, 25);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		if (m_music)
		{
			ResourceManagers::GetInstance()->PauseSound("play.mp3");
		}
		m_pause = false;
		m_money = 1.f;
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		});
	m_listButton.push_back(button);

	// choose the round
	if(m_round == 1)
	{
		m_map = std::make_shared<Map>("map1_play", 2000.f, 12, 19,
			//list enemy road positions
			std::make_pair(163.f, 61.f),
			std::make_pair(162.f, 233.f),
			std::make_pair(129.f, 239.f),
			std::make_pair(134.f, 345.f),
			std::make_pair(236.f, 354.f),
			std::make_pair(234.f, 458.f),
			std::make_pair(128.f, 466.f),
			std::make_pair(134.f, 572.f),
			std::make_pair(384.f, 567.f),
			std::make_pair(389.f, 279.f),
			std::make_pair(316.f, 274.f),
			std::make_pair(315.f, 195.f),

			//list tower positions
			std::make_pair(117.f, 188.f),
			std::make_pair(188.f, 295.f),
			std::make_pair(171.f, 408.f),
			std::make_pair(200.f, 515.f),
			std::make_pair(331.f, 514.f),
			std::make_pair(348.f, 404.f),
			std::make_pair(284.f, 313.f));

		//create list tower (not actived)
		std::shared_ptr<Tower> tower;
		for (register int i = 0; i < m_map->m_numTowers; i++)
		{
			tower = std::make_shared<Tower>(m_map->m_listTower[i].first, m_map->m_listTower[i].second);
			m_listTower.push_back(tower);
		}


		//create enemies
		std::shared_ptr<Enemy> enemy;
		for (register int i = 0; i < 10; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				50.f, 50.f, 50.f, 60.f, 5.f, (float)i * 2, "enemy_drone");
			m_listEnemy.push_back(enemy);
		}
		for (register int i = 0; i < 5; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				60.f, 60.f, 200.f, 40.f, 5.f, (float)i / 3 + 30.f, "enemy_knight");
			m_listEnemy.push_back(enemy);
		}
		enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
			100.f, 100.f, 1000.f, 30.f, 1.f, 60.f, "enemy_overlord");
		m_listEnemy.push_back(enemy);
	}
	else if (m_round == 2)
	{
		m_map = std::make_shared<Map>("map2_play", 2000.f, 12, 19,
			//list enemy road positions
			std::make_pair(314.f, 57.f),
			std::make_pair(316.f, 240.f),
			std::make_pair(346.f, 243.f),
			std::make_pair(346.f, 343.f),
			std::make_pair(242.f, 355.f),
			std::make_pair(241.f, 458.f),
			std::make_pair(344.f, 462.f),
			std::make_pair(344.f, 568.f),
			std::make_pair(95.f, 569.f),
			std::make_pair(97.f, 277.f),
			std::make_pair(166.f, 271.f),
			std::make_pair(165.f, 190.f),

			//list tower positions
			std::make_pair(373.f, 193.f),
			std::make_pair(278.f, 288.f),
			std::make_pair(311.f, 409.f),
			std::make_pair(290.f, 514.f),
			std::make_pair(143.f, 517.f),
			std::make_pair(145.f, 414.f),
			std::make_pair(181.f, 329.f));

		//create list tower (not actived)
		std::shared_ptr<Tower> tower;
		for (register int i = 0; i < m_map->m_numTowers; i++)
		{
			tower = std::make_shared<Tower>(m_map->m_listTower[i].first, m_map->m_listTower[i].second);
			m_listTower.push_back(tower);
		}


		//create enemies
		std::shared_ptr<Enemy> enemy;
		for (register int i = 0; i < 10; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				50.f, 50.f, 50.f, 100.f, 5.f, (float)i * 2, "enemy_motor");
			m_listEnemy.push_back(enemy);
		}
		for (register int i = 0; i < 15; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				60.f, 60.f, 150.f, 40.f, 5.f, (float)i / 2 + 20.f, "enemy_ice");
			m_listEnemy.push_back(enemy);
		}
		enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
			100.f, 100.f, 3000.f, 25.f, 1.f, 60.f, "enemy_skeleton");
		m_listEnemy.push_back(enemy);
	}
	else
	{
	m_map = std::make_shared<Map>("map3_play", 2000.f, 13, 24,
		//list enemy road positions
		std::make_pair(99.f, 96.f),
		std::make_pair(386.f, 106.f),
		std::make_pair(387.f, 274.f),
		std::make_pair(282.f, 276.f),
		std::make_pair(270.f, 215.f),
		std::make_pair(165.f, 216.f),
		std::make_pair(168.f, 352.f),
		std::make_pair(236.f, 363.f),
		std::make_pair(246.f, 394.f),
		std::make_pair(353.f, 402.f),
		std::make_pair(350.f, 574.f),
		std::make_pair(128.f, 574.f),
		std::make_pair(121.f, 501.f),

		//list tower positions
		std::make_pair(152.f, 152.f),
		std::make_pair(317.f, 150.f),
		std::make_pair(334.f, 218.f),
		std::make_pair(216.f, 270.f),
		std::make_pair(328.f, 335.f),
		std::make_pair(107.f, 272.f),
		std::make_pair(284.f, 449.f),
		std::make_pair(418.f, 447.f),
		std::make_pair(398.f, 627.f),
		std::make_pair(289.f, 516.f),
		std::make_pair(82.f, 613.f));

		//create list tower (not actived)
		std::shared_ptr<Tower> tower;
		for (register int i = 0; i < m_map->m_numTowers; i++)
		{
			tower = std::make_shared<Tower>(m_map->m_listTower[i].first, m_map->m_listTower[i].second);
			m_listTower.push_back(tower);
		}


		//create enemies
		std::shared_ptr<Enemy> enemy;
		for (register int i = 0; i < 10; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				50.f, 50.f, 100.f, 50.f, 5.f, (float)i / 2, "enemy_skeleton");
			m_listEnemy.push_back(enemy);
		}
		for (register int i = 0; i < 5; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				50.f, 50.f, 50.f, 70.f, 5.f, 10 + (float)i, "enemy_drone");
			m_listEnemy.push_back(enemy);
		}
		for (register int i = 0; i < 10; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				70.f, 70.f, 200.f, 35.f, 5.f, 25 + (float)i, "enemy_fire");
			m_listEnemy.push_back(enemy);
		}
		for (register int i = 0; i < 15; i++)
		{
			enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
				60.f, 60.f, 150.f, 40.f, 5.f, (float)i / 5 + 60.f, "enemy_knight");
			m_listEnemy.push_back(enemy);
		}
		enemy = std::make_shared<Enemy>(m_map->m_listPoint[0].first, m_map->m_listPoint[0].second,
			120.f, 120.f, 5000.f, 25.f, 1.f, 90.f, "enemy_wraith");
		m_listEnemy.push_back(enemy);
	}

	numEnemies = m_listEnemy.size();

	//evaluation
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("effect_victory");
	m_evaluate = std::make_shared<Sprite2D>(model, shader, texture);
	m_evaluate->Set2DPosition(screenWidth / 2, screenHeight / 2 - 100);
	m_evaluate->SetSize(500, 300);

	//evaluation rank
	texture = ResourceManagers::GetInstance()->GetTexture("effect_none");
	m_evaluateRank = std::make_shared<Sprite2D>(model, shader, texture);
	m_evaluateRank->Set2DPosition(screenWidth / 2, screenHeight / 2 - 100);
	m_evaluateRank->SetSize(200, 200);

	//display money
	texture = ResourceManagers::GetInstance()->GetTexture("frame_money");
	m_frameMoney = std::make_shared<Sprite2D>(model, shader, texture);
	m_frameMoney->Set2DPosition(screenWidth / 2, 27);
	m_frameMoney->SetSize(200, 50);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_textMoney = std::make_shared<Text>(shader, font, "MONEY: ", TEXT_COLOR::BLACK, 1.0);
	m_textMoney->Set2DPosition(Vector2(screenWidth / 2 - 55, 33));

	m_startEvaluate = m_map->m_evaluate;
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listTower)
	{
		it->m_main->HandleTouchEvents(x, y, bIsPressed);
		for (auto op : it->m_listOption)
		{
			op->HandleTouchEvents(x, y, bIsPressed);
			if (op->IsHandle()) break;
		}
		if ((it)->m_main->IsHandle()) break;
	}
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::HandleMouseMoveEvent(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	// turn on music when start
	if (m_music && m_musicPrevious && m_time < 0.001)
	{
		ResourceManagers::GetInstance()->PlaySound("play.mp3", true);
	}
	m_time += deltaTime;
	if (m_music && !m_musicPrevious)
	{
		//turn on music
		m_musicPrevious = 1;
		ResourceManagers::GetInstance()->PlaySound("play.mp3", true);
	}
	if (!m_music && m_musicPrevious)
	{
		//turn off music
		m_musicPrevious = 0;
		ResourceManagers::GetInstance()->PauseSound("play.mp3");
	}
	if (!m_pause)
	{
		// change display button if it change
		for (auto it : m_listButton)
		{
			if (it->checkTexture("button_continue"))
			{
				it->changeTexture("button_pause");
			}
		}
		for (auto it : m_listTower)
		{
			it->m_notActived->Update(deltaTime);
			it->ChangeState();
		}
		if (!m_stop)
		{
			m_backGround->Update(deltaTime);

			// if haven't lost, then continue playing
			if (m_map->m_evaluate > 0)
			{
				m_currentTime += deltaTime;

				//update money
				m_money += deltaTime / 5;
				m_textMoney->ChangeText("MONEY: " + std::to_string((int)m_money));

				for (auto it : m_listTower)
				{
					if (it->m_selected == -1)
					{
						for (register int i = 0; i < numEnemies; i++)
						{
							// ưhen the distance is less than the range
							if ((sqrt((it->m_x - m_listEnemy[i]->m_x) * (it->m_x - m_listEnemy[i]->m_x) +
								(it->m_y - m_listEnemy[i]->m_y) * (it->m_y - m_listEnemy[i]->m_y)) < it->m_range) &&
								m_currentTime > m_listEnemy[i]->m_appearTime && m_listEnemy[i]->m_currentHealth > 0)
							{
								it->m_selected = i;
							}
						}
					}
					else if ((m_listEnemy[it->m_selected]->m_currentHealth > 0) &&
						(sqrt((it->m_x - m_listEnemy[it->m_selected]->m_x) * (it->m_x - m_listEnemy[it->m_selected]->m_x) +
							(it->m_y - m_listEnemy[it->m_selected]->m_y) * (it->m_y - m_listEnemy[it->m_selected]->m_y)) < it->m_range))
					{
						it->m_attackTime += it->m_attackSpeed * deltaTime;
						if (it->m_attackTime > ATTACK_TIME)
						{
							auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
							auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
							auto texture = ResourceManagers::GetInstance()->GetTexture(it->m_textureBullet);

							std::shared_ptr<Sprite2D> bullet = std::make_shared<Sprite2D>(model, shader, texture);
							bullet->Set2DPosition(it->m_x, it->m_y);
							bullet->SetSize(it->m_width / 3, it->m_height / 3);
							it->m_listBullet.push_back(bullet);
							it->m_attackTime = 0.f;
							m_listEnemy[it->m_selected]->m_currentHealth -= it->m_damage;
							if (m_sound)
							{
								if (it->m_type == 1)
								{
									ResourceManagers::GetInstance()->PlaySound("tower_cannon.mp3", false);
								}
								else if (it->m_type == 2)
								{
									ResourceManagers::GetInstance()->PlaySound("tower_bow.mp3", false);
								}
								else
								{
									ResourceManagers::GetInstance()->PlaySound("tower_laze.mp3", false);
								}
							}
						}
						it->Update(deltaTime, m_listEnemy[it->m_selected]->m_x, m_listEnemy[it->m_selected]->m_y);
					}
					else
					{
						while (it->m_listBullet.size())
						{
							it->m_listBullet.pop_back();
						}
						it->m_selected = -1;
					}
				}

				// if there are no enemies alive then stop the game
				m_stop = true;
				for (auto it : m_listEnemy)
				{
					if (it->m_isAlive)
					{
						m_stop = false;
						if (m_currentTime > it->m_appearTime)
						{
							if (it->m_pointMap == m_map->m_numPoints)
							{
								m_map->m_evaluate -= it->m_startHealth;
								it->m_currentHealth = -1.f;
								it->m_isAlive = false;
							}
							else
							{
								if (it->m_x < m_map->m_listPoint[it->m_pointMap].first - it->m_amountError)
								{
									it->m_main->m_trend = TREND_Right;
									it->Update(deltaTime);
								}
								else if (it->m_x > m_map->m_listPoint[it->m_pointMap].first + it->m_amountError)
								{
									it->m_main->m_trend = TREND_Left;
									it->Update(deltaTime);
								}
								else if ((int)it->m_y > (int)m_map->m_listPoint[it->m_pointMap].second + it->m_amountError)
								{
									it->m_main->m_trend = TREND_Up;
									it->Update(deltaTime);
								}
								else if ((int)it->m_y < (int)m_map->m_listPoint[it->m_pointMap].second - it->m_amountError)
								{
									it->m_main->m_trend = TREND_Down;
									it->Update(deltaTime);
								}
								else
								{
									if (it->m_pointMap < m_map->m_numPoints)
									{
										it->m_pointMap++;
									}
								}
							}
						}
					}
					else
					{
						if (it->m_currentSoulTime < SOUL_TIME)
						{
							it->Update(deltaTime);
						}
					}
				}
			}
			else
			{
				m_evaluate->changeTexture("effect_defeat");
				m_latency += deltaTime;
			}
		}
	}
	else
	{
		// change display button if it change
		for (auto it : m_listButton)
		{
			if (it->checkTexture("button_pause"))
			{
				it->changeTexture("button_continue");
			}
		}
	}
}

void GSPlay::Draw()
{
	m_backGround->Draw();
	m_map->m_display->Draw();
	for (auto it : m_listTower)
	{
		for (auto bullet : it->m_listBullet)
		{
			bullet->Draw();
		}
		it->m_notActived->Draw();
		it->m_main->Draw();
	}

	for (auto it : m_listEnemy)
	{
		if (it->m_pointMap != m_map->m_numPoints)
		{
			if (it->m_isAlive)
			{
				if (m_currentTime > it->m_appearTime)
				{
					it->m_shadow->Draw();
				}
			}
			else if (it->m_currentSoulTime < SOUL_TIME && it->m_currentSoulTime > SOUL_TIME_ERROR_AMOUNT)
			{
				it->m_soul->Draw();
			}
		}
	}
	for (auto it : m_listEnemy)
	{
		if (it->m_pointMap != m_map->m_numPoints)
		{
			if (it->m_isAlive)
			{
				if (m_currentTime > it->m_appearTime)
				{
					it->m_main->Draw();
				}
			}
			else if (it->m_currentSoulTime < SOUL_TIME && it->m_currentSoulTime > SOUL_TIME_ERROR_AMOUNT)
			{
				it->m_soul->Draw();
			}
		}
	}
	for (auto it : m_listEnemy)
	{
		if (it->m_pointMap != m_map->m_numPoints)
		{
			if (it->m_isAlive)
			{
				if (m_currentTime > it->m_appearTime)
				{
					it->m_healthBarAmount->Draw();
				}
			}
			else if (it->m_currentSoulTime < SOUL_TIME && it->m_currentSoulTime > SOUL_TIME_ERROR_AMOUNT)
			{
				it->m_soul->Draw();
			}
		}
	}
	for (auto it : m_listEnemy)
	{
		if (it->m_pointMap != m_map->m_numPoints)
		{
			if (it->m_isAlive)
			{
				if (m_currentTime > it->m_appearTime)
				{
					it->m_healthBarFrame->Draw();
				}
			}
			else if (it->m_currentSoulTime < SOUL_TIME && it->m_currentSoulTime > SOUL_TIME_ERROR_AMOUNT)
			{
				it->m_soul->Draw();
			}
		}
	}
	if ((m_map->m_evaluate <= 0 && m_latency > 0.1) || m_stop)
	{
		if (!endGame)
		{
			if (m_evaluate->checkTexture("effect_victory"))
			{
				if ((int)m_map->m_evaluate == (int)m_startEvaluate)
				{
					m_evaluateRank->changeTexture("effect_victory_3");
				}
				else if (m_map->m_evaluate > m_startEvaluate * 0.5)
				{
					m_evaluateRank->changeTexture("effect_victory_2");
				}
				else
				{
					m_evaluateRank->changeTexture("effect_victory_1");
				}
				if (m_sound)
				{
					ResourceManagers::GetInstance()->PlaySound("victory.mp3", false);
				}
			}
			else
			{
				if (m_sound)
				{
					ResourceManagers::GetInstance()->PlaySound("defeat.mp3", false);
				}
			}
			endGame = true;
		}
		m_evaluate->Draw();
		m_evaluateRank->Draw();
		if (m_music)
		{
			ResourceManagers::GetInstance()->PauseSound("play.mp3");
		}
	}
	for (auto it : m_listTower)
	{
		for (auto op : it->m_listOption)
		{
			op->Draw();
		}
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_frameMoney->Draw();
	m_textMoney->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}


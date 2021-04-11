#include "Enemy.h"
#include <stdio.h>

extern int m_sound;

Enemy::Enemy()
{
}

Enemy::Enemy(float x, float y, float width, float height, float health,
	float speed, float amountError, float appearTime, std::string textureName)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_currentHealth = health;
	m_startHealth = health;
	m_speed = speed;
	m_amountError = amountError;
	m_appearTime = appearTime;
	m_currentSoulTime = 0.f;
	m_isAlive = true;
	m_pointMap = 0;

	// display enemy
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(textureName);
	m_main = std::make_shared<Animation>(model, shader, texture, 10.f, 0.f, 0.f, 0.05f, TREND_Down, 4.0f);
	m_main->Set2DPosition(m_x, m_y - m_height / POSITIONING_ADJUSTMENT_FACTOR);
	m_main->SetSize(m_width, m_height);

	//display enemy soul
	texture = ResourceManagers::GetInstance()->GetTexture("effect_soul");
	m_soul = std::make_shared<Animation>(model, shader, texture, 12.f, 0.f, 0.f, 0.05f, 0.f, 1.0f);
	m_soul->Set2DPosition(m_x, m_y - m_height / POSITIONING_ADJUSTMENT_FACTOR);
	m_soul->SetSize(m_width, m_height);

	//display shadow of enemy
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("effect_shadow");
	m_shadow = std::make_shared<Sprite2D>(model, shader, texture);
	m_shadow->Set2DPosition(m_x, m_y + m_height / POSITIONING_ADJUSTMENT_FACTOR / 2);
	m_shadow->SetSize(m_width / 3, m_height / 3);

	//display frame healthbar enemy
	texture = ResourceManagers::GetInstance()->GetTexture("healthbar_frame");
	m_healthBarFrame = std::make_shared<Sprite2D>(model, shader, texture);
	m_healthBarFrame->Set2DPosition(m_x, m_y - 3.5 * m_height / POSITIONING_ADJUSTMENT_FACTOR);
	m_healthBarFrame->SetSize(m_width * 0.8, m_height / 10);

	//display amount healthbar enemy
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("healthbar_green");
	m_healthBarAmount = std::make_shared<Animation>(model, shader, texture, 1.f, 0.f, 0.f, 0.05f, TREND_Left, 1.f);
	m_healthBarAmount->Set2DPosition(m_x, m_y - 3.5 * m_height / POSITIONING_ADJUSTMENT_FACTOR);
	m_healthBarAmount->SetSize(m_width * 0.8, m_height / 10);
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltaTime)
{
	if (m_isAlive)
	{
		switch ((int)m_main->m_trend)
		{
		case (int)TREND_Down:
			m_y += deltaTime * m_speed;
			break;
		case (int)TREND_Up:
			m_y -= deltaTime * m_speed;
			break;
		case (int)TREND_Left:
			m_x -= deltaTime * m_speed;
			break;
		case (int)TREND_Right:
			m_x += deltaTime * m_speed;
			break;
		default:
			break;
		}

		if (m_currentHealth <= 0)
		{
			m_isAlive = false;
		}

		//distance of enemy
		m_distance += m_speed * deltaTime;

		// change position of enemy
		m_main->Set2DPosition(m_x, m_y - m_height / POSITIONING_ADJUSTMENT_FACTOR);
		m_shadow->Set2DPosition(m_x, m_y + m_height / POSITIONING_ADJUSTMENT_FACTOR / 2);
		m_healthBarFrame->Set2DPosition(m_x, m_y - 3.5 * m_height / POSITIONING_ADJUSTMENT_FACTOR);
		m_healthBarAmount->Set2DPosition(m_x + 0.4 * m_width * (m_currentHealth - m_startHealth) / m_startHealth,
			m_y - 3.5 * m_height / POSITIONING_ADJUSTMENT_FACTOR);
		m_healthBarAmount->SetSize(m_width * 0.8 * m_currentHealth / m_startHealth, m_height / 10);

		// update properties
		m_main->Update(deltaTime);
		m_healthBarAmount->Update(deltaTime);

		// change color of health bar
		if (m_currentHealth / m_startHealth < 0.5)
		{
			if (m_healthBarAmount->checkTexture("healthbar_green"))
			{
				m_healthBarAmount->changeTexture("healthbar_red");
			}
		}
	}
	else
	{
		if (m_currentSoulTime < 0.001 && m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("test.mp3", false);
		}
		m_currentSoulTime += deltaTime;
		if (m_currentSoulTime < SOUL_TIME)
		{
			m_y -= deltaTime * SOUL_SPEED;
			m_soul->Set2DPosition(m_x, m_y - m_height / POSITIONING_ADJUSTMENT_FACTOR);
			m_soul->Update(deltaTime);
		}
	}
}

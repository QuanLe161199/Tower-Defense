#pragma once
#include "Animation.h"
#include "ResourceManagers.h"

#define TREND_Left	0.0f
#define TREND_Up	1.0f
#define TREND_Right	2.0f
#define TREND_Down	3.0f

#define POSITIONING_ADJUSTMENT_FACTOR 5.f

#define SOUL_TIME 2.f
#define SOUL_TIME_ERROR_AMOUNT 0.1f
#define SOUL_SPEED 20.f


class Enemy
{
public:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	float m_currentHealth;
	float m_startHealth;
	float m_speed;
	bool m_isAlive;
	int m_pointMap;
	float m_amountError; //the amount of error with the map point when moving
	float m_appearTime;
	float m_currentSoulTime;
	float m_distance = 0.f;
	std::string m_texture;
	std::shared_ptr<Animation> m_main;
	std::shared_ptr<Sprite2D> m_shadow;
	std::shared_ptr<Animation> m_healthBarAmount;
	std::shared_ptr<Animation> m_soul;
	std::shared_ptr<Sprite2D> m_healthBarFrame;

	Enemy();
	Enemy(float x, float y, float width, float height, float health, float speed, float amountError, float appearTime, std::string textureName);
	~Enemy();

	void Update(GLfloat deltaTime);
};
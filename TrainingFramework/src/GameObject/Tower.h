#pragma once
#include "Animation.h"
#include "ResourceManagers.h"

#define SIZE_NOT_ACTIVED 40.f
#define SIZE_LEVEL_1 = 50.f;
#define SIZE_LEVEL_2 = 60.f

#define BULLET_ERROR_AMOUNT 10.f
#define BULLET_SPEED 150.f

#define TAN_225 0.4142135624f
#define COT_225 2.414213562f

#define NOT_ACTIVED 0
#define OPTIONS 1
#define LEVEL1 2
#define LEVEL2 3

#define CANNON 1
#define BOW 2
#define LAZE 3

#define ATTACK_TIME 100.f

class Tower
{
public:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	float m_damage = 0.f;
	float m_attackTime = ATTACK_TIME;
	float m_attackSpeed = 0.f;
	float m_range = 0.f;
	std::string m_trend = "n";
	int m_state = NOT_ACTIVED;
	int m_type = 0;
	int m_selected;
	std::string m_texture;
	std::string m_textureBullet;
	std::shared_ptr<Sprite2D> m_main;
	std::list<std::shared_ptr<Sprite2D>> m_listBullet;
	std::shared_ptr<Animation> m_notActived;
	std::list<std::shared_ptr<Sprite2D>> m_listOption;

	Tower();
	Tower(float x, float y);
	~Tower();
	void Update(GLfloat deltaTime, float enemyPositionX, float enemyPositionY);
	void ChangeState();
};

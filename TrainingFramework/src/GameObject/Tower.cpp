#include "Tower.h"

extern float m_money;
extern int m_sound;

Tower::Tower()
{
}

Tower::Tower(float x, float y)
{
	m_x = x;
	m_y = y;
	m_width = SIZE_NOT_ACTIVED;
	m_height = SIZE_NOT_ACTIVED;
	m_selected = -1;

	//create display tower not actived
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("tower_not_actived");
	m_notActived = std::make_shared<Animation>(model, shader, texture, 8.f, 0.f, 0.f, 0.05f, 4.f, 8.0f);
	m_notActived->Set2DPosition(m_x, m_y);
	m_notActived->SetSize(m_width, m_height);


	//create cannon tower
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("effect_none");
	m_main = std::make_shared<Sprite2D>(model, shader, texture);
	m_main->Set2DPosition(m_x, m_y);
	m_main->SetSize(m_width, m_height);
}

Tower::~Tower()
{
}

void Tower::Update(GLfloat deltaTime, float enemyPositionX, float enemyPositionY)
{
	//std::cout << "size: " << m_listBullet.size() << std::endl;
	//if (m_listBullet.size() > 1)
	//	std::cout << "size: " << m_listBullet.size() << std::endl;
	int removeBullet = 0;
	for (auto it : m_listBullet)
	{
		Vector2 pos = it->Get2DPosition();
		float bulletX = pos.x;
		float bulletY = pos.y;
		if (abs(bulletY - enemyPositionY) > 4)
		{
			float angle = (enemyPositionX - bulletX) / (enemyPositionY - bulletY);
			if (enemyPositionX - bulletX > 0)
			{
				if (angle > 0)
				{
					bulletX += BULLET_SPEED * deltaTime * angle;
					bulletY += BULLET_SPEED * deltaTime;
					if (angle < TAN_225)
					{
						m_trend = "s";
					}
					else if (angle < COT_225)
					{
						m_trend = "se";
					}
					else
					{
						m_trend = "e";
					}
				}
				else
				{
					bulletX -= BULLET_SPEED * deltaTime * angle;
					bulletY -= BULLET_SPEED * deltaTime;
					if (-angle < TAN_225)
					{
						m_trend = "n";
					}
					else if (-angle < COT_225)
					{
						m_trend = "ne";
					}
					else
					{
						m_trend = "e";
					}
				}
			}
			else
			{
				if (angle > 0)
				{
					bulletX -= BULLET_SPEED * deltaTime * angle;
					bulletY -= BULLET_SPEED * deltaTime;
					if (angle < TAN_225)
					{
						m_trend = "n";
					}
					else if (angle < COT_225)
					{
						m_trend = "nw";
					}
					else
					{
						m_trend = "w";
					}
				}
				else
				{
					bulletX += BULLET_SPEED * deltaTime * angle;
					bulletY += BULLET_SPEED * deltaTime;
					if (-angle < TAN_225)
					{
						m_trend = "s";
					}
					else if (-angle < COT_225)
					{
						m_trend = "sw";
					}
					else
					{
						m_trend = "w";
					}
				}
			}
		}
		// reset bullet
		if (abs(enemyPositionX - bulletX) < BULLET_ERROR_AMOUNT && abs(enemyPositionY - bulletY) < BULLET_ERROR_AMOUNT)
		{
			removeBullet++;
		}

		// reset trend of tower
		std::string nextTrend = m_texture + m_trend;
		if (!m_main->checkTexture(nextTrend))
		{
			m_main->changeTexture(nextTrend);
		}

		it->Set2DPosition(bulletX, bulletY);
		m_main->Update(deltaTime);
	}
	for (register int i = 0; i < removeBullet; i++)
	{
		m_listBullet.pop_front();
	}
}

void Tower::ChangeState()
{
	// control to the tower
	if (m_state == LEVEL1 && m_main->m_isHandle)
	{
		m_main->m_isHandle = false;
		if (m_money > 2)
		{
			m_state = LEVEL2;
			switch (m_type)
			{
			case CANNON:
				m_main->changeTexture("tower_cannon2_n");
				m_texture = "tower_cannon2_";
				break;
			case BOW:
				m_main->changeTexture("tower_bow2_sw");
				m_texture = "tower_bow2_";
				break;
			case LAZE:
				m_main->changeTexture("tower_laze2_e");
				m_texture = "tower_laze2_";
				break;
			}
			m_damage *= 1.5;
			m_width *= 1.5;
			m_height *= 1.5;
			m_main->SetSize(m_width, m_height);
			if (m_sound)
			{
				ResourceManagers::GetInstance()->PlaySound("finish_contruction.mp3", false);
			}

			m_money -= 2;
		}
	}
	if (m_main->m_isHandle)
	{
		switch (m_state)
		{
		case NOT_ACTIVED:
			m_state = OPTIONS;
			m_main->m_isHandle = false;
			break;
		case OPTIONS:
			m_listOption.pop_back();
			m_listOption.pop_back();
			m_listOption.pop_back();
			m_state = LEVEL1;
			m_main->m_isHandle = false;
			break;
		}
	}
	if (m_state == OPTIONS)
	{
		if (!m_listOption.size())
		{
			//create options
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto texture = ResourceManagers::GetInstance()->GetTexture("tower_cannon_icon");
			std::shared_ptr<Sprite2D> choice = std::make_shared<Sprite2D>(model, shader, texture);
			choice->Set2DPosition(m_x, m_y - m_height / 1.3);
			choice->SetSize(m_width, m_height);
			m_listOption.push_back(choice);

			texture = ResourceManagers::GetInstance()->GetTexture("tower_bow_icon");
			choice = std::make_shared<Sprite2D>(model, shader, texture);
			choice->Set2DPosition(m_x - m_width / 1.5, m_y + m_height / 1.5);
			choice->SetSize(m_width, m_height);
			m_listOption.push_back(choice);

			texture = ResourceManagers::GetInstance()->GetTexture("tower_laze_icon");
			choice = std::make_shared<Sprite2D>(model, shader, texture);
			choice->Set2DPosition(m_x + m_width / 1.5, m_y + m_height / 1.5);
			choice->SetSize(m_width, m_height);
			m_listOption.push_back(choice);
		}
		for (auto op : m_listOption)
		{
			if (op->m_isHandle)
			{
				if (m_money > 1)
				{
					if (op->checkTexture("tower_cannon_icon"))
					{
						m_main->changeTexture("tower_cannon1_n");
						m_textureBullet = "bullet_cannon";
						m_texture = "tower_cannon1_";
						m_range = 300.f;
						m_attackSpeed = 50.f;
						m_damage = 20.f;
						m_type = CANNON;
					}
					if (op->checkTexture("tower_bow_icon"))
					{
						m_main->changeTexture("tower_bow1_sw");
						m_textureBullet = "bullet_bow";
						m_texture = "tower_bow1_";
						m_range = 100.f;
						m_attackSpeed = 150.f;
						m_damage = 20.f;
						m_type = BOW;
					}
					if (op->checkTexture("tower_laze_icon"))
					{
						m_main->changeTexture("tower_laze1_se");
						m_textureBullet = "bullet_laze";
						m_texture = "tower_laze1_";
						m_range = 100.f;
						m_attackSpeed = 100.f;
						m_damage = 30.f;
						m_type = LAZE;
					}
					op->m_isHandle = false;
					m_listOption.pop_back();
					m_listOption.pop_back();
					m_listOption.pop_back();
					m_state = LEVEL1;

					m_notActived->changeTexture("effect_none");
					m_width *= 1.2;
					m_height *= 1.2;
					m_main->SetSize(m_width, m_height);
					if (m_sound)
					{
						ResourceManagers::GetInstance()->PlaySound("finish_contruction.mp3", false);
					}
					m_money--;
				}
				else
				{
					op->m_isHandle = false;
				}
			}
		}
	}
}


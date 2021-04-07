#include "GSSetting.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int m_music;
extern int m_musicPrevious;
extern int m_sound;

GSSetting::GSSetting()
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_setting");

	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//sound button
	if (m_sound)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button_soundon");
	}
	else
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button_soundoff");
	}
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 50, 300);
	button->SetSize(90, 90);
	button->SetOnClick([]() {
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
			m_sound = false;
		}
		else
		{
			m_sound = true;
		}
		});
	m_listButton.push_back(button);

	//music button
	texture = ResourceManagers::GetInstance()->GetTexture("button_music");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 50, 300);
	button->SetSize(90, 90);
	button->SetOnClick([]() {
		if (m_music)
		{
			m_music = false;
		}
		else
		{
			m_music = true;
		}
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		if (m_music)
		{
			ResourceManagers::GetInstance()->PauseSound("setting.mp3");
		}
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		});
	m_listButton.push_back(button);
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSetting::HandleMouseMoveEvent(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	// change sound button state
	if(m_sound)
	{
		for (auto it : m_listButton)
		{
			if (it->checkTexture("button_soundoff"))
			{
				it->changeTexture("button_soundon");
			}
		}
	}
	else
	{
		for (auto it : m_listButton)
		{
			if (it->checkTexture("button_soundon"))
			{
				it->changeTexture("button_soundoff");
			}
		}
	}
	// turn on music when start
	if (m_music && m_musicPrevious && m_time < 0.001)
	{
		ResourceManagers::GetInstance()->PlaySound("setting.mp3", true);
	}
	m_time += deltaTime;
	if (m_music && !m_musicPrevious)
	{
		//turn on music
		m_musicPrevious = 1;
		ResourceManagers::GetInstance()->PlaySound("setting.mp3", true);
	}
	if (!m_music && m_musicPrevious)
	{
		//turn off music
		m_musicPrevious = 0;
		ResourceManagers::GetInstance()->PauseSound("setting.mp3");
	}
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

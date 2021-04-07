#include "GSMenu.h"
#include "Application.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int m_music;
extern int m_musicPrevious;
extern int m_sound;

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("logo_menu");
	m_logoGame = std::make_shared<Sprite2D>(model, shader, texture);
	m_logoGame->Set2DPosition(screenWidth / 2, 120);
	m_logoGame->SetSize(297, 226);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_RoundOption);
		if (m_music)
		{
			ResourceManagers::GetInstance()->PauseSound("menu.mp3");
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
	button->Set2DPosition(screenWidth / 2, 400);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		exit(0);
		});
	m_listButton.push_back(button);

	//setting button
	texture = ResourceManagers::GetInstance()->GetTexture("button_setting");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 500);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting);
		if (m_music)
		{
			ResourceManagers::GetInstance()->PauseSound("menu.mp3");
		}
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		});
	m_listButton.push_back(button);

	//info button
	texture = ResourceManagers::GetInstance()->GetTexture("info");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 650);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Info);
		if (m_music)
		{
			ResourceManagers::GetInstance()->PauseSound("menu.mp3");
		}
		if (m_sound)
		{
			ResourceManagers::GetInstance()->PlaySound("button.mp3", false);
		}
		});
	m_listButton.push_back(button);
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::HandleMouseMoveEvent(int x, int y)
{
	Application::GetInstance()->HandleMouseMoveEvent(x, y);
	std::cout << x << ", " << y << std::endl;
}

void GSMenu::Update(float deltaTime)
{
	// turn on music when start
	if (m_music && m_musicPrevious && m_time < 0.001)
	{
		ResourceManagers::GetInstance()->PlaySound("menu.mp3", true);
	}
	m_time += deltaTime;
	if (m_music && !m_musicPrevious)
	{
		//turn on music
		m_musicPrevious = 1;
		ResourceManagers::GetInstance()->PlaySound("menu.mp3", true);
	}
	if (!m_music && m_musicPrevious)
	{
		//turn off music
		m_musicPrevious = 0;
		ResourceManagers::GetInstance()->PauseSound("menu.mp3");
	}
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_logoGame->Draw();
}

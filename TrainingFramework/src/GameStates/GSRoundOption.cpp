#include "GSRoundOption.h"
#include "Application.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int m_music;
extern int m_musicPrevious;
extern int m_round;
extern int m_sound;

GSRoundOption::GSRoundOption()
{
}

GSRoundOption::~GSRoundOption()
{
}

void GSRoundOption::Init()
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

	//Round 1 button
	texture = ResourceManagers::GetInstance()->GetTexture("frame_money");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 150);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		m_round = 1;
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

	//Round 2 button
	texture = ResourceManagers::GetInstance()->GetTexture("frame_money");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		m_round = 2;
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

	//Round 3 button
	texture = ResourceManagers::GetInstance()->GetTexture("frame_money");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 450);
	button->SetSize(200, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		m_round = 3;
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

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_reduction");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600);
	button->SetSize(70, 70);
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

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "EASY", TEXT_COLOR::BLACK, 1.2);
	text->Set2DPosition(Vector2(screenWidth / 2 - 40, 158));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "MEDIUM", TEXT_COLOR::BLACK, 1.2);
	text->Set2DPosition(Vector2(screenWidth / 2 - 60, 308));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "HARD", TEXT_COLOR::BLACK, 1.2);
	text->Set2DPosition(Vector2(screenWidth / 2 - 40, 458));
	m_listText.push_back(text);
}

void GSRoundOption::Exit()
{
}

void GSRoundOption::Pause()
{
}

void GSRoundOption::Resume()
{
}

void GSRoundOption::HandleEvents()
{
}

void GSRoundOption::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSRoundOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSRoundOption::HandleMouseMoveEvent(int x, int y)
{
}

void GSRoundOption::Update(float deltaTime)
{
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
}

void GSRoundOption::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}

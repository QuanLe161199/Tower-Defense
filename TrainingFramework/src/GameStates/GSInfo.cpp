#include "GSInfo.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int m_music;
extern int m_musicPrevious;
extern int m_sound;

GSInfo::GSInfo()
{
}

GSInfo::~GSInfo()
{
}

void GSInfo::Init()
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

	//info frame
	texture = ResourceManagers::GetInstance()->GetTexture("frame_money");
	m_frame = std::make_shared<Sprite2D>(model, shader, texture);
	m_frame->Set2DPosition(screenWidth / 2, 200);
	m_frame->SetSize(screenWidth, 400);

	/*info link qrcode
	texture = ResourceManagers::GetInstance()->GetTexture("qr_code");
	m_infoLink = std::make_shared<Sprite2D>(model, shader, texture);
	m_infoLink->Set2DPosition(screenWidth / 2, 500);
	m_infoLink->SetSize(200, 200);*/

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->Set2DPosition(screenWidth / 2, 650);
	m_button->SetSize(200, 70);
	m_button->SetOnClick([]() {
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

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Completed April 2021", TEXT_COLOR::BLACK, 1.0);
	text->Set2DPosition(Vector2(screenWidth / 2 - 132, 120));
	m_textInfo.push_back(text);

	text = std::make_shared< Text>(shader, font, "Author Le: Van Quan", TEXT_COLOR::BLACK, 1.0);
	text->Set2DPosition(Vector2(screenWidth / 2 - 132, 200));
	m_textInfo.push_back(text);

	text = std::make_shared< Text>(shader, font, "Instructors: Mr. Hoang, Mr. Hung", TEXT_COLOR::BLACK, 1.0);
	text->Set2DPosition(Vector2(screenWidth / 2 - 190, 280));
	m_textInfo.push_back(text);
}

void GSInfo::Exit()
{
}

void GSInfo::Pause()
{
}

void GSInfo::Resume()
{
}

void GSInfo::HandleEvents()
{
}

void GSInfo::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSInfo::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	(m_button)->HandleTouchEvents(x, y, bIsPressed);
}

void GSInfo::HandleMouseMoveEvent(int x, int y)
{
}

void GSInfo::Update(float deltaTime)
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

void GSInfo::Draw()
{
	m_BackGround->Draw();
	m_frame->Draw();
	/*m_infoLink->Draw();*/
	m_button->Draw();
	for (auto it : m_textInfo)
	{
		it->Draw();
	}
}

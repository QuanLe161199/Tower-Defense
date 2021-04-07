#pragma once
#include "Sprite2D.h"

#define TREND_Down	1.0f
#define TREND_Left	2.0f
#define TREND_Up	3.0f
#define TREND_Right	4.0f

class Animation :
	public Sprite2D
{
protected:
	float m_numFrames;
	float m_currentFrame;
	float m_currentTime;
	float m_frameTime;
	float m_numTrends;
	
public:
	float m_trend;

	Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,
		float numFrames, float currentFrame, float currentTime, float frameTime, float trend, float numTrends);
	~Animation();

	void changeTexture(std::string nextTexture);
	bool checkTexture(std::string texture);
	void		Draw();
	void		Update(GLfloat deltatime);
};

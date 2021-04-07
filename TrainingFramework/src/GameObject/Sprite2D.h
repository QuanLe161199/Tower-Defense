#pragma once
#include "baseobject.h"

class Sprite2D : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;

public:
	Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	Sprite2D();
	~Sprite2D();

	void		Init();
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

	void		SetText(std::string text);
	std::string	GetText();  

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();

	bool checkTexture(std::string texture);
	void changeTexture(std::string nextTexture);

	bool m_isHandle = false;

};


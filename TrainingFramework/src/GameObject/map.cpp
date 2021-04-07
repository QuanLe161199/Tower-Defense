#include "map.h"
#include "ResourceManagers.h"

#include <cstdarg>

extern GLint screenWidth;
extern GLint screenHeight;

Map::Map()
{
}

Map::Map(std::string textureName, float evaluate, int numPoints, int numAllPoints, ...)
{
	m_numPoints = numPoints;
	m_numTowers = numAllPoints - m_numPoints;
	m_evaluate = evaluate;
	va_list marker;
	va_start(marker, numAllPoints);
	for (register int i = 0; i < numPoints; i++)
	{
		m_listPoint.push_back(va_arg(marker, point));
	}

	for (register int i = numPoints; i < numAllPoints; i++)
	{
		m_listTower.push_back(va_arg(marker, point));
	}
	
	//create display valiahle
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(textureName);
	m_display = std::make_shared<Sprite2D>(model, shader, texture);
	m_display->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_display->SetSize(screenWidth, screenHeight);

}

Map::~Map()
{
}



#pragma once
#include "Sprite2D.h"

typedef std::pair<float, float> point;

class Map
{
public:
	int m_numPoints;
	int m_numTowers;
	float m_evaluate;
	std::vector<point> m_listPoint;
	std::vector<point> m_listTower;
	bool m_isGameOver = false;
	std::shared_ptr<Sprite2D> m_display;

	Map();
	Map(std::string textureName, float evaluate, int numPoints, int numAllPoints...);
	~Map();
};
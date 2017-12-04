#pragma once
#include "Vector3.h"
#include "SFML\Graphics.hpp"
#include <string>
using std::string;
namespace GOGROUP {
	enum g {
		kUndefined,
		kEverything,
		kObstacle,
		kBoid,
		kFlag,
		kBase,
		kBullet,
		kCount
	};
}

class GameObject
{

public:
	Vector3 m_position;
	bool			m_toDelete;
	bool			m_isEnable;

	int				m_layer;
	virtual void initialize();
	virtual void update();
	virtual void render(sf::RenderWindow& wnd);
	virtual void destroy();
	void setPosition(unsigned short x, unsigned short y);
	void		setLayer(int layer);
	GameObject();
	~GameObject();
};

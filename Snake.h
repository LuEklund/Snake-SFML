#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Global.h"

class Snake : public sf::Drawable
{
private:
	std::vector<gbl::Position>	m_body;
	gbl::Map					&m_map;
	gbl::Direction				m_lastDirection;

	short						m_grow;
	bool						m_eaten;
	bool						m_alive;

public:

	Snake(gbl::Map &map);
	~Snake();

	//modifiers
	void	addBody();

	//Accessors
	const gbl::Position	&getPosition();
	bool				&getEaten();
	bool				&getAlive();

	//Functions
	void	removeSnake();
	void	spawnSnake(gbl::Position startPos);
	void	move(gbl::Direction direction);
	void	updateBody();

	void	update(const float &dt);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"

class Gui : public sf::Drawable
{
private:
	//the displayable elements
	sf::Text			m_textPlayer;
	sf::View			&m_gameView;

	

public:
	Gui(sf::View &gameView);
	~Gui();

	//inits
	bool	initGui(sf::Font &font);

	//functions
	void	setScore(const int score);

	void	update();
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};



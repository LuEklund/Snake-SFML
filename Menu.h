#pragma once
#include <iostream>
#include <sstream>

#include "SFML/Graphics.hpp"

class Menu : public sf::Drawable
{
private:
	//the window
	sf::RenderWindow	&m_Window;

	sf::Text			m_header;
	sf::Text			m_score;
	sf::Text			m_menuItems[2];
public:
	Menu(sf::RenderWindow	&window);
	~Menu();


	//init
	bool	initMenu(sf::Font &font);

	//accessors
	bool	isButtonPlay(const sf::Vector2i &mousePos);
	bool	isButtonQuit(const sf::Vector2i &mousePos);

	//modifiers
	void	setHeader(std::string headerString);
	void	setScore(const int score);

	//functions
	void	update(const sf::Vector2i &mousePos);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
};



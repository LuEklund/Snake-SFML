#pragma once
#include <random>
#include <chrono>

#include "Snake.h"
#include "Menu.h"
#include "GUI.h"

class Game : public sf::Drawable
{
private:
	enum class State
	{
		PLAYING,
		PAUSED,
		GAMEOVER
	};
	//Essentials
	sf::RenderWindow	&m_Window;
	sf::View			m_gameView;
	State				m_state;
	sf::Font			m_font;
	sf::Clock			m_clock;
	float				m_dt;

	//Map
	gbl::Map			m_map;
	sf::RectangleShape	m_cellDraw;
	sf::Color			m_colorEmpty;
	sf::Color			m_colorFood;
	sf::Color			m_colorBody;
	int					m_foods;
	int					m_score;

	//Menu
	std::unique_ptr<Menu>	m_pMenu;

	//Gui
	std::unique_ptr<Gui>	m_pGui;

	//Snake
	std::unique_ptr<Snake>	m_pSnake;
	sf::Vector2f			m_snakePos;
	gbl::Direction			m_direction;
	float					m_snakeWaited;

	//random number generator engine
	std::mt19937		m_engine;

	//Private Functions
	gbl::Position	getRandomEmptyCell();
	void			spawnFood();
	
public:
	Game(sf::RenderWindow &window);
	~Game();

	//inits
	void	initDrawingCell();
	void	initSnake();
	bool	initGame();

	//Functions
	void	isKeyPressed(sf::Keyboard::Key key);
	void	isMouseButtonReleased(sf::Mouse::Button button);

	void	update();
	void	drawMap(sf::RenderTarget &target);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};


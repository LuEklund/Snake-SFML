#include "Game.h"

gbl::Position Game::getRandomEmptyCell()
{
	int	found_empty_cell = 0;

	for (const std::array<gbl::Cell, gbl::MAP::ROWS> &column : m_map)
	{
		if (found_empty_cell != 0)
			break;
		for(const gbl::Cell &cell : column)
		{
			if (cell.type == gbl::CellType::EMPTY)
			{
				found_empty_cell = 1;
				break;
			}
		}
	}

	if (found_empty_cell != 0)
	{
		//initialize a random distrobutions for our rows and columns
		std::uniform_int_distribution<unsigned short>	distColumns(0,gbl::MAP::COLUMNS - 1);
		std::uniform_int_distribution<unsigned short>	distRows(0,gbl::MAP::ROWS - 1);

		unsigned char cell_x = static_cast<unsigned char>(distColumns(m_engine));
		unsigned char cell_y = static_cast<unsigned char>(distRows(m_engine));
		
		while (m_map[cell_x][cell_y].type != gbl::CellType::EMPTY)
		{
			cell_x = static_cast<unsigned char>(distColumns(m_engine));
			cell_y = static_cast<unsigned char>(distRows(m_engine));
		}
		return (gbl::Position(cell_x,cell_y));
	}

	//return negative ): cordinates if no free spots avilable
	return (gbl::Position(-1,-1));
}

void Game::spawnFood()
{
	//get ourself a fresh empty cell to populate with food. Yummy
	gbl::Position theEmptyCell = getRandomEmptyCell();

	//check that we got an empty cell
	if (theEmptyCell.x == -1)
		return ;
	else
	{
		m_map[theEmptyCell.x][theEmptyCell.y].type = gbl::CellType::FOOD;
		m_foods++;
	}
	// std::cout << "added food at: " << theEmptyCell.x << ", " << theEmptyCell.y << std::endl;
	return ;
}

//COnstructor
Game::Game(sf::RenderWindow &window)
	: m_Window(window)
	, m_state(State::PAUSED)
	, m_dt(0.f)
	, m_foods(0)
	, m_pMenu(std::make_unique<Menu>(window))
	, m_pGui(std::make_unique<Gui>(m_gameView))
	, m_pSnake(std::make_unique<Snake>(m_map))
	, m_snakeWaited(0.f)
	, m_direction(gbl::Direction::UP)
	, m_engine(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()))
{
	//m_engine => initialize our RNG with an seed that is craeted by using system time.
}

Game::~Game()
{
}


void Game::initDrawingCell()
{
	m_colorEmpty = sf::Color(155,155,155,255);
	m_colorFood = sf::Color::Yellow;
	m_colorBody = sf::Color::Cyan;
	m_cellDraw.setSize(sf::Vector2f(gbl::MAP::CELL_SIZE, gbl::MAP::CELL_SIZE));
	m_cellDraw.setOutlineThickness(gbl::MAP::OUTLINE_THICKNESS);
	m_cellDraw.setOutlineColor(sf::Color::White);
}

void Game::initSnake()
{
	gbl::Position	snakePosSpawn(getRandomEmptyCell());

	while(snakePosSpawn.x < 1
	|| snakePosSpawn.y < 1
	|| snakePosSpawn.x > gbl::MAP::COLUMNS - 2
	|| snakePosSpawn.y > gbl::MAP::ROWS - 2)
	{
		snakePosSpawn = getRandomEmptyCell();
	}
	m_pSnake->spawnSnake(snakePosSpawn);
}

bool Game::initGame()
{
	if (!m_font.loadFromFile("assets/Sports World-Regular.ttf"))
	{
		std::cout << "Failed to load FONT!" << std::endl;
		return false;
	}
	if (!m_pMenu->initMenu(m_font))
		return false;
	if (!m_pGui->initGui(m_font))
		return false;

	initDrawingCell();
	initSnake();

	m_gameView.setSize(300.f,300.f);
	m_snakePos = sf::Vector2f(
		static_cast<float>(m_pSnake->getPosition().x) * static_cast<float>(gbl::MAP::CELL_SIZE),
		static_cast<float>(m_pSnake->getPosition().y) * static_cast<float>(gbl::MAP::CELL_SIZE)
		);
	m_gameView.setCenter(
		m_snakePos.x + gbl::MAP::CELL_SIZE / 2.f,
		m_snakePos.y + gbl::MAP::CELL_SIZE / 2.f);
	return (true);
}



void Game::isKeyPressed(sf::Keyboard::Key key)
{
	if (m_state == State::PLAYING)
	{
		switch (key)
		{
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			m_direction = gbl::Direction::RIGHT;
			break;
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			m_direction = gbl::Direction::LEFT;
			break;
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			m_direction = gbl::Direction::UP;
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			m_direction = gbl::Direction::DOWN;
			break;
		case sf::Keyboard::Escape:
			m_state = State::PAUSED;
			m_Window.setView(m_Window.getDefaultView());
			m_pMenu->setHeader("Snake Paused");
			break;
		}
	}
}

void Game::isMouseButtonReleased(sf::Mouse::Button button)
{
	if ((m_state == State::PAUSED && button == sf::Mouse::Left)
	|| (m_state == State::GAMEOVER && button == sf::Mouse::Left))
	{
		if (m_pMenu->isButtonPlay(sf::Mouse::getPosition(m_Window)))
		{
			if (m_pSnake->getAlive() == false)
			{
				initSnake();
				m_pGui->setScore(0);
			}
			m_state = State::PLAYING;
			m_clock.restart();
			m_Window.setView(m_gameView);
		}
		else if (m_pMenu->isButtonQuit(sf::Mouse::getPosition(m_Window)))
			m_Window.close();
	}
}

void Game::update()
{
	m_dt = m_clock.restart().asSeconds();
	switch (m_state)
	{
	case State::PAUSED:
	case State::GAMEOVER:
		m_pMenu->update(sf::Mouse::getPosition(m_Window));
		break;
	case State::PLAYING:
		//with intention not haveing the game frame independet to avoid teleporting 5 tiles on 1fps
		if (m_snakeWaited >= gbl::SNAKE_WAIT_SECONDS)
		{
			m_pSnake->move(m_direction);
			if (m_pSnake->getAlive() == false)
			{
				m_state = State::GAMEOVER;
				m_Window.setView(m_Window.getDefaultView());
				m_pMenu->setHeader("Game Over");
				m_pMenu->setScore(m_score);
				m_score = 0;
				m_pSnake->removeSnake();
				return ;
			}
			if (m_pSnake->getEaten())
			{
				m_score++;
				m_pGui->setScore(m_score);
				m_foods--;
			}
			m_snakePos = sf::Vector2f(
				static_cast<float>(m_pSnake->getPosition().x) * static_cast<float>(gbl::MAP::CELL_SIZE),
				static_cast<float>(m_pSnake->getPosition().y) * static_cast<float>(gbl::MAP::CELL_SIZE)
			);
			// std::cout << "MOVED: " << m_snakePos.x << ", " << m_snakePos.y << std::endl;
			m_gameView.setCenter(
				m_snakePos.x + gbl::MAP::CELL_SIZE / 2.f,
				m_snakePos.y + gbl::MAP::CELL_SIZE / 2.f
				);
			m_snakeWaited = 0.f;
		}
		else
			m_snakeWaited += m_dt;
		m_Window.setView(m_gameView);
		m_pGui->update();
		if (m_foods < gbl::MAP::MAX_FOOD)
			spawnFood();
		break;
	}
}

//allow us to modify one cell and draw it multiple times
void Game::drawMap(sf::RenderTarget &target)
{
	// if (m_state == State::PLAYING)
	for (int x = 0; x < gbl::MAP::COLUMNS; x++)
	{
		for (int y = 0; y < gbl::MAP::ROWS; y++)
		{
			if (m_map[x][y].type == gbl::CellType::EMPTY)
				m_cellDraw.setFillColor(m_colorEmpty);
			else if (m_map[x][y].type == gbl::CellType::BODY)
				m_cellDraw.setFillColor(m_colorBody);
			else 
				m_cellDraw.setFillColor(m_colorFood);
			m_cellDraw.setPosition(
				static_cast<float>(x * gbl::MAP::CELL_SIZE),
				static_cast<float>(y * gbl::MAP::CELL_SIZE));
			target.draw(m_cellDraw);
		}
	}
	// std::cout << "fine";

}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_state == State::PAUSED || m_state == State::GAMEOVER)
		target.draw(*m_pMenu.get());
	else if (m_state == State::PLAYING)
		target.draw(*m_pGui.get());
		
}

#include "Snake.h"


Snake::Snake(gbl::Map &map)
	: m_map(map), m_lastDirection(gbl::Direction::UP), m_grow(0), m_alive(true)
{
}

Snake::~Snake()
{
}

//modifiers
void Snake::addBody()
{
	m_body.push_back(m_body.back());
}

//Accessors
const gbl::Position &Snake::getPosition()
{
	return (m_body[0]);
}

bool &Snake::getEaten()
{
	return (m_eaten);
}

bool &Snake::getAlive()
{
	return (m_alive);
}

//Functions
void Snake::updateBody()
{
	size_t node = m_body.size() - 1;
	if (m_grow)
	{
		addBody();
		m_grow--;
	}
	else
		m_map[m_body[node].x][m_body[node].y].type = gbl::CellType::EMPTY;

	for (node; node > 0; node--)
	{
		m_body[node].x = m_body[node - 1].x;
		m_body[node].y = m_body[node - 1].y;
		m_map[m_body[node].x][m_body[node].y].type = gbl::CellType::BODY;

	}

}

//Functions
//clear the whole snake back to 1st stage
void Snake::removeSnake()
{
	if (m_body.size())
	{
		for (size_t i = m_body.size() - 1; i > 0; i--)
		{
			m_map[m_body[i].x][m_body[i].y].type = gbl::CellType::EMPTY;
		}
		m_map[m_body[0].x][m_body[0].y].type = gbl::CellType::EMPTY;
	}
	m_body.clear();
	m_alive = false;
}

void Snake::spawnSnake(gbl::Position startPos)
{
	m_body.push_back(startPos);
	m_map[startPos.x][startPos.y].type = gbl::CellType::BODY;
	m_lastDirection = gbl::Direction::UP;
	m_grow = 0;
	m_eaten = false;
	m_alive = true;
}

void Snake::move(gbl::Direction direction)
{
	m_eaten = false;
	updateBody();

	//PREVENTING 180 TURNS!!!
	if ((direction == gbl::Direction::UP
	&& m_lastDirection == gbl::Direction::DOWN)

	|| (direction == gbl::Direction::DOWN
	&& m_lastDirection == gbl::Direction::UP)

	|| (direction == gbl::Direction::LEFT
	&& m_lastDirection == gbl::Direction::RIGHT)

	|| (direction == gbl::Direction::RIGHT
	&& m_lastDirection == gbl::Direction::LEFT))
		direction = m_lastDirection;
	switch (direction)
	{
	case gbl::Direction::RIGHT:
		if (m_body[0].x + 1 < gbl::MAP::COLUMNS)
			m_body[0].x++;
		else
			m_alive = false;
		break;
	case gbl::Direction::LEFT:
		if (m_body[0].x > 0)
			m_body[0].x--;
		else
			m_alive = false;
		break;
	case gbl::Direction::DOWN:
		if (m_body[0].y + 1 < gbl::MAP::ROWS)
			m_body[0].y++;
		else
			m_alive = false;
		break;
	case gbl::Direction::UP:
		if (m_body[0].y > 0)
			m_body[0].y--;
		else
			m_alive = false;
		break;
	}
	m_lastDirection = direction;
	if (m_map[m_body[0].x][m_body[0].y].type == gbl::CellType::FOOD)
	{
		m_grow++;
		m_eaten = true;
	}
	else if (m_map[m_body[0].x][m_body[0].y].type == gbl::CellType::BODY)
		m_alive = false;
	m_map[m_body[0].x][m_body[0].y].type = gbl::CellType::BODY;
}

void Snake::update(const float &dt)
{

}



void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}



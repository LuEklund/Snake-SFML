#pragma once
#include <array>

//These are global elements
namespace gbl
{
	constexpr float  SNAKE_WAIT_SECONDS = 0.1f;

	namespace MAP
	{
		constexpr unsigned char OUTLINE_THICKNESS = 1;
		constexpr unsigned char CELL_SIZE = 8;

		constexpr unsigned char COLUMNS = 20;
		constexpr unsigned char ROWS = 20;

		constexpr unsigned char MAX_FOOD = 6;
	}

	enum class Direction
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

	enum class CellType
	{
		EMPTY,
		FOOD,
		BODY
	};

	struct Cell
	{
		CellType	type;
		Cell(const CellType i_type = CellType::EMPTY)
			: type(i_type)
		{

		};
	};
	

	struct Position
	{
		short	x;
		short	y;
		Position(const short i_x, const short i_y)
			: x(i_x)
			, y(i_y)
		{


		}
	};
	
	using Map = std::array<std::array<Cell, MAP::ROWS>, MAP::COLUMNS>;
}
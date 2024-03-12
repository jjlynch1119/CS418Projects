#include "PuzzleState.h"

PuzzleState PuzzleState::NullState{ 0, 0 };

bool PuzzleState::operator==(const PuzzleState& rhs) const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i) != rhs.tiles.at(i))
			return false;
	}

	return true;
}

bool PuzzleState::operator!=(const PuzzleState& rhs) const
{
	return !(*this == rhs);
}

const PuzzleState& PuzzleState::operator=(const PuzzleState& rhs) //assignment op
{
	rows = rhs.rows;
	cols = rhs.cols;
	tiles = rhs.tiles;
	blank_position_row = rhs.blank_position_row;
	blank_position_col = rhs.blank_position_col;

	return *this;
}

bool PuzzleState::canMoveUp()
{
	return blank_position_row > 0;
}

bool PuzzleState::canMoveDown()
{
	return blank_position_row < rows - 1;
}

bool PuzzleState::canMoveLeft()
{
	return blank_position_col > 0;
}

bool PuzzleState::canMoveRight()
{
	return blank_position_col < cols - 1;
}

PuzzleState PuzzleState::moveBlankUp()
{
	PuzzleState up = *this;
	int temp;

	temp = up.tiles.at(((blank_position_row - 1) * rows) + blank_position_col);	//Store value of index we are moving to
	up.tiles.at(((blank_position_row - 1) * rows)  + blank_position_col) = 0;	//Set the index to 0
	up.tiles.at((blank_position_row * rows) + blank_position_col) = temp;		//Set the original blank location to value we stored
	up.blank_position_row--;

	return up;
}

PuzzleState PuzzleState::moveBlankDown()
{
	PuzzleState down = *this;
	int temp;

	temp = down.tiles.at(((blank_position_row + 1) * rows) + blank_position_col);
	down.tiles.at(((blank_position_row + 1) * rows) + blank_position_col) = 0;
	down.tiles.at((blank_position_row * rows) + blank_position_col) = temp;
	down.blank_position_row++;

	return down;
}

PuzzleState PuzzleState::moveBlankLeft()
{
	PuzzleState left = *this;
	int temp;

	temp = left.tiles.at((blank_position_row * rows) + blank_position_col - 1);
	left.tiles.at((blank_position_row * rows) + blank_position_col - 1) = 0;
	left.tiles.at((blank_position_row * rows) + blank_position_col) = temp;
	left.blank_position_col--;

	return left;
}

PuzzleState PuzzleState::moveBlankRight()
{
	PuzzleState right = *this;
	int temp;

	temp = right.tiles.at((blank_position_row * rows) + blank_position_col + 1);
	right.tiles.at((blank_position_row * rows) + blank_position_col + 1) = 0;
	right.tiles.at((blank_position_row * rows) + blank_position_col) = temp;
	right.blank_position_col++;

	return right;
}

void PuzzleState::read(istream& in)
{
	int input;

	for (int i = 0; i < tiles.size(); i++)
	{
		in >> input;
		
		tiles.at(i) = input;

		if (input == 0)
		{
			blank_position_col = i % cols;
			blank_position_row = i / rows;
		}
	}


	/*for (int i : tiles)
	{
		cout << i << " ";
	}

	cout << "\nBlank Position = col: " << blank_position_col << " row: " << blank_position_row;
	*/
}

void PuzzleState::print(ostream& out)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (i % rows == 0)
			cout << "\n";

		cout << tiles.at(i) << " ";
	}
}
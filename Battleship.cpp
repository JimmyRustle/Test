#include "Battleship.h"



Battleship::Battleship()
{
	for (int i = 0; i < 10; i++)
	{
		std::vector<int> row;
		for (int ii = 0; ii < 10; ii++)
		{
			row.push_back(0);
		}
		m_board.push_back(row);
	}
}


Battleship::~Battleship()
{
}

void Battleship::SetSide(int side)
{
	//1 - length 2
	//2 - length 3
	//1 - length 4
	//1 = length 5

	int x = 0;
	int y = 0;
	std::string direction;
	int shipLengths[5] = { 2,3,3,4,5 };
	bool validDirection;
	for (int i = 0; i < 5; i++)
	{
		do
		{
			validDirection = true;
			PrintBoard();
			std::cout << "Place a boat of length " << shipLengths[i] << std::endl;
			std::cout << "Enter a valid coordinate and direction (left,right,up,down), separated by a space" << std::endl;
			std::string input;
			getline(std::cin, input);
			std::string coord;
			std::string dir;

			bool foundSpace = false;
			for (int ii = 0; ii < input.size(); ii++)
			{
				if (input[ii] == ' ')
				{
					foundSpace = true;
				}

				else if (foundSpace == false)
				{
					coord.push_back(input[ii]);
				}

				else
				{
					dir.push_back(input[ii]);
				}
			}


			ConvertInputToCoord(coord, y, x);

			if (x != -1)
			{
				for (int ii = 0; ii < dir.length(); ii++)
				{
					if (dir[ii] < 97)
						dir[ii] += 32;
				}

				int lengthOfShip = shipLengths[i];
				//check if dir makes sense
				if (dir == "left")
				{
					if (x - lengthOfShip < 0)
					{
						validDirection = false;
						std::cout << "Ship crosses boundary of the board." << std::endl;
					}
					else
					{
						for (int ii = 0; ii <= lengthOfShip; ii++)
						{
							if (m_board[y][x-ii] != 0)
							{
								validDirection = false;
								std::cout << "In the way of an existing ship!" << std::endl;
								break;
							}
						}
					}
				}

				else if (dir == "right")
				{
					if (x + lengthOfShip > 9)
					{
						validDirection = false;
						std::cout << "Ship crosses boundary of the board." << std::endl;
					}
					else
					{
						for (int ii = 0; ii <= lengthOfShip; ii++)
						{
							if (m_board[y][x+ii] != 0)
							{
								validDirection = false;
								std::cout << "In the way of an existing ship!" << std::endl;
								break;
							}
						}
					}
				}

				else if (dir == "up")
				{
					if (y - lengthOfShip < 0)
					{
						validDirection = false;
						std::cout << "Ship crosses boundary of the board." << std::endl;
					}

					else
					{
						for (int ii = 0; ii <= lengthOfShip; ii++)
						{
							if (m_board[y-ii][x] != 0)
							{
								validDirection = false;
								std::cout << "In the way of an existing ship!" << std::endl;
								break;
							}
						}
					}
				}

				else if (dir == "down")
				{
					if (y + lengthOfShip > 9)
					{
						validDirection = false;
						std::cout << "Ship crosses boundary of the board." << std::endl;
					}

					else
					{
						for (int ii = 0; ii <= lengthOfShip; ii++)
						{
							if (m_board[y+ii][x] != 0)
							{
								validDirection = false;
								std::cout << "In the way of an existing ship!" << std::endl;
								break;
							}
						}
					}
				}

				else
				{
					std::cout << "Direction not in the set [left, right, up, down]" << std::endl;
				}
			}
			direction = dir;


		} while (x == -1 || validDirection == false);


		//m_board[y][x] = side;
		if (direction == "left")
		{
			for (int ii = 0; ii < shipLengths[i]; ii++)
			{
				m_board[y][x - ii] = side;
			}
		}

		if (direction == "right")
		{
			for (int ii = 0; ii < shipLengths[i]; ii++)
			{
				m_board[y][x + ii] = side;
			}
		}

		if (direction == "up")
		{
			for (int ii = 0; ii < shipLengths[i]; ii++)
			{
				m_board[y - ii][x] = side;
			}
		}

		if (direction == "down")
		{
			for (int ii = 0; ii < shipLengths[i]; ii++)
			{
				m_board[y + ii][x] = side;
			}
		}
	}
}

void Battleship::ConvertInputToCoord(std::string input, int &y, int &x)
{
	char letter = input[0];
	std::string number;
	if (input.length() == 2)
	{
		number = input[1];
	}

	else if (input.length() == 3)
	{
		number += input[1];
		number += input[2];
	}
	
	else
	{
		y = -1;
		x = -1;
		std::cout << "Input is too long or too short." << std::endl;
	}

	int numberConverted = atoi(number.c_str());
	numberConverted -= 1;
	y = numberConverted;

	int asciiVal = (int)letter;
	if (asciiVal >= 97 && asciiVal <= 122)
	{
		letter -= 32;
	}

	char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
	for (int i = 0; i < 10; i++)
	{
		if (letter == letters[i])
		{
			x = i;
			return;
		}
	}

	//if didn't find valid letter
	y = -1;
	x = -1;
	std::cout << "Couldn't match coordinate to (x,y) coord." << std::endl;
	

}


void Battleship::PrintBoard()
{
	char letters[13] = { ' ',  ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	for (int i = 0; i < 13; i++)
	{
		std::cout << letters[i];
	}

	std::cout << '\n';

	for (int i = 0; i < 10; i++)
	{
		std::cout << i + 1;
		if (i != 9)
			std::cout << "  ";
		else
			std::cout << " ";

		for (int ii = 0; ii < 10; ii++)
		{
			std::cout << m_board[i][ii];
		}
		std::cout << '\n';
	}
}

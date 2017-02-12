#pragma once
#include <vector>
#include <string>
#include <iostream>

class Battleship
{
public:
	Battleship();
	~Battleship();

	void SetSide(int side);

	void PrintBoard();

	void ConvertInputToCoord(std::string input, int &y, int &x);


private:

	
	std::vector<std::vector<int>> m_board;
	
};


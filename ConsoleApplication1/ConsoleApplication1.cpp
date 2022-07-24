#include <iostream>
#include <array>

enum class crossOrCircle
{
	EMPTY,
	CROSS,
	CIRCLE,
};

using fieldArr = std::array < std::array <crossOrCircle, 3>, 3 >;

void drawElem(const crossOrCircle elem)
{
	switch (elem)
	{
	case crossOrCircle::EMPTY:
		std::cout << " ";
		break;
	case crossOrCircle::CROSS:
		std::cout << "+";
		break;
	default:
		std::cout << "0";
		break;
	}
}

void drawField(const fieldArr &arr) 
{
	for (int i = 0; i < arr.size(); ++i)
	{
		drawElem(arr[i][0]);
		for (int j = 1; j < arr.size(); ++j)
		{
			std::cout << " | ";
			drawElem(arr[i][j]);
		}
		std::cout << std::endl;
		std::cout << "----------";
		std::cout << std::endl;
	}

}

void setElem(crossOrCircle& fieldElem, const crossOrCircle newElem)
{
	fieldElem = newElem;
}

crossOrCircle findWinner(fieldArr field) 
{
	std::array< std::array<int, 3>, 8 >	winnerSet = 
	{ 0,1,2,
	  3,4,5,
      6,7,8,
	  0,3,6,
	  1,4,7,
	  2,5,8,
	  0,4,8,
	  2,4,6 };
	int i{ 0 };
	while (i < 8)
	{
		int j{ 0 };
		bool posWin{ true };
		crossOrCircle potWinner;
		while ( (j < 3) && (posWin == true) )
		{
			if (field[winnerSet[i][j] / 3][winnerSet[i][j] % 3] == crossOrCircle::EMPTY)
			{
				posWin = false;
			}
			if (j > 0)
				if (potWinner != field[winnerSet[i][j] / 3][winnerSet[i][j] % 3])
					posWin = false;
			if ((j == 2) && (posWin == true))
			{
				return field[winnerSet[i][j] / 3][winnerSet[i][j] % 3];
			}
			potWinner = field[winnerSet[i][j] / 3][winnerSet[i][j] % 3];
			++j;
		}
		++i;
	}
	return crossOrCircle::EMPTY;
}

void game(fieldArr field)
{
	field = {};
	bool isContinue{ true };
	do
	{
		int turn;
		std::cout << "Choose first turn: (0 - cross    1 - circle): ";
		std::cin >> turn;
		bool isGameOver{ false };
		int pos;
		field = {};
		drawField(field);
		while (!isGameOver) 
		{
			if (turn == 0)
			{
				std::cout << "Cross player input position of cross: ";
				std::cin >> pos;
				setElem(field[pos / 10 - 1][pos % 10 - 1], crossOrCircle::CROSS);
				std::cout << std::endl;
			}
			else
			{
				std::cout << "Circle player input position of circle: ";
				std::cin >> pos;
				setElem(field[pos / 10 - 1][pos % 10 - 1], crossOrCircle::CIRCLE);
				std::cout << std::endl;
			}
			drawField(field);
			turn ^= 1;
			if ( (findWinner(field) == crossOrCircle::CIRCLE) || (findWinner(field) == crossOrCircle::CROSS) ) 
			{
				isGameOver = true;
				if (findWinner(field) == crossOrCircle::CIRCLE)
					std::cout << "Circle winned!\n";
				else
					std::cout << "Cross winned!\n";
			}
		}
		std::cout << "Wish to continue?: (0 - no    1 - yes): ";
		std::cin >> isContinue;
	} while (isContinue);
}

int main() 
{
	fieldArr field{};
	game(field);
	return 0;
}

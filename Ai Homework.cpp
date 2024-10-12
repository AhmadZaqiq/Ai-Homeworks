//Ahmad JR
#include <iostream>
#include <cmath>
using namespace std;

void SetGameState(int State[11][20])
{
	int Temp[11][20] =
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,3,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1},
	{1,0,1,2,0,0,0,2,2,2,2,2,2,0,2,0,0,1,0,1},
	{1,0,1,2,1,1,2,1,1,3,0,1,1,0,1,1,0,1,0,1},
	{1,0,2,2,2,2,2,1,0,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,1,2,1,1,2,1,1,1,1,1,1,2,1,1,0,1,2,1},
	{1,0,1,2,0,4,2,2,2,2,2,2,2,0,0,0,0,1,2,1},
	{1,0,1,1,0,1,2,1,1,1,1,1,1,0,1,2,1,1,2,1},
	{1,0,0,0,0,1,2,2,2,0,0,0,0,0,1,2,2,2,2,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			State[i][j] = Temp[i][j];
		}
	}

}

void PrintState(int State[11][20])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << State[i][j] << "  ";
		}
		cout << "\n\n";
	}

}

int PackmanHeuristicPills(int State[11][20])
{
	int PillsSum = 0;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (State[i][j] == 2)
			{
				PillsSum++;
			};
		}
	}

	return PillsSum;
}

int CalculateDistance(int PackmanX, int PackmanY, int GhostX, int GhostY)
{
	return (abs(GhostY - PackmanY) + abs(GhostX - PackmanX));
}

int CalculateShortestDistance(int GhostDistances[50], int ArrSize)
{
	int Min = GhostDistances[0];

	for (int i = 0; i < ArrSize; i++)
	{
		if (GhostDistances[i] < Min)
		{
			Min = GhostDistances[i];
		};
	}

	return Min;
}

int PackmanHeuristicGhostDistance(int State[11][20])
{
	int GhostDistances[50];
	int ArrCounter = 0;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (State[i][j] == 3)
			{
				GhostDistances[ArrCounter] = CalculateDistance(5, 7, j, i);
				ArrCounter++;
			}
		}
	}

	return CalculateShortestDistance(GhostDistances, ArrCounter);
}

void DisplayHeuristicsValues(int State[11][20], int Score, int GhostDistance)
{
	cout << "\n\nPills={" << Score << "}\n\n";
	cout << "\n\The Nearest ghost={" << GhostDistance << "}\n\n";
}

int main()
{
	int State[11][20];

	SetGameState(State);

	int Score = PackmanHeuristicPills(State);
	int GhostDistance = PackmanHeuristicGhostDistance(State);

	PrintState(State);

	DisplayHeuristicsValues(State, Score, GhostDistance);

	system("pause>0");

	return 0;
}

//Ahmad JR
#include <iostream>
#include<cstdlib>
#include <vector>

using namespace std;

int ReadNumber(string Message = "Please Enter Number: ")
{
	int Number = 1;

	do
	{
		cout << Message;
		cin >> Number;
	} while (Number < 1);

	return Number;
}

void PrintMatrix(int Matrix[6][6])
{
	cout << "\n";

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout.width(4);
			cout << Matrix[i][j] << " ";
		}

		cout << "\n";
	}

	cout << "\n";
}

void SetStateAndActionValues(int R[6][6], int& State, int& Action)
{
	do
	{
		State = rand() % 6;
		Action = rand() % 6;
	} while (R[State][Action] == -1);
}

vector <int> FillVector(int Action, int Q[6][6])
{
	vector <int> vNextStateValues;

	for (int i = 0; i < 6; i++)
	{
		vNextStateValues.push_back(Q[Action][i]);
	}

	return vNextStateValues;
}

int MaxOfNextState(int Action, int Q[6][6])
{
	vector <int> vNextStateValues = FillVector(Action, Q);

	if (vNextStateValues.empty()) return 0;

	int Max = vNextStateValues[0];

	for (int i = 1; i < vNextStateValues.size(); i++)
	{
		if (vNextStateValues[i] > Max)
		{
			Max = vNextStateValues[i];
		}
	}
	return Max;
}

void UpdateQValue(int Q[6][6], int R[6][6], int State, int Action, float Gamma)
{
	Q[State][Action] = R[State][Action] + (Gamma * MaxOfNextState(Action, Q));
}

void QLearning(int Q[6][6], int R[6][6], float Gamma)
{
	int State = 0;
	int Action = 0;

	SetStateAndActionValues(R, State, Action);

	UpdateQValue(Q, R, State, Action, Gamma);

}

void DisplayTabels(int Q[6][6], int R[6][6])
{
	cout << "Q Table:";

	PrintMatrix(Q);

	cout << "\nReward Table:";

	PrintMatrix(R);
}

int main()
{
	srand((unsigned)time(NULL));

	int Q[6][6] =
	{
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	};

	int R[6][6] =
	{
		{-1, -1, -1, -1,  0, -1},
		{-1, -1, -1,  0, -1,100},
		{-1, -1, -1,  0, -1, -1},
		{-1,  0,  0, -1,  0, -1},
		{ 0, -1, -1, -1, -1,100},
		{-1,  0, -1, -1,  0,100},
	};

	float Gamma = 0.8;

	DisplayTabels(Q, R);

	int Episodes = ReadNumber("Please Enter Number of Episodes: ");

	for (int i = 0; i < Episodes; i++)
	{
		QLearning(Q, R, Gamma);
	}

	cout << "\nQ Table:";

	PrintMatrix(Q);

	system("pause>0");
}
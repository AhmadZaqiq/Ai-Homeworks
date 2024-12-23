//Ahmad JR
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int ReadNumber(string Message)
{
	int Number = 0;

	do
	{
		cout << Message;
		cin >> Number;

	} while (Number < 1);

	return Number;
}

void PrintBestSolution(string BestIndividual[], int SequenceLength)
{
	cout << "\n--- Best Solution ---\n";
	for (int j = 0; j < SequenceLength; j++)
	{
		cout << "  Move " << j + 1 << ": " << BestIndividual[j] << endl;
	}
	cout << "------------------------\n";
}

void GenerateParents(int GA[3][3], string Parents[], int NumberOfParents, int Length)
{
	const int NumberOfRows = 3;
	const int NumberOfCols = 3;
	srand((unsigned)time(NULL));

	for (int i = 0; i < NumberOfParents; i++)
	{
		for (int j = 0; j < Length; j++)
		{
			int startRow = rand() % NumberOfRows;
			int startCol = rand() % NumberOfCols;
			int endRow = rand() % NumberOfRows;
			int endCol = rand() % NumberOfCols;

			while (GA[endRow][endCol] == 0)
			{
				endRow = rand() % NumberOfRows;
				endCol = rand() % NumberOfCols;
			}

			Parents[i * Length + j] = "[" + to_string(startRow) + "," + to_string(startCol) + "] to [" + to_string(endRow) + "," + to_string(endCol) + "]";
		}
	}
}

void Crossover(string Parents[], string Child[], int NumberOfParents, int Length)
{
	int IndexOfChild = 0;
	for (int i = 0; i < NumberOfParents - 1; i += 2)
	{
		for (int j = 0; j < Length; j++)
		{
			if (j < 6)
			{
				Child[IndexOfChild * Length + j] = Parents[i * Length + j];
				Child[(IndexOfChild + 1) * Length + j] = Parents[(i + 1) * Length + j];
			}
			else
			{
				Child[IndexOfChild * Length + j] = Parents[(i + 1) * Length + j];
				Child[(IndexOfChild + 1) * Length + j] = Parents[i * Length + j];
			}
		}
		IndexOfChild += 2;
	}
}

void Mutation(string Child[], int NumberOfParents, int Length)
{
	for (int i = 0; i < NumberOfParents; i++)
	{
		int index1 = rand() % Length;
		int index2 = rand() % Length;

		while (index1 == index2)
		{
			index2 = rand() % Length;
		}

		swap(Child[i * Length + index1], Child[i * Length + index2]);
	}
}

double Fitness(string Movements[], int Length, int GA[3][3], int Target_Goal[3][3])
{
	double CurrentState[3][3] = { {2, 0, 2}, {0, 0, 0}, {1, 0, 1} };
	double TotalF_Score = 0.0;

	for (int moveIndex = 0; moveIndex < Length; moveIndex++)
	{
		string movement = Movements[moveIndex];

		if (movement.size() < 13 || movement[0] != '[' || movement[9] != '[')
		{
			cout << "Invalid movement format: " << movement << endl;
			TotalF_Score -= 10.0;
			continue;
		}

		int startRow = movement[1] - '0';
		int startCol = movement[3] - '0';
		int endRow = movement[10] - '0';
		int endCol = movement[12] - '0';

		if ((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) ||
			(abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2))
		{
			if (CurrentState[startRow][startCol] != 0 && CurrentState[endRow][endCol] == 0)
			{
				CurrentState[endRow][endCol] = CurrentState[startRow][startCol];
				CurrentState[startRow][startCol] = 0;
				TotalF_Score += 1.5;
			}
			else
			{
				TotalF_Score -= 2.5;
			}
		}
		else
		{
			TotalF_Score -= 2.0;
		}
	}

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (CurrentState[row][col] == Target_Goal[row][col])
			{
				TotalF_Score += 5.0;
			}
			else if (CurrentState[row][col] != 0)
			{
				TotalF_Score -= 0.5;
			}
		}
	}

	if (TotalF_Score < 0)
	{
		TotalF_Score = abs(TotalF_Score) + 1.0;
	}

	return TotalF_Score;
}

void Selection(string Parents[], string Child[], int NumberOfParents, int Length, int GA[3][3], int Target_Goal[3][3])
{
	vector<pair<double, vector<string>>> vAll;

	for (int i = 0; i < NumberOfParents; i++)
	{
		double F_Score = Fitness(&Parents[i * Length], Length, GA, Target_Goal);
		vector<string> vMovements(Parents + i * Length, Parents + (i + 1) * Length);
		vAll.push_back({ F_Score, vMovements });
	}

	for (int i = 0; i < NumberOfParents; i++)
	{
		double F_Score = Fitness(&Child[i * Length], Length, GA, Target_Goal);
		vector<string> vMovements(Child + i * Length, Child + (i + 1) * Length);
		vAll.push_back({ F_Score, vMovements });
	}

	sort(vAll.begin(), vAll.end(), [](const pair<double, vector<string>>& a, const pair<double, vector<string>>& b)
		{
			return a.first > b.first;
		});

	for (int i = 0; i < NumberOfParents; i++)
	{
		for (int j = 0; j < Length; j++)
		{
			Parents[i * Length + j] = vAll[i].second[j];
		}
	}
}

void GeneticAlgorithm(int Generations, string Parents[], string Child[], int NumberOfParents, int Length, int GA[3][3], int Target_Goal[3][3], double BestFitness, string BestSol[])
{
	for (int i = 0; i < Generations; i++)
	{
		GenerateParents(GA, Parents, NumberOfParents, Length);
		Crossover(Parents, Child, NumberOfParents, Length);
		Mutation(Child, NumberOfParents, Length);

		Selection(Parents, Child, NumberOfParents, Length, GA, Target_Goal);

		for (int i = 0; i < NumberOfParents; i++)
		{
			double fitnessScore = Fitness(&Parents[i * Length], Length, GA, Target_Goal);
			if (fitnessScore > BestFitness)
			{
				BestFitness = fitnessScore;
				for (int j = 0; j < Length; j++)
				{
					BestSol[j] = Parents[i * Length + j];
				}
			}
		}
	}
}

int main()
{
	int GA[3][3] = { {1, 0, 1}, {0, 0, 0}, {2, 0, 2} };
	int Target_Goal[3][3] = { {1, 0, 1}, {0, 0, 0}, {2, 0, 2} };

	const int NumberOfParents = 20;
	const int Length = 16;

	string Parents[NumberOfParents * Length];
	string Child[NumberOfParents * Length];

	int Generations = ReadNumber("Enter the number of Generations: ");

	string BestSol[Length];
	double BestFitness = -1.0;

	GeneticAlgorithm(Generations, Parents, Child, NumberOfParents, Length, GA, Target_Goal, BestFitness, BestSol);

	PrintBestSolution(BestSol, Length);

	system("pause>0");
}

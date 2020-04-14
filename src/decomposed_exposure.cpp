
#include <iostream>
#include<fstream>
#include <vector>
#include <sstream>
using namespace std;

#define MAX_SIZE 1024

//Created C1, Y, D1, D2 matrices
int N;
float C1[MAX_SIZE][MAX_SIZE], C2[MAX_SIZE][MAX_SIZE];
float Y[MAX_SIZE];
float D1[MAX_SIZE], D2[MAX_SIZE];

//Binarizing the values sgn
float sgn(float value) {
    if (value == 0)  return 0;
    if (value < 0)   return -1;
    if (value > 0)   return 1;
}


void read()
{
	std::ifstream  data1("dyad_ties1.csv");
	std::string line;
	int row_number = 0;
	while (std::getline(data1, line))
	{
		row_number = row_number + 1;
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::string> parsedRow;
		while (std::getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}
		if (row_number > 1)
		{
			int source = stoi(parsedRow.at(0));
			int target = stoi(parsedRow.at(1));
			cout << row_number << " " << source << " " << target << endl;

		}
	}
	std::ifstream  data2("dyad_ties2.csv");
	while (std::getline(data2, line))
	{
		row_number = row_number + 1;
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::string> parsedRow;
		while (std::getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}
		if (row_number > 1)
		{
			int source = stoi(parsedRow.at(0));
			int target = stoi(parsedRow.at(1));
			cout << row_number << " " << source << " " << target << endl;

		}
	}
	

}

void input_data() {
	std::ifstream  data1("dyad_ties1.csv");
	std::string line;
	int row_number = 0;
	int max = 0;
	while (std::getline(data1, line))
	{
		row_number = row_number + 1;
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::string> parsedRow;
		while (std::getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}
		if (row_number > 1)
		{
			int source = stoi(parsedRow.at(0));
			int target = stoi(parsedRow.at(1));
			cout << row_number << " " << source << " " << target << endl;
			C1[source][target] = 1;
			if (max < source) {
				max = source;
			}
			else if (max < target) {
				max = target;
			}
		}
	}
	
	std::ifstream  data1("dyad_ties2.csv");
	while (std::getline(data2, line))
	{
		row_number = row_number + 1;
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::string> parsedRow;
		while (std::getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}
		if (row_number > 1)
		{
			int source = stoi(parsedRow.at(0));
			int target = stoi(parsedRow.at(1));
			cout << row_number << " " << source << " " << target << endl;
			C2[source][target] = 1;
			if (max < source) {
				max = source;
			}
			else if (max < target) {
				max = target;
			}
		}
	}
	

	//Define max after the input files is given, comparing the n value from both C1 and C2
	N = max;
	
		cout << "Output C1" << endl;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				cout << C1[i][j] << " ";
			}
			cout << endl;
		}
		
		cout << "Output C2" << endl;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				cout << C2[i][j] << " ";
			}
			cout << endl;
		}
	
		std::cout << "Input Y_Matrix:\n";

		std::ifstream  data_y("y.csv");
		row_number = 0;
		max = 0;
		while (std::getline(data_y, line))
		{
			row_number = row_number + 1;
			std::stringstream lineStream(line);
			std::string cell;
			std::vector<std::string> parsedRow;
			while (std::getline(lineStream, cell, ','))
			{
				parsedRow.push_back(cell);
			}
			if (row_number > 1)
			{
				int id = stoi(parsedRow.at(0));
				int y = stoi(parsedRow.at(1));
				cout << row_number << " " << id << " " << y << endl;
				Y[id] = y;
				if (max < id) {
					max = id;
				}
				
			}
		}


		N = max;

		cout << "Output Y" << endl;
		for (int i = 0; i <= N; i++) {
				cout <<i<<" "<< Y[i] << " "<<endl;
			
		}
	


}

//Function to calculate D1 and D2 matrices 
void calc_Decomposed_Network() {
    int i, j;

    for (i = 0; i < N; i++) {
        float s_1 = 0, s_2 = 0;
        for (j = 0; j < N;  j++) {
            s_1 += sgn(C2[i][j]) * C1[i][j] * Y[j];
            s_2 += sgn(C2[i][j]) * C1[i][j];
        }
        D1[i] = s_1 / s_2;
    }

    for (i = 0; i < N; i++) {
        float s_3 = 0, s_4 = 0;
        for (j = 0; j < N; j++) {
            s_3 += (1 - sgn(C2[i][j])) * C1[i][j] * Y[j];
            s_4 += (1 - sgn(C2[i][j])) * C1[i][j];
        }
        D2[i] = s_3 / s_4;
    }
}

//Function to display the output matrix 
void output_data() {
    int i;

    std::cout << "Decomposed_Network:\nD1_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cout << D1[i] << " ";
    std::cout << "\nD2_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cout << D2[i] << " ";
}

int main()
{
    input_data();

    calc_Decomposed_Network();

    output_data();
}




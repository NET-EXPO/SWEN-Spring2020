#include <iostream>
#include<fstream>
#include <vector>
#include <sstream>
using namespace std;


#define MAX_SIZE 1024

// Initializing the Matrices W,Y,E

int N;
float W[MAX_SIZE][MAX_SIZE] = { 0 };
float Y[MAX_SIZE];
float E[MAX_SIZE];
// function to print cell

// void read()
// {
// 	std::ifstream  data("dyad_ties.csv");
// 	std::string line;
// 	int row_number = 0;
// 	while (std::getline(data, line))
// 	{
// 		row_number = row_number + 1;
// 		std::stringstream lineStream(line);
// 		std::string cell;
// 		std::vector<std::string> parsedRow;
// 		while (std::getline(lineStream, cell, ','))
// 		{
// 			parsedRow.push_back(cell);
// 		}
// 		if (row_number > 1)
// 		{
// 			int source = stoi(parsedRow.at(0));
// 			int target = stoi(parsedRow.at(1));
// 			cout << row_number << " " << source << " " << target << endl;

// 		}
// 	}
	

// }

void input_data() {
	std::ifstream  data("dyad_ties.csv");
	std::string line;
	int row_number = 0;
	int max = 0;
	while (std::getline(data, line))
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
			W[source][target] = 1;
			if (max < source) {
				max = source;
			}
			else if (max < target) {
				max = target;
			}
		}
	}

	
	N = max;
	
		cout << "Output W" << endl;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				cout << W[i][j] << " ";
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

		cout << "Output W" << endl;
		for (int i = 0; i <= N; i++) {
				cout <<i<<" "<< Y[i] << " "<<endl;
			
		}
	


}

// Function to Calculate NETWORK Exposure Model

void calc_Network_Exposure() {
	int i, j;
	for (i = 0; i <= N; i++) {
		float s_row = 0, s_mul = 0;
		for (j = 0; j <= N; j++) {
			s_row += W[i][j];
			s_mul += W[i][j] * Y[j];
		}
		E[i] = s_mul / s_row;
	}
}

// Function for Output Display

void output_data() {
	int i;

	std::cout << "Network Exposure:\nE_Matrix:\n";
	for (i = 0; i <= N; i++)
		std::cout <<i<<" "<< E[i] << " "<<endl;
}

int main() {

	input_data();

	calc_Network_Exposure();

	output_data();

	return 0;
}

#include <iostream>
#include <iomanip>
#include <OpenXLSX/OpenXLSX.h>

using namespace std;
using namespace OpenXLSX;


#define MAX_SIZE 1024

// Initializing the Matrices W,Y,E

int N;
float W[MAX_SIZE][MAX_SIZE] = { 0 };
float Y[MAX_SIZE];
float E[MAX_SIZE];
// function to print cell


// Function to Enter Input data for N
XLDocument doc;

void input_data() {
	doc.OpenDocument("./Formula1.xlsx");
	auto dyad_ties = doc.Workbook().Worksheet("dyad_ties");
	auto y = doc.Workbook().Worksheet("y");

	auto totalRow = dyad_ties.RowCount();
	N = y.RowCount() - 1;
	cout << "N " << N << endl;
	std::cout << "Input W_Matrix:\n";

	for (int index = 2; index <= totalRow; index++) {
		auto firstRow = dyad_ties.Row(index);
		int i = firstRow.Cell(1).Value().Get<int>();
		int j = firstRow.Cell(2).Value().Get<int>();
		W[i][j] = 1;

	}
	cout << "Output W" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << W[i][j] << " ";
		}
		cout << endl;
	}




	std::cout << "Input Y_Matrix:\n";
	for (int i = 2; i <= N + 1; i++) {
		auto row = y.Row(i);
		int id = row.Cell(1).Value().Get<int>();
		int y = row.Cell(2).Value().Get<int>();
		Y[id] = y;
		cout << i << " " << id << " " << y << endl;
	}


}

// Function to Calculate NETWORK Exposure Model

void calc_Network_Exposure() {
	int i, j;
	for (i = 0; i < N; i++) {
		float s_row = 0, s_mul = 0;
		for (j = 0; j < N; j++) {
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
	for (i = 0; i < N; i++)
		std::cout << E[i] << " ";
}

int main() {

	input_data();

	calc_Network_Exposure();

	output_data();

	return 0;
}



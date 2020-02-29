

#include <iostream>

#define MAX_SIZE 1024

int N;
float C[MAX_SIZE][MAX_SIZE];
float Y[MAX_SIZE];
float F[MAX_SIZE];

float sgn(float value) {
    if (value == 0)  return 0;
    if (value < 0)   return -1;
    if (value > 0)   return 1;
}

void input_data() {    
    std::cout << "Please input number N:\n";
    std::cin >> N;

    int i, j;

    std::cout << "Please input C_Matrix:\n";
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) {
            std::cin >> C[i][j];
        }

    std::cout << "Please input Y_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cin >> Y[i];
}

void calc_Affiliation_Exposure() {
    int i, j;

    for (i = 0; i < N; i++) {
        float s_row = 0, s_mul = 0;
        for (j = 0; j < N; j++) {
            s_row += C[i][j];
            s_mul += C[i][j] * Y[j];
        }
        F[i] = s_mul / s_row;
    }
}

void output_data() {
    int i;

    std::cout << "Affiliation Exposure:\nF_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cout << F[i] << " ";
}

int main()
{
    input_data();

    calc_Affiliation_Exposure();

    output_data();
}






#include <iostream>

#define MAX_SIZE 1024

int N;
float C1[MAX_SIZE][MAX_SIZE], C2[MAX_SIZE][MAX_SIZE];
float Y[MAX_SIZE];
float D1[MAX_SIZE], D2[MAX_SIZE];

float sgn(float value) {
    if (value == 0)  return 0;
    if (value < 0)   return -1;
    if (value > 0)   return 1;
}

void input_data() {
    std::cout << "Please input number N:\n";
    std::cin >> N;

    int i, j;

    std::cout << "Please input C1_Matrix:\n";
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            std::cin >> C1[i][j];

    std::cout << "Please input C2_Matrix:\n";
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            std::cin >> C2[i][j];

    std::cout << "Please input Y_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cin >> Y[i];
}

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



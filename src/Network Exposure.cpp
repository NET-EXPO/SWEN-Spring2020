

#include <iostream>

#define MAX_SIZE 1024

int N;
float W[MAX_SIZE][MAX_SIZE];
float Y[MAX_SIZE];
float E[MAX_SIZE];

void input_data() {    
    std::cout << "Please input number N:\n";
    std::cin >> N;

    int i, j;

    std::cout << "Please input W_Matrix:\n";
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) {
            std::cin >> W[i][j];
        }

    std::cout << "Please input Y_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cin >> Y[i];
}

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

void output_data() {
    int i;

    std::cout << "Network Exposure:\nE_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cout << E[i] << " ";    
}

int main()
{
    input_data();

    calc_Network_Exposure();

    output_data();
}



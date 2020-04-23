



#include <iostream>

#define MAX_SIZE 1024

//initializing the matrices A,Y,F

int N;
int M;
float A[MAX_SIZE][MAX_SIZE];
float AT[MAX_SIZE][MAX_SIZE];
float C[MAX_SIZE][MAX_SIZE];
float Y[MAX_SIZE];
float F[MAX_SIZE];


float sgn(float value) {
    if (value == 0)  return 0;
    if (value < 0)   return -1;
    if (value > 0)   return 1;
}
//Function to enter input data for N

void input_data() {    
    std::cout << "Please input number N:\n";
    std::cin >> N;
    
    std::cout << "Please input number N:\n";
    std::cin >> M;

    int i, j;

    std::cout << "Please input A_Matrix:\n";
    for (i = 0; i < N; i++) 
        for (j = 0; j < M; j++) {
            std::cin >> A[i][j];
        }

    std::cout << "Please input Y_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cin >> Y[i];
}

void transpose_Matrix(){
      int i, j, k;
      
    for (i = 0; i < N; i++) 
        for (j = 0; j < M; j++) 
            AT[i][j] = A[j][i]; 
    
     std::cout << "Print the transpose \n";
    for (i = 0; i < M; i++) 
        for (j = 0; j < N; j++) 
        	std::cout << AT[i][j] << " ";
    
    //Multiply and store in C matrix
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            for(k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * AT[k][j];
            }
    
    	
} 

//Function to calculate Affilitaion Exposure Model
void calc_Affiliation_Exposure() {
    int i, j;
    
    std::cout << "Print C Matrix which is multiplied:\nC_Matrix:\n";
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
        	std::cout << C[i][j] << " ";

    for (i = 0; i < N; i++) {
        float s_row = 0, s_mul = 0;
        for (j = 0; j < N; j++) {
        	//Choose A or C based on test data
            s_row += C[i][j];
            s_mul += C[i][j] * Y[j];
        }
        F[i] = s_mul / s_row;
    }
}

// Function for output display
void output_data() {
    int i;

    std::cout << "Affiliation Exposure:\nF_Matrix:\n";
    for (i = 0; i < N; i++)
        std::cout << F[i] << " ";
}
// Calling Main methods
int main()
{
    input_data();
    
    transpose_Matrix();

    calc_Affiliation_Exposure();

    output_data();
}




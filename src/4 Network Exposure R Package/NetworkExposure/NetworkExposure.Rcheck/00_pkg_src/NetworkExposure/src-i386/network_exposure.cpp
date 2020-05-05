#include <Rcpp.h>
#include <iostream>
#include<fstream>
#include <vector>
#include <sstream>
using namespace std;
using namespace Rcpp;



#define MAX_SIZE 1024

// Initializing the Matrices W,Y,E

int N;
float W[MAX_SIZE][MAX_SIZE] = { 0 };
float Y[MAX_SIZE];
float E[MAX_SIZE];


void input_data(std::string dyad_ties_file, std::string y_file) {

    // std::ifstream  data("dyad_ties.csv");
    std::ifstream  data(dyad_ties_file);
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
    
    Rcout  << "Input Y_Matrix\n";
    
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
            Y[id] = y;
            if (max < id) {
                max = id;
            }
            
        }
    }
    
    
    N = max;
    
    
    
    
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
    
    Rcout  << "Network Exposure:\nE_Matrix:\n";
    for (i = 0; i <= N; i++)
      Rcout  <<i<<" "<< E[i] << " "<<endl;
    
    std::ofstream output_file;
    output_file.open ("output.csv");
    output_file << "id,E_value\n";
    for (i = 0; i <= N; i++){
        output_file<<i;
        output_file<<",";
        output_file<<E[i];
        output_file<<"\n";
        
    }
    
    output_file.close();
    Rcout <<"Output Written to output.csv"<<endl;
}

//' Calucate Network Exposure
//' 
//' 
// [[Rcpp::export]]
void show_network_exposure(std::string dyad_ties_file, std::string y_file) {
    
    input_data(dyad_ties_file,  y_file);
    
    calc_Network_Exposure();
    
    output_data();
 
}


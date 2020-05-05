

/* INCLUDE headers and necessary stuff */
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <mutex>
#include <list> 
#include <iterator> 
#include <Windows.h>
#include <ctime>
#include <wchar.h>
#include <stdio.h>
#include <filesystem>
#include <string>
/* ------------------------------------*/

using namespace std;


#define MAX_SIZE 10240

// Initializing the Matrices W,Y,E

int N;
std::mutex logMutex;
float W[MAX_SIZE][MAX_SIZE] = { 0 };
float Y[MAX_SIZE];
float E[MAX_SIZE];
// function to print cell


void read(string filename)
{
	ifstream  data(filename);
	string line;
	int row_number = 0;
	while (getline(data, line))
	{
		row_number = row_number + 1;
		stringstream lineStream(line);
		string cell;
		vector<string> parsedRow;
		while (getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}
		if (row_number > 1)
		{
			int source = stoi(parsedRow.at(0));
			int target = stoi(parsedRow.at(1));
			//cout << row_number << " " << source << " " << target << endl;

		}
	}

}

void input_data(string directory, string fileName, string yFileName, string folderName) {

	string line;
	string path = directory + "/" + folderName + "/" + fileName;
	ifstream data(path);
	int row_number = 0;
	int max = 0;
	if (data.is_open()) {
		while (getline(data, line))
		{
			row_number = row_number + 1;
			stringstream lineStream(line);
			string cell;
			vector<string> parsedRow;
			while (getline(lineStream, cell, ','))
			{
				parsedRow.push_back(cell);
			}
			if (row_number > 1)
			{
				int source = stoi(parsedRow.at(0));
				int target = stoi(parsedRow.at(1));
				//cout << row_number << " " << source << " " << target << endl;
				W[source][target] = 1;
				if (max < source) {
					max = source;
				}
				else if (max < target) {
					max = target;
				}
			}
		}
	}

	N = max;
	/*
	cout << "Output W" << endl;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << W[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Input Y_Matrix:\n";
	*/
	ifstream  data_y(directory + "/" + folderName + "/" + yFileName);
	row_number = 0;
	max = 0;
	while (std::getline(data_y, line))
	{
		row_number = row_number + 1;
		stringstream lineStream(line);
		string cell;
		vector<string> parsedRow;
		while (getline(lineStream, cell, ','))
		{
			parsedRow.push_back(cell);
		}
		if (row_number > 1)
		{
			int id = stoi(parsedRow.at(0));
			int y = stoi(parsedRow.at(1));
			//cout << row_number << " " << id << " " << y << endl;
			Y[id] = y;
			if (max < id) {
				max = id;
			}

		}
	}


	N = max;
	/*
	cout << "Output Y" << endl;
	for (int i = 0; i <= N; i++) {
		cout << i << " " << Y[i] << " " << endl;

	}*/



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
		std::cout << i << " " << E[i] << " " << endl;
	

}

// For showing the list names 
void showlist(list <string> g)
{
	list <string> ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
	{
		std::cout << '\n' << *it;
	}
	std::cout << '\n';
}

void processData(string directory, string fileName, string yFileName, string folderName)
{

	input_data(directory, fileName, yFileName, folderName);

	calc_Network_Exposure();

	//output_data();

}

list<string> namesOfFile(string folderName, string dataDirectory)
{
	list<string> fileNames;

	WIN32_FIND_DATA search_data;
	string dir(dataDirectory + folderName + "\\*.csv");

	std::wstring unicode(dir.begin(), dir.end());

	WCHAR* directory = (WCHAR*)unicode.c_str();


	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

	HANDLE handle = FindFirstFile(directory, &search_data);

	//convert from wide char to narrow char array
	 

	while (handle != INVALID_HANDLE_VALUE)
	{
		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, search_data.cFileName, -1, ch, 260, &DefChar, NULL);

		//A std:string  using the char* constructor.
		std::string ss(ch);
		fileNames.push_back(ss);
		//cout << "File Name :" << ss;

		if (FindNextFile(handle, &search_data) == FALSE)
			break;
	}

	//showlist(fileNames);
	FindClose(handle);
	return fileNames;
}

list<string> nameOfFolders(string dataDirectory)
{
	list<string> folderNames;

	WIN32_FIND_DATA search_data;
	string dir(dataDirectory + "*");

	std::wstring unicode(dir.begin(), dir.end());

	WCHAR* directory = (WCHAR*)unicode.c_str();


	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

	HANDLE handle = FindFirstFile(directory, &search_data);

	//convert from wide char to narrow char array


	while (handle != INVALID_HANDLE_VALUE)
	{
		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, search_data.cFileName, -1, ch, 260, &DefChar, NULL);

		//A std:string  using the char* constructor.
		std::string ss(ch);

		folderNames.push_back(ss);
		//cout << "File Name :" << ss;

		if (FindNextFile(handle, &search_data) == FALSE)
			break;
	}

	//showlist(fileNames);
	FindClose(handle);
	return folderNames;
}


long int unix_timestamp()
{
	time_t t = std::time(0);
	long int now = static_cast<long int> (t);
	return now;
}

bool fileExists(std::string& fileName) {
	return static_cast<bool>(std::ifstream(fileName));
}

template <typename filename, typename T1, typename T2, typename T3, typename T4>
bool writeCsvFile(filename &fileName, T1 column1, T2 column2, T3 column3, T4 column4) {
	std::lock_guard<std::mutex> csvLock(logMutex);
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::app);
	if (file) {
		file << "\"" << column1 << "\",";
		file << "\"" << column2 << "\",";
		file << "\"" << column3 << "\",";
		file << "\"" << column4 << "\"";
		file << std::endl;
		return true;
	}
	else {
		return false;
	}
}

template <typename filename, typename T1, typename T2>
bool writeNetCsvFile(filename &fileName, T1 column1, T2 column2){
	std::lock_guard<std::mutex> csvLock(logMutex);
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::app);
	if (file) {
		file << "\"" << column1 << "\",";
		file << "\"" << column2 << "\"";
		file << std::endl;
		return true;
	}
	else {
		return false;
	}
}



int main() {


	string fileName;
	string fileNameY;
	long int startTime;
	long int endTime;

	string folderName = "";
	string outputFile = "";
	string outputNetValue = "";
	//int numberOfFiles = 10;

	string dataDirectory = "Dataset\\";
	list<string> allFolderNames = nameOfFolders(dataDirectory);

	list <string> ::iterator itt;
	for (itt = allFolderNames.begin(); itt != allFolderNames.end(); ++itt)
	{
		folderName = *itt;
		outputFile = folderName + ".csv";
		//outputNetValue = "NET_OUTPUT_" + folderName;
		//numberOfFiles = 10;
		if (folderName == "." || folderName == "..")
			continue;

		list<string> allFileNames = namesOfFile(folderName, dataDirectory);
		if (allFileNames.size() == 0)
			continue;
		else {
			allFileNames.sort();

			
			if (fileExists(outputFile))
				remove(outputFile.c_str());
			writeCsvFile(outputFile, "File Name", "Start Time ", "End Time", "Execution Time");
			
			
			outputNetValue = "NET_OUTPUT_" + folderName + ".csv";
			if (fileExists(outputNetValue))
				remove(outputNetValue.c_str());
			writeNetCsvFile(outputNetValue, fileName, "");
			writeNetCsvFile(outputNetValue, "", "Net Exposure");
			

			list <string> ::iterator it;
			for (it = allFileNames.begin(); it != allFileNames.end(); ++it)
			{
				fileName = *it;
				++it;
				fileNameY = *it;
				std::cout << "\n\nFolder : " << folderName << "\nFile : " << fileName << "\nFile Y : " << fileNameY << endl;
				startTime = unix_timestamp();
				processData(dataDirectory, fileName, fileNameY, folderName);
				endTime = unix_timestamp();
				
				for (int i = 0; i < N; i++) {
					if (!writeNetCsvFile(outputNetValue, "", E[i])) {
						std::cerr << "Failed to write to file: " << fileName << "\n";
					}
				}
				if (!writeCsvFile(outputFile, fileName, startTime, endTime, (endTime - startTime))) {
					std::cerr << "Failed to write to file: " << fileName << "\n";
				}
			}
		}
	}
	std::cout << "----------";
	getchar();
	return 0;
}

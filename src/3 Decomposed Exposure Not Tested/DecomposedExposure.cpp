

/* INCLUDED headers and necessary stuff */
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
int M;

std::mutex logMutex;
float WC1[MAX_SIZE][MAX_SIZE] = { 0 };
float WC2[MAX_SIZE][MAX_SIZE] = { 0 };
float _Y[MAX_SIZE];
int AC1[MAX_SIZE][MAX_SIZE];
int AC2[MAX_SIZE][MAX_SIZE];
float D1[MAX_SIZE];
float D2[MAX_SIZE];
float Y[MAX_SIZE];
float F[MAX_SIZE];
// function to print cell


float sgn(float value) {
	if (value == 0)  return 0;
	if (value < 0)   return -1;
	if (value > 0)   return 1;
}

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

void input_data(string directory, string fileNameC1 , string fileNameC2, string yFileName, string folderName) {

	string lineC1;
	string pathC1 = directory + "/" + folderName + "/" + fileNameC1;
	ifstream dataC1(pathC1);
	int row_numberC1 = 0;
	int maxC1 = 0;
	if (dataC1.is_open()) {
		while (getline(dataC1, lineC1))
		{
			row_numberC1 = row_numberC1 + 1;
			stringstream lineStreamC1(lineC1);
			string cellC1;
			vector<string> parsedRowC1;
			while (getline(lineStreamC1, cellC1, ','))
			{
				parsedRowC1.push_back(cellC1);
			}
			if (row_numberC1 > 1)
			{
				int source = stoi(parsedRowC1.at(0));
				int target = stoi(parsedRowC1.at(1));
				//cout << row_number << " " << source << " " << target << endl;
				WC1[source][target] = 1;

			}
		}
	}


	string lineC2;
	string pathC2 = directory + "/" + folderName + "/" + fileNameC2;
	ifstream dataC2(pathC2);
	int row_numberC2 = 0;
	int maxC2 = 0;
	if (dataC2.is_open()) {
		while (getline(dataC2, lineC2))
		{
			row_numberC2 = row_numberC2 + 1;
			stringstream lineStreamC2(lineC2);
			string cellC2;
			vector<string> parsedRowC2;
			while (getline(lineStreamC2, cellC2, ','))
			{
				parsedRowC2.push_back(cellC2);
			}
			if (row_numberC2 > 1)
			{
				int source = stoi(parsedRowC2.at(0));
				int target = stoi(parsedRowC2.at(1));
				//cout << row_number << " " << source << " " << target << endl;
				WC2[source][target] = 1;

			}
		}
	}

	//N = max;
	string lineY;
	ifstream  data_y(directory + "/" + folderName + "/" + yFileName);
	int row_numberY = 0;
	int maxY = 0;
	int r = 0, c = 0;
	while (std::getline(data_y, lineY))
	{
		row_numberY = row_numberY + 1;
		stringstream lineStreamY(lineY);
		string cellY;
		vector<string> parsedRowY;
		while (getline(lineStreamY, cellY, ','))
		{
			parsedRowY.push_back(cellY);
		}
		if (row_numberY > 1)
		{
			int id = stoi(parsedRowY.at(0));
			int y = stoi(parsedRowY.at(1));
			int mode = stoi(parsedRowY.at(2));
			Y[row_numberY] = y;
			// (max < id) {
			//	max = id;
			//}

		}
	}
	N = row_numberC1;

}

void calc_DecomposedExposure() {
	int i, j;

	for (i = 0; i < N; i++) {
		float s_1 = 0, s_2 = 0;
		for (j = 0; j < N; j++) {
			s_1 += sgn(WC2[i][j]) * WC1[i][j] * Y[j];
			s_2 += sgn(WC2[i][j]) * WC1[i][j];
		}
		D1[i] = s_1 / s_2;
	}

	for (i = 0; i < N; i++) {
		float s_3 = 0, s_4 = 0;
		for (j = 0; j < N; j++) {
			s_3 += (1 - sgn(WC2[i][j])) * WC1[i][j] * Y[j];
			s_4 += (1 - sgn(WC2[i][j])) * WC1[i][j];
		}
		D2[i] = s_3 / s_4;
	}
}

// Function for Output Display

void output_data() {
	int i;

	std::cout << "DecomposedExposure:\nD1_Matrix:\n";
	for (i = 0; i < N; i++)
		std::cout << D1[i] << " ";
	std::cout << "\nD2_Matrix:\n";
	for (i = 0; i < N; i++)
		std::cout << D2[i] << " ";

}

/*
// For showing the list names 
void showlist(list <string> g)
{
	list <string> ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
	{
		std::cout << '\n' << *it;
	}
	std::cout << '\n';
}*/

void processData(string directory, string fileNameC1, string fileNameC2, string yFileName, string folderName)
{

	input_data(directory, fileNameC1, fileNameC2, yFileName, folderName);

	calc_DecomposedExposure();

	output_data();

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
bool writeNetCsvFile(filename &fileName, T1 column1, T2 column2) {
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

	string fileNameC1;
	string fileNameC2;
	string fileNameY;
	long int startTime;
	long int endTime;

	string folderName = "";
	string outputFile = "";
	string outputNetValueD1 = "";
	string outputNetValueD2 = "";
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


			outputNetValueD1 = "NET_OUTPUT_D1_" + folderName + ".csv";
			outputNetValueD2 = "NET_OUTPUT_D2_" + folderName + ".csv";
			if (fileExists(outputNetValueD1))
				remove(outputNetValueD1.c_str());
			if (fileExists(outputNetValueD2))
				remove(outputNetValueD2.c_str());

			list <string> ::iterator it;
			for (it = allFileNames.begin(); it != allFileNames.end(); ++it)
			{
				fileNameC1 = *it;
				++it;
				fileNameC2 = *it;
				++it;
				fileNameY = *it;
				std::cout << "\n\nFolder : " << folderName << "\nFileC1 : " << fileNameC1  << "\nFileC2 : " << fileNameC2 << "\nFile Y : " << fileNameY << endl;
				startTime = unix_timestamp();
				processData(dataDirectory, fileNameC1, fileNameC2, fileNameY, folderName);
				endTime = unix_timestamp();

				writeNetCsvFile(outputNetValueD1, fileNameC1, "");
				writeNetCsvFile(outputNetValueD1, "Input D1", "Output D1");
				for (int i = 0; i < N; i++) {
					if (!writeNetCsvFile(outputNetValueD1, "", D1[i])) {
						std::cerr << "Failed to write to file: " << outputNetValueD1 << "\n";
					}
				}
				if (!writeCsvFile(outputFile, fileNameC1, startTime, endTime, (endTime - startTime))) {
					std::cerr << "Failed to write to file: " << fileNameC1 << "\n";
				}

				writeNetCsvFile(outputNetValueD2, fileNameC2, "");
				writeNetCsvFile(outputNetValueD2, "Input D2", "Output D2");
				for (int i = 0; i < N; i++) {
					if (!writeNetCsvFile(outputNetValueD2, "", D2[i])) {
						std::cerr << "Failed to write to file: " << outputNetValueD2 << "\n";
					}
				}
				if (!writeCsvFile(outputFile, fileNameC2, startTime, endTime, (endTime - startTime))) {
					std::cerr << "Failed to write to file: " << fileNameC2 << "\n";
				}
			}
		}
	}
	std::cout << "----------";
	getchar();
	return 0;

}


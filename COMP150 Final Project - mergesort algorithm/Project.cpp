/*
COMP150 Term Project
Title: Binary Search and Merge Sort Algorithm
Author: Jordan Greaux
Student ID: 300216310
Due Date: December 1, 2023
*/

#include <iostream>		// includes iostream library
#include <fstream>		// includes file stream library
#include <vector>		// includes vector library
#include <cmath>		// includes cmath library
#include <string>		// includes string library
#include <iomanip>		// includes iomanip library
using namespace std;	// using standard namespace

int binarySearch(vector<int>& a, int size, int value);						// binarySearch prototype
void divide(vector<int>& a);												// divide prototype
void mergeSort(vector<int>& left, vector<int>& right, vector<int>& result);	// mergeSort prototype
void statsCalc(vector<int> a, int size);									// statsCalc prototype

int main()	// main function
{
	ifstream inputFile;		// defines input stream variable inputFile		
	ofstream outputFile;	// defines output stream variable outputfile
	string fileName;		// defines variable to hold the file name entered by user

	vector<int> vData;		// defines vector to hold variables from file
	string line;			// defines string variable to hold each line of file
	int value;				// defines integer variable to hold the conversion of string variable line
	int i = 0;				// index variable

	cout << "Please enter the name of the target file:\n";	// prompts user to enter fileName
	cout << "(for testing, the file is already in project folder - enter '1m.txt'\n";
	cin >> fileName;										// fileName input
	cout << "\nLoading...\n";								// loading message for exceptionally large datasets

	inputFile.open(fileName);	// opens inputFile
	if (!inputFile.is_open())	// validates successful opening of inputFile
	{
		cout << "Error opening file\n";
		cout << "Ensure that target file exists in program folder\n";
		return 0;
	}

	outputFile.open("sorted.txt");	// opens outputFile
	if (!outputFile.is_open())		// validates successful opening of outputFile
	{
		cout << "Error creating file\n";
		cout << "Please restart the program and try again";
	}

	while (!inputFile.eof())		// while loop runs as long as it hasnt reached end of inputFile
	{
		getline(inputFile, line);	// getline from inputFile and store in line variable
		int value = stoi(line);		// convert string line to int value
		vData.push_back(value);		// push back int value onto vector
	}

	int size = vData.size();		// create and define size of vector

	divide(vData);					// passes vector into divide function

	for (i = 0; i < size; i++)		// for loop writes values of the vector into the output file
	{
		outputFile << vData[i] << endl;
	}

	cout << endl << size << " values sorted successfully\n";	// success message
	cout << "Sorted dataset written to program file\n\n";		// file containing sorted data has been created

	statsCalc(vData, size);			// passes vector and size into the statsCalc function

	char exit = 'n';	// exit variable for do while loop - allows repetition
	do
	{
		int search = 0;		// search variable initialized as 0
		int position = -1;	// position variable initialized as -1 (does not change if search value is not found)
		cout << "Enter a value to search within the dataset\n"; // console prompt
		cin >> search;	// recieves search value from console input

		position = binarySearch(vData, size, search);	// return value from binarySearch becomes position value

		if (position < 0)													// if position is less than 0 (-1)				
		{
			cout << endl << search << " was not found in the dataset\n\n";	// output indicating search not found
		}
		else																// if position is greater than 0 (search value)
		{
			cout << endl << search << " was found in the dataset\n\n";		// output indicating search found
		}
		cout << "Do you want to search for another value? (y/n)\n";			// prompt to repeat
		cin >> exit;														// exit variable
	} while (exit == 'y' || exit == 'Y');	// if exit variable is y or Y, do while loop repeats

	cout << "\nThank you, have a nice day\n";	// exit message

	inputFile.close();	// closes inputFile
	outputFile.close(); // closes outputFile

	return 0;	// returns 0 to the main function
}

int binarySearch(vector<int>& a, int size, int value)	// binarySearch header
{														// takes pointer to the content of a, and integers size and value
	int first = 0,			// first element
		last = size - 1,	// last element
		middle,				// middle element
		position = -1;		// position element
	bool found = false;		// boolean variable for whether search value has been found

	while (!found && first <= last)	// while loop runs as long as found is opposite and first element is greater or equal to last
	{
		middle = (first + last) / 2;	// calculate midpoint
		if (a[middle] == value)			// if the middle value of a is equal to the search value
		{
			found = true;				// found becomes true
			position = middle;			// position becomes middle
		}
		else if (a[middle] > value)		// otherwise, if the middle value of a is greater than the search value
		{
			last = middle - 1;			// last element becomes the middle element minus 1
		}
		else
		{								// otherwise, if middle value of a is less than search value
			first = middle + 1;			// first element becomes middle value plus 1
		}
	}									// repeats until found is opposite (true) and first element is greater or equal to last
	return position;					// returns position to main
}

void divide(vector<int>& a)	// divide header takes pointer to the content of a
{
	int size = a.size();		// defines the size of vector
	if (size > 1)				// if the size of vector is greater than 1, proceed
	{							// size > 1 because the goal before sorting is each element in its own array
		int mid = size / 2;		// define midpoint
		vector<int> left(0);	// create left side vector, initial size 0
		vector<int> right(0);	// create right side vector, initial size 0

		for (int i = 0; i < mid; i++)	// for loop to insert elements into left side vector
		{								// i < mid = all elements that should be in the left side vector
			left.push_back(a[i]);
		}
		for (int i = 0; i < (size - mid); i++)	// for loop to insert elements into right side vector
		{										// i < (size - mid) = all elements that should be in the right side vector
			right.push_back(a[mid + i]);
		}

		divide(left);				// pass left side vector back into divide
		divide(right);				// pass right side vector back into divide
		mergeSort(left, right, a);	// pass left, right and a vector into mergeSort
	}
}// though it is not a loop, the passing of left/right back into divide makes function repeat until vector size = 1

void mergeSort(vector<int>& left, vector<int>& right, vector<int>& a)	// merge sort header
{																		// takes pointers to the content of vectors left, right and a
	int x = 0,	// index x, for placing sorted variables back into vector a
		y = 0,	// index y, for comparing left side array to right and a
		z = 0;	// index z, for comparing right side array to left and a

	while (y < left.size() && z < right.size())	// while loop runs as long as y is less than left side vector size and z is less than right side vector size
	{
		if (left[y] < right[z])	// compares if the y index left is less than z index right
		{
			a[x] = left[y];		// if true, x index of a becomes y index left
			y++;				// increment y
		}
		else
		{
			a[x] = right[z];	// otherwise, x index of a becomes z index of right
			z++;				// increment z
		}
		x++;					// increment x
	}
	// while loops for leftover variables
	while (y < left.size())		// while y is less than left size
	{
		a[x] = left[y];			// x index of a becomes y index left
		y++;					// increment y
		x++;					// increment x
	}
	while (z < right.size())	// while z is less than right size
	{
		a[x] = right[z];
		z++;					// increment z
		x++;					// increment x
	}

}

void statsCalc(vector<int> a, int size)	// statsCalc header
{
	double sum = 0;		// double variable for sum
	double sdsum = 0;	// double variable for sum of (x - mean) to the power of 2 for calculating standard deviation
	double mean = 0;	// double variable for mean
	double median = 0;	// double variable for median
	double stDev = 0;	// double variable for standard deviation
	double min = 0;		// double variable for minimum value
	double q1 = 0;		// double variable for quartile 1
	double q3 = 0;		// double variable for quartile 3
	double max = 0;		// double variable for maximum value

	int i = 0;			// index variable

	for (i = 0; i < size; i++)	// for loop calculating the sum of vector elements
	{
		sum = a[i] + sum;
	}

	mean = sum / size;			// result from previous for loop divided by size of vector

	for (i = 0; i < size; i++)	// for loop calculating the sum of (x - mean) to the power of 2
	{
		sdsum = pow((a[i] - mean), 2);
	}

	stDev = sqrt(sdsum / size);	// square root of result from previous for loop divided by size of vector

	if (size % 2 == 0)				// if size modulus 2 is 0, the dataset has an odd number of elements
	{
		median = (size + 1) / 2;	// formula for median if size is odd
	}
	else
	{
		median = ((size / 2) + ((size / 2) + 1)) / 2;	// formula for median if size is even
	}

	if (size % 2 == 0)			// if size modulus 2 is 0, the dataset has an odd number of elements
	{
		q1 = (size + 1) * 0.25;		// formula for q1 if size is odd
	}
	else
	{
		q1 = (size + 2) / 4;		// formula for 1 if size is even
	}

	if (size % 2 == 0)			// if size modulus 2 is 0, the dataset has an odd number of elements
	{
		q3 = (size + 1) * 0.75;		// formula for q3 if size is odd
	}
	else
	{
		q3 = (size + 2) / 4;		// formula for q3 if size is even
	}



	// basic statistics table output
	cout << "Basic Statistics:\n";				// table header
	cout << setw(10) << left << "Mean";			// set width to 10, orient left, output label mean
	cout << setw(10) << left << "StDev";		// set width to 10, orient left, output label stdev
	cout << setw(10) << left << "Min";			// set width to 10, orient left, output label min
	cout << setw(10) << left << "Q1";			// set width to 10, orient left, output label q1
	cout << setw(10) << left << "Median";		// set width to 10, orient left, output label median
	cout << setw(10) << left << "Q3";			// set width to 10, orient left, output label q3
	cout << setw(10) << left << "Max" << endl;	// set width to 10, orient left, output label max, end line
	cout << setw(10) << left << mean;			// set width to 10, orient left, output mean value
	cout << setw(10) << left << stDev;			// set width to 10, orient left, output stdev value
	cout << setw(10) << left << a[0];			// set width to 10, orient left, output first element in vector a
	cout << setw(10) << left << q1;				// set width to 10, orient left, output	q1 value
	cout << setw(10) << left << median;			// set width to 10, orient left, output median value
	cout << setw(10) << left << q3;				// set width to 10, orient left, output q3 value
	cout << setw(10) << left << a[size - 1];		// set width to 10, orient left, output last element in vector a
	cout << endl << endl;						// end line, end line
}
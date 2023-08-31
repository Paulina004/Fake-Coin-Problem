/********************************************************************************************
PROJECT: "Finding the Fake Coin" Programming Project
AUTHOR: Paulina DeVito

COPYING MY CODE IS STRICTLY NOT ALLOWED. Thank you for understanding.
*********************************************************************************************/



//LIBRARIES
//**************************************************************************************
#include <iostream> 
#include <iomanip>
#include <chrono>
#include <vector> 
#include <cmath> 
#include <algorithm> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace std::chrono;



//FUNCTION PROTOYPES
//**************************************************************************************
int ALG1(vector<int>& coinArr, int n);
int ALG2(vector<int>& coinArr, vector<int>& sums, int n, int start, int end);
void getSums(vector<int>& coinArr, vector<int>& sums, int n);
void print(vector<int>& A);
void printAvg(vector<double>& A);
void computeAvg(vector<double>& A);





//MAIN FUNCTION 
//**************************************************************************************
int main()
{
	/*
	cout << "************************************************FINDING THE FAKE COIN TESTING************************************************\n\n\n";

	//VARIABLES
	int max = 10;
	int n = max;
	int fakeCoinIndex1;
	int fakeCoinIndex2;

	//VECTORS 
	vector<int> coinArr(max, 1);
	vector<int> coinArrCopy(max, 1);
	vector<int> sums(max, 0);

	//RANDOMLY GENERATE THE INDEX WHERE THE FAKE COIN WILL BE 
	srand(time(NULL)); //seed the time
	//output = min + (rand() % (int)(max - min + 1)) 
	int fakeCoinIndex = 0 + (rand() % ((n-1) - 0 + 1)); //generate the random number 
	cout << "The fake coin index is... " << fakeCoinIndex << endl << endl;
	coinArr[fakeCoinIndex] = 0;
	coinArrCopy = coinArr;

	//PRINT VECTORS
	cout << "What coinArr looks like at the start..." << endl;
	print(coinArr);
	cout << endl;
	cout << "What coinArrCopy looks like at the start..." << endl;
	print(coinArrCopy);
	cout << endl;

	//GET SUMS
	getSums(coinArr, sums, n);
	cout << "What sums looks like after getSums..." << endl;
	print(sums);
	cout << endl;

	//ALG1 TEST
	fakeCoinIndex1 = ALG1(coinArr, n);
	cout << "The result of ALG1 is... " << fakeCoinIndex1 << endl;

	//ALG2 TEST
	fakeCoinIndex2 = ALG2(coinArr, sums, n, 0, (n-1));
	cout << "The result of ALG2 is... " << fakeCoinIndex2 << endl;
	*/



	
	
	cout << "************************************************FINDING THE FAKE COIN PROGRAM************************************************\n\n\n";

	//SEED
	srand((unsigned)time(NULL));

	//VARIABLES
	int max = 10000000;
	int m = 5;
	int fakeCoinIndex1;
	int fakeCoinIndex2;

	//VECTORS
	vector<int> coinArr(max, 1);
	vector<int> coinArrCopy(max, 1);
	vector<int> sums(max, 0);
	vector<double> ALG1Times(10, 0);
	vector<double> ALG2Times(10, 0);

	
	//PROCESSING
	for (int y = 1; y <= m; y++)
	{
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		//cout << "---------------------------------" << "ITERATION #" << y << ", SIZE " << n << " :: ARRAY" << "---------------------------------" << endl;
		//print(A);
		//cout << endl;
		//cout << "---------------------------------------------------------------------------------------------------------------------" << endl << endl << endl << endl;

		for (int n = 1000000; n <= 10000000; n = n + 1000000) {

			cout << "---------------------------------" << "ITERATION #" << y << ", SIZE " << n << "---------------------------------" << endl;

			//RANDOMLY GENERATE THE INDEX WHERE THE FAKE COIN WILL BE 
			//output = min + (rand() % (int)(max - min + 1))
			int fakeCoinIndex = 0 + (rand() % ((n - 1) - 0 + 1)); //generate the random number
			cout << "The fake coin index is... " << fakeCoinIndex << endl << endl;
			coinArr[fakeCoinIndex] = 0;

			//CALL GET SUMS
			getSums(coinArr, sums, n);

			//MEASUREMENTS FOR ALG1
			coinArrCopy = coinArr;
			auto t1ALG1 = chrono::steady_clock::now();
			fakeCoinIndex1 = ALG1(coinArrCopy, n);
			auto t2ALG1 = chrono::steady_clock::now();
			ALG1Times[(n / 1000000) - 1] += (double(chrono::duration_cast<chrono::microseconds>(t2ALG1 - t1ALG1).count()));
			cout << "ALG1" << endl;
			cout << "RT (in ms): " << double(chrono::duration_cast<chrono::microseconds>(t2ALG1 - t1ALG1).count()) << endl; 
			cout << "Fake Coin Index: " << fakeCoinIndex1 << endl;
			cout << endl << endl;

			//MEASUREMENTS FOR ALG2
			coinArrCopy = coinArr; 
			auto t1ALG2 = chrono::steady_clock::now();
			fakeCoinIndex2 = ALG2(coinArrCopy, sums, n, 0, (n-1));
			auto t2ALG2 = chrono::steady_clock::now();
			ALG2Times[(n / 1000000) - 1] += (double(chrono::duration_cast<chrono::microseconds>(t2ALG2 - t1ALG2).count())); 
			cout << "ALG2" << endl;
			cout << "RT (in ms): " << double(chrono::duration_cast<chrono::microseconds>(t2ALG2 - t1ALG2).count()) << endl; 
			cout << "Fake Coin Index: " << fakeCoinIndex2 << endl;
			cout << endl << endl;

			//RESET
			//reset the fakeCoinIndex back to 1 so that we don't have multiple fake coins on the next iteration
			coinArr[fakeCoinIndex] = 1;
		}
	}

	//COMPUTE AVERAGE VALUES
	cout << "************************************************COMPUTATION OF AVERAGE VALUES************************************************\n\n\n";
	cout << "Average RT for ALG1: " << endl;
	computeAvg(ALG1Times);
	printAvg(ALG1Times);
	cout << "Average RT for ALG2: " << endl;
	computeAvg(ALG2Times);
	printAvg(ALG2Times);

	

	//clear up memory
	coinArr.clear();
	coinArr.shrink_to_fit();
	coinArrCopy.clear();
	coinArrCopy.shrink_to_fit(); 

	//end main function
	return 0;
}





//*************************************************************************************
//NAME:	Brute Force (ALG1)
//PARAMETERS: vector, vector size
//OUTPUT: the index of the fake coin
//RUNTIME: O(n)
//*************************************************************************************
int ALG1(vector<int>& coinArr, int n) 
{
	//we compare the weights of the coins, iterating through the whole vector until we get the answer
	for (int i = 1; i < n; i++) {
		//this is the case when the fake coin is the first coin
		if (coinArr[0] < coinArr[i]) {
			return 0;
		}
		//this is the case when the fake coin is at some index i
		else if (coinArr[0] > coinArr[i]) {
			return i;
		}
		//we don't need to check when coinArr[0] == coinArr[i] because that means both are real coins
	}
	return -1; //-1 is returned in case there is no fake coin
}



//*************************************************************************************
//NAME:	Divide & Conquer (ALG2)
//PARAMETERS: vector, vector, vector size, start, end
//OUTPUT: the index of the fake coin
//RUNTIME: O(log(n))
//*************************************************************************************
int ALG2(vector<int>& coinArr, vector<int>& sums, int n, int start, int end)
{
	//INITIALIZE VARIABLES
	int mid; 
	int weightOfLeftSide;
	int weightOfRightSide; 
	int length = start + end + 1;
	int tempIndex = 0;  //this 0 is just a default value

	//TAKE OUT LEFTOVER COIN (IF NECESSARY)
	if ((length % 2)==1) {  
		//if there is an odd num of coins in the range, we have to take the first out to balance the scale
		tempIndex = start;
		start = start + 1;
	}
	if (start != end) {

		//DIVIDE
		mid = floor((start + end) / 2);

		//GET WEIGHTS (IN CONSTANT TIME)
		if (start == 0) {
			weightOfLeftSide = sums[mid] - 0;
			weightOfRightSide = sums[end] - sums[mid];
		}
		else {
			weightOfLeftSide = sums[mid] - sums[start - 1];
			weightOfRightSide = sums[end] - sums[mid];
		}

		//CONQUER
		if (weightOfLeftSide < weightOfRightSide) {
			return ALG2(coinArr, sums, n, start, mid);
		}
		else if (weightOfLeftSide > weightOfRightSide) {
			return ALG2(coinArr, sums, n, (mid + 1), end);
		}
		else if (weightOfLeftSide == weightOfRightSide) {
			return tempIndex;  //this means the leftover coin is the fake coin
		}
	}
	return start;
}



//*************************************************************************************
//NAME:	Get Sums (Auxiliary Function)
//PARAMETERS: vector, vector
//OUTPUT: there is no return statement this function will update a global vector data 
// structure named "sums"
//RUNTIME: O(n)
//*************************************************************************************
void getSums(vector<int>& coinArr, vector<int>& sums, int n)
{
	sums[0] = coinArr[0];
	for (int i = 1; i < n; i++) {
		sums[i] = sums[i-1] + coinArr[i];
	}
}



//*************************************************************************************
//NAME:	Print (Auxiliary Function)
//PARAMETERS: vector
//OUTPUT: N/A
//RUNTIME: O(n)
//*************************************************************************************
void print(vector<int>& A)
{
	if (A.empty()) {
		cout << "The vector is empty." << endl;
	}
	else {
		for (int i = 0; i < A.size(); i++) {
			cout << A[i] << " ";
		}
		cout << "\n";
	}
}



//*************************************************************************************
//NAME:	Print Average (Auxiliary Function)
//PARAMETERS: vector
//OUTPUT: N/A
//RUNTIME: O(n)
//*************************************************************************************
void printAvg(vector<double>& A)
{
	if (A.empty()) {
		cout << "The vector is empty." << endl;
	}
	else {
		for (int i = 0; i < A.size(); i++) {
			cout << setprecision(4) << A[i] << " ";
		}
		cout << "\n";
	}
}



//*************************************************************************************
//NAME:	Compute Average (Auxiliary Function)
//PARAMETERS: vector
//OUTPUT: N/A
//RUNTIME: O(n)
//*************************************************************************************
void computeAvg(vector<double>& A)
{
	if (A.empty()) {
		cout << "The vector is empty." << endl;
	}
	else {
		for (int i = 0; i < A.size(); i++) {
			A[i] = A[i] / 5.0; //in this program, recall that we set m = 5
		}
	}
}

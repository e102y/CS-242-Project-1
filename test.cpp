#include <iostream>
#include <string>
#include <fstream>
#include <random>

//#include <clib>
//#include "OrderedSet.hpp"
using namespace std;
unsigned int Generate (int N, int T, float P, int G, ofstream output);
void Statistics (int T, float P, int G);
void FileOutput(unsigned int O);

int main (int argc, char * argv [])
{
//	convert character array to multiple strings using ' ' as a seperator
//	stoi converts string to int
//	stof converts string to float
//	::_device rd;
	if(argc < 2)
	{
	exit(2);
	}
	int N = stoi(argv[1]);
	int T = stoi(argv[2]);
	float P = stof(argv[3]);
	int G = stoi(argv[4]);

	if(P>1  || G>2 || G<0){

	cout << "one of the inputs was wrong, please try again.";
	exit(0);
	}	
	ofstream output (argv[5]);
	if(output.fail())
	{
	cout << "File: " << argv[5] << " not found\n";
	exit(1);
	}
	if(argv[0] == "gen")
	{
	output = Generate(N,T,P,G);
	}
	output.close();
	return 0;
}
unsigned int  Generate (int N, int T, float P, int G)
{
//output header to output there
//the rest of this |SHOULD| work

	random_device rd;
	unsigned int TBit [T];
	if(G == 0){
		cout << "Linear Congruential Engine";
		minstd_rand gen(rd());
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
			for(int n = 0; n < T; n++){
				TBit[i] =  d(gen); 
			}
		}
	}
	else if(G == 1){
		cout << "Shuffle Order Engine";
		knuth_b gen(rd());
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
			for(int n = 0; n < T; n++){
				TBit[i] =  d(gen); 
			}
		}
	}
	else if(G == 2){
		cout << "Subtract With Carry Engine";
		ranlux24_base gen(rd());
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
			for(int n = 0; n < T; n++){
				TBit[i] =  d(gen); 
			}
	
		output << '\n';
		}
	}
	return TBit;
}
void Statistics (int T, float P, int G)
{
}
void FileOutput(cstring

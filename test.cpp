#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cstring>
//#include <clib>
//#include "OrderedSet.hpp"
using namespace std;
void Generate (int N, int T, float P, int G, char * O);
void Statistics (int T, float P, int G);

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
	int N = stoi(argv[2]);
	int T = stoi(argv[3]);
	float P = stof(argv[4]);
	int G = stoi(argv[5]);
	
	if(P>1  || G>2 || G<0){
	cout << "one of the inputs was wrong, please try again.";
	exit(0);
	}
	string generationType = argv[1];
	if(generationType.compare("gen") == 0)
	{
	Generate(N,T,P,G,argv[6]);
	}
	return 0;
}
void  Generate (int N, int T, float P, int G, char * O)
{
	ofstream output (O);
	if(output.fail()){
	cout << "File: " << O << " not found\n";
	exit(1);
	}
	random_device rd;
	unsigned int TBit;
	unsigned int RSeed = rd();
	output << "#==================================================================\n";
	output << "# generator "; 
	switch (G){
	case 0:
	output << "min_rand";
	break;
	case 1:
	output << "knuth_b";
	break;
	case 2:
	output << "ranlux24";
	break;
	default:
	break;
	}
	output << " seed = " << RSeed << '\n';
	output << "#==================================================================\n";
	output << "type: " << 'd' << '\n';
	output << "count: " << N << '\n';
	output << "numbit: " << 32 << '\n';
	if(G == 0){
		cout << "Linear Congruential Engine\n";
		minstd_rand gen(RSeed);
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
				TBit =  d(gen); 
			for(int n = 1; n < T; n++){
				TBit =  (TBit << 1) | d(gen); 
			}
		output << TBit << '\n';
		}
	}
	else if(G == 1){
		cout << "Shuffle Order Engine\n";
		knuth_b gen(RSeed);
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
				TBit =  d(gen); 
			for(int n = 1; n < T; n++){
				TBit =  (TBit << 1) | d(gen); 
			}
		output << TBit << '\n';
		}
	}
	else if(G == 2){
		cout << "Subtract With Carry Engine\n";
		ranlux24_base gen(RSeed);
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
				TBit =  d(gen); 
			for(int n = 1; n < T; n++){
				TBit =  (TBit << 1) | d(gen); 
			}
		output << TBit << '\n';
		}
	}
	output.close();
}
void Statistics (int T, float P, int G)
{
}

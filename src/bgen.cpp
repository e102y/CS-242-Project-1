#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cstring>
using namespace std;
void Generate (int N, int T, float P, int G, char * O);
void Statistics (int N, int T, float P, int G, char * O);

int main (int argc, char * argv [])
{
//	convert character array to multiple strings using ' ' as a seperator
//	stoi converts string to int
//	stof converts string to float
//	::_device rd;
	if(argc < 7)
	{
	cout << "Usage: <function mode> <number of iterations> <number of trials> <proboability x is true> <random number generator type> <file name>\n";
	exit(2);
	}
	int N = stoi(argv[2]);
	int T = stoi(argv[3]);
	float P = stof(argv[4]);
	int G = stoi(argv[5]);
	
	if(P>1  || G>2 || G<0 || P < 0 || N < 0){
	cout << "one of the inputs was wrong, please try again.";
	exit(0);
	}
	string generationType = argv[1];
	if(generationType.compare("gen") == 0)
	{
	Generate(N,T,P,G,argv[6]);
	}
	if(generationType.compare("stat") == 0)
	{
	Statistics(N,T,P,G,argv[6]);
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
void Statistics (int N, int T, float P, int G, char * O)
{
	ofstream output (O);
	if(output.fail()){
	cout << "File: " << O << " not found\n";
	exit(1);
	}
	float VA[N];
	unsigned int myHead = 0;
	random_device rd;
	unsigned int TBit;
	unsigned int RSeed = rd();
//	output << "Genny: "; 
/*	switch (G){
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
	}		*/
//	output << "\nP: " << P << '\n';
//	output << "count: " << N << '\n';
	if(G == 0){
		cout << "Linear Congruential Engine\n";
		minstd_rand gen(RSeed);
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
				TBit =  d(gen); 
			for(int n = 1; n < T; n++){
				TBit += d(gen); 
			}
		float temp = float(TBit)/float(T);
		output << temp  << '\n';
//		output <<  float(TBit)/float(N)  << '\n';
		myHead += TBit;
		VA[i] = TBit;
		}
	}
	else if(G == 1){
		cout << "Shuffle Order Engine\n";
		knuth_b gen(RSeed);
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
				TBit =  d(gen); 
			for(int n = 1; n < T; n++){
				TBit += d(gen); 
			}
		float temp = float(TBit)/float(T);
		output << temp  << '\n';
		myHead += TBit;
		VA[i] = TBit;
		}
	}
	else if(G == 2){
		cout << "Subtract With Carry Engine\n";
		ranlux24_base gen(RSeed);
		bernoulli_distribution d(P);
		for(int i = 0; i < N; i++){
				TBit =  d(gen); 
			for(int n = 1; n < T; n++){
				TBit += d(gen); 
			}
		float temp = float(TBit)/float(T);
		output << temp  << '\n';
		myHead += TBit;
		VA[i] = TBit;
		}
	}
	float myMean = float(myHead)/float(N);
	float Var =0;
	for(int i = 0; i < N; i++)
	{
		Var += (VA[i]-myMean)*(VA[i]-myMean);
	}
	Var = Var/(N*T);
	output << 42 << '\n';	
	output << "Expected Value: " << N*P*T << '\n';
	output << "Sample Mean: " <<  myMean << '\n';
	output << "Expected Variance: " << P*(1-P) << '\n';
	output << "Sample Variance: " << Var << '\n';
	output.close();
}

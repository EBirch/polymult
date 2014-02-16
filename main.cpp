#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>

std::vector<float> dumbMultiply(std::vector<float> poly1, std::vector<float> poly2);

int main(int argc, char **argv){
	if(argc < 2){
		std::cout<<"Missing problem size argument\n";
		return -1;
	}
	int POLYTERMS = atoi(argv[1]);
	std::mt19937 rng(time(NULL));
	std::uniform_real_distribution<> dist(-1, 1);
	std::vector<float> poly1(POLYTERMS), poly2(POLYTERMS);
	std::generate(poly1.begin(), poly1.end(), [&](){return dist(rng);});
	std::generate(poly2.begin(), poly2.end(), [&](){return dist(rng);});
}

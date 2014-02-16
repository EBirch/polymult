#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>

std::vector<float> dumbMultiply(std::vector<float> poly1, std::vector<float> poly2);
std::vector<float> fourMult(std::vector<float> poly1, std::vector<float> poly2);

int main(int argc, char **argv){
	// if(argc < 2){
	// 	std::cout<<"Missing problem size argument\n";
	// 	return -1;
	// }
	// int POLYTERMS = atoi(argv[1]);
	// std::mt19937 rng(time(NULL));
	// std::uniform_real_distribution<> dist(-1, 1);
	// std::vector<float> poly1(POLYTERMS), poly2(POLYTERMS);
	// std::generate(poly1.begin(), poly1.end(), [&](){return dist(rng);});
	// std::generate(poly2.begin(), poly2.end(), [&](){return dist(rng);});
	std::vector<float> poly1 {1, -2, 3, 8};
	std::vector<float> poly2 {1, 2, 2, 1};
	auto temp = dumbMultiply(poly1, poly2);
	for(auto &term : temp){
		std::cout<<term<<" ";
	}
	std::cout<<std::endl;
	temp = fourMult(poly1, poly2);
	for(auto &term : temp){
		std::cout<<term<<" ";
	}
	std::cout<<std::endl;
}

std::vector<float> dumbMultiply(std::vector<float> poly1, std::vector<float> poly2){
	std::vector<float> result(2 * poly1.size() - 1, 0);
	for(int i = 0; i < poly1.size(); ++i){
		for(int j = 0; j < poly2.size(); ++j){
			result[i + j] += poly1[i] * poly2[j];
		}	
	}
	return result;
}

std::vector<float> fourMult(std::vector<float> poly1, std::vector<float> poly2){
	if(poly1.size() == 1){
		return std::vector<float> {poly1[0] * poly2[0]};
	}
	std::vector<float> p1Low(&poly1[0], &poly1[poly1.size() / 2]);
	std::vector<float> p1High(&poly1[poly1.size() / 2], &poly1[poly1.size()]);
	std::vector<float> p2Low(&poly2[0], &poly2[poly2.size() / 2]);
	std::vector<float> p2High(&poly2[poly2.size() / 2], &poly2[poly2.size()]);
	std::vector<float> result(2 * poly1.size() - 1, 0);
	auto temp = fourMult(p1Low, p2Low);
	for(int i = 0; i < temp.size(); ++i){
		result[i] += temp[i];
	}
	temp = fourMult(p1High, p2High);
	for(int i = 0; i < temp.size(); ++i){
		result[poly1.size() + i] += temp[i];
	}
	temp = fourMult(p1Low, p2High);
	for(int i = 0; i < temp.size(); ++i){
		result[poly1.size() / 2 + i] += temp[i];
	}
	temp = fourMult(p1High, p2Low);
	for(int i = 0; i < temp.size(); ++i){
		result[poly1.size() / 2 + i] += temp[i];
	}
	return result;
}

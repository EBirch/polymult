#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>

std::vector<float> dumbMult(std::vector<float> poly1, std::vector<float> poly2);
std::vector<float> fourMult(std::vector<float> poly1, std::vector<float> poly2);
std::vector<float> threeMult(std::vector<float> poly1, std::vector<float> poly2);

int main(int argc, char **argv){
	if(argc < 3){
		std::cout<<"Not enough arguments"<<std::endl;
		return -1;
	}
	int POLYTERMS = atoi(argv[2]);
	std::mt19937 rng(time(NULL));
	std::uniform_real_distribution<> dist(-1, 1);
	std::vector<float> poly1(POLYTERMS), poly2(POLYTERMS);
	std::generate(poly1.begin(), poly1.end(), [&](){return dist(rng);});
	std::generate(poly2.begin(), poly2.end(), [&](){return dist(rng);});
	std::vector<float> temp;
	auto start = std::chrono::steady_clock::now();
	switch(argv[1][1]){
		case 'd': temp = dumbMult(poly1, poly2); break;
		case '4': temp = fourMult(poly1, poly2); break;
		case '3': temp = threeMult(poly1, poly2); break;
	}
	std::cout<<"Ran in "<<(std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now() - start).count())<<" seconds"<<std::endl;
	std::cout<<"Resulting coefficients: ";
	for(auto &term : temp){
		std::cout<<term<<" ";
	}
	std::cout<<std::endl;
}

std::vector<float> dumbMult(std::vector<float> poly1, std::vector<float> poly2){
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

std::vector<float> threeMult(std::vector<float> poly1, std::vector<float> poly2){
		if(poly1.size() == 1){
		return std::vector<float> {poly1[0] * poly2[0]};
	}
	std::vector<float> p1Low(&poly1[0], &poly1[poly1.size() / 2]);
	std::vector<float> p1High(&poly1[poly1.size() / 2], &poly1[poly1.size()]);
	std::vector<float> p2Low(&poly2[0], &poly2[poly2.size() / 2]);
	std::vector<float> p2High(&poly2[poly2.size() / 2], &poly2[poly2.size()]);
	std::vector<float> result(2 * poly1.size() - 1, 0);
	auto lowLow = fourMult(p1Low, p2Low);
	for(int i = 0; i < lowLow.size(); ++i){
		result[i] += lowLow[i];
	}
	auto highHigh = fourMult(p1High, p2High);
	for(int i = 0; i < highHigh.size(); ++i){
		result[poly1.size() + i] += highHigh[i];
	}
	for(int i = 0; i < p1Low.size(); ++i){
		p1Low[i] += p1High[i];
		p2Low[i] += p2High[i];
	}
	auto temp = fourMult(p1Low, p2Low);
	for(int i = 0; i < temp.size(); ++i){
		temp[i] -= (lowLow[i] + highHigh[i]);
	}
	for(int i = 0; i < temp.size(); ++i){
		result[poly1.size() / 2 + i] += temp[i];
	}
	return result;
}

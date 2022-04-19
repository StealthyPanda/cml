#include <iostream>
#include "ml.h"
#include <thread>
#include <quadmath.h>
#include <chrono>

using namespace std::chrono;

long long int bytestaken = 0, bytesreleased = 0;

void* operator new (size_t size)
{
	bytestaken += size;
	return malloc(size);
}

void operator delete (void* memory, size_t size)
{
	bytesreleased += size;
	free(memory);
}


int main()
{
	auto start = high_resolution_clock::now();

	
	NeuralNetwork nn = NeuralNetwork(4);

	InputLayer il(2);
	DenseLayer dl1(7, 2);
	DenseLayer dl2(7, 7);
	DenseLayer ol(2, 7);

	nn << il << dl1 << dl2 << ol;

	//NeuralNetwork nn = NeuralNetwork::extract("threeone.nn");

	Trainer atrainer(nn, "test3.td", 9000);
	atrainer.partition();

	char bruh;

	std::cout << nncount << std::endl;

	std::cin>>bruh;

	atrainer.lineartrain(5, 100);

	atrainer.nn.save("threeone.nn");

	std::cout << "NeuralNetwork count: " << nncount << std::endl;
	std::cout << "OutputCache count: " << occount << std::endl;

	std::cout << "Bytes taken: " << bytestaken << " Bytes released: " << bytesreleased <<std::endl;


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;
}
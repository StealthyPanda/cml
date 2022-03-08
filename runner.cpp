#include <iostream>
#include "ml.h"
#include <thread>
#include <quadmath.h>
#include <chrono>

using namespace std::chrono;

int main()
{
	auto start = high_resolution_clock::now();



	NeuralNetwork nn = NeuralNetwork(3);

	InputLayer il(2);
	DenseLayer dl1(3, 2);
	DenseLayer dl2(6, 6);
	DenseLayer ol(2, 3);

	nn << il << dl1 << ol;

	//NeuralNetwork nn = NeuralNetwork::extract("threeone.nn");

	Trainer atrainer(nn, "test3.td", 9000);
	atrainer.partition();

	atrainer.lineartrain(25, 100);

	atrainer.nn.save("threeone.nn");




	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;
}
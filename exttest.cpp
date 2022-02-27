#include <iostream>
#include <chrono>
#include <quadmath.h>
#include "ml.h"

int main()
{

	NeuralNetwork bruh = NeuralNetwork::extract("bruh15.nn");

	bruh.print();

	Trainer tr(bruh, "test2.td", 1000);
	tr.partition();

	std::cout << tr.calculatecost(tr.trainingdatasets, tr.ntraining) << std::endl;
	std::cout << tr.calculatecost(tr.testingdatasets, tr.ntesting) << std::endl;

	return 0;
}
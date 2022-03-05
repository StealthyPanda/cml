#include <iostream>
#include <chrono>
#include <quadmath.h>
#include "ml.h"


int main()
{
	NeuralNetwork ellipseboi = NeuralNetwork::extract("ellipseboi18.nn");

	Trainer somethingelse(ellipseboi, "test2.td", 1000);
	somethingelse.partition();

	NeuralNetwork gradient = somethingelse.getgradient();
	gradient.print();
	gradient.save("gradient.nn");

	return 0;
}
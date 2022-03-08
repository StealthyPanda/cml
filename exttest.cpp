#include <iostream>
#include <chrono>
#include <quadmath.h>
#include "ml.h"

/*int main()
{

	NeuralNetwork bruh = NeuralNetwork::extract("bruh16.nn");

	bruh.print();

	Trainer tr(bruh, "test2.td", 1000);
	tr.partition();

	std::cout << tr.calculatecost(tr.trainingdatasets, tr.ntraining) << std::endl;
	std::cout << tr.calculatecost(tr.testingdatasets, tr.ntesting) << std::endl;

	return 0;
}*/

int main(int argc, char const *argv[])
{
	//std::string name = "networks/ellipseboi" + std::to_string(argv[0]) + ".nn";

	//std::cout << argv[1] << std::endl;

	/*NeuralNetwork ellipseboi = NeuralNetwork(4);

	InputLayer il = InputLayer(2);
	DenseLayer dl1 = DenseLayer(4, 2);
	DenseLayer dl2 = DenseLayer(4, 4);
	DenseLayer ol = DenseLayer(2, 4);

	ellipseboi << il << dl1 << dl2 << ol;

	ellipseboi.print();

	ellipseboi.save("newboi.nn");*/

	NeuralNetwork bruh = NeuralNetwork::extract("newboi.nn");

	bruh.print();

	Trainer tr(bruh, "test2.td", 1000);
	tr.partition();

	std::cout << tr.calculatecost(tr.trainingdatasets, tr.ntraining) << std::endl;
	std::cout << tr.calculatecost(tr.testingdatasets, tr.ntesting) << std::endl;

	return 0;
}

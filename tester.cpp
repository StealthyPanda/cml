#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif
#include "ml.h"
//#include <fstream>
//#include <sstream>

/*int main()
{
	std::cout << "LETS SEE" << std::endl;
	int alist[10][10];
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			alist[i][j] = (i+j);
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			std::cout << alist[i][j] << " ";
		}
		std::cout << std::endl;
	}

	long double pi = -1*(22.0/7.0);
	std::cout << pi << std::endl;
	std::cout << sizeof(pi) << std::endl;
	

	return 0;
}*/


/*
int main()
{

	Layer al = Layer(5);

	for (int i = 0; i < 5; ++i)
	{
		std::cout << *(al.layer + i) << std::endl;
	}

	std::cout << std::endl;

	NeuralNetwork nn = NeuralNetwork(5);

	for (int i = 0; i < 5; i++)
	{
		/*for (int j = 0; j < 5; ++j)
		{
			std::cout << "(" << i << ", " << j << "): " << *(*(nn.matrix + i) + j) << std::endl;
		}
		std::cout << i << " ";
		std::cout << *(*(nn.matrix + 1) + i) << std::endl;
		//std::cout << *(*(nn.matrix + i)) << std::endl;
	}

	return 0;
}
*/

/*int main()
{
	Cell* cells = new Cell[8];
	for (int i = 0; i < 8; ++i)
	{
		long double* cellwbuff = new long double[(3+(i%2))];
		for (int j = 0; j < (3+(i%2)); ++j)
		{
			cellwbuff[j] = i*(j+1);
		}
		Cell buffcell = *(new Cell(cellwbuff, (3+(i%2)), 0));
		cells[i] = buffcell;
	}
	Layer l = Layer(cells, 8);
	l.print();
	std::cout << std::endl;
	l.append(*(new Cell(7)));
	l.print();

	return 0;
}
*/
class foo
{
public:
	int *arr;
	int index = 0;
	int startvar = 0;

	foo()
	{
		//arr = new int[5];
		arr = &startvar;
	}

	foo(int numsize)
	{
		arr = new int[numsize];
	}
	foo(int numsize, int initval)
	{

		arr = new int[numsize];
		for (int i = 0; i < numsize; ++i)
		{
			arr[i] = initval;
		}

	}

	void append(int someval)
	{
		arr[index++] = someval;
	}

};



/*int main()
{
	NeuralNetwork nn = *( new NeuralNetwork(4, *(new InputLayer(3))));
	
	nn << *(new DenseLayer(5, 3)) << *(new DenseLayer(5, 5)) << *(new DenseLayer(3, 5)) ;

	nn.print();

	nn.save("Saturday.nn");

	ml::Vector v = ml::Vector(3, 1);
	v.print();

	return 0;
}*/

/*int main()
{
	long double input[] = {2, 2, 3};
	int length = sizeof(input)/sizeof(long double);
	ml::Vector v = ml::Vector(length, input);


	InputLayer il = InputLayer(length);
	DenseLayer dl1 = DenseLayer(5, length);
	DenseLayer dl2 = DenseLayer(3, 5);
	DenseLayer dl3 = DenseLayer(1, 3);

	dl1.layer[1].weights[0] = -2;
	dl1.layer[1].weights[1] = -1;
	dl1.layer[1].weights[2] = 0;

	dl2.layer[0].weights[4] = 0;
	dl2.layer[0].weights[3] = 0;
	dl2.layer[0].weights[2] = 0;

	dl3.layer[0].weights[0] = -1;
	dl3.layer[0].weights[1] = 0;
	dl3.layer[0].weights[2] = 1;

	NeuralNetwork nn = NeuralNetwork(4, il);
	std::cout << nn.index << std::endl;
	nn << dl1;
	nn << dl2;
	nn << dl3;

	for (int i = 0; i < nn.nlayers; ++i)
	{
		nn.layers[i].print();
		std::cout << std::endl;
	}

	std::cout << nn.index << std::endl;

	ml::Vector output = (nn*v);
	output.print();

	ml::Vector output2 = (v * dl1);
	output2.print();

	ml::Vector output3 = ((v * dl1) * dl2);
	output3.print();

	nn.save("Sunday.nn");


	return 0;
}*/


/*int main()
{

	//Trainer t = Trainer("test.td");

	//std::string bruh = "-3.14159";

	/*std::stringstream bruhs(bruh);
	//long double printer = (long double) bruh;

	int buffi;
	for(int i = 0; i < 6; i++)
	{
		//bruhs >> buffi;
		std::cout << bruh[i] << std::endl;
	}

	return 0;
}*/

using namespace ml;

int main()
{
	NeuralNetwork nn = NeuralNetwork(3);
	nn << *(new InputLayer(2));
	nn << *(new DenseLayer(4, 2));
	nn << *(new DenseLayer(2, 4));

	nn.print();

	__float128 input[2] = {(22.0q/7.0q), 1.0q};

	Vector output = (nn * Vector(2, input));

	output.print();

}
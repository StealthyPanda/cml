#include <iostream>
#include "ml.h"

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


int main()
{
	NeuralNetwork nn = *( new NeuralNetwork(4, *(new InputLayer(3))));
	
	nn << *(new DenseLayer(5, 3)) << *(new DenseLayer(5, 5)) << *(new DenseLayer(3, 5)) ;

	nn.print();

	return 0;
}
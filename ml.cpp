#include "ml.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(int nlayers)
{
	this->layers = new Layer[nlayers];
	this->nlayers = nlayers;
	this->index = 0;
}

NeuralNetwork::NeuralNetwork(int nlayers, InputLayer il)
{
	this->layers = new Layer[nlayers];
	this->nlayers = nlayers;
	this->index = 1;
	this->layers[0] =  il;
}

void NeuralNetwork::print()
{
	for (int i = 0; i < this->nlayers; ++i)
	{
		std::cout << i << "th layer" << std::endl;
		this->layers[i].print();
	}
}

NeuralNetwork operator << (NeuralNetwork nn, Layer &layer)
{
	nn.layers[nn.index] = layer;
	nn.index++;
	return (nn);
}

Layer::Layer()
{
	this->ncells = 0;
	this->layer = new Cell[0];
}

Layer::Layer(int size)
{
	this->ncells = size;
	this->layer = new Cell[size];
}

Layer::Layer(Cell cells[], int ncells)
{
	this->ncells = ncells;
	this->layer = cells;
}

Layer Layer::append(Cell &cell)
{
	this->layer[this->ncells] = cell;
	this->ncells++;
}

void Layer::print()
{
	for (int i = 0; i < ncells; ++i)
	{
		Cell bc = *(this->layer + i);
		for (int j = 0; j < bc.nweights; ++j)
		{

			std::cout << bc.weights[j] << " ";

		}
		std::cout << bc.bias << std::endl;
	}
}




Cell::Cell(int size)
{
	long double *buffer = new long double[size];
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = 0;
	}
	this->weights = buffer;
	this->bias = 0;
	this->nweights = size;
}

Cell::Cell()
{
	long double buffer[1] = {0};
	this->weights = buffer;
	this->bias = 0;
	this->nweights = 1;
}


//todo: somehow figure out length of array from its pointer
Cell::Cell(const long double weights[], const int nweights, const long double bias)
{
	long double *buffer = new long double[nweights];
	for (int i = 0; i < nweights; ++i)
	{
		buffer[i] = weights[i];
	}
	this->weights = buffer;
	this->bias = bias;
	this->nweights = nweights;
}


InputLayer::InputLayer()
{
}

void InputLayer::print()
{
	Layer::print();
}

InputLayer::InputLayer(int size)
{
	this->ncells = size;
	Cell *buffer = new Cell[size];
	for (int i = 0; i < size; ++i)
	{
		Cell buffcell = *(new Cell(size));
		buffcell.weights[i] = 1;
		buffer[i] = buffcell;
	}
	this->layer = buffer;

}

DenseLayer::DenseLayer()
{

}

DenseLayer::DenseLayer(int numberofcells, int prevsize)
{
	Cell *buff = new Cell[numberofcells];
	for (int i = 0; i < numberofcells; ++i)
	{
		buff[i] = *(new Cell(prevsize));
	}
	this->layer = buff;
	this->ncells = numberofcells;
}
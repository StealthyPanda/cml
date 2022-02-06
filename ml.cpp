#include "ml.h"
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif
#include <fstream>
#include <quadmath.h>

#define FPREC 35
#define FWIDTH 25

void print(const __float128& afloat)
{
	char buffer[35];
	//"%+-#*.20Qe"
	//%+-#46.*Qe
	quadmath_snprintf(buffer, sizeof buffer, "%+-#46.*Qe", 20, afloat);
	std::cout << buffer;
}

std::ostream& operator<< (std::ostream& stream, __float128 afloat)
{
	char buffer[FPREC];

	quadmath_snprintf(buffer, sizeof buffer, "%+-#46.*Qe", FWIDTH, afloat);

	stream << buffer;

	return stream;

}

char* strepr(__float128 afloat)
{
	static char buffer[FPREC];

	quadmath_snprintf(buffer, sizeof buffer, "%+-#46.*Qe", FWIDTH, afloat);

	return buffer;
}

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

NeuralNetwork& operator << (NeuralNetwork &nn, Layer &layer)
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
	return *(this);
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
	__float128 *buffer = new __float128[size];
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = 0.0q;
	}
	this->weights = buffer;
	this->bias = 0.0q;
	this->nweights = size;
}

Cell::Cell()
{
	__float128 buffer[1] = {0.0q};
	this->weights = buffer;
	this->bias = 0.0q;
	this->nweights = 1;
}

Cell::Cell(int size, bool default1)
{
	__float128 *buffer = new __float128[size];
	for (int i = 0; i < size; ++i)
	{
		if(default1) 
			{buffer[i] = 1.0q;}
		else
			{buffer[i] = 0.0q;}
	}
	this->weights = buffer;
	this->bias = 0.0q;
	this->nweights = size;
}


//todo: somehow figure out length of array from its pointer
Cell::Cell(const __float128 weights[], const int nweights, const __float128 bias)
{
	__float128 *buffer = new __float128[nweights];
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
		buffcell.weights[i] = 1.0q;
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
		buff[i] = *(new Cell(prevsize, true));
	}
	this->layer = buff;
	this->ncells = numberofcells;
}

DenseLayer::DenseLayer(int numberofcells)
{
	Cell *buff = new Cell[numberofcells];
	for (int i = 0; i < numberofcells; ++i)
	{
		buff[i] = *(new Cell());
	}
	this->layer = buff;
	this->ncells = numberofcells;
}

void NeuralNetwork::save(const char* rawname)
{
	std::fstream savefile;

	//string filename = rawname + ".nn";

	savefile.open(rawname, std::ios::out);

	if (savefile)
	{
		for (int i = 0; i < this->nlayers; ++i)
		{
			Layer bufflayer = this->layers[i];
			for (int j = 0; j < bufflayer.ncells; ++j)
			{
				Cell buffcell = bufflayer.layer[j];
				for (int k = 0; k < buffcell.nweights; ++k)
				{
					savefile << strepr(buffcell.weights[k]) << ",";
				}
				savefile << strepr(buffcell.bias) << "|";
			}
			savefile << "\n";
		}
		savefile.close();
	}
	else
	{
		std::cout << "File saving failed" << std::endl;
	}

}

void NeuralNetwork::save()
{
	save("Jarvis");
}

ml::Vector::Vector(int size)
{
	this->list = new __float128[size];
	this->size = size;
	for (int i = 0; i < size; ++i)
	{
		this->list[i] = 0.0q;
	}
}

ml::Vector::Vector(int size, __float128 initval)
{
	this->list = new __float128[size];
	this->size = size;
	for (int i = 0; i < size; ++i)
	{
		this->list[i] = initval;
	}
}

ml::Vector::Vector(int size, __float128* initvals)
{
	this->list = new __float128[size];
	this->size = size;
	for (int i = 0; i < size; ++i)
	{
		this->list[i] = initvals[i];
	}
}


void ml::Vector::print()
{
	std::cout << "[";
	for (int i = 0; i < (this->size - 1); ++i)
	{
		std::cout << this->list[i] << ", ";
		//print(this->list[i]);
		//std::cout << ", ";
	}
	//print(this->list[this->size - 1]);
	std::cout << this->list[this->size - 1] << "]\n";
}

__float128 operator * (Cell cell, ml::Vector v)
{

	__float128 output = 0.0q;
	for (int i = 0; i < cell.nweights; ++i)
	{
		output += (v.list[i] * cell.weights[i]);
	}
	output += cell.bias;
	return output;
}

__float128 operator * (ml::Vector v, Cell cell)
{
	return (cell * v);
}






ml::Vector operator * (ml::Vector v, Layer layer)
{
	//checks if all cells have nweights the same as the number of values in the vector.
	for (int i = 0; i < layer.ncells; ++i)
	{
		if (layer.layer[i].nweights != v.size) return 0;
	}

	ml::Vector output = *(new ml::Vector(layer.ncells));
	for (int i = 0; i < output.size; ++i)
	{
		output.list[i] = (v * layer.layer[i]);
	}
	return output;
}

ml::Vector operator * (Layer layer, ml::Vector v)
{
	return (v * layer);
}


ml::Vector operator * (ml::Vector v, NeuralNetwork nn)
{
	ml::Vector output = v;
	//ml::Vector buffer = v;
	for (int i = 0; i < nn.index; ++i)
	{
		output = (nn.layers[i] * output);
	}
	return output;
}

ml::Vector operator * (NeuralNetwork nn, ml::Vector v)
{
	return (v * nn);
}


Trainer::Trainer()
{

}

/*Trainer::Trainer(const char* filename)
{
	std::fstream datafile;
	//datafile.open(filename, std::ios::in);
	std::string carr;

	
	__float128 buffld = 0.001234567891011121314151618q;
	//buffld = "0.1234567891011121314151617181920"_mpq;

	//int bruh = buffld.set_str(val, 10);
	__float128 bruh = (buffld * buffld);
	print(buffld);

	std::cout << (buffld < 0.1) << std::endl;
	//datafile.close();
}*/

NeuralNetwork::NeuralNetwork()
{
}

Trainer::Trainer(NeuralNetwork &nn, const char* filename, int ndatasets)
{
	this->nn = nn;
	this->ninps = this->nn.layers[0].ncells;
	this->nouts = this->nn.layers[this->nn.nlayers].ncells;

	std::fstream datafile;
	datafile.open(filename, std::ios::in);
	std::string buff;

	dataset *bdatasets = new dataset[ndatasets];

	std::cout << this->ninps << " " << this->nouts << std::endl;

	/*datafile >> buff;

	__float128 bfloat = strtoflt128 (buff.c_str(), NULL);

	std::cout << buff << std::endl;
	std::cout << bfloat << std::endl;*/

	//dataset ds ;
	//static __float128 bruh[20];

	/*for(int i = 0; i < ndatasets; i++)
	{
		datafile >> buff;
		bruh[i] = strtoflt128(buff.c_str(), NULL);
		//bruh[i] = bfloat;
		if (i == 0) std::cout << buff << std::endl;
	}
	ds.inputs = bruh;
	this->testd = ds;*/


	for (int i = 0; i < ndatasets; i++)
	{

		dataset ds;
		//static __float128 inputs[nn.layers[0].ncells], outputs[nn.layers[nn.nlayers].ncells];
		__float128* inputs = new __float128[nn.layers[0].ncells];
		__float128* outputs = new __float128[nn.layers[nn.nlayers].ncells];
		for (int j = 0; j < this->ninps; j++)
		{
			datafile >> buff;
			inputs[j] = strtoflt128(buff.c_str(), NULL);
		}
		for (int k = 0; k < this->nouts; k++)
		{
			datafile >>buff;
			outputs[k] = strtoflt128(buff.c_str(), NULL);
		}
		ds.inputs = inputs;
		ds.outputs = outputs;
		bdatasets[i] = ds;
	}

	this->datasets = bdatasets;


	datafile.close();
}

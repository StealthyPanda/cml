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

std::ostream& operator<< (std::ostream& stream, ml::Vector &v)
{
	stream << "[";
	for (int i = 0; i < (v.size - 1); ++i)
	{
		stream << v.list[i] << ", ";
	}
	stream << v.list[v.size - 1] << "]";
	return stream;
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

/*DenseLayer::DenseLayer(int numberofcells)
{
	Cell *buff = new Cell[numberofcells];
	for (int i = 0; i < numberofcells; ++i)
	{
		buff[i] = *(new Cell());
	}
	this->layer = buff;
	this->ncells = numberofcells;
}*/

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

ml::Vector::Vector()
{
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

__float128 ml::Vector::getMagnitude()
{
	static __float128 mag = 0.0q;

	for (int i = 0; i < this->size; ++i)
	{
		mag += powq(this->list[i], 2.0q);
	}

	mag = powq(mag, 0.5q);

	return mag;
}


__float128 operator * (Cell &cell, ml::Vector &v)
{

	__float128 output = 0.0q;
	for (int i = 0; i < cell.nweights; ++i)
	{
		output += (v.list[i] * cell.weights[i]);
	}
	output += cell.bias;
	output = (cell.actfuncsetted ? cell.actfunc(output) : DEFACTFUNC(output));
	return output;
}

__float128 operator * (ml::Vector &v, Cell &cell)
{
	return (cell * v);
}


ml::Vector operator + (ml::Vector &v1, ml::Vector &v2)
{
	static ml::Vector sum;
	if (v1.size != v2.size) return sum;

	sum = *(new ml::Vector(v1.size));
	for (int i = 0; i < v1.size; ++i)
	{
		sum.list[i] = v1.list[i] + v2.list[i];
	}

	return sum;
}
ml::Vector operator * (__float128 &fscalar, ml::Vector &v1)
{
	static ml::Vector prod;
	

	prod = *(new ml::Vector(v1.size));
	for (int i = 0; i < v1.size; ++i)
	{
		prod.list[i] = v1.list[i] * fscalar;
	}

	return prod;
}
ml::Vector operator * (ml::Vector &v2 ,__float128 &fscalar)
{
	return (fscalar * v2);
}
ml::Vector operator - (ml::Vector &v1, ml::Vector &v2)
{
	__float128 minusone = -1.0q;
	ml::Vector negv2 = v2 * minusone;
	return (v1 + negv2);
}

__float128& ml::Vector::operator [] (int n)
{
	return this->list[n];
}

__float128& Cell::operator [] (int n)
{
	return this->weights[n];
}

Cell& Layer::operator [] (int n)
{
	return this->layer[n];
}

Layer& NeuralNetwork::operator [] (int n)
{
	return this->layers[n];
}




ml::Vector operator * (ml::Vector &v, Layer &layer)
{
	//checks if all cells have nweights the same as the number of values in the vector.
	for (int i = 0; i < layer.ncells; ++i)
	{
		if (layer.layer[i].nweights != v.size) { std::cout << i << " Why tf am i being called" << std::endl << "layer.layer[i].nweights: " << layer.layer[i].nweights << " vsize: " << v.size; return 0; }
	}

	ml::Vector output = *(new ml::Vector(layer.ncells));
	for (int i = 0; i < output.size; ++i)
	{
		output.list[i] = (v * layer.layer[i]);
	}
	return output;
}

ml::Vector operator * (Layer &layer, ml::Vector &v)
{
	return (v * layer);
}


ml::Vector operator * (const ml::Vector &v, const NeuralNetwork &nn)
{
	ml::Vector output = v;
	//ml::Vector buffer = v;
	for (int i = 0; i < nn.index; ++i)
	{
		output = (nn.layers[i] * output);
	}
	return output;
}

ml::Vector operator * (const NeuralNetwork &nn, const ml::Vector &v)
{
	return (v * nn);
}

NeuralNetwork operator + (NeuralNetwork& nn1, NeuralNetwork& nn2)
{
	if (nn1.nlayers != nn2.nlayers)
	{
		std::cout << "Mr.Stark i dont feel so good" ;
		NeuralNetwork empty = *(new NeuralNetwork());
		return empty;
	}

	NeuralNetwork nnbuff = *(new NeuralNetwork(nn1.nlayers));

	int buffncells, buffnweights;

	for (int i = 0; i < nn1.nlayers; ++i)
	{
		Layer bufflayer;
		//bufflayer = *(new Layer());

		//std::cout << "called" << std::endl;

		buffncells = nn1.layers[i].ncells;

		Cell *buffcelllist = new Cell[buffncells];
		buffnweights = nn1.layers[i].layer[0].nweights;

		for (int j = 0; j < buffncells; ++j)
		{
			Cell buffcell = *(new Cell(buffnweights));

			for (int k = 0; k < buffnweights; ++k)
			{
				buffcell.weights[k] = (nn1.layers[i].layer[j].weights[k] + nn2.layers[i].layer[j].weights[k]);
			}

			buffcell.bias = nn1.layers[i].layer[j].bias + nn2.layers[i].layer[j].bias;
			buffcelllist[j] = buffcell;
		}

		bufflayer = *(new Layer(buffcelllist, buffncells));

		nnbuff << bufflayer;

		//nnbuff.print();
	}

	return nnbuff;
}

NeuralNetwork operator - (NeuralNetwork& nn1, NeuralNetwork& nn2)
{
	if (nn1.nlayers != nn2.nlayers)
	{
		std::cout << "Mr.Stark i dont feel so good" ;
		NeuralNetwork empty = *(new NeuralNetwork());
		return empty;
	}

	NeuralNetwork nnbuff = *(new NeuralNetwork(nn1.nlayers));

	int buffncells, buffnweights;

	for (int i = 0; i < nn1.nlayers; ++i)
	{
		Layer bufflayer;
		//bufflayer = *(new Layer());

		//std::cout << "called" << std::endl;

		buffncells = nn1.layers[i].ncells;

		Cell *buffcelllist = new Cell[buffncells];
		buffnweights = nn1.layers[i].layer[0].nweights;

		for (int j = 0; j < buffncells; ++j)
		{
			Cell buffcell = *(new Cell(buffnweights));

			for (int k = 0; k < buffnweights; ++k)
			{
				buffcell.weights[k] = (nn1.layers[i].layer[j].weights[k] - nn2.layers[i].layer[j].weights[k]);
			}

			buffcell.bias = nn1.layers[i].layer[j].bias - nn2.layers[i].layer[j].bias;
			buffcelllist[j] = buffcell;
		}

		bufflayer = *(new Layer(buffcelllist, buffncells));

		nnbuff << bufflayer;

		//nnbuff.print();
	}

	return nnbuff;
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
	this->nouts = this->nn.layers[this->nn.nlayers-1].ncells;
	this->ndatasets = ndatasets;

	std::fstream datafile;
	datafile.open(filename, std::ios::in);
	std::string buff;

	dataset *bdatasets = new dataset[ndatasets];


	for (int i = 0; i < ndatasets; i++)
	{

		dataset ds;
		
		__float128* inputs = new __float128[nn.layers[0].ncells];
		__float128* outputs = new __float128[nn.layers[nn.nlayers-1].ncells];

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

void Trainer::partition(float ratio)
{


	int ntraining = (int) (ratio * this->ndatasets);
	int ntesting = this->ndatasets - ntraining;

	this->ntraining = ntraining;
	this->ntesting = ntesting;

	this->trainingdatasets = this->datasets;
	this->testingdatasets = (this->datasets + ntraining);

}
void Trainer::partition()
{
	partition(0.5);
}


__float128 Trainer::calculatecost(dataset* datasetgroup)
{
	__float128 cost = 0.0q;
	ml::Vector buffoutput, buffinput, idealoutput;

	int inputsize = this->ninps;
	int outputsize = this->nouts;

	for (int i = 0; i < this->ntraining; ++i)
	{
		buffinput = ml::Vector(inputsize, datasetgroup[i].inputs);
		idealoutput = ml::Vector(outputsize, datasetgroup[i].outputs);

		buffoutput = this->nn * buffinput;

		
		cost  = cost + (buffoutput - idealoutput).getMagnitude();

	}


	return cost;
}


__float128 acttaninv(const __float128& val)
{
	return atanq(val);
}

__float128 acttanh(const __float128& val)
{
	return tanhq(val);
}


__float128 actsigmoid(const __float128& val)
{
	__float128 sigval = *(new __float128());
	sigval = (1.0q/(1.0q + expq(-1.0q * val)));
	return sigval;
}

__float128 actrelu(const __float128& val)
{
	__float128 sigval = 0.0q;
	if (val > 0.0q) sigval = val;
	return sigval;
}

__float128 actleakyrelu(const __float128& val)
{
	__float128 sigval = (LEAK * val);
	if (val > sigval) sigval = val;
	return sigval;
}

__float128 actelu(const __float128& val)
{
	__float128 sigval = *(new __float128());
	sigval = (ALPHA * (expq(val) - 1));
	return sigval;
}

__float128 actswish(const __float128& val)
{
	__float128 sigval = *(new __float128());
	sigval = (val/(1.0q + expq(-1.0q * val)));
	return sigval;
}

__float128 actnone(const __float128& val)
{
	return val;
}



void Layer::setactfunc( __float128 (*actfunc)(const __float128& val) )
{
	this->actfunc = actfunc;
	for (int i = 0; i < this->ncells; ++i)
	{
		this->layer[i].setactfunc(this->actfunc);
	}
}


void Cell::setactfunc( __float128 (*actfunc)(const __float128& val) )
{
	this->actfunc = actfunc;
	this->actfuncsetted = true;
}



/*__float128 Trainer::calculatecost()
{
	static __float128 cost = 0.0q;
	ml::Vector buffoutput, buffinput, idealoutput;

	int inputsize = this->ninps;
	int outputsize = this->nouts;

	for (int i = 0; i < this->ntraining; ++i)
	{
		buffinput = ml::Vector(inputsize, this->trainingdatasets[i].inputs);
		idealoutput = ml::Vector(outputsize, this->trainingdatasets[i].outputs);

		buffoutput = this->nn * buffinput;


		cost  = cost + (buffoutput - idealoutput).getMagnitude();

	}


	return cost;
}*/
__float128 Trainer::calculatecost()
{
	return calculatecost(this->trainingdatasets);
}

NeuralNetwork operator * (const NeuralNetwork& nn, const __float128& scalar)
{

	NeuralNetwork nnbuff = *(new NeuralNetwork(nn.nlayers));

	int buffncells, buffnweights;

	for (int i = 0; i < nn.nlayers; ++i)
	{
		Layer bufflayer;
		//bufflayer = *(new Layer());

		//std::cout << "called" << std::endl;

		buffncells = nn.layers[i].ncells;

		Cell *buffcelllist = new Cell[buffncells];
		buffnweights = nn.layers[i].layer[0].nweights;

		for (int j = 0; j < buffncells; ++j)
		{
			Cell buffcell = *(new Cell(buffnweights));

			for (int k = 0; k < buffnweights; ++k)
			{
				buffcell.weights[k] = (nn.layers[i].layer[j].weights[k] * scalar);
			}

			buffcell.bias = nn.layers[i].layer[j].bias * scalar;
			buffcelllist[j] = buffcell;
		}

		bufflayer = *(new Layer(buffcelllist, buffncells));

		nnbuff << bufflayer;

		//nnbuff.print();
	}

	return nnbuff;
}

NeuralNetwork operator * (const __float128& scalar, const NeuralNetwork& nn)
{
	return (nn * scalar);
}


ml::Vector& OutputCache::operator[](int index)
{
	return this->outputs[index];
}



ml::Vector NeuralNetwork::output(ml::Vector input, OutputCache oc, int xthlayer, int ythcell)
{
	ml::Vector out = *(new ml::Vector());

	for (int i = 0; i < this->nlayers; ++i)
	{
		if (i < xthlayer)
		{
			out = oc[i];
		}
		else
		{
			out = (out * this->layers[i]);
		}
	}

	return out;
}





NeuralNetwork Trainer::getgradient()
{
	NeuralNetwork buff = NeuralNetwork();
	return buff;

}
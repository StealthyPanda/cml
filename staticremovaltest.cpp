#include <iostream>

int taken = 0, released = 0;
void* operator new(size_t size)
{
	std::cout << "Called new for " << size << std::endl;
	taken += size;
	return malloc(size);
}

void* operator new[](size_t size)
{
	std::cout << "Called new[] for " << size << std::endl;
	taken += size;
	return malloc(size);
}

void operator delete(void* pointer, size_t size)
{
	std::cout << "Called delete for " << size << std::endl;
	released += size;
	free(pointer);
}

void operator delete[](void* pointer, size_t size)
{
	std::cout << "Called delete[] for " << size << std::endl;
	released += size;
	free(pointer);
}




class anobj
{
public:
	anobj();
	int* apointer;

	void initialise(int nbytes);
};

anobj::anobj()
{

}

void anobj::initialise(int nbytes)
{
	int *alist = new int[nbytes];
	for (int i = 0; i < nbytes; i++)
	{
		alist[i] = (i * i);
	}
	
	this->apointer = alist;
}

int main()
{
	anobj myobj = anobj();
	myobj.initialise(100);

	delete[] myobj.apointer;

	return 0;
}
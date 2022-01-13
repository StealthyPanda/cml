#include <iostream>
#include "ml.h"


class bruh
{
public:
	int publicbruh = 420;
	bruh();
	static void printsomin();
	friend void operator<<(const std::ostream &co, const bruh &ab);
	int returnsomin();
private:
	int epicbruh;
};

void operator<<(const std::ostream &co, const bruh &ab)
{
	co << ab.returnsomin();
}




bruh::bruh()
{
	return;
}

void bruh::printsomin()
{
	std::cout << "Inside printsomin" << std::endl;
}

int bruh::returnsomin()
{
	return 69;
}


using namespace std;

int main()
{
	
	
	bruh abruh = bruh();

	bruh* pointstoabruh = &abruh;

	pointstoabruh->printsomin();
	bruh::printsomin();

	cout << *(pointstoabruh);

	
	return 0;
}
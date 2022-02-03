#include <iostream>
#include <quadmath.h>


std::ostream& operator<< (std::ostream& stream, __float128 afloat)
{
	char buffer[40];

	quadmath_snprintf(buffer, sizeof buffer, "%+-#46.*Qe", 30, afloat);

	stream << buffer;

	return stream;

}



int main()
{
	__float128 pseudopi = (22.0q/70.0q);
	std::cout << pseudopi << std::endl;
}
#include <iostream>
//#include <quadmath>
#include <iomanip>
#include <quadmath.h>

/*void print(const __float128& afloat)
{
	char buffer[35];
	//"%+-#*.20Qe"
	quadmath_snprintf(buffer, sizeof buffer, "%+-#*.30Qe", 20, afloat);
	std::cout << buffer << std::endl;
}*/

int main()
{
	//relevant links for this thing:
	//https://gcc.gnu.org/onlinedocs/libquadmath/quadmath_005fsnprintf.html
	//https://gcc.gnu.org/onlinedocs/libquadmath/Math-Library-Routines.html#Math-Library-Routines
	//Compilation flags for this thing:
	//-std=gnu++11 -lquadmath -fext-numeric-literals
	//__float128 bruh = 0q;
	//long double bruh = (1.0l/3.0l);
	__float128 bruh = 3.0q;
	bruh = powq(bruh, sqrtq(bruh));
	
	std::cout  << std::endl;

	print(bruh);

	return 0;
}
#include"Poly.hpp"

int main()
{
	int coeffs1[4] = { 15, 0, 5, 3 };
	int coeffs2[5] = { 1, 1, 1, 1 };
	Poly<int> poly1(coeffs1, 4);
	Poly<int> poly2(coeffs2, 4);

	std::cout << "1> ";
	poly1.printPoly();
	std::cout << std::endl;
	
	std::cout << "2>";
	poly2.printPoly();
	std::cout << std::endl;


	std::cout << "(poly1 == poly2) - ";
	if (poly1 == poly2) std::cout << "true\n";
	else std::cout << "false\n";

	std::cout << "(poly1 < poly2) - ";
	if (poly1 < poly2) std::cout << "true\n";
	else std::cout << "false\n";

	std::cout << "(poly1 > poly2) - ";
	if (poly1 > poly2) std::cout << "true\n";
	else std::cout << "false\n";

	poly1 += poly2;
	std::cout << "(poly1 += poly2) ";
	poly1.printPoly();
	std::cout << std::endl;

	poly2 -= poly1;
	std::cout << "(poly2 -= poly1) ";
	poly2.printPoly();
	std::cout << std::endl;

	std::cout << poly1[2] << std::endl;
	std::cout << poly2[6] << std::endl;

	return 0;
}
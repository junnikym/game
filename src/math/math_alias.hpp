#ifndef MATH_ALIAS_HPP
#define MATH_ALIAS_HPP

#include <iostream>
#include <vector>

using namespace std;
using size_t_r = const size_t&;	// size type reference

#define Square(X) 	((X) * (X))
#define Cube(X) 	(Square(X) * (X))

#endif
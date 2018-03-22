#pragma once

#include <math.h>
#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;

class Rank
{
public:
	int dimensions;
	double * arr;
	Rank();
	Rank(int);
	void clear();
	friend ostream& operator<<(ostream&, const Rank&);
	friend bool operator==(const Rank&, const Rank&);
	friend bool operator!=(const Rank&, const Rank&);
};
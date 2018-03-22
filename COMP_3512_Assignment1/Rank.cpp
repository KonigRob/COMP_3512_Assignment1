#include "Rank.hpp"

Rank::Rank() : dimensions { 1 }, arr(new double[1])
{
	arr[0] = { 0.0 };
}

Rank::Rank(int size) : dimensions{ size }, arr{ new double[size] }
{
	clear();
}

void Rank::clear()
{
	for (int i = 0; i < dimensions; ++i) {
		arr[i] = 1.0;
	}
}

ostream & operator<<(ostream & output, const Rank & rank)
{
	for (int i = 0; i < rank.dimensions; ++i) {
			output << fixed << left << setprecision(6) << rank.arr[i] << "\n";
	}
	return output;
}

bool operator==(const Rank &lefthand, const Rank &righthand)
{
	if (lefthand.dimensions != righthand.dimensions) {
		return false;
	}
	for (int i = 0; i < lefthand.dimensions; ++i) {
		if (lefthand.arr[i] != righthand.arr[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Rank &lefthand, const Rank &righthand)
{
	return !operator==(lefthand, righthand);
}

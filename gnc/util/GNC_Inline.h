#pragma once

#include <cmath>

template<class T>
inline const T& LIMIT(const T& l, const T& x, const T& u)
{
	return ((x) >= (u)) ? (u) : (((x) <= (l)) ? (l) : (x));
}

template<class T>
inline T SQR(const T& a)
{
	return a == (T)0. ? (T)0. : a * a;
}

template<class T>
inline T DIST(const T& x1, const T& y1, const T& x2, const T& y2)
{
	return sqrt(SQR(x1 - x2) + SQR(y1 - y2));
}

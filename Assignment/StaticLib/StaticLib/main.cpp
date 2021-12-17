#include <iostream>
#include "C:\Users\jdy\Desktop\StaticLib\Debug\StaticLib.h"
#include "pch.h"
#pragma comment(lib,"StaticLib.lib")

int main() {
	double arr[] = { 1,1,1,1 };

	matrix<double> m(arr, 2, 2);
	return 0;
}
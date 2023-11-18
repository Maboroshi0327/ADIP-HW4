#include "HW_1.h"

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "../ImageProcessing/ImageProcessing.hpp"
using namespace dip;

void HW_1_1()
{
	Image img;
	for (int i = 1; i <= 8; i++)
	{
		stringstream filename;
		Coordinate<double> cen;
		filename << "shape100_" << i << ".raw";
		img.openRAW(filename.str().c_str(), Size(100, 100));
		cen = centroid(img);
		cout << filename.str().c_str() << ": Centroid(column, row) -> ";
		cout << "(" << cen.column << ", " << cen.row << ")" << endl;
	}
}

void HW_1_2()
{
	Image img;
	vector<int> pp({ 0, 1, 1, 0, 2, 1, 2, 0, 3 });
	vector<int> qq({ 1, 0, 1, 2, 0, 2, 1, 3, 0 });
	for (int i = 1; i <= 8; i++)
	{
		stringstream filename;
		filename << "shape100_" << i << ".raw";
		img.openRAW(filename.str().c_str(), Size(100, 100));
		cout << filename.str().c_str() << ":" << endl;

		for (int i = 0; i < 9; i++)
		{
			int p = pp[i];
			int q = qq[i];
			stringstream output;
			output.precision(6);
			output << fixed << "£g" << p << q << "-> " << centralMoments(img, p, q);
			cout << output.str() << endl;
			output.str("");
		}

		cout << endl;
	}
}

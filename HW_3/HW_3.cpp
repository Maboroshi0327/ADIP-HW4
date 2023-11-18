#include "HW_3.h"

#include <cstdint>

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "../ImageProcessing/ImageProcessing.hpp"
using namespace dip;

template<typename T1, typename T2>
vector<vector<T1>> convolutionROI(const Image& imgIn, const Image& roi, Kernel<T2>& kernel, bool normKernel);

void HW_3_1()
{
	Image flower_512x384, roi;
	flower_512x384.openRAW("flower_512x384.raw", Size(384, 512));

	gaussianBlur(flower_512x384, roi, Size(7, 7), 1.5);
	threshold(roi, roi, 180);
	roi.saveRAW("ROI.raw", true);
}

void HW_3_2()
{
	Image flower_512x384, roi;
	flower_512x384.openRAW("flower_512x384.raw", Size(384, 512));
	gaussianBlur(flower_512x384, roi, Size(7, 7), 1.5);
	threshold(roi, roi, 180);

	vector<vector<int>> foreground;
	Kernel<double> kernel = makeGaussianKernel(Size(5, 5), 2, true);
	lpf2hpf<double>(kernel, kernel);
	kernel.getReference(kernel.origin) += 1.1;
	foreground = convolutionROI<int, double>(flower_512x384, roi, kernel, false);

	vector<vector<int>> background;
	kernel = makeGaussianKernel(Size(5, 5), 2, true);
	negative(roi, roi);
	background = convolutionROI<int, double>(flower_512x384, roi, kernel, false);

	Image flower(flower_512x384.size, 0);
	for (int r = 0; r < flower.size.rows; r++)
		for (int c = 0; c < flower.size.columns; c++)
		{
			int value = abs(foreground[r][c]) + abs(background[r][c]);
			flower.img[r][c] = (value > 255) ? 255 : value;
		}

	flower.saveRAW("flower.raw", true);
}

template<typename T1, typename T2>
vector<vector<T1>> convolutionROI(const Image& imgIn, const Image& roi, Kernel<T2>& kernel, bool normKernel)
{
	int rows = imgIn.size.rows;
	int columns = imgIn.size.columns;
	int rowsKernel = kernel.size.rows;
	int colsKernel = kernel.size.columns;
	int rowOrigin = kernel.origin.row;
	int colOrigin = kernel.origin.column;

	T2 denominator = 0;
	if (normKernel == true)
		for (auto& i : kernel.kernel)
			for (auto& j : i)
				denominator += j;

	int rowPad = max(rowsKernel - rowOrigin - 1, rowOrigin);
	int colPad = max(colsKernel - colOrigin - 1, colOrigin);
	Image imgPad;
	padding(imgIn, imgPad, rowPad, colPad);

	vector<vector<T1>> imgTemp(rows, vector<T1>(columns, 0));
	for (int r = rowPad; r < rows + rowPad; r++)
		for (int c = colPad; c < columns + colPad; c++)
		{
			if (roi.img[r - rowPad][c - colPad] == 255)
			{
				T2 sum = 0;
				for (int i = -rowOrigin; i < rowsKernel - rowOrigin; i++)
					for (int j = -colOrigin; j < colsKernel - colOrigin; j++)
						sum += imgPad.img[r + i][c + j] * kernel[i + rowOrigin][j + colOrigin];
				if (normKernel)
					imgTemp[r - rowPad][c - colPad] = (T1)round((double)sum / denominator);
				else
					imgTemp[r - rowPad][c - colPad] = (T1)sum;
			}
		}

	return imgTemp;
}

#include "HW_2.h"

#include <iostream>
#include <vector>
using namespace std;

#include "../ImageProcessing/ImageProcessing.hpp"
using namespace dip;

void HW_2_1()
{
	Image slate_700x421, slate_noise_700x421;
	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));

	Image img;
	boxedBlur(slate_700x421, img, Size(3, 3));
	img.saveRAW("box_3x3.raw", true);
	boxedBlur(slate_700x421, img, Size(5, 5));
	img.saveRAW("box_5x5.raw", true);

	boxedBlur(slate_noise_700x421, img, Size(3, 3));
	img.saveRAW("box_noise_3x3.raw", true);
	boxedBlur(slate_noise_700x421, img, Size(5, 5));
	img.saveRAW("box_noise_5x5.raw", true);

	gaussianBlur(slate_700x421, img, Size(3, 3), 0.85);
	img.saveRAW("gauss_3x3.raw", true);
	gaussianBlur(slate_700x421, img, Size(5, 5), 1.03785);
	img.saveRAW("gauss_5x5.raw", true);

	gaussianBlur(slate_noise_700x421, img, Size(3, 3), 0.85);
	img.saveRAW("gauss_noise_3x3.raw", true);
	gaussianBlur(slate_noise_700x421, img, Size(5, 5), 1.03785);
	img.saveRAW("gauss_noise_5x5.raw", true);
}

void HW_2_2()
{
	Image slate_700x421, slate_noise_700x421;
	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));

	Image img;
	robertsFiltering(slate_700x421, img, -45);
	img.saveRAW("roberts_n45.raw", true);
	robertsFiltering(slate_700x421, img, 45);
	img.saveRAW("roberts_45.raw", true);
	robertsFiltering(slate_700x421, img);
	img.saveRAW("roberts.raw", true);

	robertsFiltering(slate_noise_700x421, img, -45);
	img.saveRAW("roberts_noise_n45.raw", true);
	robertsFiltering(slate_noise_700x421, img, 45);
	img.saveRAW("roberts_noise_45.raw", true);
	robertsFiltering(slate_noise_700x421, img);
	img.saveRAW("roberts_noise.raw", true);
}

void HW_2_3()
{
	Image slate_700x421, slate_noise_700x421;
	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));

	Image img;
	prewittFiltering(slate_700x421, img, 0);
	img.saveRAW("prewitt_0.raw", true);
	prewittFiltering(slate_700x421, img, 90);
	img.saveRAW("prewitt_90.raw", true);
	prewittFiltering(slate_700x421, img);
	img.saveRAW("prewitt.raw", true);

	prewittFiltering(slate_noise_700x421, img, 0);
	img.saveRAW("prewitt_noise_0.raw", true);
	prewittFiltering(slate_noise_700x421, img, 90);
	img.saveRAW("prewitt_noise_90.raw", true);
	prewittFiltering(slate_noise_700x421, img);
	img.saveRAW("prewitt_noise.raw", true);
}

void HW_2_4()
{
	Image slate_700x421, slate_noise_700x421;
	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));

	Image img;
	sobelFiltering(slate_700x421, img, 0);
	img.saveRAW("sobel_0.raw", true);
	sobelFiltering(slate_700x421, img, 90);
	img.saveRAW("sobel_90.raw", true);
	sobelFiltering(slate_700x421, img);
	img.saveRAW("sobel.raw", true);

	sobelFiltering(slate_noise_700x421, img, 0);
	img.saveRAW("sobel_noise_0.raw", true);
	sobelFiltering(slate_noise_700x421, img, 90);
	img.saveRAW("sobel_noise_90.raw", true);
	sobelFiltering(slate_noise_700x421, img);
	img.saveRAW("sobel_noise.raw", true);
}

void HW_2_5()
{
	Kernel<int> kernel;
	std::vector<std::vector<int>> vector45, vectorN45;
	Image slate_700x421, slate_noise_700x421, img, img45, imgN45;

	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));
	img.setImg(slate_700x421.size, 0);
	img45.setImg(slate_700x421.size, 0);
	imgN45.setImg(slate_700x421.size, 0);
	int rows = slate_700x421.size.rows;
	int columns = slate_700x421.size.columns;

	// slate_700x421
	kernel = makeSobelKernel(-45);
	vectorN45 = convolution<int, int>(slate_700x421, kernel, false);
	kernel = makeSobelKernel(45);
	vector45 = convolution<int, int>(slate_700x421, kernel, false);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			int abs = std::abs(vectorN45[r][c]);
			imgN45.img[r][c] = (abs > 255) ? 255 : abs;
			abs = std::abs(vector45[r][c]);
			img45.img[r][c] = (abs > 255) ? 255 : abs;
			abs = (int)std::sqrt(vector45[r][c] * vector45[r][c] + vectorN45[r][c] * vectorN45[r][c]);
			img.img[r][c] = (abs > 255) ? 255 : abs;
		}
	img.saveRAW("sobel_45n45.raw", true);
	img45.saveRAW("sobel_45.raw", true);
	imgN45.saveRAW("sobel_n45.raw", true);

	// slate_noise_700x421
	kernel = makeSobelKernel(-45);
	vectorN45 = convolution<int, int>(slate_noise_700x421, kernel, false);
	kernel = makeSobelKernel(45);
	vector45 = convolution<int, int>(slate_noise_700x421, kernel, false);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			int abs = std::abs(vectorN45[r][c]);
			imgN45.img[r][c] = (abs > 255) ? 255 : abs;
			abs = std::abs(vector45[r][c]);
			img45.img[r][c] = (abs > 255) ? 255 : abs;
			abs = (int)std::sqrt(vector45[r][c] * vector45[r][c] + vectorN45[r][c] * vectorN45[r][c]);
			img.img[r][c] = (abs > 255) ? 255 : abs;
		}
	img.saveRAW("sobel_noise_45n45.raw", true);
	img45.saveRAW("sobel_noise_45.raw", true);
	imgN45.saveRAW("sobel_noise_n45.raw", true);
}

void HW_2_6()
{
	Image slate_700x421, slate_noise_700x421;
	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));

	Image img;
	laplacianFiltering(slate_700x421, img, 4);
	img.saveRAW("laplacian_4.raw", true);
	laplacianFiltering(slate_700x421, img, 8);
	img.saveRAW("laplacian_8.raw", true);

	laplacianFiltering(slate_noise_700x421, img, 4);
	img.saveRAW("laplacian_noise_4.raw", true);
	laplacianFiltering(slate_noise_700x421, img, 8);
	img.saveRAW("laplacian_noise_8.raw", true);
}

void HW_2_8()
{
	Image slate_700x421, slate_noise_700x421, img;
	slate_700x421.openRAW("slate_700x421.raw", Size(421, 700));
	slate_noise_700x421.openRAW("slate_noise_700x421.raw", Size(421, 700));
	int rows = slate_700x421.size.rows;
	int columns = slate_700x421.size.columns;

	laplacianSharpening(slate_700x421, img, 4);
	img.saveRAW("HighBoost_1.raw", true);
	laplacianSharpening(slate_noise_700x421, img, 4);
	img.saveRAW("HighBoost_noise_1.raw", true);

	laplacianSharpening(slate_700x421, img, 8);
	img.saveRAW("HighBoost_2.raw", true);
	laplacianSharpening(slate_noise_700x421, img, 8);
	img.saveRAW("HighBoost_noise_2.raw", true);
}

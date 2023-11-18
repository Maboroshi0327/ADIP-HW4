#ifndef _ImageProcessing_
#define _ImageProcessing_

#include <cmath>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <vector>

namespace dip
{
	typedef union BitPlane
	{
		uint8_t pixel;
		struct
		{
			unsigned b0 : 1;
			unsigned b1 : 1;
			unsigned b2 : 1;
			unsigned b3 : 1;
			unsigned b4 : 1;
			unsigned b5 : 1;
			unsigned b6 : 1;
			unsigned b7 : 1;
		};
	} BitPlane;

	class Size
	{
	public:
		int rows;
		int columns;
		Size();
		Size(int rows, int columns);
		Size(const Size& source);
		int area() const;
		Size operator=(const Size& other);
		Size operator+(const int& other) const;
		Size operator-(const int& other) const;
		Size operator*(const double& other) const;
		Size operator/(const double& other) const;
		bool operator==(const Size& other) const;
		bool operator!=(const Size& other) const;
	};

	template<typename T>
	class Coordinate
	{
	public:
		T row;
		T column;
		Coordinate();
		Coordinate(T row, T column);
		Coordinate operator=(const Coordinate& other);
		bool operator==(const Coordinate& other) const;
		bool operator!=(const Coordinate& other) const;
	};

	template<typename T>
	class Kernel
	{
	public:
		Size size;
		Coordinate<int> origin;
		std::vector<std::vector<T>> kernel;
		void setKernel(Size size);
		void setKernel(Size size, T value);
		void setKernel(Size size, Coordinate<int> origin);
		void setKernel(Size size, Coordinate<int> origin, T value);
		T getValue(Coordinate<int> coord) const;
		T& getReference(Coordinate<int> coord);

		Kernel();
		Kernel(Size size);
		Kernel(Size size, T value);
		Kernel(Size size, Coordinate<int> origin);
		Kernel(Size size, Coordinate<int> origin, T value);
		Kernel(const Kernel<T>& other);
		Kernel<T> operator=(const Kernel<T>& other);
		Kernel<T> operator+(const Kernel<T>& other);
		Kernel<T> operator-(const Kernel<T>& other);
		Kernel<T> operator*(const Kernel<T>& other);
		Kernel<T> operator/(const Kernel<T>& other);
		std::vector<T>& operator[](int index);
		std::vector<T> operator[](int index) const;
	};

	template<typename T>
	void lpf2hpf(const Kernel<T>& input, Kernel<T>& output);

	class Image
	{
	public:
		Size size;
		std::vector<std::vector<uint8_t>> img;
		void openRAW(const char* FileName, Size size);
		void saveRAW(const char* FileName, bool printName);
		void setImg(const Image& source);
		void setImg(Size size, uint8_t value);
		void setImg(std::vector<std::vector<uint8_t>>& img);

		Image();
		Image(const Image& source);
		Image(Size size, uint8_t value);
		Image(std::vector<std::vector<uint8_t>>& img);
		Image operator=(const Image& other);
	};

	void nearest(const Image& imgIn, Image& imgOut, Size size);
	void bicubic(const Image& imgIn, Image& imgOut, Size size);
	double bicubic_param(double x, double a);
	void padding(const Image& imgIn, Image& imgOut, int pad);
	void padding(const Image& imgIn, Image& imgOut, int rowPad, int colPad);
	void threshold(const Image& imgIn, Image& imgOut, uint8_t th);
	void replaceBitPlane(const Image& imgIn, Image& imgOut, const Image& plane, int bit);
	void extractBitPlane(const Image& imgIn, Image& imgOut, int bit);
	void logTrans(const Image& imgIn, Image& imgOut);
	void invLogTrans(const Image& imgIn, Image& imgOut);
	void gammaTrans(const Image& imgIn, Image& imgOut, double gamma);
	void negative(const Image& imgIn, Image& imgOut);
	void histEqualize(const Image& imgIn, Image& imgOut);
	int moments(const Image& imgIn, int i, int j);
	int intPow(int x, int p);
	Coordinate<double> centroid(const Image& imgIn);
	double centralMoments(const Image& imgIn, int p, int q);
	void boxedBlur(const Image& imgIn, Image& imgOut, Size kernelSize);
	void gaussianBlur(const Image& imgIn, Image& imgOut, Size kernelSize, double sigma);
	void robertsFiltering(const Image& imgIn, Image& imgOut);
	void robertsFiltering(const Image& imgIn, Image& imgOut, int angle);
	void prewittFiltering(const Image& imgIn, Image& imgOut);
	void prewittFiltering(const Image& imgIn, Image& imgOut, int angle);
	void sobelFiltering(const Image& imgIn, Image& imgOut);
	void sobelFiltering(const Image& imgIn, Image& imgOut, int angle);
	void laplacianFiltering(const Image& imgIn, Image& imgOut, int neighbor);
	void laplacianSharpening(const Image& imgIn, Image& imgOut, int neighbor);
	Kernel<int> makeBoxKernel(Size size);
	Kernel<int> makeGaussianKernel(Size size, double sigma);
	Kernel<double> makeGaussianKernel(Size size, double sigma, bool normalize);
	Kernel<int> makeRobertsKernel(int angle);
	Kernel<int> makePrewittKernel(int angle);
	Kernel<int> makeSobelKernel(int angle);
	Kernel<int> makeLaplacianKernel(int neighbor);

	template<typename T1, typename T2>
	std::vector<std::vector<T1>> convolution(const Image& imgIn, Kernel<T2>& kernel, bool normKernel);
}

#include "ImageProcessing.ipp"

#endif /* _ImageProcessing_ */
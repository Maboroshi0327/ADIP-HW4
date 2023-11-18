#include "ImageProcessing.hpp"
namespace dip
{
	template<typename T>
	Coordinate<T>::Coordinate()
	{
		this->row = 0;
		this->column = 0;
	}

	template<typename T>
	Coordinate<T>::Coordinate(T row, T column)
	{
		this->row = row;
		this->column = column;
	}

	template<typename T>
	Coordinate<T> Coordinate<T>::operator=(const Coordinate<T>& other)
	{
		this->row = other.row;
		this->column = other.column;
		return *this;
	}

	template<typename T>
	bool Coordinate<T>::operator==(const Coordinate<T>& other) const
	{
		bool result = this->row == other.row;
		result &= this->column == other.column;
		return result;
	}

	template<typename T>
	bool Coordinate<T>::operator!=(const Coordinate& other) const
	{
		bool result = Coordinate::row != other.row;
		result |= Coordinate::column != other.column;
		return result;
	}

	template<typename T>
	void Kernel<T>::setKernel(Size size)
	{
		this->size = size;
		this->origin = Coordinate<int>(size.rows / 2, size.columns / 2);
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, 0));
	}

	template<typename T>
	void Kernel<T>::setKernel(Size size, T value)
	{
		this->size = size;
		this->origin = Coordinate<int>(size.rows / 2, size.columns / 2);
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, value));
	}

	template<typename T>
	void Kernel<T>::setKernel(Size size, Coordinate<int> origin)
	{
		this->size = size;
		this->origin = origin;
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, 0));
	}

	template<typename T>
	void Kernel<T>::setKernel(Size size, Coordinate<int> origin, T value)
	{
		this->size = size;
		this->origin = origin;
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, value));
	}

	template<typename T>
	T Kernel<T>::getValue(Coordinate<int> coord) const
	{
		return this->kernel[coord.row][coord.column];
	}

	template<typename T>
	T& Kernel<T>::getReference(Coordinate<int> coord)
	{
		return this->kernel[coord.row][coord.column];
	}

	template<typename T>
	Kernel<T>::Kernel()
	{
		this->size = Size(0, 0);
		this->origin = Coordinate<int>(0, 0);
	}

	template<typename T>
	Kernel<T>::Kernel(Size size)
	{
		this->size = size;
		this->origin = Coordinate<int>(size.rows / 2, size.columns / 2);
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, 0));
	}

	template<typename T>
	Kernel<T>::Kernel(Size size, T value)
	{
		this->size = size;
		this->origin = Coordinate<int>(size.rows / 2, size.columns / 2);
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, value));
	}

	template<typename T>
	Kernel<T>::Kernel(Size size, Coordinate<int> origin)
	{
		this->size = size;
		this->origin = origin;
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, 0));
	}

	template<typename T>
	Kernel<T>::Kernel(Size size, Coordinate<int> origin, T value)
	{
		this->size = size;
		this->origin = origin;
		this->kernel = std::vector<std::vector<T>>(size.rows, std::vector<T>(size.columns, value));
	}

	template<typename T>
	Kernel<T>::Kernel(const Kernel<T>& other)
	{
		this->size = other.size;
		this->origin = other.origin;
		this->kernel = other.kernel;
	}

	template<typename T>
	Kernel<T> Kernel<T>::operator=(const Kernel<T>& other)
	{
		this->size = other.size;
		this->origin = other.origin;
		this->kernel = other.kernel;
		return *this;
	}

	template<typename T>
	Kernel<T> Kernel<T>::operator+(const Kernel<T>& other)
	{
		if (this->size != other.size)
		{
			std::printf("Error: Kernel<T>::operator+\n");
			return *this;
		}

		Kernel<T> kernel(this->size, this->origin);
		for (int i = 0; i < this->size.rows; i++)
			for (int j = 0; j < this->size.columns; j++)
				kernel[i][j] = this->kernel[i][j] + other[i][j];

		return kernel;
	}

	template<typename T>
	Kernel<T> Kernel<T>::operator-(const Kernel<T>& other)
	{
		if (this->size != other.size)
		{
			std::printf("Error: Kernel<T>::operator-\n");
			return *this;
		}

		Kernel<T> kernel(this->size, this->origin);
		for (int i = 0; i < this->size.rows; i++)
			for (int j = 0; j < this->size.columns; j++)
				kernel[i][j] = this->kernel[i][j] - other[i][j];

		return kernel;
	}

	template<typename T>
	Kernel<T> Kernel<T>::operator*(const Kernel<T>& other)
	{
		if (this->size != other.size)
		{
			std::printf("Error: Kernel<T>::operator*\n");
			return *this;
		}

		Kernel<T> kernel(this->size, this->origin);
		for (int i = 0; i < this->size.rows; i++)
			for (int j = 0; j < this->size.columns; j++)
				kernel[i][j] = this->kernel[i][j] * other[i][j];

		return kernel;
	}

	template<typename T>
	Kernel<T> Kernel<T>::operator/(const Kernel<T>& other)
	{
		if (this->size != other.size)
		{
			std::printf("Error: Kernel<T>::operator/\n");
			return *this;
		}

		Kernel<T> kernel(this->size, this->origin);
		for (int i = 0; i < this->size.rows; i++)
			for (int j = 0; j < this->size.columns; j++)
				kernel[i][j] = this->kernel[i][j] / other[i][j];

		return kernel;
	}

	template<typename T>
	std::vector<T>& Kernel<T>::operator[](int index)
	{
		return this->kernel[index];
	}

	template<typename T>
	std::vector<T> Kernel<T>::operator[](int index) const
	{
		return this->kernel[index];
	}

	template<typename T>
	void lpf2hpf(const Kernel<T>& input, Kernel<T>& output)
	{
		Kernel<T> kernel(input);

		for (int i = 0; i < kernel.size.rows; i++)
			for (int j = 0; j < kernel.size.columns; j++)
				kernel[i][j] = -kernel[i][j];

		kernel.getReference(kernel.origin) += 1;

		output = kernel;
	}

	template<typename T1, typename T2>
	std::vector<std::vector<T1>> convolution(const Image& imgIn, Kernel<T2>& kernel, bool normKernel)
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

		int rowPad = std::max(rowsKernel - rowOrigin - 1, rowOrigin);
		int colPad = std::max(colsKernel - colOrigin - 1, colOrigin);
		Image imgPad;
		padding(imgIn, imgPad, rowPad, colPad);

		std::vector<std::vector<T1>> imgTemp(rows, std::vector<T1>(columns, 0));
		for (int r = rowPad; r < rows + rowPad; r++)
			for (int c = colPad; c < columns + colPad; c++)
			{
				T2 sum = 0;
				for (int i = -rowOrigin; i < rowsKernel - rowOrigin; i++)
					for (int j = -colOrigin; j < colsKernel - colOrigin; j++)
						sum += imgPad.img[r + i][c + j] * kernel[i + rowOrigin][j + colOrigin];
				if (normKernel)
					imgTemp[r - rowPad][c - colPad] = (T1)std::round((double)sum / denominator);
				else
					imgTemp[r - rowPad][c - colPad] = (T1)sum;
			}

		return imgTemp;
	}

}

#include <iostream>

using namespace std;

class Matrix {
public:
	struct Helper {
	public:
		Helper(int* ptr, int size) :
			dataPtr(ptr),
			size(size) {
		}

		Helper& operator=(const Helper& other) = delete;

		int& operator[](int index) {
			if (0 <= index && index < size) {
				return dataPtr[index];
			}
			else {
				throw out_of_range("Index out of range");
			}
		}

		const int& operator[](int index) const {
			if (0 <= index && index < size) {
				return dataPtr[index];
			}
			else {
				throw out_of_range("Index out of range");
			}
		}

	private:
		int* dataPtr;
		int size;

		Helper(const Helper& other) = default;
		friend class Matrix;
	};

	Matrix() :
		data(nullptr),
		sizeM(0),
		sizeN(0) {
	}

	Matrix(int x, int y) :
		Matrix() {
		data = new int* [x];
		for (int i = 0; i < x; i++) {
			try {
				data[i] = new int[y];
			}
			catch (const bad_alloc& err) {
				for (int j = 0; j < i; j++) {
					delete[] data[j];
				}
				delete[] data;
				throw;
			}
		}
		sizeM = x;
		sizeN = y;
	}

	Matrix(int x, int y, int fillNum) :
		Matrix() {
		Matrix temp(x, y);

		temp.fill(fillNum);

		swap(data, temp.data);
		swap(sizeM, temp.sizeM);
		swap(sizeN, temp.sizeN);
	}

	Matrix(const Matrix& other) :
		Matrix() {
		Matrix temp(other.sizeM, other.sizeN);

		temp.copy(other);

		swap(data, temp.data);
		swap(sizeM, temp.sizeM);
		swap(sizeN, temp.sizeN);
	}

	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			Matrix temp(other);
			swap(data, temp.data);
			swap(sizeM, temp.sizeM);
			swap(sizeN, temp.sizeN);
		}
		return *this;
	}

	Helper operator[](int index) {
		if (0 <= index && index < sizeM) {
			return Helper(data[index], sizeN);
		}
		else {
			throw out_of_range("Index out of range");
		}
	}

	const Helper operator[](int index) const {
		if (0 <= index && index < sizeM) {
			return Helper(data[index], sizeN);
		}
		else {
			throw out_of_range("Index out of range");
		}
	}

	Matrix& operator+=(const Matrix& other) {
		if (sizeM == other.sizeM && sizeN == other.sizeN) {
			for (int i = 0; i < sizeM; i++) {
				for (int j = 0; j < sizeN; j++) {
					data[i][j] += other.data[i][j];
				}
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& other) const {
		Matrix temp(*this);
		temp += other;
		return temp;
	}

	Matrix& operator-=(const Matrix& other) {
		*this += other * -1;
		return *this;
	}

	Matrix operator-(const Matrix& other) const {
		Matrix temp(*this);
		temp -= other;
		return temp;
	}

	Matrix& operator*=(int num) {
		for (int i = 0; i < sizeM; i++) {
			for (int j = 0; j < sizeN; j++) {
				data[i][j] *= num;
			}
		}
		return *this;
	}

	Matrix operator*(int num) const {
		Matrix temp(*this);
		temp *= num;
		return temp;
	}

	Matrix& operator*=(const Matrix& other) {
		if (sizeN == other.sizeM) {
			Matrix temp(sizeM, other.sizeN, 0);
			for (int i = 0; i < temp.sizeM; i++) {
				for (int j = 0; j < temp.sizeN; j++) {
					for (int k = 0; k < temp.sizeM; k++) {
						temp.data[i][j] += data[i][k] * other.data[k][j];
					}
				}

			}
			swap(data, temp.data);
			swap(sizeM, temp.sizeM);
			swap(sizeN, temp.sizeN);
		}
		return *this;
	}

	Matrix operator*(const Matrix& other) const {
		Matrix temp(*this);
		temp *= other;
		return temp;
	}

	Matrix& operator^=(int num) {
		Matrix temp(*this);
		for (int i = 1; i < num; i++) {
			*this *= temp;
		}
		return *this;
	}

	Matrix operator^(int num) const {
		Matrix temp(*this);
		temp ^= num;
		return temp;
	}

	friend ostream& operator<<(ostream& out, const Matrix& other) {
		for (int i = 0; i < other.sizeM; i++) {
			for (int j = 0; j < other.sizeN; j++) {
				out << other.data[i][j] << ' ';
			}
			out << endl;
		}
		return out;
	}

	int getRows() {
		return sizeM;
	}

	int getColumns() {
		return sizeN;
	}

	void setSize(int x, int y) {
		Matrix temp(x, y);

		temp.copy(*this);

		swap(data, temp.data);
		swap(sizeM, temp.sizeM);
		swap(sizeN, temp.sizeN);

	}

	void setSize(int x, int y, int fill) {
		Matrix temp(x, y, fill);

		temp.copy(*this);

		swap(data, temp.data);
		swap(sizeM, temp.sizeM);
		swap(sizeN, temp.sizeN);
	}

	void fill(int fillNum) {
		for (int i = 0; i < sizeM; i++) {
			for (int j = 0; j < sizeN; j++) {
				data[i][j] = fillNum;
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < sizeM; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

private:
	int** data;
	int sizeM, sizeN;

	void copy(const Matrix& other) {
		for (int i = 0; i < min(sizeM, other.sizeM); i++) {
			for (int j = 0; j < min(sizeN, other.sizeN); j++) {
				this->data[i][j] = other.data[i][j];
			}
		}
	}
};
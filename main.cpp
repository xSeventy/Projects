#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>


using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix



class Matrix {
public:
    Matrix () {
        num_rows = 0;
        num_cols = 0;
    }
    
    Matrix (const int& first, const int& second) {
        if(first < 0 || second < 0) {
            throw out_of_range("Index out of range");
        } else if(first == 0 || second == 0) {
            num_rows = 0;
            num_cols = 0;
            array.resize(num_rows, vector<int>(num_cols));
        } else {
            num_rows = first;
            num_cols = second;
            array.resize(num_rows, vector<int>(num_cols));
        }
    }
    
    void Reset (const int& first, const int& second) {
        if(first < 0 || second < 0) {
            throw out_of_range("Index out of range");
        }
        num_rows = first;
        num_cols = second;
        array.resize(num_rows, vector<int>(num_cols));
        for(int i = 0; i < first; i++) {
            for(int j = 0; j < second; j++) {
                array[i][j] = 0;
            }
        }
    }
    
    int At(const int& row, const int& col) const {
        if(row >= num_rows || col >= num_cols || row < 0 || col < 0) {
            throw out_of_range("Index out of range");
        }
        return array[row][col];
    }
    
    int& At(const int& row, const int& col) {
        if(row >= num_rows || col >= num_cols || row < 0 || col < 0) {
            throw out_of_range("Index out of range");
        }
        return array[row][col];
    }
    
    int GetNumRows () const {
        return num_rows;
    }
    
    int GetNumColumns () const {
        return num_cols;
    }
    
private:
    int num_cols;
    int num_rows;
    vector<vector<int>> array;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if(lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
        int lhs_row = lhs.GetNumRows();
        int lhs_col = lhs.GetNumColumns();
        Matrix matrix(lhs_row, lhs_col);
        for(int i = 0; i < lhs_row; i++) {
            for(int j = 0; j < lhs_col; j++) {
                matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
            }
        }
        return matrix;
    } else {
        throw invalid_argument("Matrices have different dimensions");
    }
}

ostream& operator<<(ostream& stream, const Matrix& mat) {
    stream << mat.GetNumRows() << " " << mat.GetNumColumns() << endl;
    for(int i = 0; i < mat.GetNumRows(); i++) {
        for(int j = 0; j < mat.GetNumColumns(); j++) {
            stream << mat.At(i, j) << " ";
        }
        stream << endl;
    }
    return stream;
}

istream& operator>>(istream& stream, Matrix& mat) {
    int x, y;
    stream >> x >> y;
    mat.Reset(x, y);
    for(int i = 0; i < mat.GetNumRows(); i++) {
        for(int j = 0; j < mat.GetNumColumns(); j++) {
            stream >> mat.At(i, j);
        }
    }
    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if(lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
        for(int i = 0; i < lhs.GetNumRows(); i++) {
            for(int j = 0; j < lhs.GetNumColumns(); j++) {
                if(lhs.At(i, j) != rhs.At(i, j)) {
                    return false;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

int main() {
    try {
        Matrix m(0, 1);
        Matrix m1(0, 0);
        cout << (m + m1);
    } catch(exception& ex) {
        cout << ex.what() << endl;
    }
  return 0;
}





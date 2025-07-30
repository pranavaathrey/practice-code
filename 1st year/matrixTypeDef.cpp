#include <iostream>
using namespace std;

class Matrix {
private:
    int rows, columns;
    int data[100][100];

public:
    Matrix(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
    }

    void input() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                cin >> data[i][j];
        }
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }

    Matrix operator+(Matrix addend) {
        if (rows != addend.rows || columns != addend.columns) {
            cout << "Matrix dimensions must match for addition." << endl;
            exit(1);
        }
        Matrix sum(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                sum.data[i][j] = data[i][j] + addend.data[i][j];
            }
        }
        return sum;
    }

    Matrix operator-(Matrix subtrahend) {
        if (rows != subtrahend.rows || columns != subtrahend.columns) {
            cout << "Matrix dimensions must match for subtraction." << endl;
            exit(1);
        }
        Matrix difference(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                difference.data[i][j] = data[i][j] - subtrahend.data[i][j];
            }
        }
        return difference;
    }

    Matrix operator-() {
        Matrix negated(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                negated.data[i][j] = -data[i][j];
            }
        }
        return negated;
    }

    Matrix operator~() {
        Matrix transpose(columns, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                transpose.data[j][i] = data[i][j];
        }
        return transpose;
    }

    Matrix operator*(Matrix multiplier) {
        if (columns != multiplier.rows) {
            cout << "Incompatible matrices for multiplication." << endl;
            exit(1);
        }
        Matrix product(rows, multiplier.columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < multiplier.columns; j++) {
                product.data[i][j] = 0;
                for (int k = 0; k < columns; k++) {
                    product.data[i][j] += data[i][k] * multiplier.data[k][j];
                }
            }
        }
        return product;
    }
};

int main() {
    int rows1, columns1;
    cin >> rows1 >> columns1;
    Matrix mat1(rows1, columns1);
    mat1.input();

    int rows2, columns2;
    cin >> rows2 >> columns2;
    Matrix mat2(rows2, columns2);
    mat2.input();

    cout << "Matrix product: " << endl;
    Matrix product = mat1 * mat2;
    product.print();

    cout << "Transpose of the first matrix: " << endl;
    Matrix transpose = ~mat1;
    transpose.print();

    cout << "Sum of the two matrices: " << endl;
    Matrix sum = mat1 + mat2;
    sum.print();

    cout << "Difference of the two matrices: " << endl;
    Matrix diff = mat1 - mat2;
    diff.print();

    cout << "Negation of the first matrix: " << endl;
    Matrix neg = -mat1;
    neg.print();

    return 0;
}

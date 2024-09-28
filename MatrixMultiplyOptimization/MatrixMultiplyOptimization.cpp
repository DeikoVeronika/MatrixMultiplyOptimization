#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Блокова оптимізована функція множення матриць
vector<vector<int>> multiplyMatricesBlocked(const vector<vector<int>>& A, const vector<vector<int>>& B, int blockSize = 64) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < n; kk += blockSize) {
                int iMax = min(ii + blockSize, n);
                int jMax = min(jj + blockSize, n);
                int kMax = min(kk + blockSize, n);
                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        for (int k = kk; k < kMax; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}

vector<vector<int>> generateRandomMatrix(int n, int seed) {
    vector<vector<int>> matrix(n, vector<int>(n));
    mt19937 gen(seed);
    uniform_int_distribution<> dis(0, 9999);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the matrix size: ";
    cin >> n;

    static vector<vector<int>> A, B;
    static int count = 0;

    if (count % 2 == 0) {
        A = generateRandomMatrix(n, 3);
        B = generateRandomMatrix(n, 4);
    }

    count++;

    vector<vector<int>> C = multiplyMatricesBlocked(A, B);

    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << "Matrix B:" << endl;
    printMatrix(B);
    cout << "Multiplication result (A * B):" << endl;
    printMatrix(C);

    return 0;
}

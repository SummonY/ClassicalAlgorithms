#include <iostream>

using namespace std;

const int N = 512;

template <typename T>
void Strassen(int n, T A[][N], T B[][N], T C[][N]);

int main(int argc, char *argv[])
{
    int A[N][N], B[N][N], C[N][N];
    int i, j;

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            A[i][j] = i * j;
            B[i][j] = i * j;
        }
    }

    Strassen(N, A, B, C);

    cout << "Matrix Output C: " << endl;
    /*
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            cout << C[i][j] << "  ";
        }
        cout << endl;
    }
    */
    return 0;
}


/*
 * Matrix Multiplication as the normal algorithm
 */
template <typename T>
void Matrix_Multiply(T A[][N], T B[][N], T C[][N])
{
    int i, j, t;

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            C[i][j] = 0;
            for (t = 0; t < 2; ++t) {
                C[i][j] += A[i][t] * B[t][j];
            }
        }
    }
}

/*
 * Matrix Add
 */
template <typename T>
void Matrix_Add(int n, T X[][N], T Y[][N], T Z[][N])
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            Z[i][j] = X[i][j] + Y[i][j];
        }
    }
}


/*
 * Matrix Sub
 */
template <typename T>
void Matrix_Sub(int n, T X[][N], T Y[][N], T Z[][N])
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            Z[i][j] = X[i][j] - Y[i][j];
        }
    }
}


/*
 * Strassen Algorithm
 */
template <typename T>
void Strassen(int n, T A[][N], T B[][N], T C[][N])
{
    T A11[N][N], A12[N][N], A21[N][N], A22[N][N];
    T B11[N][N], B12[N][N], B21[N][N], B22[N][N];
    T C11[N][N], C12[N][N], C21[N][N], C22[N][N];
    T M1[N][N], M2[N][N], M3[N][N], M4[N][N], M5[N][N], M6[N][N], M7[N][N];
    T AA[N][N], BB[N][N];

    if (n == 2) {
        Matrix_Multiply(A, B, C);
    } else {
        int i, j;

        for (i = 0; i < n / 2; ++i) {
            for (j = 0; j < n / 2; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n / 2];
                A21[i][j] = A[i + n / 2][j];
                A22[i][j] = A[i + n / 2][j + n / 2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n / 2];
                B21[i][j] = B[i + n / 2][j];
                B22[i][j] = B[i + n / 2][j + n / 2];
            }
        }

        // Calculate M1
        Matrix_Add(n / 2, A11, A22, AA);
        Matrix_Add(n / 2, B11, B22, BB);
        Strassen(n / 2, AA, BB, M1);

        // Calculate M2
        Matrix_Add(n / 2, A21, A22, AA);
        Strassen(n / 2, AA, B11, M2);

        // Calculate M3
        Matrix_Sub(n / 2, B12, B22, BB);
        Strassen(n / 2, A11, BB, M3);

        // Calculate M4
        Matrix_Sub(n / 2, B21, B11, BB);
        Strassen(n / 2, A22, BB, M4);

        // Calculate M5
        Matrix_Add(n / 2, A11, A12, AA);
        Strassen(n / 2, AA, B22, M5);

        // Calculate M6
        Matrix_Sub(n / 2, A21, A11, AA);
        Matrix_Add(n / 2, B11, B12, BB);
        Strassen(n / 2, AA, BB, M6);

        // Calculate M7
        Matrix_Sub(n / 2, A12, A22, AA);
        Matrix_Add(n / 2, B21, B22, BB);
        Strassen(n / 2, AA, BB, M7);

        // Calculate C11
        Matrix_Add(n / 2, M1, M4, AA);
        Matrix_Sub(n / 2, M7, M5, BB);
        Matrix_Add(n / 2, AA, BB, C11);

        // Calculate C12
        Matrix_Add(n / 2, M3, M5, C12);

        // Calculate C21
        Matrix_Add(n / 2, M2, M4, C21);

        // Calculate C22
        Matrix_Sub(n / 2, M1, M2, AA);
        Matrix_Add(n / 2, M3, M6, BB);
        Matrix_Add(n / 2, AA, BB, C22);

        for (i = 0; i < n / 2; ++i) {
            for (j = 0; j < n / 2; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + n / 2] = C12[i][j];
                C[i + n / 2][j] = C21[i][j];
                C[i + n / 2][j + n / 2] = C22[i][j];
            }
        }
    }

}

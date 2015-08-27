#include <iostream>

using namespace std;

const int N = 512;

int main()
{
    int A[N][N], B[N][N], C[N][N];
    int i, j, t;

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            A[i][j] = i * j;
            B[i][j] = i * j;
        }
    }
    

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (t = 0; t < N; ++t) {
                C[i][j] += A[i][t] * B[t][j];
            }
        }
    }
    
    cout << "Matrix multiply output: " << endl;
    /*
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    */
    return 0;
}

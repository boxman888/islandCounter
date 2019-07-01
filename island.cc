#include <iostream>
#include <string.h>

/*
 * @params Mp, address of matrix.
 * @params visited, address of visited cells.
 * @params m, current row position being checked.
 * @params n, current column position being checked.
 * @params row, row size of matrix.
 * @params col, column size of matrix.
*/
int legal_move(int** Mp, int** visited, int m, int n, const int row, const int col)
{
    if ((m >=0 && m < row) && (n >= 0 && n < col) && Mp[m][n] &&!visited[m][n])
        return 1;
    else
        return 0;
}
/*
 * @params Mp, address of matrix.
 * @params visited, address of visited cells.
 * @params m, current row position being checked.
 * @params n, current column position being checked.
 * @params row, row size of matrix.
 * @params col, column size of matrix.
*/
void DFS(int** Mp, int** visited, int m, int n, const int row, const int col)
{
    visited[m][n] = 1;
    // The possible 8 positions around a single point.
    int rowMV[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colMV[] = {-1, 0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i){
        if (legal_move(Mp, visited, m + rowMV[i], n + colMV[i], row, col)){
            DFS(Mp, visited, m + rowMV[i], n + colMV[i], row, col);
        }
    }

    return;
}
/*
 * @params Mp address of matrix.
 * @params row, row size of matrix.
 * @params col, column size of matrix.
 */
int island_count(int** Mp, const int row, const int col)
{
    int count = 0;
    // Allocate memory for visited state.
    int** visited = new int*[row];
    std::cout << "Building visited memory." << '\n';
    for (int i = 0; i < row; ++i){
        visited[i] = new int [col];
        // Set all values to zero.
        memset(visited[i], 0, sizeof(int) * col);
    }
    std::cout << "Finished building visited memory." << '\n';
    // Iterativly call depth first search on the matrix.
    for (int m = 0; m < row; ++m){
        for (int n = 0; n < col; ++n){
            if (!visited[m][n] && Mp[m][n]){
                DFS(Mp, visited, m, n, row, col);
                ++count;
            }
        }
    }

    for (int i = 0; i < row; ++i)
        delete[] visited[i];
    delete[] visited;

    return count;
}

int main()
{
    const int row = 5;
    const int col = 5;
    int** Mp = NULL;

    int M[5][5] = {{ 1, 1, 0, 0, 0},
                   { 1, 0, 0, 0, 1},
                   { 0, 0, 0, 0, 0},
                   { 1, 0, 0, 0, 1},
                   { 1, 1, 0, 0, 1}};

    std::cout << "Starting Count" << '\n';
    // Will be accessing 2d map indirectly.
    Mp = new int*[row];
    for (int i = 0; i < row; ++i)
        Mp[i] = M[i];

    // Count islands.
    std::cout << "Island Count: " << island_count(Mp, row, col) << '\n';

    delete[] Mp;
    Mp = NULL;

    return 0;
}

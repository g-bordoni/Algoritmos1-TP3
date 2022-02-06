#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

int return_previous_path(int *line, int x_index, int M){
    int start = (x_index - 1 >= 0)? x_index - 1: 0;
    int end = (x_index + 1 < M)? x_index + 1: M-1;

    int max = -1;
    for(int k=start; k<=end; k++){
        if (max < line[k])
            max = line[k];
    }
    return max;
}

int get_step(int* line, int x_index, int M){
    int start = (x_index - 1 >= 0)? x_index - 1: 0;
    int end = (x_index + 1 < M)? x_index + 1: M-1;

    int max = -1;
    int index = -1;
    for(int k=start; k<=end; k++){
        if (max < line[k]){
            max = line[k];
            index = k;
        }
    }
    return index;

}



int main (int argc, char* argv[])
{
    std::string data;

    std::cin >> data;
    int N = stoi(data);
    std::cin >> data;
    int M = stoi(data);

    int matrix[N][M];
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            std::cin >> data;
            matrix[i][j] = stoi(data);
        }
    }

    int matrix_solution[N][M];
    for(int k = 0; k<M; k++)
        matrix_solution[0][k] = matrix[0][k];

    for(int i = 1; i<N; i++){
        for(int j = 0; j<M; j++){
            matrix_solution[i][j] = matrix[i][j] + return_previous_path(matrix_solution[i-1], j, M);
        }
    }

    
    int index = -1;
    int maximum = -1;
    for(int j = 0; j<M; j++){
        if (maximum < matrix_solution[N-1][j]){
            maximum = matrix_solution[N-1][j];
            index = j;
        }
    }
    int path[N];
    path[N-1] = index;
    for(int i = N-2; i>=0; i--){
        path[i] = get_step(matrix_solution[i], path[i+1], M);
    }   

    std::cout << std::endl <<  maximum << std::endl;
    for(int i = 0; i<N; i++){
        std::cout << path[i] << " ";
    }  
    return 0;
}
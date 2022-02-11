#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

int get_value_of_the_best_path_from_the_previous_line(int *previous_line, int current_position_index, int M){
    int start = (current_position_index - 1 >= 0)? current_position_index - 1: 0;
    int end = (current_position_index + 1 < M)? current_position_index + 1: M-1;

    int better_value = -1;
    for(int k=start; k<=end; k++){
        if (better_value < previous_line[k])
            better_value = previous_line[k];
    }
    return better_value;
}

int get_step_line_index_of_the_better_path(int* line, int current_position_index, int M){
    int start = (current_position_index - 1 >= 0)? current_position_index - 1: 0;
    int end = (current_position_index + 1 < M)? current_position_index + 1: M-1;

    int better_value = -1;
    int better_value_index_position = -1;
    for(int k=start; k<=end; k++){
        if (better_value < line[k]){
            better_value = line[k];
            better_value_index_position = k;
        }
    }
    return better_value_index_position;
}


int main (int argc, char* argv[])
{
    std::string data;

    std::cin >> data;
    int N = stoi(data);
    std::cin >> data;
    int M = stoi(data);

    int input_problem_matrix[N][M];
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            std::cin >> data;
            input_problem_matrix[i][j] = stoi(data);
        }
    }

    int better_path_aggregate_value_matrix[N][M];
    for(int k = 0; k<M; k++)
        better_path_aggregate_value_matrix[0][k] = input_problem_matrix[0][k];

    for(int i = 1; i<N; i++){
        for(int j = 0; j<M; j++){
            better_path_aggregate_value_matrix[i][j] = input_problem_matrix[i][j] + get_value_of_the_best_path_from_the_previous_line(better_path_aggregate_value_matrix[i-1], j, M);
        }
    }

    
    int better_path_end_index = -1;
    int better_path_value = -1;
    for(int j = 0; j<M; j++){
        if (better_path_value < better_path_aggregate_value_matrix[N-1][j]){
            better_path_value = better_path_aggregate_value_matrix[N-1][j];
            better_path_end_index = j;
        }
    }
    int better_path[N];
    better_path[N-1] = better_path_end_index;
    for(int i = N-2; i>=0; i--){
        better_path[i] = get_step_line_index_of_the_better_path(better_path_aggregate_value_matrix[i], better_path[i+1], M);
    }   

    std::cout << better_path_value << std::endl;
    for(int i = 0; i<N; i++){
        std::cout << better_path[i];
        if (i != N-1)
            std::cout << " ";
    } 

    return 0;
}
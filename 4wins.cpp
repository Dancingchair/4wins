#include <iostream>
#include <vector>
#include "4wins_grid.cpp"

void print_grid(){
    std::cout << "\ncurrent game status: " << std::endl;
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 7; ++j){
            std::cout << grid(i, j) << " ";
        }
    std::cout << std::endl;
    }
}

bool player_won_2(char player, int row, int col){
    
    //row and col are given -> we know which field the players mark got set in.

    //HORIZONTAL:
    int count_icon = 1;
    int i = 1;

    //left
    while(true){
        if((col - i) < 0){
            break;
        }
        if(grid(row, col - i) != player){
            break;
        }
        count_icon++;
        i++;
    }

    //right
    i = 1;
    while(true){
        if((col + i) >= 7){
            break;
        }
        if(grid(row, col + i) != player){
            break;
        }
        count_icon++;
        i++;
    }

    //check if win condition is true
    if(count_icon == 4){
        return true;
    }

    //VERTICAL:
    count_icon = 1;
    i = 1;

    //downwards
    while(true){
        if((row + i) >= 6){
            break;
        }
        if(grid(row + i, col) != player){
            break;
        }
        count_icon++;
        i++;
    }

    //upwards
    i = 1;
    while(true){
        if((row - i) < 0){
            break;
        }
        if(grid(row - i, col) != player){
            break;
        }
        count_icon++;
        i++;
    }

    //check if win condition is true
    if(count_icon == 4){
        return true;
    }

    //DIAGONALLY
    count_icon = 1;

    //upwards & right
    i = 1;
    while(true){
        if((col + i) >= 7 || (row + i) >= 6){
            break;
        }
        if(grid(row + i, col + i) != player){
            break;
        }
        count_icon++;
        i++;
    }

    //downwards & left
    i = 1;
    while(true){
        if((col - i) < 0 || (row - i) < 0){
            break;
        }
        if(grid(row - i, col - i) != player){
            break;
        }
        count_icon++;
        i++;
    }

    //check if win condition is true
    if(count_icon == 4){
        return true;
    }
return false;
}

bool column_available(int column_chosen){
    if(column_chosen >= 7 || column_chosen < 0){
        std::cout << "\n this column is out of grid.. use your brain and select a valid column!" << std::endl;
        return false;
    }
    if(grid(0, column_chosen) != '_'){
        std::cout << "This column is already full. Please chose another column." << std::endl;
        return false; 
    }
    return true;
}

bool turn_player(char player){
    restart_turn_player:

    //select column
    std::cout << "\nPlease select column: ";
    int column_chosen;
    std::cin >> column_chosen;
    if(!column_available(column_chosen)){
        goto restart_turn_player;
    }
    //determine which row & fill in the players icon.
    for(int row =  5; row >= 0; --row){
        if(grid(row, column_chosen) == '_'){
            grid(row, column_chosen) = player;
            if(player_won_2(player, row, column_chosen)){
                return true;
            }
            break;
        }
    }
    return false;
}

void win_sequence(char player){
    print_grid();
    std::cout << "------------------------------------" << std::endl;
    std::cout << "||||*** Player " << player << " won! ***||||" << std::endl;
    std::cout << "------------------------------------" << std::endl;   
}

bool grid_full(){
    bool full = true;
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 7; ++j){
            if(grid(i, j) == '_'){
                full = false;
                return false;
            }
        }
    }
    return full;

}

void grid_full_sequence(){
    std::cout << "------------------------------------" << std::endl;
    std::cout << "        grid is full -> DRAW        " << std::endl;
    std::cout << "------------------------------------" << std::endl; 
}


bool replay(){
    std::cout << "Do you want to play another game (y / n) ? ";
    char answer;
    std::cin >> answer;
    if(answer == 'y'){
        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 7; ++j){
                grid(i, j) = '_';
            }
        }
        return true;
    } else if(answer == 'n'){
        std::cout << "\nAllright. Goodbye!" << std::endl;
        return false;
    } else {
        std::cout << "\nInvalid answer, please repeat." << std::endl;
        replay();
    }
}


int main(){

// idea:
// create 4x4 field using vectors or arrays
// implement adaptivity of field
//  - show wether filling your chip into a chosen row is possible or not
//  - maybe print grid?
// implement alternating turns
// implement win conditions
// implement replay option


bool restart = false;
do {
    

    while(!grid_full()){
        
        print_grid();

        //turn_player('X');
        //print_grid();
        if(turn_player('X')){
            win_sequence('X');
            if(!replay()){
                return 0;
            } else {
                restart = true;
                continue;
            }
        } else if(grid_full()){
            grid_full_sequence();
            if(!replay()){
                return 0;
            } else {
                restart = true;
                continue;
            }
        }

        //turn_player('O');
        print_grid();

        if(turn_player('O')){
            win_sequence('O');
            if(!replay()){
                return 0;
            } else {
                restart = true;
                continue;
            }  
        } else if(grid_full()){
            grid_full_sequence();
            if(!replay()){
                return 0;
            } else {
                restart = true;
                continue;
            }
        }
    }
} while(restart);


std::cout << "\n \nEnd of program." << std::endl;
return 0;
}
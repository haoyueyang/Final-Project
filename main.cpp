#include <iostream>
#include "Game.h"

int main() {
    int row;
    int col;
    char move;
    char play_again;
    bool failed = false;
    bool again = true;
    while(again == true){
        
        std::cout << "Hello! Welcome to the Game 2048!" << std::endl;
        
        Game game = Game();
        game.print();
        
        while(!failed){
            std::cout << "Would you like to go up (u)/ down(d)/ left(l) / right(r)?" ;
            std::cin >> move;
            
            game.take_input(move);
            game.move();
            game.new_entry();
            
            game.print();
            
            failed = game.check_failed();
        }
        
        std::cout << "Game Over!" << std::endl;
        std::cout << "Would you like to play again? (Y/N)" << std::endl;
        std::cin >> play_again;
        if(play_again == 'N'){
            again = false;
        }
    }

    return 0;
}

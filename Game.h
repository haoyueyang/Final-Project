#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "matrix.h"

class Game{
    
public:
    Game();
    
    void print();
    void take_input(char move);
    
    void addup();
    void adddown();
    void addleft();
    void addright();
    
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
    

    void move();
    
    int max_value();
    void new_entry();
    
    
    void entry_add(int row1, int col1, int row2, int col2);
    bool check_failed();
    
private:
    // Parameters
    Matrix<int, 16> m;
    int move_;
    
    // private functions
    int rand_entry();
    
};


#endif

#include "Game.h"
#include <vector>
#include <cmath>

Game::Game(){
    // Construct an empty matrix
    m = Matrix<int,16>(4,4);
    
    // Randomly select two entries to generate the number 2
    int x_r = rand_entry();
    int x_c = rand_entry();
    int y_r = rand_entry();
    int y_c = rand_entry();
    
    while(y_c==x_c && y_r == x_r){
        y_r = rand_entry();
        y_c = rand_entry();
    }
    
    m(x_r,x_c) = 2;
    m(y_r,y_c) = 2;
    
}

void Game::print(){
    m.print();
}

void Game::take_input(char move){
    if(move == 'u'){
        move_ =1;
    }
    else if(move == 'd'){
        move_ =2;
    }
    else if(move == 'l'){
        move_ =3;
    }
    else if(move == 'r'){
        move_ =4;
    }

}


void Game::addup(){
    for(size_t j = 0; j < 4; ++j){
        auto begin = m.col_begin(j);
        auto end = m.col_end(j);
        auto it = m.find_nonzero_bycol(begin, end);
        
        while(it!=end){

            auto it1 = it;
        
            auto it2 = m.find_nonzero_bycol(++it, end);
        
            if(*it1 == *it2){
                *it1 = *it1+*it2;
                *it2 = 0;
            }
            
            if(it2 == end){
                continue;
            }
            ++it;
        }
    }
}

void Game::moveup(){
    for(size_t j = 0; j < 4; ++j){
        auto begin = m.col_begin(j);
        auto end = m.col_end(j);
        
        auto it = m.find_nonzero_bycol(begin, end);
        auto zero = m.find_value(begin, end,0);
        size_t zero_row = zero.get_row_index();
        size_t it_row = it.get_row_index();
        
        if(zero == end){
            continue;
        }
        
        while(it != end){
            if(zero_row < it_row){
                m(zero_row,j) = *it;
                m(it_row,j) = 0;
                it = m.find_nonzero_bycol(++it,end);
                zero = m.find_value(++zero,end,0);
            }

            else if(zero_row > it_row){
                it = m.find_nonzero_bycol(++it,end);
            }
            zero_row = zero.get_row_index();
            it_row = it.get_row_index();
        }
        
        if(it == end){
            m(zero_row,j) = *it;
            m(it_row,j) = 0;
        }
    }    
}

void Game::adddown(){
    for(size_t j = 0; j < 4; ++j){
        auto begin = m.col_begin(j);
        auto end = m.col_end(j);
        auto it = m.find_bycol_rev(begin, end);
        
        while(it!=begin){
            
            auto it1 = it;
            
            auto it2 = m.find_bycol_rev(begin, --it);
            
            if(*it1 == *it2){
                *it1 = *it1+*it2;
                *it2 = 0;
            }
            
            if(it2 == begin){
                continue;
            }
            ++it;
        }
    }
}

void Game::movedown(){
    for(size_t j = 0; j < 4; ++j){
        auto begin = m.col_begin(j);
        auto end = m.col_end(j);
        
        auto it = m.find_bycol_rev(begin, end);
        auto zero = m.find_value_reverse(begin, end,0);
        size_t zero_row = zero.get_row_index();
        size_t it_row = it.get_row_index();
        
        if(zero == begin){
            continue;
        }
        
        while(it != begin){
            if(zero_row > it_row){
                m(zero_row,j) = *it;
                m(it_row,j) = 0;
                it = m.find_bycol_rev(begin,--it);
                zero = m.find_value_reverse(begin,--zero,0);
            }
            
            else if(zero_row < it_row){
                it = m.find_bycol_rev(begin,--it);
            }
            zero_row = zero.get_row_index();
            it_row = it.get_row_index();
        }
        
        if(it == begin){
            m(zero_row,j) = *it;
            m(it_row,j) = 0;
        }
    }    
}

void Game::addleft(){
    for(size_t i = 0; i < 4; ++i){
        auto begin = m.row_begin(i);
        auto end = m.row_end(i);
        auto it = m.find_nonzero_byrow(begin, end);
        
        while(it!=end){
            
            auto it1 = it;
            
            auto it2 = m.find_nonzero_byrow(++it, end);
            
            if(*it1 == *it2){
                *it1 = *it1+*it2;
                *it2 = 0;
            }
            
            if(it2 == end){
                continue;
            }
            ++it;
        }
    }
}


void Game::moveleft(){
    for(size_t i = 0; i < 4; ++i){
        auto begin = m.row_begin(i);
        auto end = m.row_end(i);
        
        auto it = m.find_nonzero_byrow(begin, end);
        auto zero = m.find_value(begin, end,0);
        size_t zero_col = zero.get_col_index();
        size_t it_col = it.get_col_index();
        
        if(zero == end){
            continue;
        }
        
        while(it != end){
            if(zero_col < it_col){
                m(i,zero_col) = *it;
                m(i,zero_col) = 0;
                it = m.find_nonzero_byrow(++it,end);
                zero = m.find_value(++zero,end,0);
            }
            
            else if(zero_col> it_col){
                it = m.find_nonzero_byrow(++it,end);
            }
            zero_col = zero.get_col_index();
            it_col = it.get_col_index();
        }
        
        if(it == end){
            m(i,zero_col) = *it;
            m(i,it_col) = 0;
        }
    }    

}

void Game::addright(){
    for(size_t i = 0; i < 4; ++i){
        auto begin = m.row_begin(i);
        auto end = m.row_end(i);
        auto it = m.find_byrow_rev(begin, end);
        
        while(it!=begin){
            
            auto it1 = it;
            
            auto it2 = m.find_byrow_rev(begin, --it);
            
            if(*it1 == *it2){
                *it1 = *it1+*it2;
                *it2 = 0;
            }
            
            if(it2 == begin){
                continue;
            }
            ++it;
        }
    }
}



void Game::moveright(){
    for(size_t i = 0; i < 4; ++i){
        auto begin = m.row_begin(i);
        auto end = m.row_end(i);
        
        auto it = m.find_byrow_rev(begin, end);
        auto zero = m.find_value_reverse(begin, end,0);
        size_t zero_col = zero.get_col_index();
        size_t it_col = it.get_col_index();
        
        if(zero == begin){
            continue;
        }
        
        while(it != begin){
            if(zero_col > it_col){
                m(i,zero_col) = *it;
                m(i,it_col) = 0;
                it = m.find_bycol_rev(begin,--it);
                zero = m.find_value_reverse(begin,--zero,0);
            }
            
            else if(zero_col < it_col){
                it = m.find_byrow_rev(begin,--it);
            }
            zero_col = zero.get_col_index();
            it_col = it.get_col_index();
        }
        
        if(it == begin){
            m(i,zero_col) = *it;
            m(i,it_col) = 0;
        }
    }

}

void Game::move(){
    if(move_ == 1){
        addup();
        moveup();
    }
 
    else if(move_ == 2){
        adddown();
        movedown();
    }
    
    else if(move_ == 3){
        addleft();
        moveleft();
    }
    else{
        moveleft();
        moveright();
    }
}

int Game::max_value(){
    int max = m(0,0);
    for(size_t i = 0; i < 4; ++i){
        for(size_t j = 0; j < 4; ++j){
            if(max < m(i,j)) {
                max = m(i,j);
            }
        }
    }
    return max;
}

void Game::new_entry(){
    int max = max_value();
    int x_r = rand_entry();
    int x_c = rand_entry();
    while(m(x_r,x_c) != 0){
        x_r = rand_entry();
        x_c = rand_entry();
    }
    int power = std::log2(max);
    int random = rand()%power+1;
    m(x_r,x_c) = std::pow(2,(random));
}



bool Game::check_failed(){
    // Check if fully occupied
    for(size_t i = 0; i < 4; ++i){
        for(size_t j = 0; j < 4; ++j){
            if(m(i,j) == 0){
                return false;
            }
        }
    }
    
    bool failed = true;
    
    // Check rows
    for(size_t i = 0; i < 4; ++i){
        for(size_t j = 0; j < 3; ++j){
            if(m(i,j) == m(i,j+1))
                failed = false;
        }
    }
    
    // Check columns
    for(size_t i = 0; i < 3; ++i){
        for(size_t j = 0; j < 4; ++j){
            if(m(i,j) == m(i+1,j))
                failed = false;
        }
    }
    return failed;
}

int Game::rand_entry(){
    int x = rand()%4;
    return x;
}

#include "matrix.h"

Matrix<ItemType, MAX_SIZE>::Matrix(): rows_(1),cols(1){
    allocSpace();
    arr[0][0] = 0;
}

Matrix<ItemType, MAX_SIZE>::Matrix(size_t r, size_t c):rows_(r),cols_(c){
    allocSpace();
    for(int i = 0; i < rows_; ++i){
        for(int j = 0; )
    }
    
}



void Matrix<ItemType, MAX_SIZE>::allocSpace(){
    arr = new double*[rows_];
    for(int i = 0; i < rows_; ++i){
        arr[i] = new double[cols];
    }
}


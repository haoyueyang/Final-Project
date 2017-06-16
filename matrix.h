#ifndef MATRIX_H
#define MATRIX_H

#include<stddef.h>
template <typename ItemType, int MAX_SIZE>

class Matrix{
  
public:
    class iterator;
    
    typedef ItemType* pointer;
    typedef ItemType& reference;
    
public:
    class iterator{
    private:
        Matrix* parent;
        int posr;
        int posc;
        
    private:
        iterator(Matrix* _parent, int _posr = 0, int _posc = 0)
        : parent(_parent), posr(_posr), posc(_posc){ }
        
        
        friend class Matrix<ItemType, MAX_SIZE>;
        
        
    public:
        reference operator*() {
            return parent(posr, posc);
        }
        
        iterator& operator++(){
            // Replace the line(s) below with your code.
            return *this;
        }
        
        iterator operator++( int unused ){
            // Replace the line(s) below with your code.
            return *this;
        }
        
        bool operator==( const iterator& rhs ) const {
            // Replace the line(s) below with your code.
            return true;
        }
        
        bool operator!=( const iterator& rhs ) const {
            // Replace the line(s) below with your code.
            return true;
        }
    };

    
private:
    ItemType *data;
    size_t rows;
    size_t cols;
    
public:
    // Default constructor
    Matrix(): data(new double[1]), rows(1), cols(1){}

    Matrix(size_t r, size_t c)
    :data(new double[r*c]), rows(r), cols(c){ }
    
    // Copy constructor
    Matrix(const Matrix& b): data(new double[(b.rows)*(b.cols)]), rows(b.rows), cols(b.cols){
        for (size_t i = 0; i < b.rows*b.cols; i++){
            data[i] = b.data[i];
        }
    }
    
    // Move constructor
    Matrix(Matrix&& other){
        data = other.data;
        other.data=nullptr;
        rows = other.rows;
        cols = other.cols;
        other.rows = 0;
        other.cols = 0;
    }
    
    // Destructor
    virtual ~Matrix() {delete[] data;}

    // Operator(i,j)
    ItemType& operator()(size_t i, size_t j){
        return data[i*cols+j];
    };

#endif

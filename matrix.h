#ifndef MATRIX_H
#define MATRIX_H

#include<stddef.h>
#include<algorithm>

// ItemType can either be int or double. We want to save memory if the type double is not needed.
// MAX_SIZE is the capacity of the matrix.
template <typename ItemType, int MAX_SIZE>

class Matrix{
  
public:
    class iterator;
    
    typedef ItemType* pointer;
    typedef ItemType& reference;
    
public:
    class iterator{
    private:
        Matrix* parent_;
        size_t posr_;
        size_t posc_;
        
    private:
        iterator(Matrix* parent, int posr = 0, int posc = 0)
        : parent_(parent), posr_(posr), posc_(posc){ }
        
        
        friend class Matrix<ItemType, MAX_SIZE>;
        
        
    public:
        size_t get_row_index(){
            return posr_;
        }
        
        size_t get_col_index(){
            return posc_;
        }
        
        
        reference operator*() {
            return parent_ -> arr[posr_][posc_];
        }
        
        iterator& operator++(){
            if(parent_->byrow_==true)
                posc_++;
            else{
                posr_++;
            }
            return *this;
        }
        
        iterator& operator--(){
            if(parent_ -> byrow_==true)
                posc_ --;
            else{
                posr_ --;
            }
            return *this;
        }
        
        iterator operator++( int unused ){
            // Replace the line(s) below with your code.
            return *this;
        }
        
        bool operator==( const iterator& rhs ) const {
            if(parent_==(rhs.parent_) && (posr_ == rhs.posr_) && (posc_ == rhs.posc_))
               return true;
            else
               return false;
        }
        
        bool operator!=( const iterator& rhs ) const {
            if(parent_!=rhs.parent_)
                return true;
            if(posr_!=rhs.posr_)
                return true;
            if(posc_!=rhs.posc_)
                return true;
            else
                return false;
        }
    };

    
private:
    // Private parameters
    size_t rows_;
    size_t cols_;
    bool byrow_;
    
    // Private functions
    
    

    // Allocate Space of the Container
    // Implementing try-catch to prevent leaking since this function is to be used in constructors.
    void allocSpace(){
        arr = nullptr;
        try{
            arr = new ItemType*[rows_];
            for(int i = 0; i < rows_; ++i){
                arr[i] = new ItemType[cols_];
            }
        }
        catch(const std::exception& e){
            delete  arr;
            throw;
            }
    }
    
 
    
public:
    // We have the array of pointers public because we want to modify it
    // in the game class later on.
    ItemType **arr;
    
    // Default constructor
    Matrix(): rows_(0),cols_(0), byrow_(true){
        allocSpace();
    }
    
    // Another constructor
    Matrix(size_t r, size_t c):rows_(r),cols_(c), byrow_(true){
        allocSpace();
        for(size_t i = 0; i < rows_; ++i){
            for(size_t j = 0; j < cols_; ++j){
                arr[i][j]=0;
            }
        }
    }
    
    // Copy constructor
    Matrix(const Matrix& b): rows_(b.rows_), cols_(b.cols_),byrow_(true){
        allocSpace();
        for(size_t i = 0; i < b.rows_; i++){
            for(size_t j = 0; j < b.cols_; ++j){
                arr[i][j] = b.arr[i][j];
            }
        }
    }
    
    // Move constructor
    Matrix(Matrix&& other):Matrix(){
        this -> swap(other);
    }

    void swap(Matrix& b){

        std::swap(rows_,b.rows_);
        std::swap(cols_,b.cols_);
        std::swap(arr,b.arr);
        b.print();
    }
    
    // Destructor
    virtual ~Matrix() {
        for(size_t i = 0; i<rows_; ++i){
            delete[] arr[i];
        }
        delete[] arr;
    }
    
    // Operator()
    ItemType& operator()(ItemType x, ItemType y){
        return arr[x][y];
    }
    
    // Operator =
    Matrix& operator=(Matrix other){
        this -> swap(other);
        return *this;
    }
    
    
    void print(){
        for(size_t i=0; i < rows_; ++i){
            for(size_t j=0; j < cols_; ++j){
                std::cout << "|" << arr[i][j];
            }
            std::cout << std::endl;
        }
    }
    
    iterator begin(){
        return iterator(this, 0,0);
    }
    
    iterator end(){
        return iterator(this, (rows_-1), (cols_-1));
    }
    
    iterator row_begin(int row){
        return iterator(this, row, 0);
    }
    
    iterator row_end(int row){
        return iterator(this, row, (cols_-1));
    }
    
    iterator col_begin(int col){
        return iterator(this, 0, col);
    }
    
    iterator col_end(int col){
        return iterator(this, (rows_-1), col);
    }

    iterator find_value(iterator begin, iterator end, const ItemType& value){
        iterator it = std::find(begin, end, value);
        return it;
    }
    
    iterator find_value_reverse(iterator begin, iterator end, const ItemType& value){
        for(; end!= begin; --end){
            if(*end == value){
                break;
            }
        }
        return end;
    }
    
    iterator find_nonzero_reverse(iterator begin, iterator end){
        for(; end != begin; --end){
            if(*end != 0){
                break;
            }
        }
        return end;
    }
    
    iterator find_nonzero_bycol(iterator begin, iterator end){
        byrow_=false;
        iterator it = std::find_if(begin, end, [](ItemType val){
            return val != 0;
        });
        return it;
    }
    

    iterator find_nonzero_byrow(iterator begin, iterator end){
        byrow_ = true;
        iterator it = std::find_if(begin, end, [](ItemType val){
            return val != 0;
        });
        return it;
    }
    
    iterator find_bycol_rev(iterator begin, iterator end){
        byrow_=false;
        iterator it = find_nonzero_reverse(begin,end);
        return it;
    }
    
    iterator find_byrow_rev(iterator begin, iterator end){
        byrow_=true;
        iterator it = find_nonzero_reverse(begin,end);
        return it;
    }
    
    ItemType col_add(size_t row1, size_t row2, size_t col1){
        ItemType result = arr[row1][col1] + arr[row2][col1];
        return result;
    }
    
    ItemType row_add(size_t col1, size_t col2, size_t row1){
        ItemType result = arr[row1][col1] + arr[row1][col1];
        return result;
    }

};


#endif

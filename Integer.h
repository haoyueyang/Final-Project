#ifndef Integer_H
#define Integer_H

class Integer{
    
public:
    // Default constructor--default value is 0
    Integer();
    
    // Constructor assigns a value val to bits_
    Integer(int val);
    
    // Produce a string which contains the bits of
    // the Integer (stored in bits_)
    // @return an std::string in the form (...)_2 where "..." denotes the bits
    // of the Integer
    bool is_zero();
    
    virtual std::string binary_string() const;
    
    // Produce a string which contains the decimal
    // representation of the Integer.
    // @return an std::string in the normal decimal form of the integer
    virtual std::string decimal_string() const;
    
    // Return the number of bits stored in bits_.
    // @return an int containing the number of its in bits_.
    inline int size() const {return bits_.size();
    }
    
    // Return the value of the bit stored at a particular index. If index
    // exceeds the number of bits, get_bit returns "false"
    // @param index is the desired index (an unsigned int)
    // @return the boolean value of bits_[index] if index < bits_.size(), and
    // "false" otherwise.
    bool get_bit(unsigned int index) const;
    
    // Sets the bit at index in bits_ to value. If value exceeds bits_.size(),
    // then value is pushed onto the back of bits_.
    // @param index an unsigned int indicating the desired location
    // @param value is the value to be assigned to bits_[index]
    void set_bit(unsigned int index, bool value);
    
    // Shifts the bits of the Integer one to the left. Equivalently, this
    // operation can be interpreted as multiplying the Integer by 2.
    void left_shift();
    
    // Assigns the value stored in val to this instance of Integer.
    // @param val a reference to the Integer which stores the desired new
    // value
    void set_value(const Integer& val);
    
    // Computes the complement of this Integer by replacing each of its
    // and vice versa.
    void complement();
    
    // Adds the Integer on the right side to the current integer.
    // @param rhs is a pointer to the Integer to be added
    // @return a reference to this integer after addition
    Integer& operator+=(const Integer& rhs);
    
    // Compare the Integer on the right side with the current Integer.
    // @param rhs is a pointer to the Integer to compare
    // @return true if the current Integer is larger than or equal to
    // the Integer on the right side. return false if the current Integer
    // is smaller than the Integer on the right side.
    bool operator >= (Integer rhs);
    
    // Subtracts the Integer on the right side from the current integer. If the
    // value of rhs is larger than this instance, the new value will be the absolute
    // value of the difference. In the following example
    //   Integer a(3);
    //   Integer b(5);
    //   a -= b;
    // the new value of a will be |3 - 5| = 2.
    // @param rhs is a pointer to the Integer to be subtracted
    // @return a reference to this integer after subtraction
    Integer& operator-=(const Integer& rhs);
    
    // Multiplies this Integer by the Integer on the right hand side.
    // @param rhs is a pointer to the Integer to multiply
    // @return a reference to this integer after multiplication
    Integer& operator*=(Integer rhs);
    
    // Divide this Integer by the Integer on the right hand side.
    // @param rhs is a pointer to the Integer to divide
    // @return a reference to this integer after division
    Integer& operator/=(Integer rhs);
    
    // Modulus this Integer by the Integer on the right hand side.
    // @param rhs is a pointer to the Integer to modulus
    // @return a reference to this Integer after modulus
    Integer& operator%=(Integer rhs);
    
    
    // Increment this integer by one (prefix)
    // @return a reference to this integer (after incrementation).
    virtual Integer& operator++();
    
    // Increment this integer by one (postfix)
    // @return a reference which stores the value before incrementation.
    virtual Integer operator++(int unused);
    
    // Decrement this Integer by one (prefix)
    // @return a reference to this Integer (after decrementation).
    virtual Integer& operator--();
    
protected:
    // The bits that store the value of an Integer. Bits are stored
    // from least to most significant.
    std::vector<bool> bits_;
    
private:
    // The "borrow" subroutine used in subtraction. Finds the next position
    // to the "left" of index in bits_ which has a value of 1, decrements this
    // bit, and increments all bits between that position and index. The function
    // returns a bool which tells if the borrowing operation was successful.
    // Note: this function is obsolete because of a new (better) implementation of
    // operator-= and operator-.
    // @param index is the index at which to borrow
    // @retun "true" if the borrow was successful (i.e., there is a 1 to the left
    // of index) and "false" if the borrow was unsuccessful.
    bool borrow(int index);
    
    // Remove the trailing zeros from an Integer. For example,
    // (00010110)_2 should be written as (10110)_2.
    void remove_trailing_zeros();
    
    // Execute division and modulus at the same time.
    // Divide the dividend by the divisor
    // Store the result of division in the vector of quotient
    // Store the result of modulus in the vector of reminder
    void div_mod (Integer dividend, Integer divisor, std::vector<bool>& quotient, std::vector<bool>& reminder);
    
};
// Add two bits b1 and b2, along with a carry bit, for example:
// 0 + 0 + 0 = 0 carry 0 (value is 0)
// 1 + 0 + 0 = 1 carry 0 (value is 1)
// 1 + 1 + 0 = 0 carry 1 (value is 10, must carry the 1)
// 1 + 1 + 1 = 1 carry 1 (value is 11, must carry the 1)
// @param b1 the first bit to be added (stored as a refernce to a  bool)
// @param b2 the second bit to be added
// @param carry the carry bit (a reference to a bool)
void add_with_carry(bool& b1, bool b2, bool& carry);

// Add two integers and return the value of the result.
// @param the left Integer to be added
// @param the right Integer to be added (a reference)
// @return the sum of lhs and rhs.
Integer operator+(Integer lhs, const Integer& rhs);

// Subtract one Integer from another and return the value of the result.
// This function assumes that result is non-negative. If the result is negative,
// the output of the function is unspecified.
// @param the left Integer
// @param the right Integer to be subtracted (a reference)
// @return the difference of lhs and rhs
Integer operator-(Integer lhs, const Integer& rhs);

// Multiply two integers and return the value of the result.
// @param the left Integer to be multiplied
// @param the right Integer to be multiplied (a reference)
// @return the product of lhs and rhs.
Integer operator*(Integer lhs, const Integer& rhs);

// Divide the Integer lhs by the Integer rhs and return the value of the result.
// @param the left Integer to be divided
// @param the right Integer to divide
// @return the quotient
Integer operator/(Integer lhs, const Integer& rhs);

// Modulus the Integer lhs by the Integer rhs and return the value of the result.
// @param the left Integer
// @param the right Integer
// @return the modulus
Integer operator%(Integer lhs, const Integer& rhs);

// Check if two integers have the same value.
// @param the left Integer
// @param the right Integer
// @return a bool which is true if and only if lhs and rhs store the same value
bool operator==(const Integer& lhs, const Integer& rhs);

class SignedInteger : public Integer {
public:
    // Default constructor, the value is 0, the sign is positive
    SignedInteger(): Integer(), sign_(true) { };
    
    // Constructor assign the value val to bits_
    // and store the sign of the Integer in a bool.
    SignedInteger(int val);
    
    // Produce a string which contains the sign and bits of
    // the SignedInteger (stored in bits_)
    // @return an std::string in the form (+ or -)(...)_2 where
    // + or - denotest the sign and "..." denotes the bits
    // of the Integer
    virtual std::string binary_string() const;
    
    // Produce a string which contains the decimal
    // representation of the SignedInteger.
    // @return an std::string in the normal decimal form of the integer
    virtual std::string decimal_string() const;
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // All the functions below are constructed based on the counterparts in the Integer class
    // and they work the exactly same way as in the Integer class
    // In addition, the operators are able to execute operations
    // on both positive and negative integers.
    ////////////////////////////////////////////////////////////////////////////////////////
    
    SignedInteger& operator+=(const SignedInteger& rhs);
    SignedInteger& operator-=(const SignedInteger& rhs);
    SignedInteger& operator*=(SignedInteger rhs);
    SignedInteger& operator/=(SignedInteger rhs);
    SignedInteger& operator%=(SignedInteger rhs);
    
    virtual SignedInteger& operator++();
    virtual SignedInteger& operator--();
    
private:
    // Store the sign of the integer as a bool.
    // Sign of the integer is true if it's positive, and false if it's negative.
    bool sign_;
    
};

SignedInteger operator+(SignedInteger lhs, const SignedInteger& rhs);
SignedInteger operator-(SignedInteger lhs, const SignedInteger& rhs);
SignedInteger operator*(SignedInteger lhs, const SignedInteger& rhs);
SignedInteger operator/(SignedInteger lhs, const SignedInteger& rhs);
SignedInteger operator%(SignedInteger lhs, const SignedInteger& rhs);

std::ostream& operator<< (std::ostream& os, const Integer& val);
std::istream& operator>> (std::istream& is, Integer& val);
std::ostream& operator<< (std::ostream& os, const SignedInteger& val);
std::istream& operator>> (std::istream& is, SignedInteger& val);


#endif

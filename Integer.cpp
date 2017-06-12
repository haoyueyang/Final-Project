#include "Integer.h"
#include <string>
#include <iostream>
#include <cmath>

Integer::Integer() {
    bits_.push_back(false);
}

Integer::Integer(int val) {
    
    // If val is 0, bits_ should be {false}
    if(val == 0) {
        bits_.push_back(false);
        return;
    }
    
    // Read the bits of val by repeatedly dividing by 2 and checking the
    // remainder % 2. Push bits to bits_.
    while(val != 0) {
        bits_.push_back(val % 2 != 0);
        val /= 2;
    }
}

bool Integer::is_zero() {
    bool is_zero = false;
    
    if(bits_.size() == 1 && bits_[0] == false)
        is_zero = true;
    
    return is_zero;
}

std::string Integer::binary_string() const {
    
    std::string str_bits = ""; // the bits stored as a string
    
    // str_bits starts with (
    str_bits = '(';
    
    
    char bit; // a single bit to append to str_bits
    
    // append the bits of bits_ to str_bits... notice that the
    // bits_[0] is the least signifcant bit, so it should be
    // printed last, bits_[1] should be second-to-last, etc.
    for(int i = bits_.size() - 1; i >= 0; --i) {
        bit = bits_[i] ? '1' : '0';
        str_bits += bit;
    }
    
    // str_bits ends with )_2
    str_bits += ")_2";
    
    return str_bits;
}

std::string Integer::decimal_string() const {
    
    std::vector<int> decimal; // the vector stores the decimal bits of the integer
    std::string result;       // the result stores the bits as a string
    int total= 0;             // total stores the value of the integer
    char digit;               // digit stores each digit of the integer in a char
    
    for(int i = 0; i < bits_.size(); ++i)  // add up the total decimal value of the integer
        total += bits_[i] * pow(2, i);
    
    if(total == 0)            // If total is zero, simply append 0 to the decimal vector.
        decimal.push_back(0);
    
    while(total != 0) {       // Store the integer in a vector of ints in decimal form.
        decimal.push_back(total % 10);
        total /= 10;
    }
    
    for(int i = decimal.size()-1; i >=0; --i) {   // Convert the ints in the vector to chars
        digit = '0' + decimal[i];                 // and store them in a string.
        result += digit;
    }
    return result;
}

bool Integer::get_bit(unsigned int index) const {
    if(index < bits_.size())
        return bits_[index];
    
    return false;
}

void Integer::set_bit(unsigned int index, bool value) {
    
    if(index < bits_.size()) {
        
        bits_[index] = value;
        
    } else {
        
        bits_.push_back(value);
        
    }
}

void Integer::left_shift() {
    
    // push "false" to the first position of bits_
    bits_.insert(bits_.begin(), false);
    
}

// "set_value" could be made more efficient by
// updating values of bits_ rather than always deleting values,
// then pushing new values.
void Integer::set_value(const Integer& val) {
    // the size of this instance
    int max_index = size() - 1;
    
    // remove everything from bits_
    for(int i = 0; i <= max_index; ++i) {
        bits_.pop_back();
    }
    
    max_index = val.size() - 1;
    
    // add the bits from val to bits_
    for(int i = 0; i <= max_index; ++i) {
        bits_.push_back(val.get_bit(i));
    }
}

void Integer::complement() {
    int size = bits_.size();
    
    // Flip each bit of bits_
    for(int i = 0; i < size; ++i) {
        bits_[i] = !bits_[i];
    }
    
    // Make sure there aren't any trailing zeros.
    remove_trailing_zeros();
}

bool Integer:: operator >=(Integer rhs) {
    remove_trailing_zeros();             // Remove all the trailing 0s to ensure integers have smallest sizes.
    rhs.remove_trailing_zeros();
    
    if(bits_.size() > rhs.size())        // If the size of one integer is larger than another
        return true;                     // the integer is larger.
    else if(bits_.size() < rhs.size())
        return false;
    else{   // Compare each digits of the two integers from the most significant digit.
        
        // loop through the bits_ values of the instance and compare each bit with rhs.
        for(int i = bits_.size() -1; i >=0; --i){    // If lhs has a 1 in a digit when rhs has a 0
            if(bits_[i] < rhs.bits_[i])              // return true.
                return false;
            else if(bits_[i] > rhs.bits_[i])
                return true;
        }
        return true;
    }
}

Integer& Integer::operator+=(const Integer& rhs) {
    int lhs_max_index = bits_.size() - 1;
    int rhs_max_index = rhs.size() - 1;
    
    // max_index is the larger of the maximum indices of this instance and rhs
    int max_index = (lhs_max_index > rhs_max_index) ? lhs_max_index : rhs_max_index;
    
    // the carry bit from adding bits
    bool carry = false;
    
    // the current bits from lhs and rhs, respectively
    bool cur_lhs_bit, cur_rhs_bit;
    
    
    // Loop through the bit values of this instance and rhs and add bits
    // in each position, along with the carry bit from adding at the previous
    // index.
    for(int i = 0; i <= max_index; ++i) {
        cur_lhs_bit = get_bit(i);
        cur_rhs_bit = rhs.get_bit(i);
        
        add_with_carry(cur_lhs_bit, cur_rhs_bit, carry);
        
        set_bit(i, cur_lhs_bit);
    }
    
    // If there is a carry bit after adding all bits, append it to the end of bits_
    if(carry) {
        bits_.push_back(carry);
    }
    
    return *this;
}
Integer& Integer::operator-=(const Integer& rhs) {
    
    // if this and rhs have the same value, set this one to 0
    if((*this) == rhs) {
        Integer zero(0);
        set_value(zero);
        
        return *this;
    }
    
    int lhs_max_index = bits_.size() - 1;
    int rhs_max_index = rhs.size() - 1;
    
    // max_index is the larger of the maximum indices of this instance and rhs
    int max_index = (lhs_max_index > rhs_max_index) ? lhs_max_index : rhs_max_index;
    
    // the carry bit from adding bits
    bool carry = false;
    
    // the current bits from lhs and rhs, respectively
    bool cur_lhs_bit, cur_rhs_bit;
    
    
    // Loop through the bit values of this instance and rhs and add bits
    // in each position, along with the carry bit from adding at the previous
    // index.
    for(int i = 0; i <= max_index; ++i) {
        cur_lhs_bit = get_bit(i);
        cur_rhs_bit = rhs.get_bit(i);
        
        // Note that we add the complement to cur_rhs_bit!
        add_with_carry(cur_lhs_bit, !cur_rhs_bit, carry);
        
        set_bit(i, cur_lhs_bit);
    }
    
    // If there is a carry bit after adding all bits, ignore it, and increment
    if(carry) {
        
        // This code gets called if the difference is positive
        this -> Integer::operator++();
        
        remove_trailing_zeros();
        
    } else {
        
        // This code gets called if the difference is negative
        complement();
        
    }
    
    return *this;
}


Integer& Integer::operator*=(Integer rhs) {
    
    // If rhs is 0, set the value to 0 (= rhs)
    if(rhs.size() == 1 && rhs.get_bit(0) == false) {
        set_value(rhs);
    }
    
    
    Integer new_value(0); // the new value (after multiplication)
    
    int max_index = bits_.size() - 1;
    
    // Loop through each bit of this instance and add the corresponding
    // "shifts" of rhs to new_value. For example, if we see a 1 in the k-th
    // bit of this instance, add the k-th shift of rhs to new_value.
    for(int i = 0; i <= max_index; ++i) {
        
        if(bits_[i]) {
            new_value.Integer::operator += (rhs);
        }
        
        rhs.left_shift();
    }
    
    // Assign this instance the value of new_value.
    set_value(new_value);
    
    return *this;
}


Integer& Integer::operator/=(Integer rhs){
    std::vector<bool> quotient;
    std::vector<bool> reminder;
    
    if(rhs == Integer(0))     // If divisor is 0, the operation is illegal. cout error to the console.
        std::cout << "Division by 0 error!" << std::endl;
    
    else {
        div_mod(*this, rhs, quotient, reminder);
        bits_ = quotient;
        
        remove_trailing_zeros();
    }
    return *this;
}

Integer& Integer::operator%=(Integer rhs){
    std::vector<bool> quotient;
    std::vector<bool> reminder;
    
    if(rhs == Integer(0))
        std::cout << "Modulus by 0 error!" << std::endl;
    
    else {
        div_mod(*this, rhs, quotient, reminder);
        bits_ = reminder;
        
        remove_trailing_zeros();
    }
    return *this;
}

Integer& Integer::operator++() {
    // Create an Integer "one" with value 1
    Integer one(1);
    
    // Add "one" to this instance.
    Integer::operator+=(one);
    
    return *this;
}

Integer Integer::operator++(int unused) {
    // Make a copy of this Integer
    Integer copy(*this);
    
    // Increment this version
    this -> Integer::operator++();
    
    // Return the copy containing the previous version
    return copy;
}

Integer& Integer::operator--(){
    Integer one(1);   // Creat an Integer "one" with value 1
    Integer::operator-=(one);  // Subtract 1 from the instance
    
    return *this;
}

bool Integer::borrow(int index) {
    int i = index + 1;
    int max_index = bits_.size() - 1;
    
    // Find the next value 1 ("true") in bits_ larger than index
    while(i <= max_index && !bits_[i]) {
        ++i;
    }
    
    // If on such value 1 exists, return false
    if(i > max_index)
        return false;
    
    // Otherwise set the value at i to false...
    bits_[i] = false;
    
    
    // ...and set all values of bits_[j] with j between index and i
    // to 1 ("true")
    --i;
    
    for(; i >= index; --i) {
        bits_[i] = true;
    }
    
    return true;
}

void Integer::remove_trailing_zeros() {
    
    int i = bits_.size() - 1;
    
    // Starting from the largest index in bits_, pop_back values until
    // we see the first 1 ("true")
    while((i > 0) && !bits_[i]) {
        bits_.pop_back();
        --i;
    }
    
    // If bits_ is empty, push a 0 ("false") onto bits_
    if(bits_.size() == 0) {
        bits_.push_back(false);
    }
}

void Integer::div_mod (Integer dividend, Integer divisor, std::vector<bool>& quotient, std::vector<bool>& reminder){
    
    Integer current(0);
    int dvd_size = dividend.size(), dsr_size = divisor.size();
    
    if (divisor == Integer(0)){            // If divisor is 0, the division and modulus operation is illegal
        return;                            // We deal with this situation in the operator /= and %=
    }                                      // Here we directly returns nothing.
    
    else if (dividend == divisor) {        // If dividend is equal to divisor
        quotient.push_back(true);          // Simply make quotient 1 and remider 0.
        reminder.push_back(false);
    }
    
    else if (!(dividend >= divisor))       // If dividend is smaller than divisor
    {                                      // Make dividend 0 and reminder the dividend.
        quotient.push_back(false);
        reminder = dividend.bits_;
    }
    
    else{                                  // The following code execute division using long division alogrithm
        current.bits_.pop_back();          // Clean up current and make current empty.
        
        // loop through the last (divisor_size -1) digits of divident to current
        // and append those digits to current from the least significant digit to the most significant digit.
        for (int i = 0; i < dsr_size -1; ++i)
            current.bits_.insert(current.bits_.begin(),dividend.bits_[dvd_size-1-i]);
        
        int start = dsr_size - 1;
        
        // loop through the bits_value of dividend
        // append one more digit from dividend to current each time
        // compare the current to divisor. If current is larger, add one to quotient
        // If current is smaller, add 0 to quotient.
        for(int i = start; i < dvd_size; ++i){      // Append one more digit to current
            current.bits_.insert(current.bits_.begin(),dividend.bits_[dvd_size-1-i]);
            if (current >= divisor){                // If current is larger, subtract the divisor from current.
                quotient.insert(quotient.begin(),true);
                current.Integer::operator -= (divisor);
            }
            
            else
                quotient.insert(quotient.begin(),false);
            
        }
        reminder = current.bits_;
    }
}

void add_with_carry(bool& b1, bool b2, bool& carry) {
    
    if(b1 && b2 && carry) {
        
        // If all bits are 1, then new bit and carry
        // bit are 1 so we don't need to do anything
        return;
        
    } else if((b1 && b2) || (b1 && carry) || (b2 && carry)) {
        
        // If two bits are 1, then carry bit is 1
        // and new bit is 0
        b1 = false;
        carry = true;
        
        return;
        
    } else if(b1 || b2 || carry) {
        // If one of the three bits is 1 then new bit is 1
        // and carry bit is 0
        b1 = true;
        carry = false;
        return;
    }
    
    // If all 3 are false, new bit and carry bit stay 0
}

Integer operator+(Integer lhs, const Integer& rhs) {
    lhs.Integer::operator += (rhs);
    return lhs;
}

Integer operator-(Integer lhs, const Integer& rhs) {
    lhs.Integer::operator -= (rhs);
    return lhs;
}

Integer operator*(Integer lhs, const Integer& rhs) {
    lhs.Integer::operator *= (rhs);
    return lhs;
}

Integer operator/(Integer lhs, const Integer& rhs) {
    lhs.Integer::operator /= (rhs);
    return lhs;
}

Integer operator%(Integer lhs, const Integer& rhs) {
    lhs.Integer::operator %= (rhs);
    return lhs;
}

bool operator==(const Integer& lhs, const Integer& rhs) {
    int size = lhs.size();
    
    // If lhs and rhs have different sizes, they are not equal
    if(size != rhs.size()) {
        return false;
    }
    
    // Check that the bits of lhs and rhs are the same. If they ever differ,
    // return false.
    for(int i = 0; i < size; ++i) {
        if(lhs.get_bit(i) != rhs.get_bit(i)) {
            return false;
        }
    }
    
    // All of the bits of lhs and rhs are the same, so they store the same value.
    return true;
}


SignedInteger::SignedInteger(int val) : Integer(val) {
    if (val < 0)      // If val is a negative number, the sign is stored as false.
        sign_ = false;
    else
        sign_ = true;
}

std::string SignedInteger::binary_string() const { // Work exacly the same as the counterpart in integer class
    std::string result = Integer::binary_string();
    std::string sign = "";
    if(sign_)   // If the sign is true, add a positive sign in front of the string.
        sign = "+";
    
    else
        sign = "-";
    
    result.insert(0, sign);
    return result;
}

std::string SignedInteger::decimal_string() const { // Work exacly the same as the counterpart in integer class
    std::string result = Integer::decimal_string();
    std::string sign = "";
    if(!sign_)  // If the sign is true, add a positive sign in front of the string.
        sign = "-";
    else
        sign = "+";
    
    result.insert(0, sign);
    return result;
    
}

SignedInteger& SignedInteger::operator+=(const SignedInteger& rhs) {
    if(sign_ && rhs.sign_)    // If both of the integers are positive, we don't change the sign.
        //*this += rhs;
        this->Integer::operator+= (rhs);
    
    else if((!sign_) &&(!rhs.sign_))  // If both the integers are negative, we don't change the sign either.
        this->Integer::operator+= (rhs);
    
    else if(!(sign_) && rhs.sign_) {  // If the instance is negative, and the parameter is positive
        // *this = rhs - *this;        // and if the instance is smaller, we change the sign to be positive.
        this -> Integer::operator-=(rhs);
        if(!(*this >= rhs))
            sign_ = true;
    }
    
    else if(sign_ && (!rhs.sign_)) {
        //*this -= rhs;                 // If the instance is positive, and the parameter is negative
        this->Integer::operator-= (rhs); // and the parameter is larger, we change the sign to be negative.
        if(!(*this >= rhs))
            sign_ = false;
    }
    return *this;
}

SignedInteger& SignedInteger::operator-=(const SignedInteger& rhs) {
    if(sign_ && rhs.sign_) {
        this -> Integer::operator-=(rhs);       // The reasoning for subtraction is the same as addition.
        if (!(*this >= rhs))
            sign_ = false;
    }
    
    else if((!sign_)&& (!rhs.sign_)) {
        this -> Integer::operator-=(rhs);
        if (!(*this >= rhs))
            sign_ = true;
    }
    
    else if(sign_ &&(!rhs.sign_))
        this -> Integer::operator+=(rhs);
    
    else if((!sign_) && (rhs.sign_))
        this -> Integer::operator+=(rhs);
    
    return *this;
}

SignedInteger& SignedInteger::operator *= (SignedInteger rhs) {
    this -> Integer::operator*=(rhs);
    if((sign_&& rhs.sign_) || ((!sign_)&& (!rhs.sign_)))   // If the two integers have the same sign,
        sign_ = true;                                      // the result has the positive sign
    else
        sign_ = false;                                     // If the two integers have the opposite sign
    // the result has the negative sign
    return *this;
}

SignedInteger& SignedInteger::operator /= (SignedInteger rhs) {
    this -> Integer::operator/=(rhs);
    if((sign_&& rhs.sign_) || ((!sign_)&& (!rhs.sign_)))
        sign_ = true;
    else
        sign_ = false;
    
    return *this;
}

SignedInteger& SignedInteger::operator %= (SignedInteger rhs) {
    this -> Integer::operator%=(rhs);                     // If the two integers have the same sign
    
    if((!sign_)&& rhs.sign_)                              // we don't need to change the sign of the result
        sign_ = false;                                    // According to the arithmatic of normal ints in c++
    // if the first integer is negative and the second is positive
    else if(sign_&&(!rhs.sign_))                          // mod is negative
        sign_ = true;                                     // reversely, mod is positive
    
    return *this;
}

SignedInteger& SignedInteger::operator++() {
    if (sign_)                                   // If the integer is positive, we do increment on bits_
        this -> Integer::operator++();
    else {
        this -> Integer::operator--();           // If the integer is negative, we do decrement on bits_
        if (*this == 0){
            sign_ = true;
        }
    }
    
    return *this;
}


SignedInteger& SignedInteger::operator--() {
    if (sign_)
        this -> Integer::operator--();
    else {
        this -> Integer::operator++();
        if (*this == 0)
            sign_ = true;
    }
    return *this;
}

SignedInteger operator+(SignedInteger lhs, const SignedInteger& rhs) {
    lhs += rhs;
    return lhs;
}

SignedInteger operator-(SignedInteger lhs, const SignedInteger& rhs) {
    lhs -= rhs;
    return lhs;
}

SignedInteger operator*(SignedInteger lhs, const SignedInteger& rhs) {
    lhs *= rhs;
    return lhs;
}

SignedInteger operator/(SignedInteger lhs, const SignedInteger& rhs) {
    lhs /= rhs;
    return lhs;
}

SignedInteger operator%(SignedInteger lhs, const SignedInteger& rhs) {
    lhs%= rhs;
    return lhs;
}



std::ostream& operator<< (std::ostream& os, const Integer& val) {
    std::string decimal;
    decimal = val.decimal_string();
    
    os << decimal;
    return os;
}

std::istream& operator>> (std::istream& is, Integer& val) {
    int input;
    
    is >> input;
    val = Integer(input);
    return is;
}


std::ostream& operator<< (std::ostream& os, const SignedInteger& val) {
    std::string decimal;
    decimal = val.decimal_string();
    
    os << decimal;
    return os;
}


std::istream& operator>> (std::istream& is, SignedInteger& val) {
    char sign;
    int input;
    
    bool sign_;

    if(is >> input) {
        sign_ = true;
        val = SignedInteger(input);
    }
    
    else{
        is.clear();
        is.unget();
        sign = is.peek();
        while(!(sign == '+' || sign == '-')) {
            is.get();
            sign = is.peek();
        }
        
        if (sign == '+'){
            sign_ = true;
            is.get();
        }
        
        else if(sign == '-'){
            sign_ = false;
            is.get();
        }
        
        
        is >> input;
        val = SignedInteger(input);
    }
    return is;
}


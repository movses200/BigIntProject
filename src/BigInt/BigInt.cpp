#include <BigInt/BigInt.h>

#include <iostream>
#include <vector>

using namespace std;

namespace ACA
{

BigInt::BigInt() :digits("") {}

BigInt::BigInt(const string& s)
{
	if(s.size() >= 2 && s[0] == '0'){
		std::cout << "Your input is not correc, write only numbers!!!\n";
		throw std::logic_error("Trying to input none number expression!!!\n");
	}

	for(auto it = s.begin();it != s.end(); it++){
		if(((*it)-48) < 0 || ((*it)-48) > 9){
			std::cout << "Your input is not correc, write only numbers!!!\n";
			throw std::logic_error("Trying to input none number expression!!!\n");
		}
	}
	digits = s;
	//to check
}

BigInt::BigInt(unsigned long long nr)
{
	while(nr!=0){
		int digit = nr % 10;
		char ch_of_digit = (char)digit + 48;
		digits.push_back(ch_of_digit);
		nr/=10;
	}
	// to check
}

BigInt::BigInt(const BigInt& other)
{
	digits = other.digits;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    // Guard self assignment
    if (this == &other)
    {
        return *this;
    }
	this->digits=other.digits;
	
    return *this;
	//to check
}

/*
BigInt& BigInt::operator=(BigInt other) noexcept
{
    // exchange resources between *this and other
    std::swap(digits, other.digits);
    return *this;
}
*/

bool operator==(const BigInt& lhs, const BigInt& rhs)
{
    return lhs.digits == rhs.digits;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
	if(lhs.digits.size() < rhs.digits.size()){
		return true;
	}else if(lhs.digits.size() > rhs.digits.size()){
		return false;
	}else{
		auto l_it = lhs.digits.begin();
		auto r_it = rhs.digits.begin();
		while(l_it != lhs.digits.end()){
			if(*l_it < *r_it){
				return true;
			}else if (*l_it > *r_it){
				return false;
			}
			l_it++;
			r_it++;
		}
		return false;
	}
}

bool operator>(const BigInt& lhs, const BigInt& rhs)
{
	return rhs < lhs;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs > rhs);
}

BigInt& BigInt::operator++()
{
	if ((int)digits.back() - 48 >= 0 && (int)digits.back() - 48 < 9) {
		char tmp = digits.back() + 1;
		digits.pop_back();
		digits.push_back(tmp);
	}
	else{
		auto it = digits.end() - 1;
		while (it != digits.begin() && *it == '9') {
			*it = '0';
			it--;
		}
		if (it == digits.begin() && *it == '9') {
			digits.front() = '0';
			digits = '1' + digits;
		}
		else{
			*it += 1;
		}
	}
	return *this;
		//++i
}

BigInt BigInt::operator++(int)
{
	BigInt old = *this;
	operator++(); // prefix increment
	return old;
	//i++
}

BigInt& BigInt::operator--(){
	if (digits == "0") {
		return *this;
	}
	
	if ((int)digits.back() - 48 >= 1 && (int)digits.back() - 48 <= 9) {
		char tmp = digits.back() - 1;
		digits.pop_back();
		digits.push_back(tmp);
	}
	else{
		auto it = digits.end() - 1;
		while (it != digits.begin() && *it == '0') {
			*it = '9';
			it--;
		}
		if (it == digits.begin() && *it == '1') {
			digits.erase(it);
		}
		else{
			*it -= 1;
		}
	}
	return *this;
	//++i
}

BigInt BigInt::operator--(int /* tmp */)
{
	BigInt old = *this;
	operator--(); // prefix decrement
	return old;
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	int this_i=this->digits.size()-1;

	int rhs_i=rhs.digits.size()-1;

	int saved = 0;

	while(this_i >= 0 && rhs_i >= 0){

		int this_int_digit = (int)(this->digits[this_i])-48;

		int rhs_digit = (int)(rhs.digits[rhs_i])-48;
		
		int number=this_int_digit+rhs_digit+saved;

		this->digits[this_i]=(char)(number%10)+48;

		if(number>9){
			saved=1;
		}else{
			saved=0;
		}

		this_i--;
		rhs_i--;
	}

	while (this_i>=0){
		
		int this_int_digit = (int)(this->digits[this_i])-48;
		
		int number=this_int_digit+saved;

		this->digits[this_i]=(char)(number%10)+48;

		if(number>9){
			saved=1;
		}else{
			saved=0;
		}
		
		this_i--;
	}

	while(rhs_i>=0){

		int rhs_int_digit=(int)rhs.digits[rhs_i]-48;

		int number=rhs_int_digit+saved;

		char str_digit=(char)(number%10)+48;

		this->digits=(str_digit+this->digits);

		if (number>9) {
			saved=1;
		}
		else {
			saved=0;
		}

		rhs_i--;
	}

	if(saved==1){
		this->digits="1"+this->digits;
	}

    return *this;
}

BigInt operator+(BigInt lhs, const BigInt& rhs)
{
	lhs += rhs;
	return lhs;
}

BigInt& BigInt::operator-=(const BigInt& rhs)
{
	if (*this < rhs) {
		std::cout << "BigInt numbers can't be negative\n";			
		throw std::logic_error("Trying to make BigInt negative!!!");
	}
	else if (*this == rhs) {
		this->digits = "0";
		return *this;
	}
	else {

		int rhs_i = rhs.digits.size() - 1;
		int this_i = this->digits.size() - 1;
		while (rhs_i >= 0 && this_i >= 0) {
				
			if (this->digits[this_i] >= rhs.digits[rhs_i]) {
				int this_digit = (int)(this->digits[this_i]) - 48;
				int rhs_digit = (int)(rhs.digits[rhs_i]) - 48;					
				this->digits[this_i] = (char)(this_digit - rhs_digit) + 48;
			}
			else{
				int this_digit = (int)(this->digits[this_i]) - 48;
				int rhs_digit = (int)(rhs.digits[rhs_i]) - 48;
				this->digits[this_i] = (char)(this_digit + 10 - rhs_digit) + 48;

				int find_none_zero = this_i-1;
				while(this->digits[find_none_zero] == '0') {
					this->digits[find_none_zero] = '9';
					find_none_zero--;
				}
				this->digits[find_none_zero] = (char)((int)(this->digits[find_none_zero]) - 48 - 1) + 48;
			}
			this_i--;
			rhs_i--;
		}
	}

	auto it = this->digits.begin();
	int i = 0;
	while (this->digits[i] == '0') {
		i++;
	}
	this->digits=this->digits.erase(0, i);
	return *this;
}

BigInt operator-(BigInt lhs, const BigInt& rhs)
{
	lhs -= rhs;
	return lhs;
}

BigInt& BigInt::operator *=(const BigInt & rhs){
	if (rhs.digits[0] == '0' || this->digits[0] == '0') {
		this->digits = "0";
		return *this;
	}
		else {
		string this_tmp = "0";
		string ten_s = "";
		int int_saved = 0;


		int rhs_i = rhs.digits.size() - 1;
		while (rhs_i >= 0) {

			string str_summery = "";
			int rhs_int_digit = (int)(rhs.digits[rhs_i]) - 48;
			int this_i = this->digits.size() - 1;
			while (this_i >= 0) {

				int this_int_digit = (int)(this->digits[this_i]) - 48;
				int number = rhs_int_digit * this_int_digit + int_saved;

				char add_to_summery = (char)(number % 10) + 48;
				str_summery = add_to_summery + str_summery;

				int_saved = number / 10;
				this_i--;
			}

			str_summery += ten_s;

			if (int_saved != 0) {
				char ch_saved = (char)(int_saved)+48;
				str_summery = ch_saved + str_summery;
			}

			BigInt this_tmp_bigint(this_tmp);
			BigInt rhs_tmp_bigint(str_summery);
			this_tmp_bigint += rhs_tmp_bigint;
			this_tmp = this_tmp_bigint.digits;

			ten_s += "0";
			rhs_i--;

		}
		this->digits = this_tmp;
	}
	return *this;
}

BigInt operator*(BigInt lhs, const BigInt& rhs)
{	
	lhs *= rhs;
	return lhs;
}	

//////////////////////////////////// is very slow ///////////////////////////////////////
BigInt& BigInt::operator/=(const BigInt& rhs)
{
	if(rhs.digits=="0"){
		std::cout<<"The number can't be divided by 0 !!!\n"; 
		throw std::logic_error("Trying to divide by 0 !!!\n");
	}

	BigInt count("0");
	while(*this>=rhs){
		*this-=rhs;
		count++;
	}
	
	*this=count;

    return *this;
}

BigInt operator/(BigInt lhs, const BigInt& rhs)
{
	lhs /= rhs;
	return lhs;
}

BigInt& BigInt::operator%=(const BigInt& rhs)
{
	if(rhs.digits=="0"){
		std::cout<<"The number can't be divided by 0 !!!\n"; 
		throw std::logic_error("Trying to divide by 0 !!!\n");
	}

	while(*this>rhs){
		*this-=rhs;
	}

    return *this;
}

BigInt operator%(BigInt lhs, const BigInt& rhs)
{
	lhs %= rhs;
	return lhs;
}

//////////////////////////////////// is very slow ///////////////////////////////////////
BigInt& BigInt::operator^=(const BigInt& rhs){
	if (rhs.digits == "0") {
		this->digits = "1";
		return *this;
	}

	BigInt pow_count = rhs;
	BigInt one("1");
	BigInt this_tmp = *this;

	while (pow_count > one) {
		*this *= this_tmp;
		--pow_count;
	}

	return *this;
}

BigInt operator^(BigInt lhs, const BigInt& rhs)
{
	lhs ^= rhs;
	return lhs;
}

istream& operator>>(istream& in, BigInt& a)
{
    string input;
	in>>input;
	BigInt for_copy(input);
	a=for_copy;
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a)
{
	out << a.toString();
    return out;
}

} // namespace ACA
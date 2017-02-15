/*
 * BigInt - Big Integer class
 */
#ifndef BIGINT_H
#define BIGINT_H

#include <ostream>
#include <string>
#include <complex>
#include <vector>
#include <assert.h>
#include <math.h>

class BigInt {
public:
    // CTORS & DTOR
    ~BigInt() {
        if (mem != NULL)
            delete mem;
        mem = NULL;
    }

    BigInt() {
        mem = new std::string();
        memSign = 1;
        mem->push_back('0');
    }

    BigInt(const BigInt &that) {
        mem = new std::string();
        *mem = *(that.mem);
        memSign = that.memSign;
    }

    template<class NumberType>
    BigInt(NumberType number) {
        if (number < 0) {
            memSign = -1;
            number *= -1;
        } else if (number > 0) {
            memSign = 1;
        } else {
            memSign = 0;
        }
        mem = new std::string();
        while (number != 0) {
            mem->push_back(number % 10 + '0');
            number /= 10;
        }
        if (mem->empty()) {
            mem->push_back('0');
        } else {
            BigInt::reverse(*mem);
        }
    }

    Bigint(std::string data, int radix) {
        
    }

    BigInt(std::string data) {
        mem = new std::string(data);
        if ((*mem)[0] == '-') {
            mem->erase(mem->begin());
            memSign = -1;
        } else {
            memSign = 1;
        }
        trim();
    }

    BigInt(const char * data) {
        mem = new std::string(data);
        if ((*mem)[0] == '-') {
            mem->erase(mem->begin());
            memSign = -1;
        } else {
            memSign = 1;
        }
        trim();
    }

    Bigint(const char * data, int radix) {
    }
    
    BigInt &operator=(const BigInt &that) {
        if (this != &that){
            if (mem == NULL){
                mem = new std::string();
            }
            *mem = *(that.mem);
            memSign = that.memSign;
        }
        trim();
        return *this;
    }

    BigInt powMod(int n, BigInt mod) {
        BigInt a = BigInt::unsignedDivide((*this), mod).second;
        BigInt ans = 1;
        int sign = 1;
        if (n & 1)
            sign = a.sign();
        while (n > 0) {
            if (n & 1)
                ans = BigInt::unsignedDivide(BigInt::unsignedMultiply(ans, a), mod).second;
            a = BigInt::unsignedDivide(BigInt::unsignedMultiply(a, a), mod).second;
            n >>= 1;
        }
        ans.memSign = sign;
        ans.trim();
        return ans;        
    }

    BigInt pow(int n) {
        BigInt a = (*this);
        BigInt ans = 1;
        int sign = 1;
        if (n & 1)
            sign = a.sign();
        while (n > 0) {
            if (n & 1)
                ans = BigInt::unsignedMultiply(ans, a);
            a = BigInt::unsignedMultiply(a, a);
            n >>= 1;
        }
        ans.memSign = sign;
        ans.trim();
        return ans;
    }

    bool isZero() {
        trim();
        return (*mem)[0] == '0';
    }

    bool isOdd() const {
        return ((*mem)[mem->size() - 1] - '0') % 2 == 1;
    }

    bool isEven() const {
        return ((*mem)[mem->size() - 1] - '0') % 2 == 0;
    }

    

    static BigInt max(BigInt a, BigInt b) {
        return a > b ? a : b;
    }

    static BigInt min(BigInt a, BigInt b) {
        return a < b ? a : b;
    }    
    
    BigInt max(BigInt that) {
        return (*this) < that ? that : (*this);
    }

    BigInt min(BigInt that) {
        return (*this) > that ? that : (*this);
    }    

    BigInt modInverse(BigInt a) {
        
    }

    BigInt gcd(BigInt a) {
        BigInt b = (*this);
        while (!a.isZero() && !b.isZero()) {
            int cmp = unsignedCompare(a, b);
            if (cmp > 0) {
                a = unsignedDivide(a, b).second;
            } else {
                b = unsignedDivide(b, a).second;
            }
        }
        if (a.isZero())
            return b;
        else
            return a;
    }

    BigInt negate() {
        BigInt ans(*this);
        ans.memSign *= -1;
        return ans;
    }

    int sign() const {
        return memSign;
    }

    int size() const {
        return (int)mem->size();
    }

    std::string toString() const {
        return ((memSign < 0 ? "-" : "") + (*mem));
    }

    std::string toString(int radix) const {
        
    }

    short int toShortInt() const {
        short int ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        if (sign() < 0)
            ans *= -1;
        return ans;
    }

    int toInt() const {
        int ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        if (sign() < 0)
            ans *= -1;
        return ans;
    }

    long toLong() const {
        long ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        if (sign() < 0)
            ans *= -1;
        return ans;
    }

    long long int toLongLongInt() const {
        long long int ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        if (sign() < 0)
            ans *= -1;
        return ans;
    }

    unsigned short int toUnsignedShortInt() const {
        unsigned short int ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        return ans;
    }

    unsigned int toUnsignedInt() const {
        unsigned int ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        return ans;
    }

    unsigned long toUnsignedLong() const {
        unsigned long ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        return ans;
    }

    unsigned long long int toUnsignedLongLongInt() const {
        unsigned long long int ans = 0;
        for (int i = 0; i < mem->size(); i++)
            ans = ans * 10 + (*mem)[i] - '0';
        return ans;
    }

    static int compare(BigInt var1, BigInt var2) {
        var1.trim();
        var2.trim();
        int sign1 = var1.sign();
        int sign2 = var2.sign();
        if (sign1 * sign2 <= 0) {
            return sign1 - sign2;
        } else if (sign1 * sign2 > 0) {
            return (sign1 < 0 ?
                    BigInt::unsignedCompare(var2, var1) :
                    BigInt::unsignedCompare(var1, var2));
        }
    }

    BigInt abs() {
        BigInt ans = (*this);
        ans.memSign = 1;
        return ans;
    }

    enum {
        UNSIGNED_CLASSICAL_MULTIPLY_THRESOLD = 1000,
        UNSIGNED_KARATSUBA_MULTIPLY_THRESOLD = 2000,
    };

    BigInt& operator+=(const BigInt &var1);
    BigInt& operator-=(const BigInt &var1);
    BigInt& operator*=(const BigInt &var1);
    BigInt& operator/=(const BigInt &var1);
    BigInt& operator%=(const BigInt &var1);

    BigInt operator++(int);
    BigInt& operator++();
    BigInt operator--(int);
    BigInt& operator--();

private:
    std::string *mem;
    int memSign;

    void trim() {
        while (!mem->empty() && (*mem)[0] == '0')
            mem->erase(mem->begin());
        if (mem->empty()) {
            mem->push_back('0');
            memSign = 0;
        }
    }

    void balance(BigInt &that) {
        std::string zero = "0";
        while (this->size() < that.size())
            *(this->mem) = zero + *(this->mem);
        while (this->size() > that.size())
            *(that.mem) = zero + *(that.mem);
    }

    static BigInt unsignedAdd(BigInt var1, BigInt var2) {
        var1.trim();
        var2.trim();
        var1.balance(var2);
        std::string ans = "";
        std::string &a = *var1.mem;
        std::string &b = *var2.mem;
        int carry = 0, sum;
        for (int i = a.size() - 1; i >= 0; i--) {
            sum = (a[i] - '0') + (b[i] - '0') + carry;
            ans.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        if(carry > 0)
            ans.push_back(carry % 10 + '0');
        BigInt::reverse(ans);
        return BigInt(ans);
    }

    static BigInt unsignedSubtract(BigInt var1, BigInt var2) {
        var1.trim();
        var2.trim();
        var1.balance(var2);
        std::string &a = *var1.mem;
        std::string &b = *var2.mem;
        std::string c = "";
        int sign = 1;
        BigInt ans;
        if (unsignedCompare(a, b) < 0) {
            sign = -1;
            std::swap(a, b);
        }
        int carry = 0, diff;
        for (int i = a.size() - 1; i >= 0; i--) {
            diff = a[i] - b[i] - carry;
            if (diff < 0) {
                diff += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            c.push_back(diff % 10 + '0');
        }
        if(carry > 0)
            c.push_back(carry % 10 + '0');
        BigInt::reverse(c);
        (*ans.mem) = c;
        ans.memSign = sign;
        ans.trim();
        return ans;
    }

    static BigInt unsignedClassicalMultiply(BigInt var1, BigInt var2) {
        BigInt bTimes[10], ans;
        for (int i = 1; i <= 9; i++)
            bTimes[i] = BigInt::unsignedAdd(bTimes[i - 1], var2);
        std::string &a = *var1.mem;
        for (int i = 0; i < a.size(); i++) {
            ans.mem->push_back('0');
            ans = unsignedAdd(ans, bTimes[a[i] - '0']);
        }
        return ans;
    }

    static std::vector<std::complex<double> > FFT0(std::vector<int> a) {
        std::vector<int> aOdd, aEven;
        int n = a.size();
        if (n == 1) {
            std::vector<std::complex<double> > tmp;
            tmp.push_back(a[0]);
            return tmp;
        }
        for (int i = 0; i < n; i += 2) {
            aEven.push_back(a[i]);
            aOdd.push_back(a[i + 1]);
        }
        std::vector<std::complex<double> > yOdd = FFT0(aOdd);
        std::vector<std::complex<double> > yEven = FFT0(aEven);
        std::vector<std::complex<double> > y(n, std::complex<double>());
        std::complex<double> w0(cos(2 * M_PI / n), sin(2 * M_PI / n));
        std::complex<double> w = 1;
        for (int i = 0; i < n / 2; i++) {
            y[i] = yEven[i] + w * yOdd[i];
            y[i + n / 2] = yEven[i] - w * yOdd[i];
            w *= w0;
        }
        return y;
    }

    static std::vector<std::complex<double> > FFT(BigInt var) {
        std::vector<int> a;
        for (int i = var.mem->size() - 1; i >= 0; i--)
            a.push_back((*var.mem)[i] - '0');
        return FFT0(a);
    }

    static std::vector<std::complex<double> > invertFFT(std::vector<std::complex<double> > a) {
        std::vector<std::complex<double> > aOdd, aEven;
        int n = a.size();
        if (n == 1) return a;
        for (int i = 0; i < n; i += 2) {
            aEven.push_back(a[i]);
            aOdd.push_back(a[i + 1]);
        }
        std::vector<std::complex<double> > yOdd = invertFFT(aOdd);
        std::vector<std::complex<double> > yEven = invertFFT(aEven);
        std::vector<std::complex<double> > y(n, std::complex<double>());
        std::complex<double> w0(cos(2 * M_PI / n), sin(-2 * M_PI / n));
        std::complex<double> w = 1;
        for (int i = 0; i < n / 2; i++) {
            y[i] = yEven[i] + w * yOdd[i];
            y[i + n / 2] = yEven[i] - w * yOdd[i];
            w *= w0;
        }
        return y;
    }

    static BigInt unsignedFastMultiply(BigInt var1, BigInt var2) {
        var1.trim();
        var2.trim();
        int maxSize = var2.size();
        if (maxSize < var1.size())
            maxSize = var1.size();
        int len = 1;
        while (len <= maxSize)
            len *= 2;
        len *= 2;
        while (var1.size() < len)
            (*var1.mem) = "0" + (*var1.mem);
        while (var2.size() < len)
            (*var2.mem) = "0" + (*var2.mem);
        std::vector<std::complex<double> > pVar1 = FFT(var1);
        std::vector<std::complex<double> > pVar2 = FFT(var2);
        std::vector<std::complex<double> > var3;
        for (int i = 0; i < pVar1.size(); i++)
            var3.push_back(pVar1[i] * pVar2[i]);
        var3 = invertFFT(var3);
        std::string ans;
        int carry = 0;
        for (int i = 0; i <= var3.size() - 1; i++) {
            int sum = (int)round(var3[i].real() / len) + carry;
            ans.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        if (carry > 0)
            ans.push_back(carry + '0');
        BigInt::reverse(ans);
        return ans;
    }

    static BigInt unsignedMultiply(BigInt var1, BigInt var2) {
        int minSize = var1.size();
        if (minSize > var2.size())
            minSize = var2.size();
        if (minSize <= UNSIGNED_CLASSICAL_MULTIPLY_THRESOLD) {
            if (var1.size() < var2.size())
                return unsignedClassicalMultiply(var1, var2);
            else
                return unsignedClassicalMultiply(var2, var1);
        } else {
            return unsignedFastMultiply(var1, var2);
        }
    }

    static std::pair<BigInt, BigInt> unsignedDivide(BigInt var1, BigInt var2) {
        var1.trim();
        var2.trim();
        assert (unsignedCompare(var2, "0") != 0);
        std::string &a = *var1.mem;
        std::string &b = *var2.mem;
        std::string ans;
        BigInt c;
        for (int i = 0; i <= a.size(); i++) {
            int time = 0;
            if (unsignedCompare(c, var2) >= 0) {
                while (unsignedCompare(c, var2) >= 0) {
                    time++;
                    c = BigInt::unsignedSubtract(c, var2);
                }
                ans.push_back(time + '0');
            }
            if (i < a.size())
                c.mem->push_back(a[i]);
        }
        c.trim();
        c.memSign = 1;
        return make_pair<BigInt>(ans, c);
    }

    static int unsignedCompare(BigInt var1, BigInt var2) {
        var1.trim();
        var2.trim();
        var1.balance(var2);
        std::string &a = *var1.mem;
        std::string &b = *var2.mem;
        return a.compare(b);
    }

    static void reverse(std::string &mem) {
        int i = 0;
        int j = mem.size() - 1;
        while (i < j) {
            std::swap(mem[i], mem[j]);
            i++;
            j--;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& a);
    friend std::istream& operator>>(std::istream& in, BigInt& a);

    friend BigInt operator+(const BigInt &var1, const BigInt &var2);
    friend BigInt operator-(const BigInt &var1, const BigInt &var2);
    friend BigInt operator*(const BigInt &var1, const BigInt &var2);
    friend BigInt operator/(const BigInt &var1, const BigInt &var2);
    friend BigInt operator%(const BigInt &var1, const BigInt &var2);

    friend bool operator> (const BigInt &var1, const BigInt &var2);
    friend bool operator>=(const BigInt &var1, const BigInt &var2);
    friend bool operator< (const BigInt &var1, const BigInt &var2);
    friend bool operator<=(const BigInt &var1, const BigInt &var2);
    friend bool operator==(const BigInt &var1, const BigInt &var2);
    friend bool operator!=(const BigInt &var1, const BigInt &var2);
};

std::ostream& operator<<(std::ostream& out, const BigInt& a) {
    out << a.toString();
    return out;
}

std::istream& operator>>(std::istream& in, BigInt& a) {
    std::string str;
    in >> str;
    a = str;
    return in;
}

BigInt operator+(const BigInt &var1, const BigInt &var2) {
    BigInt ans;
    if (var1.sign() * var2.sign() > 0) {
        ans = BigInt::unsignedAdd(var1, var2);
        ans.memSign = var1.sign();
    } else if (var1.sign() < 0) {
        ans = BigInt::unsignedSubtract(var2, var1);
    } else {
        ans = BigInt::unsignedSubtract(var1, var2);
    }
    ans.trim();
    return ans;
}

BigInt operator-(const BigInt &var1, const BigInt &var2) {
    int sign1 = var1.sign();
    int sign2 = -var2.sign();
    BigInt ans;
    if (sign1 * sign2 > 0) {
        ans = BigInt::unsignedAdd(var1, var2);
        ans.memSign = sign1;
    } else if (sign1 < 0) {
        ans = BigInt::unsignedSubtract(var2, var1);
    } else {
        ans = BigInt::unsignedSubtract(var1, var2);
    }
    ans.trim();
    return ans;
}

BigInt operator*(const BigInt &var1, const BigInt &var2) {
    BigInt ans = BigInt::unsignedMultiply(var1, var2);
    ans.memSign = var1.sign() * var2.sign();
    ans.trim();
    return ans;
}

BigInt operator/(const BigInt &var1, const BigInt &var2) {
    BigInt ans = BigInt::unsignedDivide(var1, var2).first;
    ans.memSign = var1.sign() * var2.sign();
    ans.trim();
    return ans;
}

BigInt operator%(const BigInt &var1, const BigInt &var2) {
    BigInt ans = BigInt::unsignedDivide(var1, var2).second;
    ans.memSign = var1.sign() * var2.sign();
    ans.trim();
    return ans;
}

BigInt& BigInt::operator+=(const BigInt &var1) {
    (*this) = (*this) + var1;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt &var1) {
    (*this) = (*this) - var1;
    return *this;
}

BigInt& BigInt::operator*=(const BigInt &var1) {
    (*this) = (*this) * var1;
    return *this;
}

BigInt& BigInt::operator/=(const BigInt &var1) {
    (*this) = (*this) / var1;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt &var1) {
    (*this) = (*this) % var1;
    return *this;
}

bool operator> (const BigInt &var1, const BigInt &var2) {
    return BigInt::compare(var1, var2) > 0;
}

bool operator>=(const BigInt &var1, const BigInt &var2) {
    return BigInt::compare(var1, var2) >= 0;
}

bool operator< (const BigInt &var1, const BigInt &var2) {
    return BigInt::compare(var1, var2) < 0;
}

bool operator<=(const BigInt &var1, const BigInt &var2) {
    return BigInt::compare(var1, var2) <= 0;
}

bool operator==(const BigInt &var1, const BigInt &var2) {
    return BigInt::compare(var1, var2) == 0;
}

bool operator!=(const BigInt &var1, const BigInt &var2) {
    return BigInt::compare(var1, var2) != 0;
}

BigInt BigInt::operator++(int) {
    BigInt ans(*this);
    (*this) += 1;
    return ans;
}

BigInt& BigInt::operator++() {
    (*this) += 1;
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt ans(*this);
    (*this) -= 1;
    return ans;
}

BigInt& BigInt::operator--() {
    (*this) -= 1;
    return *this;
}

#endif

/*
 * END OF Big Integer class
 */

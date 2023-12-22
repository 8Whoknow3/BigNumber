/* Create by WhoKnow!
 * BigNumber Project
*/

#include "bits/stdc++.h"

using namespace std;

class BigNumber{
    string number;
    bool pos;
public:
    BigNumber();
    explicit BigNumber(const string &);
    explicit BigNumber(long long int);
    BigNumber(BigNumber const &);
    BigNumber& operator =(const BigNumber &);
    void checkTrue();
    void printnumber();
    void shiftL();
    void shiftR();
    void shiftL(long long int);
    void shiftR(long long int);
    void inc();
    void dec();
    BigNumber sum(const BigNumber &);
    BigNumber sub(const BigNumber &);
    BigNumber multbyoneDigit(int);
    BigNumber mult(const BigNumber &);
    BigNumber div(const BigNumber &);
    BigNumber pow(const BigNumber &);
    BigNumber operator*(const BigNumber &);

    friend bool operator >(const BigNumber &a1, const BigNumber &a2);
    friend bool operator >=(const BigNumber &a1, const BigNumber &a2);
    friend BigNumber fib(long long int num);
    friend BigNumber fac(long long int num);

};

BigNumber ::BigNumber() {
    pos = true;
}

BigNumber :: BigNumber(const string& str){
    if(str[0] == '-'){
        pos = false;
    }
    else{
        pos = true;
    }
    if(!pos)
        for(long long int i = 1; i < str.size(); i++)
            number += str[i];
    else
        for(long long int i = 0; i < str.size(); i++)
            number += str[i];
    checkTrue();
}

BigNumber ::BigNumber(long long int num){
    string str = to_string(num);
    if(str[0] == '-'){
        pos = false;
    }
    else{
        pos = true;
    }
    if(!pos)
        for(long long int i = 1; i < str.size(); i++)
            number += str[i];
    else
        for(long long int i = 0; i < str.size(); i++)
            number += str[i];
    checkTrue();
}

BigNumber::BigNumber(const BigNumber &other) {
    pos = other.pos;
    number = other.number;
}

void BigNumber::printnumber() {
    if((long long int)number.size() == 0){
        cout << "0" << "\n";
        return;
    }
    if(!pos)
        cout << "-";
    for(long long int i = 0; i < (long long int) number.size(); i++){
            cout << number[i];
    }
    cout << "\n";
}

void BigNumber::checkTrue() {
    long long int n = (long long int) number.size();
    long long int cnt = 0;
    for(int i = 0; i < n; i++){
        if(number[i - cnt] == '0'){
            number.erase(0, 1);
            cnt++;
        }
        else if(number[i - cnt] != '0')
            return;
    }
}

BigNumber &BigNumber::operator=(const BigNumber &other) {
    pos = other.pos;
    number = other.number;
    return *this;
}

void BigNumber::shiftL() {
    long long int i = 0;
    for(; i < (long long int) number.size() - 1; i++)
        number[i] = number[i + 1];
    number[i] = '0';
}

void BigNumber::shiftR() {
    long long int i = (long long int) number.size() - 1;
    for(; i > 0 ; i--)
        number[i] = number[i - 1];
    number[i] = '0';
}

void BigNumber::shiftL(long long int rep) {
    for(long long int i = 0; i < rep; i++)
        shiftL();
}

void BigNumber::shiftR(long long int rep) {
    for(long long int i = 0; i < rep; i++)
        shiftR();
}

void BigNumber::inc() {
    if(!pos){
        long long int i = 1;
        long long int n = (long long int) number.size();
        while (true){
            if(number[n - i] != '0'){
                number[n - i] -= 1;
                return;
            }
            else{
                number[n - i] = '9';
                i++;
                continue;
            }
        }
    }
    else{
        long long int i = 1;
        long long int n = (long long int) number.size();
        while(true){
            int m = number[n - i] - '0' + 1;
            if(m == 10 && i != n){
                number[n - i] = '0';
                i++;
            }
            else if(i == n){
                number[n - i] = '0';
                number.insert(0, 1, '0' + 1);
                return;
            }
            else{
                number[n - i] = '0' + m;
                return;
            }
        }
    }
}

void BigNumber::dec() {
    if(!pos){
        long long int i = 1;
        long long int n = (long long int) number.size();
        while(true){
            int m = number[n - i] - '0' + 1;
            if(m == 10 && i != n){
                number[n - i] = '0';
                i++;
            }
            else if(i == n){
                number[n - i] = '0';
                number.insert(0, 1, '0' + 1);
                return;
            }
            else{
                number[n - i] = '0' + m;
                return;
            }
        }
    }
    else{
        long long int i = 1;
        long long int n = (long long int) number.size();
        while (true){
            if(number[n - i] != '0'){
                number[n - i] -= 1;
                return;
            }
            else{
                number[n - i] = '9';
                i++;
                continue;
            }
        }
    }

}

bool operator>(const BigNumber &a1, const BigNumber &a2) {
    if(!a1.pos && a2.pos)
        return false;
    if(a1.pos && !a2.pos)
        return true;
    if(a1.pos && a2.pos) {
        if(a1.number.size() > a2.number.size())
            return true;
        if(a2.number.size() > a1.number.size())
            return false;
        int m = a1.number.compare(a2.number);
        if(m == 0 || m == -1)
            return false;
        return true;
    }
    if(!a1.pos && !a2.pos) {
        if(a2.number.size() > a1.number.size())
            return true;
        if(a1.number.size() > a2.number.size())
            return false;
        int m = a1.number.compare(a2.number);
        if(m == 0 || m == 1)
            return false;
        return true;
    }
}

BigNumber BigNumber::sum(const BigNumber & other) {
    BigNumber a1 = *this, a2 = other, ans, temp;
	if(!a1.pos || !a2.pos){
		if(!a1.pos && !a2.pos){
			a1.pos = true; a2.pos = true;
			ans = a1.sum(a2);
			ans.pos = false;
			return ans;
		}
		else if(!a1.pos){
			a1.pos = true; a2.pos = true;
			ans = a2.sub(a1);
			if(a1 > a2)
				ans.pos = false;
			else if(a2 > a1)
				ans.pos = true;
			return ans;
		}
		else if(!a2.pos){
			a1.pos = true; a2.pos = true;
			ans = a1.sub(a2);
			if(a1 > a2)
				ans.pos = true;
			else if(a2 > a1)
				ans.pos = false;
			return ans;
		}
	}
	else{
		if(a2 > a1){
			temp = a1;
			a1 = a2;
			a2 = temp;
		}
	}
    long long int i = 0;
    long long int carry = 0;
    auto n1 = (long long int) a1.number.size(); auto n2 = (long long int) a2.number.size();
    while(i < n2){
        long long int m = a1.number[n1 - 1 - i] - '0' + a2.number[n2 - 1 - i] - '0' + carry;
        ans.number.insert(0, to_string(m % 10));
        carry = m / 10;
        i++;
    }
    while(i < n1){
        long long int m = a1.number[n1 - 1 - i] - '0' + carry;
        ans.number.insert(0, to_string(m % 10));
        carry = m / 10;
        i++;
    }
    while(carry > 0){
        ans.number.insert(0, to_string(carry % 10));
        carry /= 10;
    }
    return ans;
}

BigNumber BigNumber::sub(const BigNumber & other) {
    BigNumber a1 = *this; BigNumber a2 = other; BigNumber ans;
    if(!a1.pos || !a2.pos){
        if(!a1.pos && !a2.pos) {
            a1.pos = true;
            a2.pos = true;
            ans = a2.sub(a1);
            if(a2 > a1)
                ans.pos = true;
            else
                ans.pos = false;
            return ans;
        }
        else if(!a1.pos){
            a1.pos = true;
            ans = a1.sum(a2);
            ans.pos = false;
            return ans;
        }
        else if(!a2.pos){
            a2.pos = true;
            ans = a1.sum(a2);
            ans.pos = true;
            return ans;
        }
    }
    if(a1 > a2)
        ans.pos = true;
    else
        ans.pos = false;
    if(*this > other && this->pos){
        a1 = *this; a2 = other;
    }
    else{
        a2 = *this; a1 = other;
    }
    long long int i = 0;
    long long int n1 =(long long int) a1.number.size(); long long int n2 =(long long int) a2.number.size();
    long long int carry = 0;
    while(i < n2){
        long long int a = a1.number[n1 - 1 - i] - '0' - carry;
        long long int b = a2.number[n2 - 1 - i] - '0';
        if(a >= b){
            ans.number.insert(0, to_string(a - b));
            carry = 0;
        }
        else{
            ans.number.insert(0, to_string(a + 10 - b));
            carry = 1;
        }
        i++;
    }
    while(i < n1){
        long long int a = a1.number[n1 - 1 - i] - '0' - carry;
        if(a >= 0) {
            ans.number.insert(0, to_string(a));
            carry = 0;
        }
        else{
            ans.number.insert(0, to_string(a + 10));
            carry = 1;
        }
        i++;
    }
    ans.checkTrue();
    return ans;

}

BigNumber BigNumber::multbyoneDigit(int num) {
    BigNumber ans;
    if(!pos || num < 0){
        if(!pos && num > 0)
            ans.pos = false;
        else if(!pos && num < 0){
            ans.pos = true;
            num *= -1;
        }
        else if(num < 0) {
            ans.pos = false;
            num *= -1;
        }
    }
    long long int carry = 0;
    for(long long int i = (long long int) number.size() - 1; i >= 0 ; i--){
        int m = num * (number[i] - '0') + carry;
        ans.number.insert(0, to_string(m % 10));
        carry = m / 10;
    }
    while(carry > 0){
        ans.number.insert(0, to_string(carry % 10));
        carry /= 10;
    }
    return ans;
}

BigNumber BigNumber::mult(const BigNumber &other) {
    BigNumber a1 = *this, a2 = other, ans;
    bool flag = true;
    if(!a1.pos && !a2.pos)
        flag = true;
    else if(!a1.pos || !a2.pos)
        flag = false;
    a1.pos = true;
    a2.pos = true;
    if(a1 > a2){
        long long int carry = 0;
        long long int n1 = (long long int) a1.number.size(), n2 = (long long int) a2.number.size();
        for(long long int i = n2 - 1; i >= 0; i--){
            BigNumber temp;
            long long int s = n2 - 1 - i;
            while(s > 0) {
                temp.number.append("0");
                s--;
            }
            for(long long int j = n1 - 1; j >= 0; j--){
                long long int m = (a1.number[j] - '0') * (a2.number[i] - '0') + carry;
                temp.number.insert(0, to_string(m % 10));
                carry = m / 10;
            }
            while(carry > 0){
                temp.number.insert(0, to_string(carry % 10));
                carry /= 10;
            }
            ans = ans.sum(temp);
        }
    }
    else {
        long long int carry = 0;
        long long int n1 = (long long int) a1.number.size(), n2 = (long long int) a2.number.size();
        for (long long int i = n1 - 1; i >= 0; i--) {
            BigNumber temp;
            long long int s = n1 - 1 - i;
            while (s > 0) {
                temp.number.append("0");
                s--;
            }
            for (long long int j = n2 - 1; j >= 0; j--) {
                long long int m = (a1.number[i] - '0') * (a2.number[j] - '0') + carry;
                temp.number.insert(0, to_string(m % 10));
                carry = m / 10;
            }
            while (carry > 0) {
                temp.number.insert(0, to_string(carry % 10));
                carry /= 10;
            }
            ans = ans.sum(temp);
        }
    }
    ans.pos = flag;
    return ans;
}

BigNumber BigNumber::div(const BigNumber &other) {
    if(other.number.empty()){
        cout << "You cant divide by 0!" << endl;
        exit(0);
    }
    BigNumber a1 = *this, a2 = other;
    bool flag;
    if((!a1.pos && !a2.pos) || a1.pos && a2.pos)
        flag = true;
    else if(!a1.pos || !a2.pos)
        flag = false;
    long long int cnt = 0;
    a1.pos = true;
    a2.pos = true;
    while(a1 >= a2) {
        long long int n = (long long int) a1.number.size() - (long long int) a2.number.size();
        string a = a2.number;
        long long int jam = 1;
        for (int i = 1; i < n; i++) {
            a.append("0");
            jam *= 10;
        }
        BigNumber temp(a);
        while (a1 >= temp) {
            a1 = a1.sub(temp);
            cnt += jam;
        }	
    }
    BigNumber ans(cnt);
    ans.pos = flag;
    return ans;
}

bool operator>=(const BigNumber &a1, const BigNumber &a2) {
    if(!a1.pos && a2.pos)
        return false;
    if(a1.pos && !a2.pos)
        return true;
    if(a1.pos && a2.pos) {
        if(a1.number.size() > a2.number.size())
            return true;
        if(a2.number.size() > a1.number.size())
            return false;
        int m = a1.number.compare(a2.number);
        if(m == -1)
            return false;
        return true;
    }
    if(!a1.pos && !a2.pos) {
        if(a2.number.size() > a1.number.size())
            return true;
        if(a1.number.size() > a2.number.size())
            return false;
        int m = a1.number.compare(a2.number);
        if(m == 1)
            return false;
        return true;
    }
}

BigNumber fib(long long int num) {
    BigNumber a1("0"), a2("1") ,ans;
    if(num == 0)
        return a1;
    else if(num == 1)
        return a2;
    for(long long int i = 2; i <= num; i++) {
        ans = a1.sum(a2);
        a1 = a2;
        a2 = ans;
    }
    return ans;
}

BigNumber fac(long long int num) {
    BigNumber ans("1");
    if(num == 0 || num == 1)
        return ans;
    for(long long int i = 1; i <= num; i++){
        BigNumber temp(i);
        ans = ans * temp;
    }
    return ans;
}

BigNumber BigNumber::pow(const BigNumber &other) {
    BigNumber base, cnt("10"), ans = *this;
    for(int i = 1; i < 10; i++)
        ans = ans * (*this);
    while(other >= cnt.sum(cnt)){
        base = ans;
        ans = ans * ans;
        cnt = cnt.sum(cnt);
    }
    BigNumber temp("2");
    BigNumber cntplus(cnt.div(temp));
    while(other >= cnt.sum(cntplus)){
        ans = ans * base;
        cnt = cnt.sum(cntplus);
    }
    BigNumber one("1");
    while(other > cnt){
        ans = ans * (*this);
        cnt = cnt.sum(one);
    }
    return ans;
}

BigNumber BigNumber::operator*(const BigNumber &other) {
    BigNumber first = *this, f = *this, a = other, zero("0"), ans("0");
    while(a > zero) {
        string o = "1";
        auto n = (long long int) a.number.size();
        string jam = f.number;
        for (int i = 1; i < n; i++) {
            jam.append("0");
            o.append("0");
        }
        BigNumber jamcnt(o);
        first.number = jam;
        if(n == 1){
            int m = (a.number[a.number.size() - 1]) - '0';
            ans = ans.sum(first.multbyoneDigit(m));
            break;
        }
        while (a.number.size() > n - 1) {
            ans = ans.sum(first);
            a = a.sub(jamcnt);
        }
    }
    return ans;
}

int main(){
    while(true) {
        cout << "\nEnter First number : ";
        string first; cin >> first;
        cout << "Enter Second number : ";
        string second; cin >> second;
        BigNumber a(first); BigNumber b(second);
        Start:
        cout << "\n1)sum\n2)sub\n3)mult\n4)*5)div\n6)pow\n7)Enter new number\n8)exit\nYour choice :";
        int c;
        cin >> c;
        switch (c) {
            case 1:
                cout << "Sum : "; (a.sum(b)).printnumber();
                break;
            case 2:
                cout << "Sub : "; (a.sub(b)).printnumber();
                break;
            case 3:
                cout << "mult : "; (a.mult(b)).printnumber();
                break;
            case 4:
                cout << "* : "; (a * b).printnumber();
                break;
            case 5:
                cout << "div : "; (a.div(b)).printnumber();
                break;
            case 6:
                cout << "pow : "; (a.pow(b)).printnumber();
                break;
            case 7:
                continue;
            case 8:
                exit(0);
            default:
                break;
        }
        continue;
    }
}
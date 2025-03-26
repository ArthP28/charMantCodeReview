
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

//helper functions
int findCommonDenominator(int d1, int d2);
int gcd(int d1, int d2);
int countDigits(int num);
void addCharToMant(int integer, int num, int den, char result[], int len, bool isPos);
void addTester();
void subtractTester();
void multiplyTester();
void divideTester();

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 2;
    n1 = 2;
    d1 = 3;

    c2 = 1;
    n2 = 1;
    d2 = 2; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //THIS IS A DIFFERENT ANSWER NOW
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer for add: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer on divide: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

     //addTester();
    //subtractTester();
    //multiplyTester();
    divideTester();

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    //find common denominators
    int newDenom = findCommonDenominator(d1, d2);

    //update numerators 
    int newN1 = n1 * (newDenom / d1);
    int newN2 = n2 * (newDenom / d2);

    //mutiply c1 and c2 by new denominator and combine with current numerator
    newN1 += c1 * newDenom;
    newN2 += c2 * newDenom;

    //add newN1 and newN2 togther
    int sum = newN1 + newN2;

    //split back into a fraction
    int whole = sum / newDenom;
    int remainder = sum % newDenom;

   addCharToMant(whole, remainder, newDenom, result, len, true);
       
   return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers

    int diffOfChar;
    int diffOfMant;
    bool isPos = true;

    int newDenominator = findCommonDenominator(d1, d2);

    int newN1 = newDenominator / d1;
    newN1 *= n1;
    int newN2 = newDenominator / d2;
    newN2 *= n2;

    int newChar1 = (c1 * newDenominator) + newN1;
    int newChar2 = (c2 * newDenominator) + newN2;

    int diff = newChar1 - newChar2;

    if (diff < 0) { //the number is negative
        isPos = false;
        diff *= -1;
    }

    int whole = diff / newDenominator;
    int remainder = (diff % newDenominator);
    
    addCharToMant(whole, remainder, newDenominator, result, len, isPos);


    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    bool isPos = true;
    if (c1 < 0) {
        c1 *= -1;
        isPos = false;
    }
    if (c2 < 0) {
        c2 *= -1;
        isPos = false;
    }
    else if (c2 && c1 < 0) {
        c1 *= -1;
        c2 *= -1;
    }
   
    int newN1 = (c1 * d1) + n1;
    int newN2 = (c2 * d2) + n2;
    int newDenom = d1 * d2;

    int product = newN1 * newN2;

    int whole = product / newDenom;
    int remainder = product % newDenom;
   
    addCharToMant(whole, remainder, newDenom, result, len, isPos);

    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    //set this equal to true unless a negative number is entered
    bool isPos = true;
    if (c1 < 0) {
        c1 *= -1;
        isPos = false;
    }
    else if (c2 < 0) {
        c2 *= -1;
        isPos = false;
    }
    else if (c2 && c1 < 0) {
        c1 *= -1;
        c2 *= -1;
    }

    int newN1 = (c1 * d1) + n1;
    int newN2 = (c2 * d2) + n2;

    //now multiply the first fraction by the reciprocal of the second
    int product1 = newN1 * d2;
    int product2 = newN2 * d1;

    int whole = product1 / product2;
    int remainder = product1 % product2;

    addCharToMant(whole, remainder, product2, result, len, isPos);

    return true;
}

//This is the start of my helper functions

int findCommonDenominator(int d1, int d2) {
   //first we need to find the GCD or greatest common divisor
    int commDiv = gcd(d1, d2);
    int commDenom = (d1 / commDiv) * d2;

    return commDenom;
}

int gcd(int d1, int d2) {

    while (d2 != 0) {
        int temp = d2;
        d2 = d1 % d2;
        d1 = temp;
    }

    return d1;
}

int countDigits(int num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }

    while (num != 0) { //keep dividing by 10 until num becomes zero
        num /= 10;
        count++;
    }

    return count;
}

void addCharToMant(int integer, int num, int den, char result[], int len, bool isPos) {
    
    int index = 0;
    int numDigits = countDigits(integer);
    int temp = integer;

    if (isPos == false) {
        result[index++] = '-';
    }

    //start from the back and iterate down the integer
    int startIndex = index + numDigits - 1;
    for (int i = startIndex; i >= index; i--) {
        result[i] = '0' + (temp % 10);
        temp /= 10;
    }
    
    index += numDigits;

    //add decimal point
    result[index++] = '.';
    int remainder = num % den;
    int count = index;

    for (int i = count; i < len - 1; i++) {
        remainder *= 10;
        result[i] = '0' + (remainder / den);
        remainder %= den;
        index++;

        if (remainder == 0) { //stop here when there isn't any more decimal point numbers
            break;
        }

    }
   
    result[index] = '\0'; //terminate the string
    
}

void addTester() {

    char result[10];
    int c1 = 1;
    int n1 = 4;
    int d1 = 5;

    int c2 = 5;
    int n2 = 1;
    int d2 = 4;

    //1.8 + 5.25 = 7.05
    add(c1, n1, d1, c2, n2, d2, result, 10);

    cout << "Result on add(): " << result << endl;

    char result1[10];
    c1 = 2;
    n1 = 3;
    d1 = 7;

    c2 = 2;
    n2 = 2;
    d2 = 7;

    //2.42857142857 + 2.28571428571 = 4.7142857
    add(c1, n1, d1, c2, n2, d2, result1, 10);

    cout << "Result on add(): " << result1 << endl;

    //2.66666666 + 3.46 = 6.12666666

    char result2[10];
    c1 = 2;
    n1 = 2;
    d1 = 3;

    c2 = 3;
    n2 = 23;
    d2 = 50;

    add(c1, n1, d1, c2, n2, d2, result2, 10);
    cout << "Result on add(): " << result2 << endl;
}

void subtractTester() {

    char result[10];
    int c1 = 10;
    int n1 = 2;
    int d1 = 3;

    int c2 = 4;
    int n2 = 3;
    int d2 = 8;

    //10.6666666 - 4.375 = 6.291666
    subtract(c1, n1, d1, c2, n2, d2, result, 10);
    cout << "Result on subtract(): " << result << endl;
    
    char result1[10];
    c1 = 3;
    n1 = 5;
    d1 = 7;

    c2 = 4;
    n2 = 1;
    d2 = 3;

    //3.71428571 - 4.3333333333 = -0.61904759
    subtract(c1, n1, d1, c2, n2, d2, result1, 10);
    cout << "Result on subtract(): " << result1 << endl;

    char result2[10];
    c1 = 4;
    n1 = 3;
    d1 = 4;

    c2 = 5;
    n2 = 1;
    d2 = 5;

    //4.75 - 5.20 = -0.45
    subtract(c1, n1, d1, c2, n2, d2, result2, 10);
    cout << "Result on subtract(): " << result2 << endl;

}

void multiplyTester() {
    char result[10];
    int c1 = -2;
    int n1 = 1;
    int d1 = 2;

    int c2 = 3;
    int n2 = 2;
    int d2 = 3;

    //2.5 * 3.66666666 = -9.166666666
    multiply(c1, n1, d1, c2, n2, d2, result, 10);
    cout << "Result on multiply():" << result << endl;

    char result1[10];
    c1 = 30;
    n1 = 4;
    d1 = 5;

    c2 = 4;
    n2 = 2;
    d2 = 3;

    //30.8 * 4.66666666 = 143.73333333
    multiply(c1, n1, d1, c2, n2, d2, result1, 10);
    cout << "Result on multiply():" << result1 << endl;

    char result2[10];
    c1 = 5;
    n1 = 1;
    d1 = 9;

    c2 = 2;
    n2 = 3;
    d2 = 5;

    //5.1111111 * 2.6 = 13.2888888888
    multiply(c1, n1, d1, c2, n2, d2, result2, 10);
    cout << "Result on multiply():" << result2 << endl;

}

void divideTester() {
    char result[10];
    int c1 = 4;
    int n1 = 1;
    int d1 = 4;

    int c2 = 3;
    int n2 = 1;
    int d2 = 6;
    
    //4.25 / 3.16666666 = 1.34210529
    divide(c1, n1, d1, c2, n2, d2, result, 10);
    cout << "Results on divide(): " << result << endl;

    char result1[10];
    c1 = -1;
    n1 = 2;
    d1 = 3;

    c2 = 2;
    n2 = 3;
    d2 = 4;

    //-1.666666 / 2.75 = -0.606060364
    divide(c1, n1, d1, c2, n2, d2, result1, 10);
    cout << "Results on divide():" << result1 << endl;

    char result2[10];
    c1 = 7;
    n1 = 1;
    d1 = 3;

    c2 = 2;
    n2 = 5;
    d2 = 6;

    //7.333333 / 2.8333333 = 2.58823521
    divide(c1, n1, d1, c2, n2, d2, result2, 10);
    cout << "Results on divide():" << result2 << endl;
}

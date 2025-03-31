
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
void checkCharacteristics(bool& isPos, int& c1, int& c2);

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

     addTester();
    subtractTester();
    multiplyTester();
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
    int newDenominator = findCommonDenominator(d1, d2);

    //update numerators 
    int newNumerator1 = n1 * (newDenominator / d1);
    int newNumerator2 = n2 * (newDenominator / d2);

    //mutiply c1 and c2 by new denominator and combine with current numerator
    newNumerator1 += c1 * newDenominator;
    newNumerator2 += c2 * newDenominator;

    //add newNumerator1 and newNumerator2 togther
    int sum = newNumerator1 + newNumerator2;

    //turn back into a mixed number
    int whole = sum / newDenominator;
    int remainder = sum % newDenominator;
    

    addCharToMant(whole, remainder, newDenominator, result, len, true);
       
   return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers

    bool isPos = true;

    //find common denominator
    int newDenominator = findCommonDenominator(d1, d2);

    //update numerator based on new denominator
    int newNumerator1 = newDenominator / d1;
    newNumerator1 *= n1;
    int newNumerator2 = newDenominator / d2;
    newNumerator2 *= n2;

    //turn into an improper fraction
    int newCharacteristic1 = (c1 * newDenominator) + newNumerator1;
    int newCharacteristic2 = (c2 * newDenominator) + newNumerator2;

    //subtract new numerators by each other
    int diff = newCharacteristic1 - newCharacteristic2;
    

    if (diff < 0) { //the number is negative, set it to positive and set isPos to false
        isPos = false;
        diff *= -1;
    }

    //turn back into a mixed number
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
    checkCharacteristics(isPos, c1, c2);

    //turn into a improper fraction
    int newNumerator1 = (c1 * d1) + n1;
    int newNumerator2 = (c2 * d2) + n2;
    int newDenominator = d1 * d2;

    //multiply numerators
    int product = newNumerator1 * newNumerator2;

    //turn back into a mixed number
    int whole = product / newDenominator;
    int remainder = product % newDenominator;
   
    addCharToMant(whole, remainder, newDenominator, result, len, isPos);

    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    bool isPos = true;
    checkCharacteristics(isPos, c1, c2);

    int newN1 = (c1 * d1) + n1;
    int newN2 = (c2 * d2) + n2;

    //now multiply the first fraction by the reciprocal of the second
    int product1 = newN1 * d2;
    int product2 = newN2 * d1;

    //turn back into a mixed number
    int whole = product1 / product2;
    int remainder = product1 % product2;

    addCharToMant(whole, remainder, product2, result, len, isPos);

    return true;
}

//This is the start of my helper functions

void checkCharacteristics(bool& isPos, int& c1, int& c2) {
    //check to see if one or both numbers entered are negative
    //if one is then the product is negative and we cleanse the value
    //if both are then the product is still positive but we still need to cleanse the value
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
}

int findCommonDenominator(int d1, int d2) {
   //first we need to find the GCD or greatest common divisor
    int commDiv = gcd(d1, d2);
    int commDenom = (d1 / commDiv) * d2;

    return commDenom;
}

int gcd(int d1, int d2) {

    while (d2 != 0) {
        //Using the Euclidean Algorithm
        //by repeatledy finding the remainder of the two denominators
        //then updating the two values with the remainder and dividend
        //eventually the remainder becomes zero and the quotient becomes the GCD
        int temp = d2;
        d2 = d1 % d2;
        d1 = temp;
    }

    return d1;
}

int countDigits(int num) {
    //counts the amount of digits a integer has and returns that number
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
    //this function takes a characteristic and mantissa, 2 3/4
    //then adds them together to make a floating point number
    
    int index = 0;
    int numDigits = countDigits(integer);
    int temp = integer;

    //if number is negative add - 
    if (isPos == false) {
        result[index++] = '-';
    }
    
    //start from the back of the integer or before decimal point
    int startIndex = index + numDigits - 1;
    for (int i = startIndex; i >= index; i--) {
        result[i] = '0' + (temp % 10);
        temp /= 10;
    }
    
    //update index
    index += numDigits;

    //add decimal point
    result[index++] = '.';


    for (int i = index; i < len - 1; i++) {
        //move decimal point over one place
        num *= 10;

        //use long division
        //add whole number to mantissa
        //remainder replaces num
        result[i] = '0' + (num / den);
        num %= den;

        //increase index so that we can correctly terminate string at the end
        index++;

        if (num == 0) { //stop here when there isn't any more numbers to divide
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


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
void addCharToMant(int integer, int num, int den, char result[], int len);
void addTester();
void subtractTester();
//void fractionToDecimal(int num, int den, char result[], int len);

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

    if (subtract(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //diplay string with answer 0.8333333
        cout << "Answer for subtract: " << answer << endl;
    }
    else
    {
        //display error message
        cout << "Error on subtract" << endl;
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

   // addTester();
    subtractTester();

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
    
    //add c1 and c2 together 
    int sumOfChar = c1 + c2;
    int sumOfMant;

    //check if denominators are the same
    if (d1 == d2) {
        sumOfMant = n1 + n2;
        addCharToMant(sumOfChar, sumOfMant, d1, result, len);
    }
    else  { //if here find a way to make denominators equal
        int newDenominator = findCommonDenominator(d1, d2);
        //cout << "The new denominator of " << d1 << " and " << d2 << " is " << newDenominator << endl;

        //now update numerators
        int newN1 = newDenominator / d1;
        newN1 = newN1 * n1;

        int newN2 = newDenominator / d2;
        newN2 = newN2 * n2;

        //now add numerators together
        sumOfMant = newN1 + newN2;
        if (sumOfMant >= newDenominator) { //check if the fraction is greater than or equal to 1
            sumOfChar += (sumOfMant / newDenominator);
            sumOfMant = sumOfMant % newDenominator;
        }
        
        addCharToMant(sumOfChar, sumOfMant, newDenominator, result, len);
       
    }

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers

    //substract c1 and c2
    int diffOfChar = c1 - c2;
    int diffOfMant;

    if (d1 == d2) {
        diffOfMant = n1 - n2;
    } 
    else { //find common denominator
        int newDenominator = findCommonDenominator(d1, d2);

        //update numerators
        int newN1 = newDenominator / d1;
        newN1 *= n1;
        int newN2 = newDenominator / d2;
        newN2 *= n2;

        //subtract numerators
        if(newN1)
        diffOfMant = newN1 - newN2;

        addCharToMant(diffOfChar, diffOfMant, newDenominator, result, len);
    }

    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
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

void addCharToMant(int integer, int num, int den, char result[], int len) {
 
    int numDigits = countDigits(integer);
    int temp = integer;
    int index = 0;

    for (int i = 0; i < numDigits; i++) {
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

    cout << "Result: " << result <<  " and should be: 7.05" << endl;

    char result1[10];
    c1 = 2;
    n1 = 3;
    d1 = 7;

    c2 = 2;
    n2 = 2;
    d2 = 7;

    //2.42857142857 + 2.28571428571 = 4.7142857
    add(c1, n1, d1, c2, n2, d2, result1, 10);

    cout << "Result: " << result1 << " and should be: 4.7142857" << endl;

    //2.66666666 + 3.46 = 6.12666666

    char result2[10];
    c1 = 2;
    n1 = 2;
    d1 = 3;

    c2 = 3;
    n2 = 23;
    d2 = 50;

    add(c1, n1, d1, c2, n2, d2, result2, 10);
    cout << "Result: " << result2 << " and should be: 6.126666666" << endl;
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
    cout << "Result: " << result << endl;
    
    char result1[10];
    c1 = 3;
    n1 = 5;
    d1 = 7;

    c2 = 4;
    n2 = 1;
    d2 = 3;

    //3.71428571 - 4.3333333333 = -0.61904759
    subtract(c1, n1, d1, c2, n2, d2, result1, 10);
    cout << "Result: " << result1 << endl;




}

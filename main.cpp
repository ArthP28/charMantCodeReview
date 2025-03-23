
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
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

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
    }
    else  { //if here find a way to make denominators equal
        int newDenominator = findCommonDenominator(d1, d2);
        cout << "The new denominator of " << d1 << " and " << d2 << " is " << newDenominator << endl;

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


        //now format the c string
        if (sumOfMant == 0) { //no fraction just a whole number
            //check how many digits the whole number contains
            int numDigits = countDigits(sumOfChar);
            cout << numDigits << endl;

            //add the integer to the c string
                char digit = '0' + sumOfChar;
                result[numDigits - 1] = digit;
                result[numDigits] = '\0';
            
        }
        else {

        }
        
    }

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
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

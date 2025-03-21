
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

// -- HELPER FUNCTIONS --
int findCharAtPosition(const char numString[], char charToFind);
int charToInt(char charToConvert);
int wholePlaceValue(int value, int power);
bool isNumericChar(char charToCheck);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "-120a3.456"; 
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
    c1 = 1; // Characteristic
    n1 = 1; // Numerator
    d1 = 2; // Denominator

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
    c = 0; // c is reinitialized to 0 to prevent accidental changes
    int numberToAdd = 0; // The int that will be converted from the char in the C String
    int floatingPointLocation = findCharAtPosition(numString, '.'); // The index of the floating point if it exists
    // Count from the beginning of the floating point to the largest whole place value
    for(int i = floatingPointLocation - 1; i >= 0; i--)
    {
        if(numString[i] == '-') // If the whole number is negative, multiply the whole result by -1
        {
            c *= -1;
        }
        else if (numString[i] == '+')
        {
            // If the number starts with a plus sign, nothing happens because the number is positive. Move onto the next number
        }
        else if (isNumericChar(numString[i]))
        {
            numberToAdd = charToInt(numString[i]);
            c += wholePlaceValue(numberToAdd, floatingPointLocation - i - 1); // Add to c the int on the C String raised to its place value
        }
        else // If an invalid character is read, return false
        {
            return false;
        }
    }
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //First find if the floating point exists
    numerator = 456;
    denominator = 1000;
    return true;
}

// ******** MY HELPER FUNCTIONS ********

// Returns the location of a specific character to find. It works like std::find() but it does not require range parameters
int findCharAtPosition(const char numString[], char charToFind){
    int currentPosition = 0;
    while(numString[currentPosition] != '\0' && numString[currentPosition] != charToFind){
        currentPosition++;
    }
    return currentPosition; // Either returns the position of the char if found, or the length of the string if it cannot be found
}

int charToInt(char charToConvert){ // Converts a numeric char into an integer
    int result = -1;
    if(isNumericChar(charToConvert)){ // Only takes whole numbers from 0 - 9, anything that isn't is returned as -1
        result = charToConvert - '0';
    }
    return result;
}

int wholePlaceValue(int value, int power){ // Returns the product of a specific number times 10 raised to a place value
    // IMPORTANT: 0 = 1 (ones), 1 = 10 (tens), 2 = 100 (hundreds), 3 = 1000 (thousands)
    int exponent = 1;
    for(int i = 0; i < power; i++){ // For loop calculates place value exponent, 10 to the nth power
        exponent *= 10;
    }
    return value * exponent;
}

bool isNumericChar(char charToCheck){
    // Boolean returns true if the numeric value of a char is between the values of the lowest numeric char and the highest numeric char.
    return charToCheck >= '0' && charToCheck <= '9';
}

//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    result[0] = '4';
    result[1] = '.';
    result[2] = '1';
    result[3] = '6';
    result[4] = '6';
    result[5] = '6';
    result[6] = '6';
    result[7] = '6';
    result[8] = '6';
    result[9] = '\0';

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

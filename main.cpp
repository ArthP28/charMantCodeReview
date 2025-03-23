
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
int skipTrailingZeroes(const char numString[], int floatPointIndex);

const int MAXIMUM_MANTISSA_PLACE_VALUE = 10; // Mantissa can only be up to ten digits long. Any mantissa longer than that will have its remaining digits truncated.

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "321.456"; 
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
            c += wholePlaceValue(numberToAdd, floatingPointLocation - i); // Add to c the int on the C String raised to its place value
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
    numerator = 0;
    denominator = 0;
    //First find if the floating point exists
    int floatingPointLocation = findCharAtPosition(numString, '.');
    if(numString[floatingPointLocation] == '\0') // If it doesn't, the mantissa becomes 0 / 1;
    {
        numerator = 0;
        denominator = 1;
    }
    else // If it does, proceed with finding the mantissa
    {
        // Step 1: Load up all numbers from the mantissa to a separate C String

        // Go through all trailing zeroes from the floating point until we reach a number that isn't 0
        int nonZeroIndex = skipTrailingZeroes(numString, floatingPointLocation);
        int maxRange = MAXIMUM_MANTISSA_PLACE_VALUE - nonZeroIndex;
        char mantissa[MAXIMUM_MANTISSA_PLACE_VALUE];
        // This variable holds the nonZeroIndex added by the index of the floating point, so that the following loop algorithm finds a mantissa number at the correct location
        int floatIndex = 0;
        for(int i = 0; i < maxRange; i++){
            floatIndex = nonZeroIndex + floatingPointLocation;
            if(isNumericChar(numString[floatIndex])){
                mantissa[i] = numString[floatIndex];
            } else if (numString[floatIndex] == '\0') // If the end of numString is reached early, stop putting more chars inside the mantissa string
            {
                maxRange = i;
                break;
            }
            else // If a non-numeric character or null terminator function is found, stop the loop and return false
            {
                return false;
            }
            nonZeroIndex++;
        }
        mantissa[maxRange] = '\0'; // End C String with null terminator (So that is functions like a C String)

        // Step 2: Count backwards from the last number of the mantissa to the first, using the same algorithm as the characteristic
        int numberToAdd = 0;
        for(int i = maxRange - 1; i >= 0; i--){
            numberToAdd = charToInt(mantissa[i]);
            numerator += wholePlaceValue(numberToAdd, maxRange - i); // Add to c the int on the C String raised to its place value
        }

        // Step 3: Calculate the denominator by raising ten to the length of the entire mantissa, including the trailing zeroes
        int mantissaLength = nonZeroIndex;
        denominator = wholePlaceValue(1, mantissaLength);
    }
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
    int result = 0;
    int exponent = 1;
    for(int i = 0; i < power - 1; i++){ // For loop calculates place value exponent, 10 to the nth power
        exponent *= 10;
    }
    result = value * exponent;
    return result;
}

bool isNumericChar(char charToCheck){
    // Boolean returns true if the numeric value of a char is between the values of the lowest numeric char and the highest numeric char.
    return charToCheck >= '0' && charToCheck <= '9';
}

int skipTrailingZeroes(const char numString[], int floatPointIndex){
    // Iterates through all trailing zeroes from the floating point until a number that isn't zero is reached
    int nonZeroIndex = floatPointIndex + 1;
    while(numString[nonZeroIndex] == '0'){
        nonZeroIndex++;
    }
    return nonZeroIndex - floatPointIndex; // Then return the index of that nonzero number in the mantissa
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

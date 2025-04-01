
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

//test helpers
void testCharacteristicAndMantissa();
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(const char number[]);

const int MAXIMUM_PLACE_VALUE = 10; // Mantissa can only be up to ten digits long. Any mantissa longer than that will have its remaining digits truncated.

int main()
{
    //characteristic and mantissa test
    testCharacteristicAndMantissa();

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

void testCharacteristicAndMantissa()
{
    //number with a non-zero characteristic a decimal point and a non-zero mantissa
    shouldConvert("123.456", 123, 456, 1000);
    shouldConvert("    123.456", 123, 456, 1000);
    shouldConvert("123.456    ", 123, 456, 1000);
    shouldConvert("    123.456    ", 123, 456, 1000);
    
    //unary plus/minus
    shouldConvert("+123.456", 123, 456, 1000);
    shouldConvert("   +123.456", 123, 456, 1000);
    shouldConvert("+123.456   ", 123, 456, 1000);
    shouldConvert("   +123.456   ", 123, 456, 1000);
    shouldConvert("-123.456", -123, 456, 1000);
    shouldConvert("   -123.456", -123, 456, 1000);
    shouldConvert("-123.456   ", -123, 456, 1000);
    shouldConvert("    -123.456   ", -123, 456, 1000);

    //number with a zero characteristic and a non-zero mantissa
    shouldConvert("0.456", 0, 456, 1000);
    shouldConvert("   0.456", 0, 456, 1000);
    shouldConvert("0.456   ", 0, 456, 1000);
    shouldConvert("   0.456   ", 0, 456, 1000);
    
    //number with no characteristic digits and a non-zero mantissa
    shouldConvert(".456", 0, 456, 1000);
    shouldConvert("    .456", 0, 456, 1000);
    shouldConvert(".456   ", 0, 456, 1000);
    shouldConvert("   .456   ", 0, 456, 1000);
    
    //number with a non-zero characteristic and no mantissa
    shouldConvert("0", 0, 0, 10);
    shouldConvert("-0", -0, 0, 10);
    shouldConvert("123456", 123456, 0, 10);
    shouldConvert("   123456", 123456, 0, 10);
    shouldConvert("123456   ", 123456, 0, 10);
    shouldConvert("   123456   ", 123456, 0, 10);
    
    //unary plus/minus
    shouldConvert("-123456", -123456, 0, 10);
    shouldConvert("   -123456", -123456, 0, 10);
    shouldConvert("-123456   ", -123456, 0, 10);
    shouldConvert("   -123456   ", -123456, 0, 10);
    shouldConvert("+123456", 123456, 0, 10);
    shouldConvert("   +123456", 123456, 0, 10);
    shouldConvert("+123456   ", 123456, 0, 10);
    shouldConvert("   +123456   ", 123456, 0, 10);

    //number with a non-zero characteristic and a zero mantissa
    shouldConvert("123456.0", 123456, 0, 10);
    shouldConvert("   123456.0", 123456, 0, 10);
    shouldConvert("123456.0   ", 123456, 0, 10);
    shouldConvert("   123456.0   ", 123456, 0, 10);
    
    //unary plus/minus
    shouldConvert("-123456.0", -123456, 0, 10);
    shouldConvert("   -123456.0", -123456, 0, 10);
    shouldConvert("-123456.0   ", -123456, 0, 10);
    shouldConvert("   -123456.0   ", -123456, 0, 10);
    shouldConvert("+123456.0", 123456, 0, 10);
    shouldConvert("   +123456.0", 123456, 0, 10);
    shouldConvert("+123456.0   ", 123456, 0, 10);
    shouldConvert("   +123456.0   ", 123456, 0, 10);

    //check leading and trailing zeros
    shouldConvert("000123.456", 123, 456, 1000);
    shouldConvert("123.45600000", 123, 456, 1000);
    shouldConvert("00000123.45600000", 123, 456, 1000);
    
    //unary plus/minus
    shouldConvert("-000123.456", -123, 456, 1000);
    shouldConvert("-123.45600000", -123, 456, 1000);
    shouldConvert("-00000123.45600000", -123, 456, 1000);
    shouldConvert("+000123.456", 123, 456, 1000);
    shouldConvert("+123.45600000", 123, 456, 1000);
    shouldConvert("+00000123.45600000", 123, 456, 1000);

    //significant zeros in mantissa
    shouldConvert("123.00000456", 123, 456, 100000000);
    shouldConvert("-123.00000456", -123, 456, 100000000);
    shouldConvert("+123.00000456", 123, 456, 100000000);

    //these should fail
    shouldNotConvert("");
    shouldNotConvert("   ");
    shouldNotConvert(".");
    shouldNotConvert("+");
    shouldNotConvert("-");
    shouldNotConvert("..");
    shouldNotConvert("+.");
    shouldNotConvert("-.");
    shouldNotConvert("c");
    shouldNotConvert("cat");
    shouldNotConvert("-cat");
    shouldNotConvert("123.");
    shouldNotConvert("123.   ");
    shouldNotConvert("123.456+");
    shouldNotConvert("123.456 +");
    shouldNotConvert("123.456 cat");
    shouldNotConvert("123.cat");
    shouldNotConvert("cat.456");
    shouldNotConvert("+-123.456");
    shouldNotConvert("1.23.456");
    shouldNotConvert(".123.456");
    shouldNotConvert("--123.456");
    shouldNotConvert("123   456");
    shouldNotConvert("123  .  456");
    shouldNotConvert("  123  .  456");
    shouldNotConvert("127.0.0.1");
}
//--
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
    int c, n, d;

    //if the conversion from C string to integers can take place
    if (characteristic(number, c) && mantissa(number, n, d))
    {
        if (c == expectedCharacteristic && n == expectedNumerator && d == expectedDenominator)
        {
            //test passes, do not print anything on a successful test
        }
        else
        {
            cout << "Test failed: '" << number << "' "
                << "was parsed but did not produce the expected results" << endl;

            if (expectedCharacteristic != c)
            {
                cout << "expected characteristic: " << expectedCharacteristic << " "
                    << "actual characteristic: " << c << endl;
            }

            if (expectedNumerator != n)
            {
                cout << "expected numerator: " << expectedNumerator << " "
                    << "actual numerator: " << n << endl;

            }

            if (expectedDenominator != d)
            {
                cout << "expected denominator: " << expectedDenominator << " "
                    << "actual denominator: " << d << endl;
            }
        }
    }
    else
    {
        cout << "Test failed: '" << number << "' "
            << "was NOT parsed when it should have been." << endl;
        if (expectedCharacteristic != c)
        {
            cout << "expected characteristic: " << expectedCharacteristic << " "
                << "actual characteristic: " << c << endl;
        }

        if (expectedNumerator != n)
        {
            cout << "expected numerator: " << expectedNumerator << " "
                << "actual numerator: " << n << endl;

        }

        if (expectedDenominator != d)
        {
            cout << "expected denominator: " << expectedDenominator << " "
                << "actual denominator: " << d << endl;
        }
    }
}
//--
void shouldNotConvert(const char number[])
{
    int c, n, d;

    //if the conversion from C string to integers can take place
    if (characteristic(number, c) && mantissa(number, n, d))
    {
        cout << "Test failed: '" << number << "' "
            << "was parsed when it should NOT have been." << endl;
    }
}


//--
// This function has since been restructured to parse into another C string, so that further evaluation will be tested on it
bool characteristic(const char numString[], int& c)
{
    c = 0; // c is reinitialized to 0 to prevent accidental changes
    int numberToAdd = 0; // The int that will be converted from the char in the C String

    if(numString == ""){ // If nothing is in the numeric C String, return false before doing anything else
        return false; // Null C Strings are not allowed!
    }

    int floatingPointLocation = findCharAtPosition(numString, '.'); // The index of the floating point if it exists
    char characteristic[MAXIMUM_PLACE_VALUE];
    int lengthOfNumber = 0;
    // Count from the beginning of the floating point to the largest whole place value
    for(int i = 0; i < floatingPointLocation; i++)
    {
        if (isNumericChar(numString[i]))
        {
            characteristic[i] = numString[i]; // Add to c the int on the C String raised to its place value
            lengthOfNumber = i + 1;
            // Any trailing spaces will stop the parsing
            if(numString[i+1] == ' '){ // This goes inside the numeric condition so it only works when there are numbers found
                break;
            }
        }
        else if(numString[i] == '-' || numString[i] == '+') // Unary signs are acceptable as long as they precede a number
        {
            if(isNumericChar(numString[i+1])){
                characteristic[i] = numString[i];
            } else {
                return false;
            }
        } else if (numString[i] == ' '){ // Count any leading spaces in the string that will be discarded later
            characteristic[i] = numString[i];
        }
        else // If an invalid character is read, return false
        {
            return false;
        }
    }
    characteristic[lengthOfNumber] = '\0'; // End String with Null Terminator

    // Iterating Through Character String backwards (Least Significant Digit to greatest)
    for(int i = lengthOfNumber - 1; i >= 0; i--){
        if(characteristic[i] == '-'){
            if(c < 0){ // Double negatives (--) are illegal
                return false;
            } else if (characteristic[i + 1] == '+'){ // Negative Positives (+-) are also illegal
                return false;
            } else { // Multiply by -1 to get negative
                c *= -1;
            }
        } else if (characteristic[i] == '+'){
            if(c < 0){ // Negative Positives (+-) are illegal
                return false;
            } else if (characteristic[i + 1] == '+'){ // Positive Positives (++) are also illegal
                return false;
            } else {
                // Do nothing. Unary Plus only means the float is positive
            }
        } else if (characteristic[i] == ' '){ // Stop iterating when we approach leading spaces
            break;
        } else { // Add converted int to c
            numberToAdd = charToInt(characteristic[i]);
            c += wholePlaceValue(numberToAdd, lengthOfNumber - i);
        }
    }

    return true; // If no interruptions, characteristic parsing is good!
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    numerator = 0;
    denominator = 0;
    //First find if the floating point exists
    int floatingPointLocation = findCharAtPosition(numString, '.');
    if(numString[floatingPointLocation] == '\0') // If it doesn't, the mantissa becomes 0 / 10;
    {
        numerator = 0;
        denominator = 10;
    }
    else // If it does, proceed with finding the mantissa
    {
        // Step 1: Load up all numbers from the mantissa to a separate C String

        // Go through all trailing zeroes from the floating point until we reach a number that isn't 0
        int nonZeroIndex = skipTrailingZeroes(numString, floatingPointLocation);
        int maxRange = MAXIMUM_PLACE_VALUE;
        char mantissa[MAXIMUM_PLACE_VALUE];
        // This variable below holds the nonZeroIndex added by the index of the floating point, so that the following loop algorithm finds a mantissa number at the correct location
        int floatIndex = 0;
        int numberOfZeroes = 0; // This counts the number of trailing zeroes
        for(int i = 0; i < maxRange; i++){
            floatIndex = nonZeroIndex + floatingPointLocation;
            if(isNumericChar(numString[floatIndex])){
                mantissa[i] = numString[floatIndex];
                if (numString[floatIndex] == '0'){ // Since this counter variable only stores trailing zeroes, any non-zero number will reset it
                    numberOfZeroes++;
                } else {
                    numberOfZeroes = 0;
                }
            } else if (numString[floatIndex] == ' '){ // Any spaces will also be counted towards the mantissa. Handling them comes later on in the function
                mantissa[i] = numString[floatIndex];
            }
            else if (numString[floatIndex] == '\0') // If the end of numString is reached early, stop putting more chars inside the mantissa string
            {
                maxRange = i;
                break;
            }
            else // If a non-numeric character is found, stop the loop and return false
            {
                return false;
            }
            nonZeroIndex++;
        }
        mantissa[maxRange] = '\0'; // End C String with null terminator (So that is functions like a C String)
        
        // Step 2: Count backwards from the last number of the mantissa to the first, using the same algorithm as the characteristic, in order to produce the numerator
        int numeratorRange = maxRange - numberOfZeroes; // This new variable chops off the trailing zeroes at the end, so that the numerator is calculated correctly
        int numberToAdd = 0;
        int numSpaces = 0; // Records the amount of space chars that will be excluded when adding to the numerator by place value
        for(int i = numeratorRange - 1; i >= 0; i--){
            if(isNumericChar(mantissa[i])){
                numberToAdd = charToInt(mantissa[i]);
                numerator += wholePlaceValue(numberToAdd, numeratorRange - i - numSpaces); // Add to numerator the int on the C String raised to its place value
            } else if (mantissa[i] == ' '){
                if(isNumericChar(mantissa[i+1])){ // Leading spaces are not allowed in a mantissa!
                    return false;
                }
                numSpaces++;
            } else { // Any other symbol, if picked up into mantissa for some reason, returns false in case.
                return false;
            }
        }

        // Step 3: Calculate the denominator by raising ten to the length of the entire mantissa, including the leading zeroes
        int mantissaLength = nonZeroIndex;
        // Get rid of all trailing zeroes and spaces to correctly calculate mantissa
        if (numberOfZeroes > 0){
            mantissaLength -= numberOfZeroes;
        }
        if (numSpaces > 0){
            mantissaLength -= numSpaces;
        }
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
    int result = 0; // FIXED: Changed result variable here to 0 since setting it to -1 was pointless
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

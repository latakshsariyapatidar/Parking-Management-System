#include <string>
#include <iostream>
#include <stdexcept>
#include "Vehicle.h"


using namespace std;

int main()
{
    string registrationNumber = "CAR-1234-Lataksh";
    try
    {
        Car c1("");
        cout << c1.getRegistrationNumber();
    }
    catch (const invalid_argument &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
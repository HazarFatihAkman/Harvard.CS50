#include <iostream>
#include <string>

using namespace std;

class contactInformation
{
    public :
        string firstName;
        string lastName;
        string phoneNumer;

        bool validate(string input)
        {
            if (input == "")
            {
                return false;
            }

            return true;
        }

        void reset()
        {
            firstName = "";
            lastName = "";
            phoneNumer = "";
        }
};

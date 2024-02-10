#include "Models/phonebookEvents.h"

using namespace std;

int main(void)
{
    cin.clear();
    cin.sync();

    contactInformation contactInfo;
    phonebookEvents events;
    events.phonebookPath = "phonebook.json";
    int selectedMode, quitApp = 0;

    while (quitApp == 0)
    {
        while(selectedMode != 1 && selectedMode != 2 && selectedMode != 3)
        {
            if (quitApp == 0)
            {
                cout << "1. New Contact \n";
                cout << "2. Contact List \n";
                cout << "3. Delete Contact (you should know index number of contact -> check contact list first if you don't know) \n";
                cout << "----------------- \n";

                cin >> selectedMode;

                cout << "------------ \n" << endl; 
            }
        }

        if (selectedMode == 1)
        {
            contactInfo.reset();
            cout << "_____________\n";
            cout << "[New Contact] \n";

            while(!contactInfo.validate(contactInfo.firstName))
            {
                cout << "Contact First Name : ";
                getline(cin >> ws, contactInfo.firstName);
            }

            while(!contactInfo.validate(contactInfo.lastName))
            {
                cout << "Contact Last Name : ";
                getline(cin >> ws, contactInfo.lastName);
            }

            while(!contactInfo.validate(contactInfo.phoneNumer))
            {
                cout << "Contact Phone Number : ";
                getline(cin >> ws, contactInfo.phoneNumer);
            }

            events.addContact(contactInfo);
            selectedMode = 0;
        }
        else if (selectedMode == 2)
        {
            events.printExistsContacts();
            selectedMode = 0;
        }
        else if (selectedMode == 3)
        {
            string index;
            cout << "What's the index number of contact?" << endl;
            getline(cin >> ws, index);
            events.deleteContactInfoByIndexNumber(::stoi(index));

            selectedMode = 0;
        }

        cout << "Quit App? yes(1)/no(0)" << endl;
        cin >> quitApp;
    }
}
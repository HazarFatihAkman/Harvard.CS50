#include <fstream>
#include <list>
#include <algorithm>
#include "contactInformation.h"

using namespace std;

class phonebookEvents
{
    public :
        string phonebookPath;

        void addContact(contactInformation contactInfo)
        {
            string jsonLine, previousStr, cleanJsonLine = "";
            string newJsonData = getJsonTemplate(contactInfo);

            list<string> contacts = getExistsContacts();
            auto found = std::find(contacts.begin(), contacts.end(), newJsonData);

            if (found == contacts.end())
            {
                contacts = addCommaToLastData(contacts);
                contacts.push_back(newJsonData);
                cout << "First Name : " + contactInfo.firstName + "\n";
                cout << "Last Name : " + contactInfo.lastName + "\n";
                cout << "Phone Number :" + contactInfo.phoneNumer + "\n";
            }
            else
            {
                cout << "This contact's already exist" << endl;
                return;
            }

            writeJsonDataList(createJsonContent(contacts));
            cout << contactInfo.firstName + " " + contactInfo.lastName + " added" << endl;
        };

        list<string> getExistsContacts()
        {
            string jsonLine, previousStr, cleanJsonLine;
            list<string> contacts;
            ifstream jsonFile(phonebookPath);

            while(getline(jsonFile, jsonLine))
            {
                cleanJsonLine = getCleanStr(jsonLine, ' ');
                if (cleanJsonLine == "[" || cleanJsonLine == "]")
                {
                    previousStr = cleanJsonLine;
                }
                if (cleanJsonLine != "[" && previousStr == "[")
                {
                    contacts.push_back(jsonLine);
                }
            }

            jsonFile.close();
            return contacts;
        };

        void printExistsContacts()
        {
            int i = 1;
            for(string contact : getExistsContacts())
            {
                printContactInfoByJsonData(contact, ::to_string(i));
                i++;
            }
        };

        void printContactInfoByJsonData(string jsonData, string index)
        {
            string delimiter = ",";
            jsonData = getCleanStr(jsonData, ' ');
            jsonData = getCleanStr(jsonData, '{');
            jsonData = getCleanStr(jsonData, '}');
            
            cout << "[" + index + "]---------------" << endl;

            size_t pos = 0;
            while ((pos = jsonData.find(",")) != std::string::npos)
            {
                string value = jsonData.substr(0, pos);
                cout << value << endl;
                jsonData.erase(0, pos + delimiter.length());

                if ((pos = jsonData.find(",")) == std::string::npos)
                {
                    cout << jsonData << endl;
                }
            }
        };

        void deleteContactInfoByIndexNumber(int index)
        {
            list<string> contacts, newContacts;
            contacts = getExistsContacts();
            if (contacts.size() == 0)
            {
                cout << "Phonebook is empty." << endl;
                return;
            }

            int i = 1;
            for(string contact : contacts)
            {
                if (i != index)
                {
                    newContacts.push_back(contact);
                }
                i++;
            }
            
            writeJsonDataList(createJsonContent(newContacts));
            cout << "\n" << endl;
            cout << " Removed " + index << endl;
        };

    private :
        string getJsonTemplate(contactInformation contactInfo)
        {
            return "        { \"firstname\" : \"" + contactInfo.firstName + "\", \"lastName\" : \"" + contactInfo.lastName + "\", \"phoneNumber\" : \"" + contactInfo.phoneNumer + "\" }";
        };

        string getCleanStr(string str, char removeChar)
        {
            str.erase(remove(str.begin(), str.end(), removeChar), str.end());
            return str;
        };

        ::list<string> addCommaToLastData(::list<string> list)
        {
            ::list<string> responseList;
            int i = 1;

            for(string value : list)
            {
                if (list.size() == i)
                {
                    responseList.push_back(value + ",");
                }
                else
                {
                    responseList.push_back(value);
                }

                i++;
            }

            return responseList;
        };

        void writeJsonDataList(list<string> jsonDataList)
        {
            ofstream jsonFile(phonebookPath);

            for(string str : jsonDataList)
            {
                jsonFile << str << endl;
            }

            jsonFile.close();
        };

        list<string> createJsonContent(list<string> contacts)
        {
            list<string> jsonDataList;
            
            //Header
            jsonDataList.push_back("{");
            jsonDataList.push_back("    \"contacts\" :");
            jsonDataList.push_back("    [");
            
            for(string contact : contacts)
            {
                jsonDataList.push_back(contact);
            }
            
            //Footer
            jsonDataList.push_back("    ]");
            jsonDataList.push_back("}");

            return jsonDataList;
        }
};

// File: proj2.cpp
// Project: CMSC 202 proj2, Fall 2021
// Author: Gabe Aquino
// Date: 10/13/2021
// Section: 30/33
// E-mail: lq90575@umbc.edu
// Emulates a friend finder program

#include <iostream>
#include <string>
#include <fstream>
using namespace std;



// Person.h
//constants
const int MAX_FRIENDS = 10; //Maximum number of friends a person can have

class Person {
    public:
        // Name: Person
        // Desc - Default Constructor for a Person
        // Preconditions - Creates a Person with no data associated with it
        // Postconditions - a Person is created
        Person();
        // Name: Person
        // Desc - Overloaded Constructor for a Person
        // Preconditions - Creates a Person with passed data
        // Postconditions - a Person is created
        Person(string, string, int, int);
        // Name: AddFriend
        // Desc - A person pointer is stored from the roster of people in an organization
        // Preconditions - A person pointer is passed
        // Postconditions - A person pointer is added to this perosn's m_friend's array
        //                  if not at maximum and not already in the array
        void AddFriend(Person*);
        // Name: RemoveFriend
        // Desc - Removes a person pointer from this peron's m_friend array
        // Preconditions - Person pointer exists in m_friend
        // Postconditions - Person is removed from m_friend and all pointers are moved towards front
        void RemoveFriend();
        // Name: CheckID
        // Desc - Checks to see if a specific person ID exists in m_friends - Note: IDs will always be unique in proj2
        // Preconditions - m_friends is populated
        // Postconditions - Returns true if id exists in m_friends else false
        bool CheckID(int);
        // Name: DisplayFriends
        // Desc - Displays information about each friend in the m_friend array
        // Preconditions - People are in the m_friend array
        // Postconditions - Displays information about person object in array
        void DisplayFriends();
        // Name: DisplayDetails
        // Desc - Displays information about this person
        // Preconditions - Person data is populated
        // Postconditions - Displays information about person object
        void DisplayDetails();
        // Name: SetDetails
        // Desc - Used as a setter for first name, last name, age, and id
        // Preconditions - Person already created
        // Postconditions - Member variables populated
        void SetDetails(string, string, int, int);
    private:
        string m_fName; //Person's first name
        string m_lName; //Person's last name
        int m_age; //Peron's age
        int m_ID; //Person's ID
        Person* m_friends[MAX_FRIENDS]; //Person's array of friends
        int m_friendCount; //Person's count of friends
};



// Person.cpp
Person::Person() {
    m_fName = "";
    m_lName = "";
    m_age = 0;
    m_ID = 0;
    m_friendCount = 0;
}

Person::Person(string fName, string lName, int age, int ID) {
    m_fName = fName;
    m_lName = lName;
    m_age = age;
    m_ID = ID;
}

void Person::AddFriend(Person* personAddress) {
    // You can only add a friend if you have less than MAX_FRIENDS
    if(m_friendCount < MAX_FRIENDS) {
        // You can only add a friend if you weren't friends with them before
        if(CheckID(personAddress->m_ID) == false) {
            m_friends[m_friendCount] = personAddress;
            m_friendCount++;

            cout << "You are now friends with " << personAddress->m_fName << "!" << endl;
        }

        // Otherwise it'll tell you that you were already friends with this guy
        else {
            cout << "You are already friends with " << personAddress->m_fName << "..." << endl;
        }
    } else {
        cout << "You can't have more than " << MAX_FRIENDS << " friends! sorry :(" << endl;
    }
}

void Person::RemoveFriend() {
    // You can only remove a friend if you even had one to begin with
    if(m_friendCount > 0) {
        DisplayFriends();

        int remove;
        cout << "Who would you like to remove?" << endl;
        cin >> remove;

        // remove can only be an integer between the inclusive range of 1 to n where n = m_friendCount
        if(1 <= remove && remove <= m_friendCount) {
            // Shifts the list of friends starting at the remove index over 1 to the left
            // I'm sure there are many ways to remove friends but this is just the simplest way for me
            for(int i = remove - 1; i < MAX_FRIENDS - 1; i++) {
                m_friends[i] = m_friends[i + 1];
            }

            // The last person in the friend list has to be updated to the memory address of a Person object with no name
            Person noOne;
            m_friendCount--;
            m_friends[m_friendCount] = &noOne;

            // If you don't know, this is a reference to Naruto
            // I might as well add an anime reference cause why not :/
            cout << "Weren't you gonna break our bond?! " << m_fName << "?!" << endl;
        }

        else {
            cout << "Invalid Input - Must be a number between 1 - " << m_friendCount << endl;
        }
    }

    // You can't remove a friend if you didn't even had one to begin with
    else {
        cout << "Dude, you're lonely... ;_;" << endl;
    }
}

bool Person::CheckID(int ID) {
    bool isFound = false;

    // Checks for each friend in the list of friends if any one of them matches the ID
    for(int i = 0; i < m_friendCount; i++) {
        if((*m_friends[i]).m_ID == ID) {
            isFound = true;
        }
    }

    return isFound;
}

void Person::DisplayFriends() {
    if(m_friendCount == 0) {
        cout << "You don't have any friends yet :(" << endl;
    } else {
        cout << "Friend List for " << m_fName << endl;

        // For each line, displays the information of each friend
        for(int i = 0; i < m_friendCount; i++) {
            cout << (i + 1) << ". ";
            (*m_friends[i]).DisplayDetails();
            cout << endl;
        }
    }
}

void Person::DisplayDetails() {
    cout << m_fName << " " << m_lName << " (" << m_age << " yrs) " << m_ID;
}

void Person::SetDetails(string fName, string lName, int age, int ID) {
    m_fName = fName;
    m_lName = lName;
    m_age = age;
    m_ID = ID;
}



// Organization.h
//Constants
const int MAX_PEOPLE = 40; //Maximum number of people in organization
const string FILE_NAME = "proj2_data.txt";

class Organization {
    public:
        // Name: Organization
        // Desc - Default constructor for Organization
        // Preconditions - None
        // Postconditions - Organization is created (empty) with 0 people in the roster
        Organization();
        // Name: SetName
        // Dsec - Sets m_name by asking user for name
        // Preconditions - m_name exists
        // Postconditions - Asks user for the organization name and populates m_name
        void SetName();
        // Name: LoadRoster
        // Desc - Sets m_fileName by asking user. Then populates all of the people loaded from file
        // Preconditions - m_fileName exists. m_roster empty
        // Postconditions - Asks user for m_fileName. Loads data from file and populates m_roster
        void LoadRoster();
        // Name: DisplayRoster
        // Desc - Displays a numbered list of everyone in the roster (starts at 1)
        // Preconditions - m_roster is populated
        // Postconditions - Displays a numbered list of people
        void DisplayRoster();
        // Name: GetPerson
        // Desc - Displays a list of people in m_roster and user enters number of desired person.
        //        Returns pointer of that person in m_roster
        // Preconditions - m_roster is populated
        // Postconditions - Returns pointer for the person chosen from list
        Person* GetPerson();
    private:
        string m_name; //Name of the organization
        string m_fileName; //Name of the input file
        int m_numRoster; //Number of people in roster
        Person m_roster [MAX_PEOPLE]; //Roster of people in the organization
};



// Organization.cpp
Organization::Organization() {
    // m_name = "";
    // m_fileName = FILE_NAME;
    // m_numRoster = MAX_PEOPLE;

    fstream myFile;

    m_name = "";
    do {
        cout << "Enter file name: ";
        cin >> m_fileName;
        myFile.open(m_fileName, ios::in);
    } while(myFile.is_open() == false);
    m_numRoster = MAX_PEOPLE;

    if(myFile.is_open()) {
        myFile.close();
    }
}

void Organization::SetName() {
    cout << "What is the name of your organization?" << endl;
    cin.ignore();
    getline(cin, m_name);
}

void Organization::LoadRoster() {
    fstream myFile;
    myFile.open(m_fileName, ios::in);
    int numLoaded = 0;

    // Updates the information for all 40 People objects in m_roster
    for(int i = 0; i < m_numRoster; i++) {
        //s_age and s_ID are temporary string types for age and ID
        string fName, lName, s_age, s_ID;

        getline(myFile, fName, ',');
        getline(myFile, lName, ',');
        getline(myFile, s_age, ',');
        getline(myFile, s_ID);

        // Officially turns the string types of s_age and s_ID to their proper int types: age and ID
        int age, ID;
        age = stoi(s_age);
        ID = stoi(s_ID);

        // Here is where the information of every Person object in m_roster is properly updated
        m_roster[i].SetDetails(fName, lName, age, ID);
        numLoaded++;
    }

    cout << numLoaded << " people loaded into the roster" << endl;

    if(myFile.is_open()) {
        myFile.close();
    }
}

void Organization::DisplayRoster() {
    cout << "****" << m_name << "****" << endl;

    for(int i = 0; i < MAX_PEOPLE; i++) {
        cout << (i + 1) << " ";
        m_roster[i].DisplayDetails();
        cout << endl;
    }
}

Person* Organization::GetPerson() {
    int chosen;

    DisplayRoster();
    cout << "Who would you like to friend?" << endl;
    cin >> chosen;

    // Validates input so that chosen must be in the range of 1 - 40
    if((1 <= chosen && chosen <= MAX_PEOPLE) == false) {
        do {
            cout << "Invalid Input - Must be a range between 1 - " << MAX_PEOPLE << endl;
            cout << "Who would you like to friend?" << endl;
            cin >> chosen;
        } while((1 <= chosen && chosen <= MAX_PEOPLE) == false);
    }

    // I thought I'd just change this now since indeces start at 0 while lists start at 1
    chosen--;

    Person* address = &(m_roster[chosen]);

    return address;
}



// FriendFinder.h
class FriendFinder {
    public:
        // Name: FriendFinder
        // Desc - Default constructor for application for finding friends
        // Preconditions - Creates a person and an organization
        // Postconditions - Welcomes user and calls Start()
        FriendFinder();
        // Name: GetDetails
        // Desc - Asks user for their first name, last name, age, and ID to populate m_me
        // Preconditions - None
        // Postconditions - Populates information related to m_me
        void GetDetails();
        // Name: DisplayMenu
        // Desc: - Displays main menu for application
        // Preconditions - None
        // Postconditions - Called from Start updates integer passed
        void DisplayMenu(int &choice);
        // Name: Start
        // Desc - Main function running FriendFinder
        //        Calls GetDetails
        //        Populates data for organization
        //        Continually calls DisplayMenu until someone enters 4 (exit)
        // Preconditions - m_me and m_organization are created but not populated
        // Postconditions - Runs until user enters 4. Thanks user for usage. Ends application
        void Start();
    private:
        Person m_me; //Information about me
        Organization m_organization; //Information about my organization
};



// FriendFinder.cpp

FriendFinder::FriendFinder() {
    cout << "*****************************" << endl;
    cout << "Welcome to UMBC Friend Finder" << endl;
    cout << "*****************************" << endl << endl;

    // LET'S GET IT!
    Start();
}

void FriendFinder::GetDetails() {
    string fName, lName, s_age, s_ID, orgName;
    int age, ID;

    cin.ignore();

    // Populates all information for m_me and m_organization
    cout << "What is your first name?" << endl;
    getline(cin, fName);
    cout << "What is your last name?" << endl;
    getline(cin, lName);
    cout << "What is your age?" << endl;
    cin >> s_age;
    age = stoi(s_age);
    // Validate that age must be a positive number, cause negative age doesn't make sense...
    while(age < 0) {
        cout << "Dude, you're hilarious... but like seriously, what is your age?" << endl;
        cin >> s_age;
        age = stoi(s_age);
    }
    cout << "What is your ID?" << endl;
    cin >> s_ID;
    ID = stoi(s_ID);
    // Validate that ID must be a positive number, cause we have to be SERIOUS here >:(
    while(ID < 0) {
        cout << "No way that your ID is a negative number! Please type it again :)" << endl;
        cin >> s_ID;
        ID = stoi(s_ID);
    }
    m_organization.SetName();
    m_organization.LoadRoster();

    m_me.SetDetails(fName, lName, age, ID);
}

void FriendFinder::DisplayMenu(int &choice) {
    cout << "What would you like to do?" << endl;
    cout << "1. Display Entire Organization" << endl;
    cout << "2. Display Friend List" << endl;
    cout << "3. Search for a Friend" << endl;
    cout << "4. Remove Friend" << endl;
    cout << "5. Exit" << endl;

    cin >> choice;
}

void FriendFinder::Start() {
    GetDetails();

    int choice;
    
    do {
        cout << endl;
        DisplayMenu(choice);

        // Validates choice so that is has to be in the inclusive range of 1 - 5
        // Otherwise the program won't do much after and just repeat DisplayMenu(choice);
        if(1 <= choice && choice <= 5) {

            // Choice #1: Display Entire Organization
            if(choice == 1) {
                cout << "You are: ";
                m_me.DisplayDetails();
                cout << endl << endl;

                m_organization.DisplayRoster();
            }

            // Choice #2: Display Friend List
            else if(choice == 2) {
                m_me.DisplayFriends();
            }

            // Choice #3: Search for Friend
            else if(choice == 3) {
                Person* personAddress = m_organization.GetPerson();
                m_me.AddFriend(personAddress);
            }

            // Choice #4: Remove Friend
            else if(choice == 4) {
                m_me.RemoveFriend();
            }

            // Choice #5: Exit
            // No code is needed - The program will just take itself out of the while loop
        } else {
            cout << "Invalid Input - Must be a number between 1 - 5" << endl;
        }
    } while(choice != 5);

    cout << "Thank you for using UMBC Friend Finder!";
}





//Do not edit main!
int main() {
    FriendFinder test;
    return 0;
}
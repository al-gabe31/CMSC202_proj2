#include <iostream>
#include <string>
#include "FriendFinder.h"
#include "Organization.h" //Must be implemented before FriendFinder
#include "Person.h" //Must be implemented before FriendFinder

using namespace std;

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

    // Populates all information for m_me and m_organization
    cout << "What is your first name?" << endl;
    cin >> fName;
    cout << "What is your last name?" << endl;
    cin >> lName;
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
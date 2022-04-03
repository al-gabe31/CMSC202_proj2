#include <iostream>
#include <string>
#include "FriendFinder.h"
#include "Organization.h" //Must be implemented before FriendFinder
#include "Person.h" //Must be implemented before FriendFinder

using namespace std;

Organization::Organization() {
    m_name = "";
    m_fileName = FILE_NAME;
    m_numRoster = MAX_PEOPLE;
}

void Organization::SetName() {
    cout << "What is the name of your organization?" << endl;
    cin >> m_name;
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
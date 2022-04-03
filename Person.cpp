#include <iostream>
#include <string>
#include "FriendFinder.h"
#include "Organization.h" //Must be implemented before FriendFinder
#include "Person.h" //Must be implemented before FriendFinder

using namespace std;

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
        cout << "You can have more than " << MAX_FRIENDS << " friends! sorry :(" << endl;
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
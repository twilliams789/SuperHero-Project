// Name: Tristen Williams
// File Name: project2.cpp
// Date: 3 October, 2026
// Program Description: Creates and manages a superhero team using a one-way linked list.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Hero
{
    string name;
    string role;
    Hero* next;
};
int heroCount = 0;
// Function prototypes
Hero* buildTeam(string filename);
void showTeam(Hero* head);
void deployHero(Hero* head);
void removeHero(Hero*& head);
void rearrangeTeam(Hero*& head);

// Build linked list from file
Hero* buildTeam(string filename)
{
    ifstream inputFile;
    inputFile.open(filename);
    // Starting with empty linked list
    Hero* head = NULL;
    Hero* tail = NULL;
    Hero* pnew = NULL;

    string name;
    string role;

    while (getline(inputFile, name, '|')) // Parsing
    {
        getline(inputFile, role);

        // Create a new node
        pnew = new Hero;

        pnew->name = name;
        pnew->role = role;
        pnew->next = NULL;

        // First node
        if (head == NULL)
        {
            head = pnew;
            tail = pnew;
        }
        // Insert at end
        else
        {
            tail->next = pnew;
            tail = pnew;
        }
        heroCount++;
    }

    inputFile.close();
    pnew = NULL;
    return head;
}
// Display team
void showTeam(Hero* head)
{
    Hero* walker = NULL;
    walker = head;
    int number = 1;
    cout << "--------------------------------" << endl;
    while (walker != NULL)
    {
        cout << number << ") " << walker->name << " " << walker->role << endl;
        walker = walker->next;
        number++;
    }
    cout << "--------------------------------" << endl;
}

// Deploy superhero
void deployHero(Hero* head)
{
    int heroNumber; // Variable to pick hero
    cout << "Enter the superhero number (1-" << heroCount << "): ";
    cin >> heroNumber;

    while (heroNumber < 1 || heroNumber > heroCount)
    {
        cout << "Invalid superhero number, enter again: ";
        cin >> heroNumber;
    }
    Hero* walker = NULL;
    walker = head; // Starts search from head
    int number = 1;
    while (number < heroNumber)
    {
        walker = walker->next;
        number++;
        // walker now points to next superhero
    }
    cout << walker->name << " has been deployed, role is " << walker->role << "!" << endl;
    walker = NULL;
}
// Remove superhero
void removeHero(Hero*& head)
{
    int heroNumber;
    cout << "Enter the superhero number (1-" << heroCount << "): ";
    cin >> heroNumber;
    while (heroNumber < 1 || heroNumber > heroCount)
    {
        cout << "Invalid superhero number, enter again: ";
        cin >> heroNumber;
    }
    // Delete first node
    if (heroNumber == 1)
    {
        Hero* tmp = NULL;
        tmp = head;
        head = head->next;
        cout << tmp->name << " has been removed from the team!" << endl;
        delete tmp;
        tmp = NULL;
        heroCount--;
    }
    // Delete middle or last node
    else
    {
        Hero* pre = NULL;
        Hero* cur = NULL;
        pre = head;
        cur = head->next;
        int number = 2;

        while (number < heroNumber)
        {
            pre = cur;
            cur = cur->next;
            number++;
        }
        pre->next = cur->next; // Making node point to next node after one that was deleted
        cout << cur->name << " has been removed from the team!" << endl;
        delete cur;
        pre = NULL;
        cur = NULL;
        heroCount--;
    }
}
// Rearrange a group of heroes
void rearrangeTeam(Hero*& head)
{
    int startNumber;
    int endNumber;
    cout << "Enter the starting superhero number (1-" << heroCount << "): ";
    cin >> startNumber;

    while (startNumber < 1 || startNumber > heroCount)
    {
        cout << "Invalid superhero number, enter again: ";
        cin >> startNumber;
    }
    cout << "Enter the ending superhero number (1-" << heroCount << "): ";
    cin >> endNumber;

    while (endNumber < startNumber || endNumber > heroCount)
    {
        cout << "Invalid superhero number, enter again: ";
        cin >> endNumber;
    }
    // If selected group already starts at head
    if (startNumber == 1)
    {
        cout << "Team rearranged!" << endl;
    }
    else
    {
        Hero* pre = NULL;
        Hero* cur = NULL;
        Hero* first = NULL;   // will point to first node in group 
        Hero* last = NULL;   // will point to last nide in selected group
        Hero* after = NULL;  // will point to node right after selected group

        pre = head;
        cur = head->next;
        int number = 2;

        // Find first selected node
        while (number < startNumber)
        {
            pre = cur;
            cur = cur->next;
            number++;
        }
        first = cur; // Saving first node in group

        // Find last selected node
        while (number < endNumber)
        {
            cur = cur->next;
            number++;
        }
        last = cur; // Saving last node in group

        // Save node after selected group
        after = last->next;

        // Remove group from old position
        pre->next = after;

        // Attach selected group before old head
        last->next = head;

        // Selected group now starts the list
        head = first;
        // Deallocating variables
        pre = NULL;
        cur = NULL;
        first = NULL;
        last = NULL;
        after = NULL;

        cout << "Team rearranged!" << endl;
    }
}
int main()
{
    Hero* head = NULL;
    string filename;
    int option = 0;
    cout << "Enter the superhero filename: ";
    cin >> filename;
    head = buildTeam(filename);
    cout << "Superhero team created!" << endl;

    while (option != 5)
    {
        cout << "1) Show the team" << endl;
        cout << "2) Deploy a superhero" << endl;
        cout << "3) Remove a superhero" << endl;
        cout << "4) Rearrange the team" << endl;
        cout << "5) Quit" << endl;

        cout << "Enter your option: ";
        cin >> option;

        while (option < 1 || option > 5)
        {
            cout << "Invalid option, enter again: ";
            cin >> option;
        }
        if (option == 1)
        {
            showTeam(head);
        }
        else if (option == 2)
        {
            deployHero(head);
        }
        else if (option == 3)
        {
            removeHero(head);
        }
        else if (option == 4)
        {
            rearrangeTeam(head);
        }
    }
    cout << "The team is ready for its next mission!" << endl;

    return 0;
}
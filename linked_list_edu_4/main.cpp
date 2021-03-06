#include <string>
#include <iostream>

#include "LinkedList.h"

using namespace std;

/*
    Program: LinkedList
    Purpose: This program takes a list of contestants for the show "Survivor"
             and let's the user remove them one by one, then outputs what the
             user has placed in the list in the first place.

    Inputs: A list of contestants. (Twice. Once for insertion, and once for
            removal).
    Outputs: The list that was originally input.

*/

// Grabs a list of contestants from user input.
LinkedList<string> GetContestants()
{
    LinkedList<string> retVal;

    string lastInput;

    do
    {
        cout << "Contestant's name? ";
        cin >> lastInput;

        retVal.Push(lastInput);
    }
    while(lastInput != "fin");

    retVal.Pop();    // Remove the "fin" that was inserted last.

    cout << "Done!\n\n";

    return retVal;
}

// Clears out the linked list one by one based on user input.
string GetLastManStanding(LinkedList<string>& contestants)
{
    string lastRemoval;

    while(!contestants.empty())
    {
        string toRemove;

        cout << "Who shall we remove? ";
        cin >> toRemove;

        if(contestants.remove(toRemove))
        {
            lastRemoval = toRemove;
            cout << "Contestant removed!\n";
        }
        else
            cout << "Contestant not found.\n";
    }

    return lastRemoval;
}

// Spits out a linked list to cout. This would be so much nicer if I did it iteratively like so...
/*
    void DisplayList(const LinkedList<string>& toDisplay)
    {
        for(LinkedList<string>::iterator i = toDisplay.begin(); i != toDisplay.end(); ++i)
            cout << "Contestant: " << *i << "\n";
    }
*/
void DisplayList(LinkedList<string>::iterator beginning, const LinkedList<string>::iterator& end)
{
    if(beginning == end)
        return;

    cout << "Contestant: " << *beginning << "\n";

    DisplayList(++beginning, end);
}

void CongratulateWinner(string winner)
{
    cout << "\n" << winner << " wins!\n";
}

int main(int, wchar_t**)
{
    LinkedList<string> contestants = GetContestants();
    LinkedList<string> backup(contestants);

    string winner = GetLastManStanding(contestants);

    DisplayList(backup.begin(), backup.end());

    CongratulateWinner(winner);

    system("PAUSE");
    return 0;
}

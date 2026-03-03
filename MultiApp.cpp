#include <iostream>
#include <cstdlib>
using namespace std;
//edit frow Andrew
///maksim
int main()
{
    int choice;

    while (true)
    {
        cout << "\n=== MENU ===\n";
        cout << "1 - Aquarium\n";
        cout << "2 - Bubbles\n";
        cout << "3 - Snow\n";
        cout << "0 - Exit\n";
        cout << "Choose:   ";

        cin >> choice;
        //Нинтендо свичч
        switch (choice)
        {
        case 1:
            system("Aquarium.exe");
            break;

        case 2:
            system("Bubbles.exe");
            break;

        case 3:
            system("Snow.exe");
            break;

        case 0:
            return 0;

        default:
            cout << "Wrong choice!\n";
        }
    }
}

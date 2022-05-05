#include <iostream>
#include "RoomsController.h"
#include "ReservationsController.h"


void printCommands();

int main()
{
    try
    {
        RoomsController roomController;
        ReservationsController reservationsController;
        size_t command;
        printCommands();
        do {
            cout << "Input command" << endl;
            cin >> command;
            switch (command)
            {
            case 1: roomController.readFromConsole(); break;
            case 2: roomController.writeToFile(); break;
            case 3: roomController.writeToConsole(); break;
            case 4: reservationsController.readFromConsole(); break;
            case 5: reservationsController.writeToFile(); break;
            case 6: reservationsController.writeToConsole(); break;
            case 7: {
                reservationsController.viewFreeRoom(roomController.getRooms(), roomController.getRoomsCount());
                break;
            }
            case 8:
            {
                roomController.writeToFile();
                reservationsController.writeToFile();
                break;
            }
            default:
                break;
            }
        } while (command != 0);
    }
    catch (const std::exception& ex)
    {
        cout << ex.what();
    }
   

    return 0;
}

void printCommands()
{
    cout << "Commands:"<<endl;
    cout << "0 - End" << endl;
    //cout << "1 - Read rooms from file " << endl;
    cout << "1 - Add rooms from console " << endl;
    cout << "2 - Save rooms to file " << endl;
    cout << "3 - View all rooms " << endl;

    //cout << "5 - Read reservation rooms from file " << endl;
    cout << "4 - Add reservation rooms from console " << endl;
    cout << "5 - Save reservation rooms to file " << endl;
    cout << "6 - View all reservation rooms " << endl;
    cout << "7 - Get all free rooms for date" << endl;
    cout << "8 - Save all changes" << endl;
}

#include <iostream>
#include "RoomsController.h"
#include "ReservationsController.h"
#include "CloseRoomsController.h"

void printCommands();

int main()
{
    try
    {
        RoomsController roomController;
        ReservationsController reservationsController;
        CloseRoomsController closedRoomsController;
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
            case 5: reservationsController.removeReservation(); break;
            case 6: reservationsController.writeToFile(); break;
            case 7: reservationsController.writeToConsole(); break;
            case 8: {
                reservationsController.viewFreeRoom(roomController.getRooms(), roomController.getRoomsCount());
                break;
            }
            case 9: reservationsController.writeToFileReservetedRoomsInPeriod(); break;
            case 10: closedRoomsController.readFromConsole(); break;
            case 11: closedRoomsController.writeToConsole(); break;
            case 12: closedRoomsController.writeToFile(); break;
            case 13:
            {
                roomController.writeToFile();
                reservationsController.writeToFile();
                closedRoomsController.writeToFile();
                break;
            }
            default:
                break;
            }
        } while (command != 0);
    }
    catch (const std::exception& ex)
    {
        cout <<"ERR: "<< ex.what();
    }
   

    return 0;
}

void printCommands()
{
    cout << "Commands:"<<endl;
    cout << "0 - End" << endl;
    
    cout << "Rooms:" << endl;
    cout << "1 - Add new rooms from console" << endl;
    cout << "2 - Save rooms to file " << endl;
    cout << "3 - View all rooms " << endl;
    cout << "Reservations:" << endl;
    cout << "4 - Create a reservation from console" << endl;
    cout << "5 - Remove a reservation/release room" << endl;
    cout << "6 - Save reservated rooms to file " << endl;
    cout << "7 - View all reservated rooms " << endl;
    cout << "8 - Get all free rooms for date" << endl;
    cout << "9 - Write to file all reservated rooms in period" << endl;
    cout << "Close room:" << endl;
    cout << "10 - Close room" << endl;
    cout << "11 - View all closed rooms " << endl;
    cout << "12 - Save closed rooms to file " << endl;

    cout << "13 - Save all changes" << endl;
}

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

static int p = 0; // Keeps track of the number of buses installed

class a {
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];
public:
    void install();    // Function to add a new bus
    void allotment();  // Function to reserve a seat
    void empty();      // Function to initialize all seats as empty
    void show();       // Function to display bus reservations
    void avail();      // Function to show available buses
    void position(int i); // Function to display seating position
    void saveData();   // Function to save bus data to a file
    void loadData();   // Function to load bus data from a file
} bus[10]; // Array to store up to 10 buses

// Function to print a horizontal line with a given character
void vline(char ch) {
    for (int i = 80; i > 0; i--)
        cout << ch;
}

// Function to save the current bus data to a file
void a::saveData() {
    ofstream outFile("bus_data.txt", ios::binary);
    if (outFile) {
        outFile.write((char*)&p, sizeof(p)); // Save the number of buses
        outFile.write((char*)bus, sizeof(bus)); // Save bus data
        outFile.close();
    }
}

// Function to load bus data from a file
void a::loadData() {
    ifstream inFile("bus_data.txt", ios::binary);
    if (inFile) {
        inFile.read((char*)&p, sizeof(p)); // Load the number of buses
        inFile.read((char*)bus, sizeof(bus)); // Load bus data
        inFile.close();
    }
}

// Function to install a new bus
void a::install() {
    cout << "Enter bus no: ";
    cin >> bus[p].busn;
    cout << "\nEnter Driver's name: ";
    cin >> bus[p].driver;
    cout << "\nArrival time: ";
    cin >> bus[p].arrival;
    cout << "\nDeparture: ";
    cin >> bus[p].depart;
    cout << "\nFrom: \t\t\t";
    cin >> bus[p].from;
    cout << "\nTo: \t\t\t";
    cin >> bus[p].to;
    bus[p].empty(); // Initialize seats as empty
    p++; // Increment bus count
    saveData(); // Save updated bus data
}

// Function to reserve a seat
void a::allotment() {
    int seat;
    char number[5];
    top:
    cout << "Bus no: ";
    cin >> number;
    int n;
    for (n = 0; n < p; n++) {
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }
    if (n >= p) {
        cout << "Enter correct bus number \n";
        goto top;
    }
    
    cout << "\nSeat Number: ";
    cin >> seat;
    if (seat > 32) {
        cout << "\nThere are only 32 seats available in this bus.";
    } else {
        if (strcmp(bus[n].seat[seat / 4][(seat % 4) - 1], "Empty") == 0) {
            cout << "Enter passenger's name: ";
            cin >> bus[n].seat[seat / 4][(seat % 4) - 1];
            saveData(); // Save updated seat allocation
        } else {
            cout << "Seat no. is already reserved. \n";
        }
    }
}

// Function to initialize all seats as empty
void a::empty() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(bus[p].seat[i][j], "Empty");
        }
    }
}

// Function to display bus reservations
void a::show() {
    int n;
    char number[5];
    cout << "Enter bus no: ";
    cin >> number;
    for (n = 0; n < p; n++) {
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }
    if (n >= p) {
        cout << "Enter correct bus no: ";
        return;
    }
    vline('*');
    cout << "Bus no: \t" << bus[n].busn << "\nDriver: \t" << bus[n].driver << "\t\tArrival time: \t"
         << bus[n].arrival << "\nDeparture time: " << bus[n].depart << "\nFrom: \t\t" << bus[n].from
         << "\t\tTo: \t\t" << bus[n].to << "\n";
    vline('*');
    bus[0].position(n);
    int a = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            a++;
            if (strcmp(bus[n].seat[i][j], "Empty") != 0)
                cout << "\nSeat number " << (a - 1) << " is reserved for " << bus[n].seat[i][j] << ".";
        }
    }
}

// Function to display seating position and availability
void a::position(int l) {
    int s = 0, availableSeats = 0;
    for (int i = 0; i < 8; i++) {
        cout << "\n";
        for (int j = 0; j < 4; j++) {
            s++;
            cout.width(5);
            cout.fill(' ');
            cout << s << ".";
            cout.width(10);
            cout.fill(' ');
            cout << bus[l].seat[i][j];
            if (strcmp(bus[l].seat[i][j], "Empty") == 0) {
                availableSeats++;
            }
        }
    }
    cout << "\n\nThere are " << availableSeats << " seats empty in Bus No: " << bus[l].busn;
}

// Function to display all available buses
void a::avail() {
    for (int n = 0; n < p; n++) {
        vline('*');
        cout << "Bus no: \t" << bus[n].busn << "\nDriver: \t" << bus[n].driver << "\t\tArrival time: \t"
             << bus[n].arrival << "\nDeparture time: \t" << bus[n].depart << "\nFrom: \t\t" << bus[n].from
             << "\t\tTo: \t\t\t" << bus[n].to << "\n";
        vline('*');
        vline('_');
    }
}

int main() {
    bus[0].loadData(); // Load saved data on startup
    int w;
    while (1) {
        cout << "\n\n\n\n\n";
        cout << "\t\t\t1.Create Bus\n\t\t\t2.Reserve a seat\n\t\t\t3.Show Bus Reservations\n\t\t\t4.Show Buses Available \n\t\t\t5.Exit";
        cout << "\n\t\t\tEnter your choice:->  ";
        cin >> w;
        switch (w) {
        case 1:
            bus[p].install();
            break;
        case 2:
            bus[p].allotment();
            break;
        case 3:
            bus[0].show();
            break;
        case 4:
            bus[0].avail();
            break;
        case 5:
            return 0;
        }
    }
}

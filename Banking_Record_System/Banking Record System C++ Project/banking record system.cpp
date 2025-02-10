#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Structure to store account records
struct Record {
    string accountNumber;
    string name;
    double balance;
};

// Function to add a new record
void addRecord(vector<Record>& records) {
    Record newRecord;
    cout << "Enter account number: ";
    cin >> newRecord.accountNumber;
    cout << "Enter name: ";
    cin.ignore(); // Ignore leftover newline character
    getline(cin, newRecord.name);
    cout << "Enter balance: ";
    cin >> newRecord.balance;
    records.push_back(newRecord);
    
    // Append the new record to the file
    ofstream outFile("records.txt", ios::app);
    if (outFile) {
        outFile << newRecord.accountNumber << "," << newRecord.name << "," << newRecord.balance << endl;
        outFile.close();
    }
    cout << "Record added successfully.\n";
}

// Function to display all records
void showRecords() {
    ifstream inFile("records.txt");
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    
    vector<Record> validRecords;
    string accountNumber, name;
    double balance;
    
    // Read records from the file
    while (getline(inFile, accountNumber, ',') && getline(inFile, name, ',') && inFile >> balance) {
        if (!accountNumber.empty()) {
            validRecords.push_back({accountNumber, name, balance});
        }
        inFile.ignore(); // Ignore newline character
    }
    inFile.close();
    
    if (validRecords.empty()) {
        cout << "No valid records to display.\n";
        return;
    }
    
    // Display up to 10 records
    int count = 0;
    for (size_t i = 0; i < validRecords.size(); ++i) {
        cout << "Account Number: " << validRecords[i].accountNumber << " | Name: " << validRecords[i].name << " | Balance: " << validRecords[i].balance << endl;
        if (++count >= 10) break;
    }
}

// Function to search for a specific record by account number
void searchRecord() {
    string searchAccount;
    cout << "Enter account number to search: ";
    cin >> searchAccount;
    
    ifstream inFile("records.txt");
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    
    string accountNumber, name;
    double balance;
    bool found = false;
    
    // Search for the record in the file
    while (getline(inFile, accountNumber, ',') && getline(inFile, name, ',') && inFile >> balance) {
        if (accountNumber == searchAccount) {
            cout << "Account Number: " << accountNumber << " | Name: " << name << " | Balance: " << balance << endl;
            found = true;
            break; // Stop searching after finding the record
        }
        inFile.ignore();
    }
    inFile.close();
    
    if (!found) {
        cout << "Record not found.\n";
    }
}

// Function to delete a record by account number
void deleteRecord() {
    string deleteAccount;
    cout << "Enter account number to delete: ";
    cin >> deleteAccount;
    
    ifstream inFile("records.txt");
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    
    vector<Record> records;
    string accountNumber, name;
    double balance;
    bool deleted = false;
    
    // Read records and filter out the one to delete
    while (getline(inFile, accountNumber, ',') && getline(inFile, name, ',') && inFile >> balance) {
        if (accountNumber != deleteAccount) {
            records.push_back({accountNumber, name, balance});
        } else {
            deleted = true; // Mark that a record was deleted
        }
        inFile.ignore();
    }
    inFile.close();
    
    // Rewrite the file without the deleted record
    ofstream outFile("records.txt", ios::trunc);
    for (size_t i = 0; i < records.size(); ++i) {
        outFile << records[i].accountNumber << "," << records[i].name << "," << records[i].balance << endl;
    }
    outFile.close();
    
    if (deleted) {
        cout << "Record deleted successfully.\n";
    } else {
        cout << "Record not found.\n";
    }
}

// Function to update an existing record
void updateRecord() {
    string updateAccount;
    cout << "Enter account number to update: ";
    cin >> updateAccount;
    
    ifstream inFile("records.txt");
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    
    vector<Record> records;
    string accountNumber, name;
    double balance;
    bool updated = false;
    
    // Read and modify the specified record
    while (getline(inFile, accountNumber, ',') && getline(inFile, name, ',') && inFile >> balance) {
        if (accountNumber == updateAccount) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new balance: ";
            cin >> balance;
            updated = true; // Mark that a record was updated
        }
        records.push_back({accountNumber, name, balance});
        inFile.ignore();
    }
    inFile.close();
    
    // Rewrite the file with updated data
    ofstream outFile("records.txt", ios::trunc);
    for (size_t i = 0; i < records.size(); ++i) {
        outFile << records[i].accountNumber << "," << records[i].name << "," << records[i].balance << endl;
    }
    outFile.close();
    
    if (updated) {
        cout << "Record updated successfully.\n";
    } else {
        cout << "Record not found.\n";
    }
}

// Main function to provide menu-based interaction
int main() {
    vector<Record> records;
    int choice;
    
    do {
        cout << "\n1. Add Record\n2. Show Records\n3. Search Record\n4. Delete Record\n5. Update Record\n6. Exit\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addRecord(records);
                break;
            case 2:
                showRecords();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                updateRecord();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

const int MAX_ENTRIES = 10;

class Appointment {
public:
    string doctorName;
    string patientName;
    string date;
    string status;
};

Appointment appointments[MAX_ENTRIES];
int appointmentCount = 0;

class Billing {
public:
    string patientName;
    float amount;
    bool paid;
};

Billing bills[MAX_ENTRIES];
int billCount = 0;

class Room {
public:
    int roomNumber;
    bool isOccupied;
};

Room rooms[5] = { {101,false}, {102,false}, {103,false}, {104,false}, {105,false} };

class MedicalRecord {
public:
    string patientName;
    string diagnosis;
    string treatment;
};

MedicalRecord records[MAX_ENTRIES];
int recordCount = 0;

class User {
protected:
    string username;
    string password;

public:
    User() {} // default constructor
    User(string u, string p) {
        username = u;
        password = p;
    }

    bool login(string u, string p) {
        return (username == u && password == p);
    }

    virtual void displayMenu() = 0;
};

// --------------------- PATIENT ---------------------
class Patient : public User {
public:
    Patient() {}
    Patient(string u, string p) : User(u, p) {}

    void displayMenu() {
        cout << endl;
        cout << "--- Patient Menu ---" << endl;
        cout << "1. Book Appointment" << endl;
        cout << "2. View Appointments" << endl;
        cout << "3. View Bills" << endl;
        cout << "4. View Medical Records" << endl;
        cout << "0. Logout" << endl;
    }

    void bookAppointment() {
        if (appointmentCount < MAX_ENTRIES) {
            cout << "Enter Doctor Name: ";
            cin >> appointments[appointmentCount].doctorName;
            appointments[appointmentCount].patientName = username;
            cout << "Enter Date (DD/MM): ";
            cin >> appointments[appointmentCount].date;
            appointments[appointmentCount].status = "Scheduled";
            appointmentCount++;
            cout << "Appointment booked." << endl;
        } else {
            cout << "Appointment list is full." << endl;
        }
    }

    void viewAppointments() {
        for (int i = 0; i < appointmentCount; i++) {
            if (appointments[i].patientName == username) {
                cout << appointments[i].doctorName << " with "
                     << appointments[i].patientName << " on "
                     << appointments[i].date << " ["
                     << appointments[i].status << "]" << endl;
            }
        }
    }

    void viewBills() {
        for (int i = 0; i < billCount; i++) {
            if (bills[i].patientName == username) {
                cout << "Patient: " << bills[i].patientName << " | Amount: "
                     << bills[i].amount << " | Status: ";
                cout << (bills[i].paid ? "Paid" : "Unpaid") << endl;
            }
        }
    }

    void viewMedicalRecords() {
        for (int i = 0; i < recordCount; i++) {
            if (records[i].patientName == username) {
                cout << "Patient: " << records[i].patientName << endl;
                cout << "Diagnosis: " << records[i].diagnosis << endl;
                cout << "Treatment: " << records[i].treatment << endl;
            }
        }
    }
};

// --------------------- RECEPTIONIST ---------------------
class Receptionist : public User {
public:
    Receptionist() {}
    Receptionist(string u, string p) : User(u, p) {}

    void displayMenu() {
        cout << endl;
        cout << "--- Receptionist Menu ---" << endl;
        cout << "1. Assign Room" << endl;
        cout << "2. Create Bill" << endl;
        cout << "0. Logout" << endl;
    }

    void assignRoom() {
        string name;
        cout << "Enter patient name: ";
        cin >> name;
        for (int i = 0; i < 5; i++) {
            if (!rooms[i].isOccupied) {
                rooms[i].isOccupied = true;
                cout << "Room " << rooms[i].roomNumber << " assigned to " << name << "." << endl;
                return;
            }
        }
        cout << "No rooms available." << endl;
    }

    void createBill() {
        if (billCount < MAX_ENTRIES) {
            cout << "Enter patient name: ";
            cin >> bills[billCount].patientName;
            cout << "Enter amount: ";
            cin >> bills[billCount].amount;
            bills[billCount].paid = false;
            billCount++;
            cout << "Bill created." << endl;
        } else {
            cout << "Bill list is full." << endl;
        }
    }
};

// --------------------- DOCTOR ---------------------
class Doctor : public User {
public:
    Doctor() {}
    Doctor(string u, string p) : User(u, p) {}

    void displayMenu() {
        cout << endl;
        cout << "--- Doctor Menu ---" << endl;
        cout << "1. View Appointments" << endl;
        cout << "2. Add Medical Record" << endl;
        cout << "0. Logout" << endl;
    }

    void viewAppointments() {
        for (int i = 0; i < appointmentCount; i++) {
            if (appointments[i].doctorName == username) {
                cout << appointments[i].doctorName << " with "
                     << appointments[i].patientName << " on "
                     << appointments[i].date << " ["
                     << appointments[i].status << "]" << endl;
            }
        }
    }

    void addMedicalRecord() {
        if (recordCount < MAX_ENTRIES) {
            cout << "Enter patient name: ";
            cin >> records[recordCount].patientName;
            cin.ignore();
            cout << "Enter diagnosis: ";
            getline(cin, records[recordCount].diagnosis);
            cout << "Enter treatment: ";
            getline(cin, records[recordCount].treatment);
            recordCount++;
            cout << "Medical record added." << endl;
        } else {
            cout << "Medical record list is full." << endl;
        }
    }
};

// ------------------ USER LISTS ------------------
Patient patients[MAX_ENTRIES];
Doctor doctors[MAX_ENTRIES];
Receptionist receptionists[MAX_ENTRIES];
int patientCount = 0, doctorCount = 0, receptionistCount = 0;

// ------------------ MAIN ------------------
int main() {
    int choice;
    do {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Register New User\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int type;
            string uname, pass;
            cout << "User Type (1=Patient, 2=Doctor, 3=Receptionist): ";
            cin >> type;
            cout << "Enter Username: ";
            cin >> uname;
            cout << "Enter Password: ";
            cin >> pass;

            if (type == 1 && patientCount < MAX_ENTRIES) {
                patients[patientCount++] = Patient(uname, pass);
                cout << "Patient registered.\n";
            } else if (type == 2 && doctorCount < MAX_ENTRIES) {
                doctors[doctorCount++] = Doctor(uname, pass);
                cout << "Doctor registered.\n";
            } else if (type == 3 && receptionistCount < MAX_ENTRIES) {
                receptionists[receptionistCount++] = Receptionist(uname, pass);
                cout << "Receptionist registered.\n";
            } else {
                cout << "Invalid type or user limit reached.\n";
            }
        }

        else if (choice == 2) {
            string u, pw;
            cout << "Enter Username: ";
            cin >> u;
            cout << "Enter Password: ";
            cin >> pw;

            bool loggedIn = false;

            for (int i = 0; i < patientCount; i++) {
                if (patients[i].login(u, pw)) {
                    loggedIn = true;
                    int ch;
                    do {
                        patients[i].displayMenu();
                        cout << "Choice: ";
                        cin >> ch;
                        if (ch == 1) patients[i].bookAppointment();
                        else if (ch == 2) patients[i].viewAppointments();
                        else if (ch == 3) patients[i].viewBills();
                        else if (ch == 4) patients[i].viewMedicalRecords();
                    } while (ch != 0);
                    break;
                }
            }

            for (int i = 0; i < receptionistCount && !loggedIn; i++) {
                if (receptionists[i].login(u, pw)) {
                    loggedIn = true;
                    int ch;
                    do {
                        receptionists[i].displayMenu();
                        cout << "Choice: ";
                        cin >> ch;
                        if (ch == 1) receptionists[i].assignRoom();
                        else if (ch == 2) receptionists[i].createBill();
                    } while (ch != 0);
                    break;
                }
            }

            for (int i = 0; i < doctorCount && !loggedIn; i++) {
                if (doctors[i].login(u, pw)) {
                    loggedIn = true;
                    int ch;
                    do {
                        doctors[i].displayMenu();
                        cout << "Choice: ";
                        cin >> ch;
                        if (ch == 1) doctors[i].viewAppointments();
                        else if (ch == 2) doctors[i].addMedicalRecord();
                    } while (ch != 0);
                    break;
                }
            }

            if (!loggedIn) {
                cout << "Login failed. Try again.\n";
            }
        }

    } while (choice != 0);

    cout << "Exiting system. Goodbye!\n";
    return 0;
}


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>


#define MAX_ROOMS 100
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 100
#define MAX_PHONE_LENGTH 12
#define MAX_DATE_LENGTH 20
#define MAX_CNIC_LENGTH 15

using namespace std;

class Customer {
public:
    char Name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char from_date[MAX_DATE_LENGTH];
    char to_date[MAX_DATE_LENGTH];
    float payment_advance;
    int booking_id;
    char university[MAX_NAME_LENGTH];
    char campus[MAX_NAME_LENGTH];
    char semester[MAX_NAME_LENGTH];
    char cnic[MAX_CNIC_LENGTH];
    char father_name[MAX_NAME_LENGTH];
    char father_designation[MAX_NAME_LENGTH];
    char mother_name[MAX_NAME_LENGTH];
    char mother_designation[MAX_NAME_LENGTH];
    string gender;
    bool mess_registered; 
};

class Room {
public:
    int stype;
    int roomNumber;
    int rent;
    int status;
    string gender;
    Customer cust[3]; // Allow up to 3 customers for 3 seater room
    int customer_count;
    static int count;
    static Room rooms[MAX_ROOMS]; // Static member to store rooms

    Room() : stype(0), roomNumber(0), rent(0), status(0), gender(""), customer_count(0) {} // Default constructor

    static Room addRoom(int);
    static void searchRoomByNumber(int);
    static void displayRoom(const Room&);
    static void saveRoomsToFile();
    static void loadRoomsFromFile();
};

int Room::count = 0;
Room Room::rooms[MAX_ROOMS]; // Define static member outside the class

Room Room::addRoom(int rno) {
    Room room;
    room.roomNumber = rno;
    cout << "\nType Size (3/2/1 Seater) : ";
    cin >> room.stype;
    cout << "\nMonthly Rent : ";
    cin >> room.rent;
    cout << "\nMales Room/ Female Room: ";
    cin >> room.gender;
    room.status = 0;
    room.customer_count = 0;
    cout << "\nRoom Added Successfully!";
    return room;
}

void Room::searchRoomByNumber(int rno) {
     bool found = false;
    for (int i = 0; i < Room::count; i++) {
        if (rooms[i].roomNumber == rno) {
            found = true;
            cout << "Room Details\n";
            if (rooms[i].status == 1) {
                cout << "\nRoom is Reserved";
            } else {
                cout << "\nRoom is available";
            }
            displayRoom(rooms[i]);
            break;
        }
    }
    if (!found) {
        cout << "\nRoom not found";
    }
}

void Room::displayRoom(const Room& tempRoom) {
     cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType Size (3/2/1 Seater): " << tempRoom.stype;
    cout << "\nRent: " << tempRoom.rent;
    cout << "\nGender Specific: " << tempRoom.gender;
}

void Room::saveRoomsToFile() {
     ofstream file("rooms.txt");
    if (file.is_open()) {
        for (int i = 0; i < Room::count; ++i) {
            file << rooms[i].roomNumber << " "
                 << rooms[i].stype << " "
                 << rooms[i].rent << " "
                 << rooms[i].gender << " "
                 << rooms[i].status << " "
                 << rooms[i].customer_count << "\n";
            for (int j = 0; j < rooms[i].customer_count; ++j) {
                file << rooms[i].cust[j].Name << " "
                     << rooms[i].cust[j].gender << " "
                     << rooms[i].cust[j].university << " "
                     << rooms[i].cust[j].campus << " "
                     << rooms[i].cust[j].semester << " "
                     << rooms[i].cust[j].phone << " "
                     << rooms[i].cust[j].cnic << " "
                     << rooms[i].cust[j].father_name << " "
                     << rooms[i].cust[j].father_designation << " "
                     << rooms[i].cust[j].mother_name << " "
                     << rooms[i].cust[j].mother_designation << "\n";
            }
        }
        file.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void Room::loadRoomsFromFile() {
    ifstream file("rooms.txt");
    if (file.is_open()) {
        Room::count = 0;
        while (file >> rooms[Room::count].roomNumber) {
            file >> rooms[Room::count].stype
                 >> rooms[Room::count].rent
                 >> rooms[Room::count].gender
                 >> rooms[Room::count].status
                 >> rooms[Room::count].customer_count;
            for (int j = 0; j < rooms[Room::count].customer_count; ++j) {
                file >> rooms[Room::count].cust[j].Name
                     >> rooms[Room::count].cust[j].gender
                     >> rooms[Room::count].cust[j].university
                     >> rooms[Room::count].cust[j].campus
                     >> rooms[Room::count].cust[j].semester
                     >> rooms[Room::count].cust[j].phone
                     >> rooms[Room::count].cust[j].cnic
                     >> rooms[Room::count].cust[j].father_name
                     >> rooms[Room::count].cust[j].father_designation
                     >> rooms[Room::count].cust[j].mother_name
                     >> rooms[Room::count].cust[j].mother_designation;
            }
            Room::count++;
        }
        file.close();
    } else {
        cout << "Unable to open file for reading.\n";
    }
}

class HostelMgnt {
public:
    void checkIn();
    void getAvailRoom();
    void getTotalRegisteredRooms();
    void searchCustomer(const char *);
    void checkOut(int);
    void guestSummaryReport();
    void studentMenu();
    void mealSchedule();
    void registerComplaint();
    void applyForMess();
    void HostelFee();
    void viewRoomMates();
    void RejectMess(); 
    void MakeAnnouncements();
    
    bool isCnicUnique(const char* cnic) {
    for (int i = 0; i < Room::count; ++i) {
        for (int j = 0; j < Room::rooms[i].customer_count; ++j) {
            if (strcmp(Room::rooms[i].cust[j].cnic, cnic) == 0) {
                return false;
            }
        }
    }
    return true;
}
};


void HostelMgnt::checkIn() {
    Customer customer;
    cout << "Enter Student Name: ";
    cin.getline(customer.Name, MAX_NAME_LENGTH);
    cout << "Enter your gender(male/female): ";
    cin >> customer.gender;
    cout <<"Enter University: ";
    cin.ignore();
    cin.getline(customer.university, MAX_NAME_LENGTH);
    cout << "Enter Campus: ";
    cin.getline(customer.campus, MAX_NAME_LENGTH);
    cout << "Enter Semester: ";
    cin.getline(customer.semester, MAX_NAME_LENGTH);
    cout << "Enter Phone: ";
    cin.getline(customer.phone, MAX_PHONE_LENGTH);

    // Ensure CNIC is unique
    bool uniqueCnic = false;
    while (!uniqueCnic) {
        cout << "Enter CNIC: ";
        cin.getline(customer.cnic, MAX_CNIC_LENGTH);
        if (isCnicUnique(customer.cnic)) {
            uniqueCnic = true;
        } else {
            cout << "This CNIC is already registered to another student. Please enter a different CNIC.\n";
        }
    }

    cout << "Enter Father's Name: ";
    cin.getline(customer.father_name, MAX_NAME_LENGTH);
    cout << "Enter Father's Designation: ";
    cin.getline(customer.father_designation, MAX_NAME_LENGTH);
    cout << "Enter Mother's Name: ";
    cin.getline(customer.mother_name, MAX_NAME_LENGTH);
    cout << "Enter Mother's Designation: ";
    cin.getline(customer.mother_designation, MAX_NAME_LENGTH);

    int seaterChoice;
    cout << "Select Seater Type (1/2/3): ";
    cin >> seaterChoice;

    bool roomFound = false;
    for (int i = 0; i < Room::count; ++i) {
        if (Room::rooms[i].status == 0 && Room::rooms[i].stype == seaterChoice && Room::rooms[i].gender == customer.gender) {
            cout << "\nRoom Number: " << Room::rooms[i].roomNumber << endl;
            cout << "Type Size (3/2/1 Seater): " << Room::rooms[i].stype << endl;
            cout << "Rent: " << Room::rooms[i].rent << endl;
            cout << endl;
            roomFound = true;
        }
    }

    if (!roomFound) {
        cout << "No rooms available of the requested type and gender.\n";
        return;
    }

    // Room selection by the student
    int selectedRoomNumber;
    roomFound = false;
    do {
        cout << "Enter the room number you want to book: ";
        cin >> selectedRoomNumber;

        // Find the selected room and assign it to the student
        for (int i = 0; i < Room::count; ++i) {
            if (Room::rooms[i].roomNumber == selectedRoomNumber && Room::rooms[i].status == 0 && Room::rooms[i].customer_count < Room::rooms[i].stype && Room::rooms[i].gender == customer.gender) {
                Room::rooms[i].cust[Room::rooms[i].customer_count] = customer;
                Room::rooms[i].customer_count++;
                if (Room::rooms[i].customer_count == Room::rooms[i].stype) {
                    Room::rooms[i].status = 1; // Mark the room as reserved if it's fully occupied
                }
                cout << "\nRoom number " << Room::rooms[i].roomNumber << " for student " << customer.Name << " is booked now." << endl;
                roomFound = true;
                break;
            }
        }

        if (!roomFound) {
            cout << "Invalid room number or room is not available. Please enter again." << endl;
        }
    } while (!roomFound);

    Room::saveRoomsToFile();
}

void HostelMgnt::getAvailRoom() {
   for (int i = 0; i < Room::count; i++) {
        if (Room::rooms[i].status == 0) {
            Room::displayRoom(Room::rooms[i]);
            cout << "\n\nPress enter for next room";
            getchar();
        }
    }
}

void HostelMgnt::getTotalRegisteredRooms() {
     cout << "\nTotal registered rooms: " << Room::count;
    cout << "\nRooms details:\n";
    for (int i = 0; i < Room::count; i++) {
        Room::displayRoom(Room::rooms[i]);
        cout << endl;
    }
}

void HostelMgnt::searchCustomer(const char* name) {
    bool found = false;
    for (int i = 0; i < Room::count; i++) {
        for (int j = 0; j < Room::rooms[i].customer_count; j++) {
            cout << "Checking customer: " << Room::rooms[i].cust[j].Name << " against " << name << endl;
            
            if (strcmp(Room::rooms[i].cust[j].Name, name) == 0) {
                cout << "\nCustomer Name: " << Room::rooms[i].cust[j].Name;
                cout << "\nRoom Number: " << Room::rooms[i].roomNumber;
                cout << "\nGender: " << Room::rooms[i].cust[j].gender;
                cout << "\nUniversity: " << Room::rooms[i].cust[j].university;
                cout << "\nCampus: " << Room::rooms[i].cust[j].campus;
                cout << "\nSemester: " << Room::rooms[i].cust[j].semester;
                cout << "\nPhone: " << Room::rooms[i].cust[j].phone;
                cout << "\nCNIC: " << Room::rooms[i].cust[j].cnic;
                cout << "\nFather's Name: " << Room::rooms[i].cust[j].father_name;
                cout << "\nFather's Designation: " << Room::rooms[i].cust[j].father_designation;
                cout << "\nMother's Name: " << Room::rooms[i].cust[j].mother_name;
                cout << "\nMother's Designation: " << Room::rooms[i].cust[j].mother_designation;
                cout << "\n---------------------------------------";
                cout << "\n\nPress enter for next record";
                getchar();
                found = true;
            }
        }
    }
    if (!found) {
        cout << "\nStudent not found.";
    }
}

void HostelMgnt::checkOut(int roomNum) {
    Room::loadRoomsFromFile();
    for (int i = 0; i < Room::count; i++) {
        if (Room::rooms[i].roomNumber == roomNum) {
            if (Room::rooms[i].status == 0) {
                cout << "\nRoom is already vacant.";
                return;
            }

            // Ask for the student's name
            char studentName[MAX_NAME_LENGTH];
            cout << "Enter the name of the student to check out: ";
            cin.ignore(); // Clear the input buffer
            cin.getline(studentName, MAX_NAME_LENGTH);

            // Find and remove the student
            bool studentFound = false;
            for (int j = 0; j < Room::rooms[i].customer_count; j++) {
                if (strcmp(Room::rooms[i].cust[j].Name, studentName) == 0) {
                    // Shift remaining customers up
                    for (int k = j; k < Room::rooms[i].customer_count - 1; k++) {
                        Room::rooms[i].cust[k] = Room::rooms[i].cust[k + 1];
                    }
                    Room::rooms[i].customer_count--;
                    studentFound = true;

                    // Check if the room is now vacant
                    if (Room::rooms[i].customer_count == 0) {
                        Room::rooms[i].status = 0;
                    }

                    cout << "\nStudent " << studentName << " has been checked out from room number " << roomNum << ".";
                    Room::saveRoomsToFile();
                    return;
                }
            }

            if (!studentFound) {
                cout << "\nStudent not found in room number " << roomNum << ".";
                return;
            }
        }
    }
    cout << "\nRoom number not found.";
}


void HostelMgnt::guestSummaryReport() {
    if (Room::count == 0) {
        cout << "\n No Guest in Hotel ";
    }
    for (int i = 0; i < Room::count; i++) {
        if (Room::rooms[i].status == 1) {
            cout << "\n Customer details for room No. " << Room::rooms[i].roomNumber;
           

 for (int j = 0; j < Room::rooms[i].customer_count; j++) {
                cout << "\nStudent Name: " << Room::rooms[i].cust[j].Name;
                cout << "\nGender: " << Room::rooms[i].cust[j].gender;
                cout << "\nUniversity: " << Room::rooms[i].cust[j].university;
                cout << "\nCampus: " << Room::rooms[i].cust[j].campus;
                cout << "\nSemester: " << Room::rooms[i].cust[j].semester;
                cout << "\nPhone: " << Room::rooms[i].cust[j].phone;
                cout << "\nCNIC: " << Room::rooms[i].cust[j].cnic;
                cout << "\nFather's Name: " << Room::rooms[i].cust[j].father_name;
                cout << "\nFather's Designation: " << Room::rooms[i].cust[j].father_designation;
                cout << "\nMother's Name: " << Room::rooms[i].cust[j].mother_name;
                cout << "\nMother's Designation: " << Room::rooms[i].cust[j].mother_designation;
                cout << "\n---------------------------------------";
            }
            cout << "\nPress enter for next room";
            getchar();
        }
    }
}



void HostelMgnt::applyForMess() {
    char name[MAX_NAME_LENGTH];
    char cnic[MAX_CNIC_LENGTH];

    cout << "Enter your name: ";
    cin.getline(name, MAX_NAME_LENGTH);

    cout << "Enter your CNIC: ";
    cin.getline(cnic, MAX_CNIC_LENGTH);

    bool studentFound = false;
    for (int i = 0; i < Room::count; ++i) {
        for (int j = 0; j < Room::rooms[i].customer_count; ++j) {
            // Debug: Print the name and CNIC being compared
            cout << "Comparing: Name - " << Room::rooms[i].cust[j].Name << ", CNIC - " << Room::rooms[i].cust[j].cnic << endl;
            cout << "With: Name - " << name << ", CNIC - " << cnic << endl;

            // Compare the name and CNIC, ensuring that they match exactly
            if (strcmp(Room::rooms[i].cust[j].Name, name) == 0 && strcmp(Room::rooms[i].cust[j].cnic, cnic) == 0) {
                studentFound = true;
                cout << "Student found!\n";
                cout << "Do you want to apply for mess (Fee: 6000 rupees)? (yes/no): ";
                string choice;
                cin >> choice;
                if (choice == "yes") {
                    // Update student's details to reflect mess registration
                    // For simplicity, let's assume a boolean flag for mess registration
                    Room::rooms[i].cust[j].mess_registered = true;
                    cout << "Mess registration successful.\n";
                } else {
                    cout << "Mess registration cancelled.\n";
                }
                break; // Exit the inner loop once the student is found
            }
        }
        if (studentFound) {
            break; // Exit the outer loop once the student is found
        }
    }

    if (!studentFound) {
        cout << "Student not found. Please ensure that the name and CNIC are correct.\n";
    }
}

int operator+(const Room& room, int messFee) {
    return room.rent + messFee;
}


void HostelMgnt::HostelFee() {
    char name[MAX_NAME_LENGTH];
    char cnic[MAX_CNIC_LENGTH];
    const int messFee = 6000; 

    cout << "Enter your name: ";
    cin.getline(name, MAX_NAME_LENGTH);

    cout << "Enter your CNIC: ";
    cin.getline(cnic, MAX_CNIC_LENGTH);

    bool studentFound = false;
    for (int i = 0; i < Room::count; ++i) {
        for (int j = 0; j < Room::rooms[i].customer_count; ++j) {
            cout << "Comparing: Name - " << Room::rooms[i].cust[j].Name << ", CNIC - " << Room::rooms[i].cust[j].cnic << endl;
            cout << "With: Name - " << name << ", CNIC - " << cnic << endl;

            if (strcmp(Room::rooms[i].cust[j].Name, name) == 0 && strcmp(Room::rooms[i].cust[j].cnic, cnic) == 0) {
                studentFound = true;
                if (Room::rooms[i].cust[j].mess_registered) {
                    // If mess is registered, calculate and display total fee
                    int totalFee = Room::rooms[i].rent + messFee;
                    cout << "Student found!\n";
                    cout << "Mess Fee: " << messFee << endl;
                    cout << "Room Fee: " << Room::rooms[i].rent << endl;
                    cout << "Total Fee: " << totalFee << endl;
                } else {
                    // If mess is not registered, display only room fee
                    cout << "Student found!\n";
                    cout << "Mess Fee: Not Registered\n";
                    cout << "Room Fee: " << Room::rooms[i].rent << endl;
                }
                break; // Exit the inner loop once the student is found
            }
        }
        if (studentFound) {
            break; // Exit the outer loop once the student is found
        }
    }

    if (!studentFound) {
        cout << "Student not found. Please ensure that the name and CNIC are correct.\n";
    }
}


void HostelMgnt::viewRoomMates() {
    char name[MAX_NAME_LENGTH];
    char cnic[MAX_CNIC_LENGTH];
    cout << "Enter your name: ";
    cin.getline(name, MAX_NAME_LENGTH);
    cout << "Enter your CNIC: ";
    cin.getline(cnic, MAX_CNIC_LENGTH);

    bool studentFound = false;
    for (int i = 0; i < Room::count; i++) {
        for (int j = 0; j < Room::rooms[i].customer_count; j++) {
            if (strcmp(Room::rooms[i].cust[j].Name, name) == 0 && strcmp(Room::rooms[i].cust[j].cnic, cnic) == 0) {
                studentFound = true;
                cout << "\nRoommates for room number " << Room::rooms[i].roomNumber << ":\n";
                bool roommatesFound = false;
                for (int k = 0; k < Room::rooms[i].customer_count; k++) {
                    if (k != j) { // Exclude the student who is checking for roommates
                        roommatesFound = true;
                        cout << "Name: " << Room::rooms[i].cust[k].Name << endl;
                        cout << "Gender: " << Room::rooms[i].cust[k].gender << endl;
                        cout << "University: " << Room::rooms[i].cust[k].university << endl;
                        cout << "Campus: " << Room::rooms[i].cust[k].campus << endl;
                        cout << "Semester: " << Room::rooms[i].cust[k].semester << endl;
                        cout << "Phone: " << Room::rooms[i].cust[k].phone << endl;
                        cout << "CNIC: " << Room::rooms[i].cust[k].cnic << endl;
                        cout << "---------------------------------------" << endl;
                    }
                }
                if (!roommatesFound) {
                    cout << "No roommates yet.\n";
                }
                return;
            }
        }
    }
    if (!studentFound) {
        cout << "\nStudent not found.\n";
    }
}




void HostelMgnt::RejectMess() {
    char name[MAX_NAME_LENGTH];
    char cnic[MAX_CNIC_LENGTH];

    cout << "Enter your name: ";
    cin.getline(name, MAX_NAME_LENGTH);

    cout << "Enter your CNIC: ";
    cin.getline(cnic, MAX_CNIC_LENGTH);

    bool studentFound = false;
    for (int i = 0; i < Room::count; ++i) {
        for (int j = 0; j < Room::rooms[i].customer_count; ++j) {
            if (strcmp(Room::rooms[i].cust[j].Name, name) == 0 && strcmp(Room::rooms[i].cust[j].cnic, cnic) == 0) {
                studentFound = true;
                if (Room::rooms[i].cust[j].mess_registered) {
                    Room::rooms[i].cust[j].mess_registered = false;
                    cout << "Mess facility has been successfully rejected.\n";
                } else {
                    cout << "You are not registered for the mess facility.\n";
                }
                Room::saveRoomsToFile();
                return;
            }
        }
    }
    if (!studentFound) {
        cout << "Student not found. Please ensure that the name and CNIC are correct.\n";
    }
}

void HostelMgnt::MakeAnnouncements(){
	                        string Announcement;
                            cout << "Enter the announcement: ";
                            getline(cin, Announcement);
                            ofstream announcementFile("announcement.txt", ios::app);
                            if (announcementFile.is_open()) {
                                announcementFile << Announcement << endl;
                                announcementFile.close();
                                cout << "Announcement filed successfully.\n";
                            } else {
                                cout << "Unable to open Announcement file.\n";
                            }
}



int main() {
    Room::loadRoomsFromFile();
    HostelMgnt hm;
    int choice;
    int rno;
    char name[MAX_NAME_LENGTH];

    do {
        cout << "\n\nHotel Management System\n";
        cout << "1. Administrator\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int adminChoice;
                do {
                    cout << "\nAdministrator Menu\n";
                    cout << "1. Check-In Room\n";
                    cout << "2. Get Available Rooms\n";
                    cout << "3. Search Customer\n";
                    cout << "4. Check-Out Room\n";
                    cout << "5. Guest Summary Report\n";
                    cout << "6. Add Room\n";
                    cout << "7. Get Total Registered Rooms\n";
                    cout << "8. Announcements\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;
                    cin.ignore();

                    switch (adminChoice) {
                        case 1:
                            hm.checkIn();
                            break;
                        case 2:
                            hm.getAvailRoom();
                            break;
                        case 3:
                            cout << "Enter Customer Name: ";
                         
                            cin.getline(name, MAX_NAME_LENGTH);
                            hm.searchCustomer(name);
                            break;
                        case 4:
                            cout << "Enter Room Number: ";
                            cin >> rno;
                            hm.checkOut(rno);
                            break;
                        case 5:
                            hm.guestSummaryReport();
                            break;
                        case 6:
                            if (Room::count < MAX_ROOMS) {
                                cout << "Enter Room Number: ";
                                cin >> rno;
                                Room::rooms[Room::count++] = Room().addRoom(rno);
                                Room::saveRoomsToFile();
                            } else {
                                cout << "Maximum room limit reached!";
                            }
                            break;
                        case 7:
                            hm.getTotalRegisteredRooms();
                            break;
                        case 8:
                        	hm.MakeAnnouncements();
                        	break;
                        	
                        case 0:
                            cout << "Returning to Main Menu.\n";
                            break;
                        default:
                            cout << "Invalid choice! Please try again.";
                    }
                } while (adminChoice != 0);
                break;
            }
            case 2: {
                int studentChoice;
                do {
                    cout << "\nStudent Menu\n";
                    cout << "1. View Meal Schedule/Facility\n";
                    cout << "2. File a Complaint\n";
                    cout << "3. Apply for mess\n";
                    cout << "4. View the fee\n";
                    cout << "5. View roommates\n";
                    cout << "6. View announcements\n";
                    cout << "7. Reject mess facility\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> studentChoice;
                    cin.ignore();

                    switch (studentChoice) {
                        case 1:
                            // Display meal schedule
                            cout << "\nDAYS                      BREAKFAST                  LUNCH                      DINNER\n";
                            cout << "MONDAY                 omelette/paratha/chai       daal/roti/raita             chk qorma/roti\n";
                            cout << "TUESDAY                aalo paratha/chai           lobia/roti/raita            chk haleem/roti\n";
                            cout << "WEDNESDAY              chanay/paratha/chai         sada pulao                  chk biryani\n";
                            cout << "THURSDAY               aalo paratha/chai           aalo matar/roti             daal chana/roti\n";
                            cout << "FRIDAY                 omlette/paratha/chai        daal/roti/raita             chk qorma/roti\n";
                            cout << "SATURDAY               chanay/paratha/chai         sada pulao                  fried rice/sauce\n";
                            cout << "SUNDAY                 aalo paratha/chai           aalo bhujia/roti            beef qeema/roti\n";
                            break;
                        case 2: {
                            // File a complaint
                            string complaint;
                            cout << "Enter your complaint: ";
                            getline(cin, complaint);
                            ofstream complaintFile("complaint.txt", ios::app);
                            if (complaintFile.is_open()) {
                                complaintFile << complaint << endl;
                                complaintFile.close();
                                cout << "Complaint filed successfully.\n";
                            } else {
                                cout << "Unable to open complaint file.\n";
                            }
                            break;
                        }
                        case 3:
                        	hm.applyForMess();
                        	break;
                        	
                        case 4:
						    hm.HostelFee();
						    break;
						    
						case 5:
							hm.viewRoomMates();
							break;
							
						case 6:
							
							
						case 7:
							hm.RejectMess();
							break;
							
                        	
                        case 0:
                            cout << "Returning to Main Menu.\n";
                            break;
                        default:
                            cout << "Invalid choice! Please try again.";
                    }
                } while (studentChoice != 0);
                break;
            }
            case 3:
                cout << "Thank you for using the Hotel Management System.";
                break;
            default:
                cout << "Invalid choice! Please try again.";
        }
    } while (choice != 3);
}
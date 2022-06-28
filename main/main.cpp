#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <list> //double linked list
#include <iostream>
#include <string>  // for the atoi conversion
#include <iomanip> // for organizing output into columns
#include <vector>
using namespace std;

// forward declarations
class Person;
class Train;
class Queue;
/* ----CLASSES---- */
class Menu // class for managing the app's menu
{
public:
    static void displayMenu();         // displays the menu
    static void select(int selection); // receives user's input and performs the corresponding function
    static void exit_prog();           // exits the app
};
struct Time // structure for managing the Arrival and Departing times
{
    int min;
    int hour;
};
class Train // class for managing the availabe functions of a train
{
private:
    int trainNo, cost, seats, booked_seats;
    string from, to, train_type;
    Time t_leave, t_arrive;

public:
    /* --ADD/REMOVE TRAINS--*/
    void addTrain();
    static void deleteTrain(int num);
    /* --DISPLAY TRAINS--*/
    static void displayTrainInfo(int num);
    static void displaySchedule();
    /* --BOOK SEATS--*/
    static void resSeat(int num, int val);
    /* --TRAIN CHECKERS--*/
    static bool trainExists(int num);   // check train is booked
    static bool checkForSeats(int num); // checks for already registerd trains in the system
    /* --GETTERS--*/
    int
    getTrainNo()
    {
        return this->trainNo;
    }
    Time getLeavingTime() { return this->t_leave; }
    Time getArrivingTime() { return this->t_arrive; }
    string getDeparture() { return this->from; }
    string getDestination() { return this->to; }
};
class Person // class for managing the functions of a passenger
{
private:
    int id, tel;
    list<int> trains;
    string name, surname, nationality, address;

public:
    /* --BOOK TRAIN-- */
    void book();                 // book train for each customer (Menu Option Νο 6)
    void bookFromQueue(int num); // book train for the oldestcustomer in
                                 // (call ONLY when a reservation is cancelled)
    void cancel();               // cancel a reservation (Menu Option Νο 7)
    void cancelFromTrain(Person &p1, int num1);
    /* --SHOW PASSENGER'S INFO-- */
    static bool displayPersonInfo(int id);
    /* --CHECHKER FOR UNIQUE ID-- */
    static bool uniqueID(int id);
    /* --GETTERS-- */
    int getID() { return this->id; }
    string getName() { return this->name; }
    string getSurname() { return this->surname; }
};
struct Node // structure for managing each train's queue
{
    Person person;
    Node *next;
};
class Queue // class that stores passengers on each train's queue
{
private:
    int queueNo;
    Node *rear;
    Node *front;

public:
    /* --CREATE NEW QUEUE-- */
    Queue(int queueId); // queueID is the same as the train number for eachtrain
    /* --ADD/REMOVE ELEMENTS-- */
    void enqueue(Person p); // add a new passenger
    void dequeue();         // remove the passenger add last
    static void display(int num);
    Person oldest();
    /* --CHECK FOR EMPTY QUEUE-- */
    bool isEmpty(); // returns true if queue is empty
    /* --GETTERS-- */
    int getNo() { return this->queueNo; }
    Node *getFront() { return this->front; }
    Node *getRear() { return this->rear; }
    /* --SETTERS-- */
    void setFront(Node *f)
    {
        if (f == 0)
        {
            this->front = NULL;
        }
        else
        {
            this->front = f;
        }
    }
    void setRear(Node *r)
    {
        this->rear = r;
    }
};
/* ----FUNCTIONS-CHECKERS FOR THE INPUTS---- */
bool checkNumber(string s)
{ // checks if the input string consists ONLY ofnumbers
    // enter if string is NOT empty
    if (!s.empty())
    {
        // checks if string contains space or any alphabets
        for (int i = 0; i < s.length(); i++)
        {
            if (((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')))
            {
                return false;
            }
        }
        // check if string is a postive number
        if (atoi(s.c_str()) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool checkString(string s)
{ // checks if string consists only of letters
    if (!s.empty())
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (!((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' &&
                                                         s.at(i) <= 'Z')))
            {
                return false;
            }
        }
        return true;
    }
    else
    { // return false
        return false;
    }
}
/* --CHECKERS FOR DIRECT TRAINS-- */
bool checkTime(string time)
{ // check the validity of the time (must bexx:xx, where x = Natural number)
    // enter ONLY if string is NOT empty
    if (!time.empty())
    {
        for (int i = 0; i < time.length(); i++)
        {
            if (i == 2)
            {
                if (time.at(i) != ':')
                {
                    return false;
                }
            }
            else if (!(time.at(i) >= '0' && time.at(i) <= '9'))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
/* --CHECKER FOR NON-DIRECT TRAINS-- */
bool checkTime2(Time tLeaving, Time tArriving)
{ // checks thevalidity of arrival and departure time
    if (tLeaving.hour > tArriving.hour)
    {
        return true;
    }
    else if (tLeaving.hour == tArriving.hour)
    {
        if (tLeaving.min > tArriving.min)
        {
            return true;
        }
    }
    return false;
}
/*
-------------------------------------------------------------------------------------------
IMPLEMENTATION
--------------------------------------------------------------------------------------------
*/
/* ----GLOBAL VARS---- */
list<Train> tlist;  // store the trains of the system
list<Person> plist; // store the passengers
list<Queue> qlist;  // store the customers in the trains' waiting queues
/* ----FUNCTION OF CLASS Queue---- */
Queue::Queue(int queueId)
{
    this->queueNo = queueId;
    this->rear = NULL;
    this->front = NULL;
}
void Queue::enqueue(Person p)
{
    Node *temp = new Node;
    temp->person = p;
    temp->next = NULL;
    if (this->front == NULL)
    {
        this->front = temp;
    }
    else
    {
        this->rear->next = temp;
    }
    this->rear = temp;
}
void Queue::dequeue()
{
    Node *temp = new Node;
    temp = this->front;
    this->front = this->front->next;
    delete temp;
}

void Queue::display(int num)
{
    for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i)
    {
        if (num == i->queueNo)
        {
            Node *p = new Node;
            p = i->front;
            if (i->front == NULL)
            {
                cout << "\n Empty queue.\n";
            }
            else
            {
                cout << "\nPassengers waiting on queue:" << endl;
                // Left positions characters to the left, within the set field width
                cout << left << setw(15) << "ID" << left << setw(15) << "Name" << left << setw(15) << "Surame" << endl;
                while (p != NULL)
                {
                    cout << left << setw(15) << p->person.getID() << left << setw(15) << p->person.getName() << left << setw(15) << p->person.getSurname() << endl;
                    p = p->next;
                }
            }
        }
    }
}
Person Queue::oldest()
{
    return this->front->person;
}
bool Queue::isEmpty()
{
    if (this->front == NULL && this->rear == NULL)
    {
        return true;
    }
    return false;
}
/* ----FUNCTIONS OF CLASS Menu---- */
void Menu::displayMenu()
{
    int selection; // user's menu choice
    string temp;   // temp to store user's input
    do
    {
        cout << "-----------------------------------------------";
        cout << "\n\t RAILWAY RESERVATION SYSTEM \n\n ";
        cout
            << "Please pick an option from the menu below. \n";
        cout << "1. Add new trains \n";
        cout << "2. Delete trains \n";
        cout << "3. Display train schedule \n";
        cout << "4. Display train details \n";
        cout << "5. Display passenger personal info \n";
        cout << "6. Book reservation \n";
        cout << "7. Cancel reservation \n";
        cout << "8. Exit \n\n";
        cout << "-----------------------------------------------" << endl;
        cout << "Enter the number of a menu option: ";
        cin >> temp;
        // check validity of input
        while (!checkNumber(temp))
        {
            cout << "Please enter a number!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> temp;
        }
        cout << endl;
        selection = atoi(temp.c_str());
        select(selection);
    } while (true);
}
void Menu::select(int selection)
{
    Train f;     // Train's object
    Person p;    // class Person's object
    string temp; // temp to store input
    switch (selection)
    {
    case 1:
        f.addTrain();
        break;
    case 2:
        if (!tlist.empty())
        {
            cout << "Enter Train Number you want to delete: ";
            cin >> temp;
            cout << endl;
            while (!checkNumber(temp))
            {
                cout << "Train Number must be a number!"
                     << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> temp;
                cout << endl;
            }
            Train::deleteTrain(atoi(temp.c_str()));
        }
        else
        {
            cout << "There are no trains to delete" << endl;
        }
        break;
    case 3:
        if (!tlist.empty())
        {
            Train::displaySchedule();
        }
        else
        {
            cout << "There are no scheduled trains!" << endl;
        }
        break;
    case 4:
        if (!tlist.empty())
        {
            cout << "Please insert train's number: ";
            cin >> temp;
            cout << endl;
            while (!checkNumber(temp))
            {
                cout << "Train number must be a number!"
                     << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> temp;
                cout << endl;
            }
            Train::displayTrainInfo(atoi(temp.c_str()));
        }
        else
        {
            cout << "There are no scheduled trains!" << endl;
        }
        break;
    case 5:
        if (!plist.empty())
        {
            cout << "Please insert ID number: ";
            cin >> temp;
            while (!Person::displayPersonInfo(
                atoi(temp.c_str())))
            {
                cout << "Wrong ID number!" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> temp;
                cout << endl;
            }
        }
        else
        {
            cout << "There are no registered clients at the moment !" << endl;
        }
        break;
    case 6:
        p.book();
        break;
    case 7:
        p.cancel();
        break;
    case 8:
        Menu::exit_prog();
        break;
    default:
        cout << "Invalid selection \n";
    }
}
void Menu::exit_prog()
{
    cout << "Thank you for using our system! \n";
    exit(1); // exit
}
/* ----FUNCTIONS OF CLASS Train---- */
void Train::addTrain()
{
    /* ----INITIALISE VARS----*/
    bool flag = false; // used in loops
    /* --Check for arrival, departure time validity (USED ONLY IN
    BOARDING & ARRIVING TIME)-- */
    vector<string> fields; // stores, splitted, user input to be checked
    string temp;           // stores user's input temp
    char *pch;             // stores result of function strtok()
    int hour;              // stores hour
    int min;               // store minutes
    cout << "Add new trains by giving the following attributes: \n";
    // clean stream
    cin.clear();
    cin.ignore(256, '\n');
    /* --TRAIN NUBMER-- */
    cout << "Train Number: ";
    // get user's input
    getline(cin, temp);
    do
    {
        flag = true;
        // check input
        if (!checkNumber(temp))
        {
            cout << "Please insert a valid Train Number! " << endl;
            flag = false;
            getline(cin, temp);
        }
        else if (Train::trainExists(atoi(temp.c_str())))
        {
            cout << "This Train already exists!" << endl;
            cout << "Please insert a valid Train Number!" << endl;
            flag = false;
            getline(cin, temp);
        }
        else
        {
            flag = true;
            this->trainNo = atoi(temp.c_str());
        }
    } while (!flag);
    /* --DEPARTURE-- */
    cout << "Departure: ";
    flag = false;
// check input
LOOP:
    do
    {
        getline(cin, temp);
        if ((temp.length() <= 10) && (checkString(temp)))
        {
            this->from = temp;
            flag = true;
        }
        else
        {
            cout << "Please insert a valid Departure city! ";
            goto LOOP;
        }
    } while (!flag);
    /* --DESTINATION-- */
    cout << "Destination: ";
    flag = false;
// check input
LOOP2:
    do
    {
        getline(cin, temp);
        if ((temp.length() <= 10) && (checkString(temp)) &&
            (temp.compare(this->from)))
        {
            this->to = temp;
            flag = true;
        }
        else
        {
            cout << "Please insert a valid Destination city! ";
            goto LOOP2;
        }
    } while (!flag);
    /* --DEPARTURE TIME-- */
    cout << "Boarding time (e.g. 19:40): "; // ask from user for th boarding time
    flag = false;
// check input
LOOP3:
    do
    {
        getline(cin, temp);
        if (temp.length() != 5 || !checkTime(temp))
        {
            cout << "Please insert a valid boarding time (e.g. 19:40)! ";
            goto LOOP3;
        }
        char t_temp[temp.length()];
        strcpy(t_temp, temp.c_str());
        // split string into hours and minutes
        pch = strtok(t_temp, ":");
        while (pch != NULL)
        {
            fields.push_back(pch);
            pch = strtok(NULL, ":");
        }
        hour = atoi(fields[0].c_str());
        min = atoi(fields[1].c_str());
        // check time
        if ((hour >= 0 && hour <= 23) && (min >= 0 && min <= 59))
        {
            this->t_leave.hour = hour;
            this->t_leave.min = min;
            flag = true;
        }
        else
        {
            cout << "Please insert a valid boarding time (e.g. 19:40)! ";
            fields.clear();
        }
    } while (!flag);
    /* --ARRIVAL TIME-- */
    cout << "Arriving time (e.g. 21:40): ";
    flag = false;
    fields.clear(); // clear fields (because it was used before, at "DEPARTURE TIME")
// check input
LOOP4:
    do
    {
        getline(cin, temp);
        if (temp.length() > 5 || !checkTime(temp))
        {
            cout << "Please insert a valid boarding time (e.g. 19:40)! ";
            goto LOOP4;
        }
        char t_temp[temp.length()];
        strcpy(t_temp, temp.c_str());
        // split string
        pch = strtok(t_temp, ":");
        while (pch != NULL)
        {
            fields.push_back(pch);
            pch = strtok(NULL, ":");
        }
        hour = atoi(fields[0].c_str());
        min = atoi(fields[1].c_str());
        // check validity of time
        if ((hour >= 0 && hour <= 23) && (min >= 0 && min <= 59))
        {
            this->t_arrive.hour = hour;
            this->t_arrive.min = min;
            flag = true;
        }
        else
        {
            cout << "Please insert a valid arriving time (e.g. 19:40)! ";
            fields.clear();
        }
    } while (!flag);
    /* --TICKET COST-- */
    cout << "Ticket price: ";
LOOP5:
    do
    {
        getline(cin, temp);
        flag = true;
        // check input
        if (!checkNumber(temp))
        {
            cout << "Please insert a valid ticket price!" << endl;
            flag = false;
            goto LOOP5;
        }
        else
        {
            flag = true;
            this->cost = atoi(temp.c_str());
        }
    } while (!flag);
    /* --TRAIN TYPE-- */
    cout << "Train type: ";
    getline(cin, this->train_type);
    while (this->train_type.empty())
    {
        cout << "Please insert a valid train type!" << endl;
        getline(cin, this->train_type);
    }
    /* --No OF SEATS-- */
    cout << "Number of seats: ";
LOOP6:
    do
    {
        getline(cin, temp);
        flag = true;
        // check input
        if (!checkNumber(temp))
        {
            cout << "Please insert a valid number of seats!" << endl;
            flag = false;
            goto LOOP6;
        }
        else
        {
            flag = true;
            this->seats = atoi(temp.c_str());
        }
    } while (!flag);
    /* --No of BOOKED SEATS-- */
    cout << "Number of booked seats: ";
LOOP7:
    do
    {
        getline(cin, temp);
        flag = true;
        // check input
        if (!checkNumber(temp))
        {
            cout << "Please insert a valid number of booked seats!"
                 << endl;
            flag = false;
            goto LOOP7;
        }
        else if (atoi(temp.c_str()) > this->seats)
        {
            cout << "Booked seats must be less than train's seats!" << endl;
            flag = false;
            goto LOOP7;
        }
        else
        {
            flag = true;
            this->booked_seats = atoi(temp.c_str());
        }
    } while (!flag);
    cout << endl;
    tlist.push_back(*this); // add object to the tlist
    Queue q(this->trainNo); // create new queue for the newly added train
    qlist.push_back(q);     // add object to the qlist
    cout << "Train No: " << this->trainNo << " was successfully added!"
         << endl;
}
void Train::deleteTrain(int num)
{
    for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end();
         ++i)
    {
        if (num == i->getNo())
        {
            // enter if waiting queue for the train is NOT empty
            if (i->isEmpty())
            {
                // delete object from list
                for (std::list<Train>::iterator i2 =
                         tlist.begin();
                     i2 != tlist.end(); ++i2)
                {
                    if (num == (i2->trainNo))
                    {
                        i2 = tlist.erase(i2);
                        i = qlist.erase(i);
                        cout << "Train with number: "
                             << num << " was successfully deleted" << endl;
                        break;
                    }
                }
            }
            else
            {
                cout << "There are passengers in the queue of the train with No : " << num << endl;
                cout << "Remove ALL of them from the queue first !" << endl;
            }
        }
    }
    for (std::list<Person>::iterator i = plist.begin(); i != plist.end();
         ++i)
    {
        i->cancelFromTrain(*i, num);
    }
    return;
}
void Train::displayTrainInfo(int num)
{
    string l_time, a_time; // departure and arrival time
    stringstream convert;
    stringstream convert2;
    for (std::list<Train>::iterator i = tlist.begin(); i != tlist.end(); ++i)
    {
        if (num == i->trainNo)
        {
            convert.str(std::string());  // clear stringstream "convert"
            convert2.str(std::string()); // clear stringstream "convert2"
            convert << i->t_leave.hour;
            convert2 << i->t_leave.min;
            l_time = convert.str() + ":" + convert2.str();
            convert.str(std::string());  // clear stringstream "convert"
            convert2.str(std::string()); // clear stringstream "convert2"
            convert << i->t_arrive.hour;
            convert2 << i->t_arrive.min;
            a_time = convert.str() + ":" + convert2.str();
            cout << left << setw(10) << "TRAIN" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS"
                 << left << setw(10) << "BOOKED" << endl;
            cout << left << setw(10) << i->trainNo << left << setw(10) << i->from << left << setw(10) << i->to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i->cost << left << setw(10) << i->train_type << left << setw(10) << i->seats << left
                 << setw(10) << i->booked_seats << endl;
            Queue::display(num);
            return;
        }
    }
    cout << "Invalid number of train was given." << endl;
}
void Train::displaySchedule()
{
    string l_time, a_time; // departure and arrivale time
    stringstream convert;
    stringstream convert2;
    cout << "\n\t\t\t\t TRAIN SCHEDULE" << endl
         << endl;
    cout << left << setw(10) << "TRAIN" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10)
         << "BOOKED" << endl;
    for (std::list<Train>::iterator i = tlist.begin(); i != tlist.end();
         ++i)
    {
        convert.str(std::string());  // clear stringstream "convert"
        convert2.str(std::string()); // clear
        convert << i->t_leave.hour;
        convert2 << i->t_leave.min;
        l_time = convert.str() + ":" + convert2.str();
        convert.str(std::string());  // clear stringstream
        convert2.str(std::string()); // clear
        convert << i->t_arrive.hour;
        convert2 << i->t_arrive.min;
        a_time = convert.str() + ":" + convert2.str();
        cout << left << setw(10) << i->trainNo << left << setw(10) << i->from << left << setw(10) << i->to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i->cost << left << setw(10) << i->train_type << left << setw(10) << i->seats << left
             << setw(10) << i->booked_seats << endl;
    }
    cout << endl;
}
void Train::resSeat(int num, int val)
{
    for (std::list<Train>::iterator i = tlist.begin(); i != tlist.end(); ++i)
    {
        if (num == (i->trainNo))
        {
            i->booked_seats += val;
            break;
        }
    }
}
bool Train::trainExists(int num)
{
    for (std::list<Train>::iterator i = tlist.begin(); i != tlist.end(); ++i)
    {
        if (num == i->trainNo)
        {
            return true;
        }
    }
    return false;
}
bool Train::checkForSeats(int num)
{
    for (std::list<Train>::iterator i = tlist.begin(); i != tlist.end(); ++i)
    {
        if (num == (i->trainNo))
        {
            if (i->seats == i->booked_seats)
                return false;
            else
                return true;
        }
    }
}
/* ----FUNCTIONS OF CLASS Person---- */
void Person::book()
{
    /* ----INITIALISE VARS----*/
    /* --TRAINS-- */
    string temp; // temp to store user's input, to be checked
    int num;     // stores train's number, after successful check
    /* --VARS FOR NON DIRECT TRAINS-- */
    int counter = 1; // stores the amount(>=2) of the non-direct trains
    string choice;   // stores user's choice for adding or not more trains to their reservation
    Time tArriving;
    Time tLeaving;
    string Departure;
    string Destination;
    list<int> nums;                        // store trains' numbers
    list<int>::iterator i1 = nums.begin(); // iterator for accessing List nums
    /* --VAR FOR LOOPS-- */
    bool flag = true;
    // clean stream
    cin.clear();
    cin.ignore(256, '\n');
    if (!tlist.empty())
    {
        cout << "Insert y (yes) for a new client or n (no) for an existing client.";
        getline(cin, choice);
        // enter if client is new
        if (choice == "y" || choice == "Y")
        {
            cout << "Please give us your personal info. " << endl;
            /* --NAME-- */
            cout << "Name: ";
            flag = false;
        // check input
        LOOP8:
            do
            {
                getline(cin, this->name);
                if ((this->name.length() <= 10) &&
                    (checkString(this->name)))
                {
                    flag = true;
                }
                else
                {
                    cout << "Please insert a valid Name! ";
                    goto LOOP8;
                }
            } while (!flag);
            /* --SURNAME-- */
            cout << "Surname: ";
            flag = false;
        // check input
        LOOP9:
            do
            {
                getline(cin, this->surname);
                if ((this->surname.length() <= 10) &&
                    (checkString(this->surname)))
                {
                    flag = true;
                }
                else
                {
                    cout << "Please insert a valid Surname! ";
                    goto LOOP9;
                }
            } while (!flag);
            /* --ID No-- */
            cout << "ID number: ";
        // check input
        LOOP10:
            do
            {
                getline(cin, temp);
                flag = true;
                if (!checkNumber(temp))
                {
                    cout << "Please insert a valid ID number"
                         << endl;
                    flag = false;
                    goto LOOP10;
                }
                else if (!Person::uniqueID(atoi(temp.c_str())))
                {
                    cout << "Please check the validity of your ID number " << endl;
                    flag = false;
                    goto LOOP10;
                }
                else
                {
                    flag = true;
                    this->id = atoi(temp.c_str());
                }
            } while (!flag);
            /* --NATIONALITY-- */
            cout << "Nationality: ";
            flag = false;
        // check input
        LOOP11:
            do
            {
                getline(cin, this->nationality);
                if ((this->nationality.length() <= 10) &&
                    (checkString(this->nationality)))
                {
                    flag = true;
                }
                else
                {
                    cout << "Please insert a valid Nationality! ";
                    goto LOOP11;
                }
            } while (!flag);
            /* --ADDRESS-- */
            cout << "Address: ";
            getline(cin, this->address);
            /* --TEL-- */
            cout << "Telephone: ";
            getline(cin, temp);
            // check input
            while (!checkNumber(temp))
            {
                cout << "Please insert a valid telephone number!"
                     << endl;
                getline(cin, temp);
            }
            this->tel = atoi(temp.c_str());
        }
        else
        { // existing customer
            cout << "Pleas give us your ID No: ";
            getline(cin, temp);
            // check input
            while (!checkNumber(temp))
            {
                cout << "Please insert a valid ID number!" << endl;
                flag = false;
                getline(cin, temp);
            }
            // check if ID No is unique
            if (!(Person::uniqueID(atoi(temp.c_str()))))
            {
                for (std::list<Person>::iterator i =
                         plist.begin();
                     i != plist.end(); ++i)
                {
                    if (atoi(temp.c_str()) == i->id)
                    {
                        this->name = i->name;
                        this->surname = i->surname;
                        this->id = i->id;
                        this->nationality = i->nationality;
                        this->address = i->address;
                        this->tel = i->tel;
                        for (std::list<int>::iterator i2 =
                                 i->trains.begin();
                             i2 != i->trains.end(); ++i2)
                        {
                            this->trains.push_back(*i2);
                        }
                        // after copying the customers info,
                        // delete the old object pointingto them
                        i = plist.erase(i);
                        break;
                    }
                }
            }
            else
            {
                cout << "Wrong ID number!" << endl;
                return;
            }
        }
        // display trains
        Train::displaySchedule();
        /* --TRAIN No-- */
        cout << "\n\nEnter the number of the train you 're intrested in:  ";
        getline(cin, temp);
        flag = true;
        // check input
        while (!checkNumber(temp) ||
               !Train::trainExists(atoi(temp.c_str())))
        {
            cout << "Please insert a valid Train No!" << endl;
            getline(cin, temp);
        }
        num = atoi(temp.c_str());
        /*
        ------------------------------------------------------------
        BOOK CUSTOMER'S
        CHOSEN TRAINS(S)
        ------------------------------------------------------------
        */
        // DIRECT TRAINS
        if (Train::checkForSeats(num))
        { // check for vacancy
            this->trains.push_back(num);
            Train::resSeat(num, 1);
            cout << "Your train with No: " << num << " was successfully booked." << endl;
            // NON-DIRECT TRAINS
        }
        else
        {
            choice = "y";
            cout << "There are no available direct trains for this destination." << endl;
            cout << "Please enter the special numbers for the alternative trains.";
            while (choice == "y" || choice == "Y")
            { // exit if user doesn't want to add more trains LOOP12 : cout << "\nNumber #" << counter << " : "; getline(cin, temp);
                // check input
                while (!checkNumber(temp) ||
                       !Train::trainExists(atoi(temp.c_str())))
                {
                    cout << "Please insert a valid Train No!" << endl;
                    cin >> temp;
                }
                num = atoi(temp.c_str());
                if (counter > 1)
                { // enter if user has entered 2 or more trains
                    // store the arrival, departure time and the departure, arriving city
                    for (std::list<Train>::iterator i2 =
                             tlist.begin();
                         i2 != tlist.end(); ++i2)
                    {
                        if (*i1 == i2->getTrainNo())
                        {
                            tArriving = i2->getArrivingTime();
                            Destination = i2->getDestination();
                        }
                        else if (num == i2->getTrainNo())
                        {
                            tLeaving = i2->getLeavingTime();
                            Departure = i2->getDeparture();
                        }
                    }
                    // check validity of each train
                    if (!(checkTime2(tLeaving, tArriving) &&
                          !Departure.compare(Destination)))
                    {
                        cout << "Please enter a train to a valid Destination !" << endl;
                        // goto LOOP12;
                    }
                }
                nums.push_back(num); // add the train's number
                i1++;
                if (counter >= 2)
                {
                    cout << "Do you want to add more train numbers ? (y / n) ";
                    getline(cin, choice);
                }
                counter++;
            }
            // check for vacancies in the chosen trains
            // and add all of the train's numbers to the specific node of the list trains
            for (std::list<int>::iterator i = nums.begin(); i !=
                                                            nums.end();
                 ++i)
            {
                flag = Train::checkForSeats(*i) and flag;
                this->trains.push_back(*i);
            }
            // enter ONLY if there are vacant seats and reserve a seat to each chosen train
            if (flag)
            {
                for (std::list<int>::iterator i = nums.begin(); i !=
                                                                nums.end();
                     ++i)
                {
                    Train::resSeat(*i, 1);
                }
                cout << "Your trains were successfully booked."
                     << endl;
                // if, at least, one train is fully booked add the customer to the queues of each train
            }
            else
            {
                cout << endl;
                cout << "Some of the trains you inserted were over booked." << endl;
                for (std::list<int>::iterator i = nums.begin(); i != nums.end();
                     ++i)
                {
                    for (std::list<Queue>::iterator i2 =
                             qlist.begin();
                         i2 != qlist.end(); ++i2)
                    {
                        if (*i == i2->getNo())
                        {
                            i2->enqueue(*this);
                        }
                    }
                }
                cout << "We have added you in queues for each of these trains." << endl;
            }
        }
        plist.push_back(*this); // add object to plist
    }
    else
    {
        cout << "There are no available trains at the moment." << endl;
        return;
    }
}
void Person::bookFromQueue(int num)
{ // is called only from cancel()
    bool flag = true;
    Person queueFront; // object of the customer added last
    // find the oldest customer
    for (std::list<Queue>::iterator it = qlist.begin(); it != qlist.end(); ++it)
    {
        if (num == it->getNo())
        {
            if (!(it->isEmpty()))
            {
                queueFront = it->oldest();
                break;
            }
            else
            {
                return;
            }
        }
    }
    // check if all of the customer's chosen trains have vacant seats
    for (std::list<int>::iterator i = queueFront.trains.begin(); i !=
                                                                 queueFront.trains.end();
         ++i)
    {
        flag = Train::checkForSeats(*i) and flag;
    }
    // enter ONLY if there are vacancies in ALL of the customer's chosen trains
    // and book them
    if (flag)
    {
        Node *p = new Node;
        // find the trains of the oldest customer
        for (std::list<int>::iterator i = queueFront.trains.begin(); i !=
                                                                     queueFront.trains.end();
             ++i)
        {
            // delete him from the queues
            for (std::list<Queue>::iterator i2 = qlist.begin(); i2 !=
                                                                qlist.end();
                 ++i2)
            {
                if (*i == i2->getNo())
                {
                    p = i2->getFront();
                    while (p != NULL)
                    {
                        if (queueFront.id == p->person.id)
                        {
                            i2->dequeue();
                            Train::resSeat(*i, 1);
                        }
                        p = p->next;
                    }
                }
            }
        }
    }
}
void Person::cancelFromTrain(Person &p, int num)
{
    p.trains.remove(num);
}
void Person::cancel()
{
    string id, num;
    int counter = 1;         // counter that stores user's wrong inputs
    bool trainFound = false; // is false if customer has already booked a seat in a train
    bool isInQueue = false;  // is false if the customer, that will be deleted, doesn't belong in
    // the queue of each train
    if (!plist.empty())
    {
        // clean stream
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please give us your ID number: ";
        getline(cin, id);
        cout << endl;
        // check input
        while (!checkNumber(id))
        {
            cout << "Please insert a valid ID number!" << endl;
            getline(cin, id);
            cout << endl;
        }
        while (!Person::displayPersonInfo(atoi(id.c_str())))
        {
            if (counter == 5)
            {
                cout << "Wrong ID number was given too many times.";
                return;
            }
            else
            {
                cout << "Please check your ID Number." << endl;
                getline(cin, id);
                cout << endl;
                while (!checkNumber(id))
                {
                    cout << "Please insert a valid ID number!"
                         << endl;
                    getline(cin, id);
                    cout << endl;
                }
            }
            counter++;
        }
        cout << "\nWhich train do you want to cancel (enter the train number)? ";
        getline(cin, num);
        counter = 1;
        // check input
        while (!checkNumber(num))
        {
            cout << "Please insert a valid train number!" << endl;
            getline(cin, num);
            cout << endl;
        }
        // iterate through the passenger's trains
        for (std::list<Person>::iterator i = plist.begin(); i != plist.end();
             ++i)
        {
            if (atoi(id.c_str()) == i->id)
            {
                // check input and exit if counter = 5
                do
                {
                    for (std::list<int>::iterator i2 = (i->trains).begin(); i2 != (i->trains).end(); ++i2)
                    {
                        if (atoi(num.c_str()) == *i2)
                        {
                            trainFound = true;
                            i2 = trains.erase(i2); // delete train from passenger's info
                            break;
                        }
                    }
                    if (counter == 5)
                    {
                        cout << "Wrong train number was given too many times.";
                        return;
                    }
                    else if (!trainFound)
                    {
                        cout << "Please check your train number !.";
                        getline(cin, num);
                        cout << endl;
                        // check input
                        while (!checkNumber(num))
                        {
                            cout << "Please insert a valid train number !" << endl;
                            getline(cin, num);
                            cout << endl;
                        }
                    }
                    counter++;
                } while (!trainFound);
                break;
            }
        }
        // delete client from the queue of the train, if they are a part of it
        for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end();
             ++i)
        {
            if (atoi(num.c_str()) == i->getNo())
            {
                if (!i->isEmpty())
                {
                    Node *p = new Node;
                    Node *previousNode;
                    p = i->getFront();
                    while (p != NULL)
                    {
                        if (atoi(id.c_str()) == p->person.id)
                        {
                            isInQueue = true;
                            // enter if the client is on the first position
                            if (p == i->getFront())
                            {
                                i->setFront(p->next);
                                // enter if queue has only one element
                                if (i->getFront() == i->getRear())
                                {
                                    i->setRear(NULL);
                                }
                            }
                            else if (p == i->getRear())
                            { // enter if client is in the last poitsion of the queue
                                previousNode->next = NULL;
                            }
                            else
                            {
                                previousNode->next = p->next;
                            }
                            delete (p);
                            break;
                        }
                        previousNode = p;
                        p = p->next;
                    }
                }
            }
        }
        // enter if passenger is NOT part of the current queue
        if (!isInQueue)
        {
            Train::resSeat(atoi(num.c_str()), -1);
            this->bookFromQueue(atoi(num.c_str()));
        }
        cout << "\nYour reservation was successfully removed! \n"
             << endl;
    }
    else
    {
        cout << "There are no registered clients at the moment!" << endl;
    }
}
bool Person::displayPersonInfo(int id)
{
    for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i)
    {
        if (id == i->id)
        {
            cout << "\n\t\t\t\t PERSONAL INFO" << endl
                 << endl;
            cout << left << setw(15) << "NAME" << left << setw(15) << "SURNAME" << left << setw(15) << "ID No" << left << setw(15) << "NATIONALITY" << left << setw(15) << "ADDRESS" << left
                 << setw(15) << "TELEPHONE" << endl;
            cout << left << setw(15) << i->name << left << setw(15) << i->surname << left << setw(15) << i->id << left << setw(15)
                 << i->nationality << left << setw(15) << i->address << left << setw(15)
                 << i->tel << endl
                 << endl;
            cout << "Your train(s): ";
            for (std::list<int>::iterator i2 = (i->trains).begin(); i2 !=
                                                                    (i->trains).end();
                 ++i2)
            {
                cout << *i2 << " ";
            }
            cout << endl;
            return true;
        }
    }
    cout << "ID number was not found. Check again!" << endl;
    return false;
}
bool Person::uniqueID(int id)
{
    for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i)
    {
        if (id == i->getID())
        {
            return false;
        }
    }
    return true;
}
int main()
{
    Menu::displayMenu();
    return 0;
}

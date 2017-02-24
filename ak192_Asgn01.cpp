/* AnnMarie Kolbl : Project 1
ak192@zips.uakron.edu | ID:3079881
Linked List and Array City Project
*/

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "math.h"

using namespace std;

//city data type
struct City
{
    string Name; //name of city
    double xValue; //xCoordinate of city
    double yValue; //yCoordinate of city
};

class CityLinkedList
{
    struct ListNode
    {
        City value; //value in the node
        struct ListNode *next; //to point to the next node
    };
    ListNode *head = nullptr;

public:

    //Constructor
    CityLinkedList()
    { head == nullptr; }

    //Destructor
    ~CityLinkedList();

    //Operations
    void insertNode(City); //to insert a node
    City searchNode_Name(string); //to search by name
    City searchNode_Coord(double, double); //to search by coordinate
    int deleteNode_Name(string); //to delete by name
    int deleteNode_Coord(double, double); //to delete by coordinate
    int traverseList(double, double, double, string);
    void printList() const; //to print the whole list
};

//function prototypes
int arrayInsert(City [], City, int&, const int); //insert into array
City arraySearch_Name(City [], string, int); //search array by name
City arraySearch_Coord(City [], double, double, int); //search array by coordinate
int arrayDelete_Name(City [], string, int&); //delete city by name
int arrayDelete_Coord(City [], double, double, int&); //delete city by coordinate
int arrayTraversal(City [], double, double, double, string, int); //traverse array
void arrayPrint(City [], int); //prints out array

double dec_to_rad(double); //changes decimals to radians
double distanceFormula(double, double, double, double); //calculates the distance


int main()
{
    chrono::time_point<chrono::system_clock> start, endT;

    /* CODE USED FOR GATHERING TIME DATA
    start = chrono::system_clock::now();
    endT = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = endT-start;
    time_t end_time = chrono::system_clock::to_time_t(endT);

    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    */

    const int SIZE = 900; //constant size for the array
    CityLinkedList linked; //CityLinkedList object

    City cityArray[SIZE]; //City array
    int sizeOfArray = 0; //to hold the size of the array

    char implementOpt; //to hold implementation option
    int operationOpt = 0; //to hold operation option

    //loop for continued input
    while(operationOpt != 8)
    {
        //prints out menu
        cout << endl << "********************************" << endl;
        cout << "Implementation Options: " << endl;
        cout << "A. Use an array-based list implementation" << endl;
        cout << "B. Use a linked-list implementation" << endl;
        cout << endl;
        cout << "Operation Options: " << endl;
        cout << "1. Insert a record " << endl;
        cout << "2. Search for a record by name" << endl;
        cout << "3. Search for a record by coordinate " << endl;
        cout << "4. Delete a record by name " << endl;
        cout << "5. Delete a record by coordinate " << endl;
        cout << "6. Print records within a given distance of a specified location " << endl;
        cout << "7. Print all records " << endl;
        cout << "8. Exit " << endl;

        cout << endl;
        cout << "Enter your implementation option: ";
        cin >> implementOpt;

        cout << "Enter your operation option: ";
        cin >> operationOpt;
        cout << endl;

        //input validation
        if(implementOpt != 'A' && implementOpt != 'a' && implementOpt != 'B' && implementOpt != 'b')
        {
            cout << "You have entered an incorrect implementation option." << endl;
        }

        //input validation
        if(operationOpt <= 0 || operationOpt > 8)
            cout << "You have entered an incorrect operation option." << endl;
        else if(operationOpt == 8)
            return 0; //termination for exit case

        //for array-based implementation
        if(implementOpt == 'A' || implementOpt == 'a')
        {
            switch(operationOpt)
            {
            case 1: //to insert a node
                {
                    City temp1; //to hold user input
                    int returnNum; //to hold search output

                    cin.ignore();
                    cout << "Enter the name of the city: ";
                    getline(cin, temp1.Name);
                    cout << "Enter the x coordinate of the city: ";
                    cin >> temp1.xValue;
                    cout << "Enter the y coordinate of the city: ";
                    cin >> temp1.yValue;


                    start = chrono::system_clock::now();

                    //inserts the city into the array
                    returnNum = arrayInsert(cityArray, temp1, sizeOfArray, SIZE);

                    if(returnNum == 1) //if the city is already in the array
                        cout << "No need to insert again, as this record exists in the existing data set." << endl;
                    else if(returnNum == 0) //if the array is full
                        cout << "The array is full. Unable to insert city." << endl;
                    else
                        cout << "Inserted Successfully." << endl;

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 2:
                {
                    string temp2; //to hold user input
                    City output; //to hold search output

                    cin.ignore();
                    cout << "Enter the name of the city to be searched: ";
                    getline(cin, temp2);

                    start = chrono::system_clock::now();

                    //search the array for the city by name
                    output = arraySearch_Name(cityArray, temp2, sizeOfArray);

                    if(output.Name == "") //if the city is not in the array
                    {
                        cout << endl << "No such record exists in the existing data set." << endl;
                    }
                    else
                    {
                        //print out the city record in the array
                        cout << endl << "Output: " << endl;
                        cout << output.Name << ", (" << output.xValue << "," << output.yValue << ")" << endl;
                    }

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 3:
                {
                    double xCoord; //to hold user input xCoord
                    double yCoord; //to hold user input yCoord
                    City output; //to hold search output

                    cout << "Enter the x coordinate of the city to be searched: ";
                    cin >> xCoord;
                    cout << "Enter the y coordinate of the city to be searched: ";
                    cin >> yCoord;

                    start = chrono::system_clock::now();

                    //search the array for the city by coordinates
                    output = arraySearch_Coord(cityArray, xCoord, yCoord, sizeOfArray);

                    if(output.Name == "") //if the city is not in the array
                        cout << endl << "No such record exists in the existing data set." << endl;
                    else
                    {
                        //print out the city record in the array
                        cout << endl << "Output: " << endl;
                        cout << output.Name << ", (" << output.xValue << "," << output.yValue << ")" << endl;
                    }

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
                    break;
                }
            case 4:
                {
                    string temp4; //to hold user input
                    int output; //to hold output from delete function

                    cin.ignore();
                    cout << "Enter the name of the city to be deleted: ";
                    getline(cin, temp4);

                    start = chrono::system_clock::now();

                    //delete the city from the array by name
                    output = arrayDelete_Name(cityArray, temp4, sizeOfArray);

                    if(output == 1) //if the city was in the array
                        cout << "Deleted successfully." << endl;
                    else
                        cout << "No such record exists in the existing data set." << endl;

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 5:
                {
                    double xCoord; //to hold user input xCoord
                    double yCoord; //to hold user input yCoord
                    int output; //to hold output from delete function

                    cout << "Enter the x coordinate of the city to be deleted: ";
                    cin >> xCoord;
                    cout << "Enter the y coordinate of the city to be deleted: ";
                    cin >> yCoord;

                    start = chrono::system_clock::now();

                    //delete the city from the array by coordinate
                    output = arrayDelete_Coord(cityArray, xCoord, yCoord, sizeOfArray);

                    if(output == 1) //if the city was in the array
                        cout << "Deleted successfully." << endl;
                    else
                        cout << "No such record exists in the existing data set." << endl;

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
                    break;
                }
            case 6:
                {
                    string cityName; //to hold user input
                    City temp; //to hold search function output
                    double xCoord; //to hold converted xCoord
                    double yCoord; //to hold converted yCoord
                    double distance; //to hold user input distance
                    int counter = 0; //to hold the number of cities printed

                    cin.ignore();
                    cout << "Enter the name of the specified location: ";
                    getline(cin, cityName);

                    //to see if the city is in the array
                    temp = arraySearch_Name(cityArray, cityName, sizeOfArray);

                    if(temp.Name == "") //if the city is not in the array
                        cout << "No record exists in the existing data set." << endl;
                    else
                    {
                        cout << "Enter distance: ";
                        cin >> distance;

                        start = chrono::system_clock::now();

                        //convert to radians
                        xCoord = dec_to_rad(temp.xValue);
                        yCoord = dec_to_rad(temp.yValue);

                        //run through the array and find cities within specified distance
                        counter = arrayTraversal(cityArray, xCoord, yCoord, distance, cityName, sizeOfArray);

                        if(counter == 0) //if no cities are within the specified distance
                            cout << "No such record exists in the existing data set." << endl;
                    }

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 7:
                {
                    start = chrono::system_clock::now();

                    //print out the cities in the array
                    arrayPrint(cityArray, sizeOfArray);

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            }
        }
        //for linked list implementation
        if(implementOpt == 'B' || implementOpt == 'b')
        {
            switch(operationOpt)
            {
            case 1: //to insert a node
                {
                    City temp1; //to hold user input
                    City searchOutput1; //to hold search output name
                    City searchOutput2; //to hold search output coord

                    cin.ignore();
                    cout << "Enter the name of the city: ";
                    getline(cin, temp1.Name);
                    cout << "Enter the x coordinate of the city: ";
                    cin >> temp1.xValue;
                    cout << "Enter the y coordinate of the city: ";
                    cin >> temp1.yValue;

                    start = chrono::system_clock::now();

                    //check to see if user input is already in list
                    searchOutput1 = linked.searchNode_Name(temp1.Name);
                    searchOutput2 = linked.searchNode_Coord(temp1.xValue, temp1.yValue);


                    //if the city is not in the list
                    if(searchOutput1.Name == "" && searchOutput2.Name == "")
                    {
                        //insert the node into the list
                        linked.insertNode(temp1);

                        cout << "Record inserted successfully." << endl;
                    }
                    else
                        cout << "No need to insert again, as this record exists in the existing data set." << endl;

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 2: //to search by name
                {
                    City temp2; //to hold search output
                    string tempInput; //to hold user input

                    cin.ignore();
                    cout << "Enter the name of the city to be searched: ";
                    getline(cin, tempInput);

                    start = chrono::system_clock::now();

                    //search the list for the city
                    temp2 = linked.searchNode_Name(tempInput);

                    //if the city is not in the list
                    if(temp2.Name == "")
                    {
                        cout << endl;
                        cout << "No such record exists in the existing data set." << endl;
                    }
                    else
                    {
                        //print out the city record in the list
                        cout << endl << "Output: " << endl;
                        cout << temp2.Name << ", (" << temp2.xValue << "," << temp2.yValue << ")" << endl;
                    }

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 3:
                {
                    City temp3; //to hold search output
                    double xCoord; //to hold user input xCoord
                    double yCoord; //to hold user input yCoord

                    cout << "Enter the x coordinate of the city to be searched: ";
                    cin >> xCoord;
                    cout << "Enter the y coordinate of the city to be searched: ";
                    cin >> yCoord;

                    start = chrono::system_clock::now();

                    //search the list for the city
                    temp3 = linked.searchNode_Coord(xCoord, yCoord);

                    //if the city is not in the list
                    if(temp3.Name == "")
                    {
                        cout << endl;
                        cout << "No such record exists in the existing data set." << endl;
                    }
                    else
                    {
                        //print out the city record in the list
                        cout << endl << "Output: " << endl;
                        cout << temp3.Name << ", (" << temp3.xValue << "," << temp3.yValue << ")" << endl;
                    }

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 4:
                {
                    string tempInput4; //to hold user input
                    int returnNum4 = 0; //to hold return number

                    cin.ignore();
                    cout << "Enter the name of the city to be deleted: ";
                    getline(cin, tempInput4);

                    start = chrono::system_clock::now();

                    //delete the node from the list
                    returnNum4 = linked.deleteNode_Name(tempInput4);

                    if(returnNum4 == 1) //if the city was in the list
                        cout << "Deleted successfully." << endl;
                    if(returnNum4 == 2) //if the city was not in the list
                        cout << "No such record exists in the existing data set." << endl;

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 5:
                {
                    double xCoord5; //to hold user input xCoord
                    double yCoord5; //to hold user input yCoord
                    int returnNum5; //to hold return number

                    cout << "Enter the x coordinate of the city to be deleted: ";
                    cin >> xCoord5;
                    cout << "Enter the y coordinate of the city to be deleted: ";
                    cin >> yCoord5;

                    start = chrono::system_clock::now();

                    //delete the node from the list
                    returnNum5 = linked.deleteNode_Coord(xCoord5, yCoord5);

                    if(returnNum5 == 1) //if the city was in the list
                        cout << "Deleted successfully." << endl;
                    if(returnNum5 == 2) //if the city was not in the list
                        cout << "No such record exists in the existing data set." << endl;

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 6:
                {
                    string cityName; //to hold user input
                    City returnCity; //to hold search output
                    double distance; //to hold user input
                    double xCoord; //to hold x value from dec_to_rad
                    double yCoord; //to hold y value from dec_to_rad
                    int counter; //to hold return from traverseList

                    cin.ignore();
                    cout << "Enter name of the specified location: ";
                    getline(cin, cityName);

                    //search for the name of the city in the list
                    returnCity = linked.searchNode_Name(cityName);

                    //if the city is not in the list
                    if(returnCity.Name == "")
                    {
                        cout << "No such record exists in the existing data set." << endl;
                    }
                    else
                    {
                        cout << "Enter distance: ";
                        cin >> distance;

                       start = chrono::system_clock::now();

                        //convert x and y to radians
                        xCoord = dec_to_rad(returnCity.xValue);
                        yCoord = dec_to_rad(returnCity.yValue);

                        //traverse the list
                        counter = linked.traverseList(xCoord, yCoord, distance, cityName);

                        //if there are no members matching the requested distance
                        if(counter == 0)
                            cout << "No such record exists in the existing data set." << endl;
                    }

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

                    break;
                }
            case 7:
                {
                    start = chrono::system_clock::now();

                    //prints out the whole list
                    linked.printList();

                    endT = chrono::system_clock::now();

                    chrono::duration<double> elapsed_seconds = endT-start;
                    time_t end_time = chrono::system_clock::to_time_t(endT);

                    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
                    break;
                }
            }
        }
    }
}

/******************************************
Array Insert: Inserts a city into the first
unfilled element in the array. Accepts an
array, the city to insert, the number of
elements in the array passed by reference,
and the constant size of the array. Returns
an integer value.
******************************************/
int arrayInsert(City cityArray[], City insertCity, int &arraySize, const int SIZE)
{
    if(arraySize >= SIZE) //if the array is full
        return 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(cityArray[i].Name == insertCity.Name) //if the city is already in the array
            return 1;
        if(cityArray[i].xValue == insertCity.xValue)
        {
            if(cityArray[i].yValue == insertCity.yValue)
                return 1;
        }
    }
    cityArray[arraySize] = insertCity; //insert the city
    arraySize++; //increment
    return 2;
}

/****************************************
Array Search by Name: searches the array
for the city by name. Passed an array,
a string of user input, and the number
of elements in the array. Returns a city.
****************************************/
City arraySearch_Name(City cityArray[], string input, int arraySize)
{
    //blank city
    City temp;
    temp.Name = "";
    temp.xValue = 0;
    temp.yValue = 0;

    for(int i = 0; i < arraySize; i++) //traverse the array
    {
        if(cityArray[i].Name == input) //if the city is in the array
        {
            return cityArray[i];
        }
    }
    return temp; //if the city is not in the array

}

/****************************************
Array Search by Coord: searches the array
for the city by coordinate. Passed an array,
two doubles of coordinates, and the number
of elements in the array. Returns a city.
****************************************/
City arraySearch_Coord(City cityArray[], double xCoord, double yCoord, int arraySize)
{
    //blank city
    City temp;
    temp.Name = "";
    temp.xValue = 0;
    temp.yValue = 0;

    for(int i = 0; i < arraySize; i++) //traverse the array
    {
        if(cityArray[i].xValue == xCoord) //if the x coordinate is in the array
        {
            if(cityArray[i].yValue == yCoord) //if the y coordinate is in the array
            {
                return cityArray[i];
            }
        }
    }
    return temp; //if the city is not in the array
}

/******************************************************
Array Delete by Name: searches the array and deletes
an element based on the name of the city. Passed an
array, a string holding the name to search for, and
the number of elements passed by reference. Returns an
integer.
******************************************************/
int arrayDelete_Name(City cityArray[], string input, int &arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(cityArray[i].Name == input) //if the city is in the array
        {
            for(int k = i; k < arraySize - 1; k++)
            {
                cityArray[k] = cityArray[k + 1];//data shift left
            }
            arraySize--; //decrements
            return 1;
        }
    }
    return 2; //if the city was not in the array
}

/******************************************************
Array Delete by Coord: searches the array and deletes
an element based on the coordinate of the city. Passed
an array, two doubles holding the coordinates, and
the number of elements passed by reference. Returns an
integer.
******************************************************/
int arrayDelete_Coord(City cityArray[], double xCoord, double yCoord, int &arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(cityArray[i].xValue == xCoord) //if the x coordinate is in the array
        {
            if(cityArray[i].yValue == yCoord) //if the y coordinate is in the array
            {
                for(int k = i; k < arraySize - 1; k++)
                {
                    cityArray[k] = cityArray[k + 1]; //data shift left
                }
                arraySize--; //decrements
                return 1;
            }
        }
    }
    return 2; //if the city was not in the array
}

/****************************************
Array Print: prints out all the elements
contained in the array. Accepts an array
and the number of filled elements, returns
nothing.
****************************************/
void arrayPrint(City cityArray[], int arraySize)
{
    if(arraySize == 0) //if there are no elements in the array
    {
        cout << "The array is empty." << endl;
        return;
    }

    for(int i = 0; i < arraySize; i++) //traverse the array
    {
        cout << cityArray[i].Name << ", (" << cityArray[i].xValue << "," << cityArray[i].yValue << ")" << endl;
    }
}

/*******************************************************************
Array Traversal: traverses the array and calculates the distance
between the input city and the rest of the cities in the array.
Accepts an array, two coordinate points, the input distance, the
name of the city, and the number of filled elements. Returns an int
********************************************************************/
int arrayTraversal(City cityArray[], double xCoord1, double yCoord1, double distance, string input, int arraySize)
{
    if(arraySize == 0) //if there are no elements in the array
        cout << "The list is empty." << endl;

    int counter = 0; //to hold the number of cities that match search parameters
    double xCoord2; //to hold the converted x coordinate
    double yCoord2; //to hold the converted y coordinate
    double returnDistance; //to hold the distance returned

    for(int i = 0; i < arraySize; i++)
    {
        if(cityArray[i].Name != input) //if the city is not the one the user searched for
        {
            xCoord2 = dec_to_rad(cityArray[i].xValue); //convert x coordinate to radians
            yCoord2 = dec_to_rad(cityArray[i].yValue); //convert y coordinate to radians

            returnDistance = distanceFormula(xCoord1, yCoord1, xCoord2, yCoord2); //calculate the distance

            if(returnDistance <= distance) //if calculated distance is less than input distance
            {
                ++counter; //increment

                //display the value in the array
                cout << cityArray[i].Name << ", (" << cityArray[i].xValue << "," << cityArray[i].yValue << ")" << endl;
            }
        }
    }
    return counter; //return number of cities that match search parameters
}


/***************************************
Decimal to Radians: accepts a double
and converts from a decimal to radians.
Returns a double
***************************************/
double dec_to_rad(double dec)
{
    return dec * (3.1415926535/180.0);
}

/***************************************
Distance Formula: Calculates the distance
between 2 cities. Accepts 4 coordinates
as doubles, returns a double
****************************************/
double distanceFormula(double lat1, double long1, double lat2, double long2)
{
    double e;
    const double R = 3963.191;

    e = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long2 - long1));

    return e * R;
}

/****************************************
Print List Function: Traverses the list
and prints out each element. Accepts
no parameters, returns nothing
****************************************/
void CityLinkedList::printList() const
{
    ListNode *nodePtr; //to traverse the list

    if(!head)
        cout << "The list is empty." << endl;

    nodePtr = head; //points to the head of the list

    while(nodePtr != nullptr)
    {
        //display the value in the node
        cout << nodePtr->value.Name << ", (" << nodePtr->value.xValue << "," << nodePtr->value.yValue << ")" << endl;

        //move through the array
        nodePtr = nodePtr->next;
    }
}

/*********************************************
Insert Node Function: Traverses the list and
inserts a node into it. Accepts a newValue of
type City and returns nothing.
*********************************************/
void CityLinkedList::insertNode(City newValue)
{
    ListNode *newNode; //to hold the new node to be inserted
    ListNode *nodePtr; //to traverse the list
    ListNode *previousNode = nullptr; //to hold the previous node

    newNode = new ListNode;
    newNode->value = newValue; //assign value to newNode

    if(!head) //if there are no elements
    {
        head = newNode; //make new node the head
        newNode->next = nullptr;
    }
    else
    {
        nodePtr = head; //point to the head of the list

        previousNode = nullptr;

        while(nodePtr != nullptr && nodePtr->value.xValue < newValue.xValue) //traverse the list
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        if(previousNode == nullptr) //insert the node into the list
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else //insert the node into the list
        {
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}

/******************************************
Search Node by Name Function: Traverses
the list and searches for a member by the
name of the city. Accepts a string containing
the city name, returns City from the list
*******************************************/
City CityLinkedList::searchNode_Name(string value)
{
    ListNode *nodePtr; //to traverse the list

    City tmp; //create a blank city
    tmp.Name = "";
    tmp.xValue = 0;
    tmp.yValue = 0;

    if(!head) //if the list is empty
        return tmp; //return the blank city

    nodePtr = head; //points node to head of list

    while(nodePtr != nullptr)
    {
        if(nodePtr->value.Name == value) //if the name is in the list
        {
            return nodePtr->value;
        }
        else
        {
            nodePtr = nodePtr->next; //traverse the list
        }
    }

    return tmp; //return blank city
}

/*********************************************
Search Node by Coordinate Function: Traverses
the list and searches for a member by the
coordinates of the city. Accepts two doubles
containing the city coordinates, and returns
a City from the list
*********************************************/
City CityLinkedList::searchNode_Coord(double xCoord, double yCoord)
{
    ListNode *nodePtr; //to traverse the list

    City tmp; //create blank city
    tmp.Name = "";
    tmp.xValue = 0;
    tmp.yValue = 0;

    if(!head) //if the list is empty
        return tmp;

    nodePtr = head; //points node to head of list

    while(nodePtr != nullptr)
    {
        if(nodePtr->value.xValue == xCoord && nodePtr->value.yValue == yCoord) //if the coordinates are in the list
        {
            return nodePtr->value;
        }
        else
        {
            nodePtr = nodePtr->next; //traverse the list
        }
    }

    return tmp; //return the blank city
}

/****************************************************
Delete Node by Name: Traverses the list to
find the element to delete and deletes it.
Accepts a string containing the name of the
city, returns an integer to indicate whether
the record existed and whether it has been deleted
*****************************************************/
int CityLinkedList::deleteNode_Name(string value)
{
    ListNode *nodePtr; //to traverse the list
    ListNode *previousNode; //to keep track of the previous node

    if(!head) //if the list is empty
        return 2;

    if(head->value.Name == value) //if the city is the first value in the list
    {
        nodePtr = head->next;
        delete head;
        head = nodePtr;
        return 1;
    }

    previousNode = head;
    nodePtr = head->next;

    while(nodePtr != nullptr)
    {
        if(nodePtr->value.Name == value) //if the city is in the list
        {
            previousNode->next = nodePtr->next;
            delete nodePtr;
            nodePtr = previousNode;
            return 1;
        }
        //traverse the array
        previousNode = previousNode->next;
        nodePtr = nodePtr->next;
    }
    return 2;
}

/****************************************************
Delete Node by Coordinate: Traverses the list to
find the element to delete and deletes it.
Accepts two doubles containing the coordinates of
the city, returns an integer to indicate whether
the record existed and whether it has been deleted
*****************************************************/
int CityLinkedList::deleteNode_Coord(double xCoord, double yCoord)
{
    ListNode *nodePtr; //to traverse the list
    ListNode *previousNode; //to keep track of the previous node

    if(!head) //if the list is empty
        return 2;

    //if the coordinates belong to the first element in the list
    if(head->value.xValue == xCoord)
    {
        if(head->value.yValue == yCoord)
        {
            nodePtr = head->next;
            delete head;
            head = nodePtr;
            return 1;
        }
    }

    previousNode = head;
    nodePtr = head->next;

    while(nodePtr != nullptr)
    {
        if(nodePtr->value.xValue == xCoord) //if the x coordinate is in the list
        {
            if(nodePtr->value.yValue == yCoord) //if the y coordinate is in the list
            {
                previousNode->next = nodePtr->next;
                delete nodePtr;
                nodePtr = previousNode;
                return 1;
            }
        }
        //traverse the list
        previousNode = previousNode->next;
        nodePtr = nodePtr->next;
    }
    return 2;
}

/**********************************************
Traverse List Function: Traverses the list
and calculates the distance between all the
points in the list and user-input point. Accepts
two doubles holding the initial coordinates,
a double holding the distance requirement, and a
string holding the initial city name. Returns an
integer to indicate whether any cities fall within
the given radius
************************************************/
int CityLinkedList::traverseList(double xCoord1, double yCoord1, double distance, string cityName)
{
    ListNode *nodePtr; //to traverse the list
    double xCoord2; //to hold the x coordinate
    double yCoord2; //to hold the y coordinate
    double returnDistance; //to hold the return distance
    int counter = 0; //to hold the number of cities that match the search parameters

    if(!head) //if the list is empty
        cout << "The list is empty." << endl;

    nodePtr = head; //points to the head of the list

    while(nodePtr != nullptr) //traverse the list
    {
        if(nodePtr->value.Name != cityName)
        {
            xCoord2 = dec_to_rad(nodePtr->value.xValue); //convert to radians
            yCoord2 = dec_to_rad(nodePtr->value.yValue); //convert to radians

            returnDistance = distanceFormula(xCoord1, yCoord1, xCoord2, yCoord2); //calculate distance between 2 cities

            if(returnDistance <= distance) //if the city is within range
            {
                ++counter; //increment

                //display the value in the node
                cout << nodePtr->value.Name << ", (" << nodePtr->value.xValue << "," << nodePtr->value.yValue << ")" << endl;
            }
        }
        //move through the array
        nodePtr = nodePtr->next;
    }
    return counter; //return number of cities that matched search parameters
}

/******************************
   CityLinkedList Destructor
******************************/
CityLinkedList::~CityLinkedList()
{
    ListNode *nodePtr;
    ListNode *nextNode;

    nodePtr = head;

    while(nodePtr != nullptr) //traverse the list
    {
        nextNode = nodePtr->next;
        delete nodePtr; //delete

        nodePtr = nextNode;
    }
}

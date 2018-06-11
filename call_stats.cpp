/*
Name: Gregory Hudson
Foundations of Computer Science COP (3014)
Professor Lofton Bullard
Due date: 4/14/17
Due time:11:59pm
Module 11 - Assignment #10

Description: The class will manage a dynamic array of call records

*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
    
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

class call_class
{
public:
	call_class();
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	call_class & operator-(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator<<(ostream & out_to_screen, call_class & Org); //prints all the elements in the 
																			//list to the screen.
private:
	int count;
	int size;
	call_record *call_DB;
};




/************************************************************************************************************************************/
//Name: default constructor
//Precondition: call_DB is empty
//Postcondition: call_DB has the data that was stores in the data file call_stats_data.txt
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;

	call_DB = new call_record[size];

	ifstream in;
	in.open("callstats_data.txt");

	while (!in.eof())
	{
	
		if (is_full())
		{

		double_size();
	}

			in >> call_DB[count].firstname;
			in >> call_DB[count].lastname;
			in >> call_DB[count].cell_number;
			in >> call_DB[count].relays;
			in >> call_DB[count].call_length;

			count++;

		}

		in.close();

	}





/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: count is set to zero
//Postcondition: count is zero
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: count is set equal to size 
//Postcondition: count equals size
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: key is constant, searching for key in call_DB[i].cell_number
//Postcondition: key is found in cell number 
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	for (int i = 0; i < count; i++) {

		if (call_DB[i].cell_number == key) {

			return i;
		}
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: memeber function of call_class
//Postcondition: call_DB is an index bigger
//Decription: adds the informaton for a call record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full()) {

		double_size();
	}

	cout << "Enter the firstname, lastname, cell number, relays and call length" << endl;

	cin >> call_DB[count].firstname;
	cin >> call_DB[count].lastname;
	cin >> call_DB[count].cell_number;
	cin >> call_DB[count].relays;
	cin >> call_DB[count].call_length;

	count++;

}

/********************************************************************************************************************************/
//Name: operator-
//Precondition: key is constant in this function
//Postcondition: call_DB is decremented by one index if key is found in call_DB
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	int loc = search(key);
	
	for (int i = loc; i < count; i++) 
	{

		if (loc != -1) {
			call_DB[i] = call_DB[i + 1];
		}
		
		count--;
	}

	
	return *this;
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: call_DB is full 
//Postcondition: call_DB size is twice its original size 
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: The net cost, tax rate, call tax and total cost are not defined
//Postcondition: The net cost, tax rate, call tax and total cost are defined
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int i = 0; i < count; i++)
	{

		call_DB[i].net_cost = (call_DB[i].relays / 50.0 * 0.40 * call_DB[i].call_length);

		if (call_DB[i].relays >= 0.0 && call_DB[i].relays <= 5.0)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (call_DB[i].relays >= 6.0 && call_DB[i].relays <= 11.0)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (call_DB[i].relays >= 12.0 && call_DB[i].relays <= 20.0)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (call_DB[i].relays >= 21.0 && call_DB[i].relays <= 50.0)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else
		{
			call_DB[i].tax_rate = 0.12;
		}

		//call tax calculation
		call_DB[i].call_tax = (call_DB[i].net_cost * call_DB[i].tax_rate);

		//total cost calculation
		call_DB[i].total_cost = (call_DB[i].net_cost + call_DB[i].call_tax);
	}
}


/****************************************************************************************************************************/
//Name: operator<<
//Precondition:  variables have been defined and initalized 
//Postcondition: prints all the fields of the call record in call_DB to the screen 
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen.
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	for (int i = 0; i<Org.count; i++)
	{
		out.setf(ios::showpoint);
		out.setf(ios::fixed);
		out.precision(2);



		out << Org.call_DB[i].firstname << "  " << Org.call_DB[i].lastname
			<< "  " << Org.call_DB[i].relays << "  " << Org.call_DB[i].cell_number
			<< "  " << Org.call_DB[i].call_length << "  " << Org.call_DB[i].net_cost <<
			"  " << Org.call_DB[i].tax_rate << "  " << Org.call_DB[i].call_tax << "  " << Org.call_DB[i].total_cost << endl;
	}



	return out;  //must have this statement
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: call_DB is not empty 
//Postcondition: call_DB is empty
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[] call_DB;
	call_DB = 0;
}


//driver to test the functionality of your class.
int main()
{
	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";
	call_class MyClass;
	cout << "Finish TEST1: testing the default constructor\n\n\n\n";

	cout << "Test2: Testing add, double_size, process, and is_full() \n";
	MyClass.add();
	MyClass.process();
	cout << MyClass << endl;
	
	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, serach, and is_empty\n";
	MyClass - "5617278899" - "9546321555" - "1234567890";
	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";
	cout << MyClass << endl;
	cout << "Fist TEST4\n\n\n\n";

	cout << "The destructor will be called automatically\n";

	return 0;
}

//PROGRAM NEEDS C++11 TO RUN
#include <iostream>	//for standard input output functions
#include <fstream>	//for filing
#include <string>	//for string functions
#include <unistd.h>	//for sleep functions
#include <conio.h>	//for getch function
using namespace std;

//function and class declaration
class Room;
class Customer;
void changeAvailability(bool av, string check,string name);
void checkOut(string n, int r);

class Room{
	private:
		int room_no;
		string type;
		bool availability;
		double costperday;
		static int noOfRooms;
		string customerName;
		friend class Customer;
	public:
		Room()
		{
			//default constructor
		}
		Room(int r, string t, bool a, double c)	//parameterized constructor
		{
			room_no=r; 
			type=t; 
			availability=a; 
			costperday=c;
			noOfRooms++;
		}
		//setter functions
		void set_roomno(int r){
			room_no=r;
		}
		void set_type(string type){
			this->type=type;
		}
		void set_avail(bool a){
			availability=a;
		}
		void set_cost(double c){
			costperday=c;
		}
		void set_customername(string c){
			customerName=c;
		}
		
		//getter functions
		int get_roomno() const{
			return room_no;
		}
		double get_cost() const{
			return costperday;
		}
		static int get_noOfRooms(){
			return noOfRooms;
		}
		bool get_avail(){
			return availability;
		}		
		string get_customername(){
			return customerName;
		}
		static int add_room(){
			noOfRooms++;
		}
		static int del_room(){
			noOfRooms--;
		}
};
int Room::noOfRooms=12;	//initialization of static variable

class Customer{
	private:
		string name;
		char gender;
		const int days_staying;
		double bill;
		int roomServiceOrders;
		static int noOfCustomers;
		Room room;
		
	public:
		Customer():days_staying(){		//default constructor
			noOfCustomers++; 
			roomServiceOrders=0; 
			bill=0;
		}
		//parameterized constructor with member initializer list for constant data member
		Customer(string n, char g, int d): days_staying(d){	
			name=n; 
			gender=g;
			noOfCustomers++; 
			roomServiceOrders=0; 
			bill=0;
		}
		Customer(string n, char g, int d, int r, double b): days_staying(d){	
			name=n; 
			gender=g; 
			roomServiceOrders=r; 
			bill=b;
		}
		//copy constructor
		Customer(const Customer &c): days_staying(c.days_staying){	
			name=c.name; 
			gender=c.gender;
			roomServiceOrders=c.roomServiceOrders; 
			bill=c.bill;
		}
		
		void orderRoomService();	//member function to order room service
		
		void checkIn(string t);		//member function to book a room
		
		friend void checkOut(string n, int r);	//friend function to check out
		
		//setter functions
		void setname(string name){
			this->name=name;
		}
		void setgender(char gender){
			this->gender=gender;
		}
		inline void set_bill(){
			bill=room.get_cost()*days_staying;
		}
		void setroomserviceorders(int rms){
			roomServiceOrders=rms;
		}
		
		//getter functions
		string get_name() const{
			return name;
		}
		char get_gender() const{
			return gender;
		}
		int get_days() const{
			return days_staying;
		}
		double get_bill() const{
			return bill;
		}
		int get_roomServiceOrders() const{
			return roomServiceOrders;
		}
		static int get_noOfCustomers(){
			return noOfCustomers;
		}
};
int Customer::noOfCustomers=6;	//initialization of static variable

class Staff{	
	//data mambers
	protected:
	int employeeID;
	string name;
	string position;
	string hiredate;
	int hoursworked;
	static int totalWorkers;
	
	public:
	Staff(){
		//default constructor
	}
	
	//parameterized
	Staff(int employeeID,string name,string position,string hiredate,int hoursworked):employeeID(employeeID){
		this->name=name;
		this->position=position;
		this->hiredate=hiredate;
		this->hoursworked=hoursworked;
		totalWorkers=totalWorkers+1;
	}
	
	//setters
 	void set_employeeID(int employeeID){
		this->employeeID=employeeID;
	}
	
	void set_name(string name){
		this->name=name;
	}
	
	void set_position(string position){
		this->position=position;
	}
	
	void set_hiredate(string hiredate){
		this->hiredate=hiredate;
	}
	
	void set_hoursworked(int hoursworked){
		this->hoursworked=hoursworked;
	}
	
	//getters
	int get_employeeID() const{
		return employeeID;
	}
	
	string get_name() const{
		return name;
	}
	
	string get_position() const{
		return position;
	}
	
	string get_hiredate() const{
		return hiredate;
	}
	
	int get_hoursworked() const{
		return hoursworked;
	}
	
	static int get_totalworkers(){
		return totalWorkers;
	}
	
	//member functions
	virtual void display(){	//overridden function
		cout<<endl<<"----------------EMPLOYEE DETAILS---------------------\n";
		cout<<"Employee ID = "<<employeeID<<endl;
		cout<<"Employee name = "<<name<<endl;
		cout<<"Employee position = "<<position<<endl;
		cout<<"Employee hire date = "<<hiredate<<endl;
		cout<<"Employee hours worked = "<<hoursworked<<endl<<endl;
	}
	
	//overloaded functions
	void addHours(){
		hoursworked++;
		//update staff file	
		ifstream file;
		file.open("Staff.txt");
    	string text, filename, a1,a2,a3,a4,a5;
  		// create new file to store staff records 
 		ofstream newf("temp3.txt");
    	while (file>>text){
   		 	file>>a1; file>>a2; file>>a3; file>>a4; file>>a5; 
			if(stoi(a1)==employeeID){
				//write updated value for hoursworked
    			newf<<text<<"   "<<a1<<"	"<<a2<<"		"<<a3<<"	   "<<a4<<"	  "<<hoursworked<<endl;	
			}
			else{
				//read from old file and input in temporary file
				newf<<text<<"   "<<a1<<"	"<<a2<<"		"<<a3<<"	   "<<a4<<"	  "<<a5<<endl;	
			}
		}
		// Close the files
		newf.close();
		file.close();
		ifstream infile;
		infile.open("temp3.txt");
		ofstream outfile;
		outfile.open("Staff.txt", ios::trunc);
		//copy records from temp file back to staff file
		while (getline (infile, text)) {
		  outfile << text << endl;
		}
		// Close the files
		newf.close();
		outfile.close();
		//delete old file
		remove("temp3.txt");
	}
	void addHours(int n){
		hoursworked+=n;
		//update staff file	
		ifstream file;
		file.open("Staff.txt");
    	string text, filename, a1,a2,a3,a4,a5;
  		// create new file to store staff records 
 		ofstream newf("temp3.txt");
    	while (file>>text){
   		 	file>>a1; file>>a2; file>>a3; file>>a4; file>>a5; 
			if(stoi(a1)==employeeID){
				//write updated value for hoursworked
    			newf<<text<<"   "<<a1<<"	"<<a2<<"		"<<a3<<"	   "<<a4<<"	  "<<hoursworked<<endl;	
			}
			else{
				//read from old file and input in temporary file
				newf<<text<<"   "<<a1<<"	"<<a2<<"		"<<a3<<"	   "<<a4<<"	  "<<a5<<endl;	
			}
		}
		// Close the files
		newf.close();
		file.close();
		ifstream infile;
		infile.open("temp3.txt");
		ofstream outfile;
		outfile.open("Staff.txt", ios::trunc);
		//copy records from temp file back to staff file
		while (getline (infile, text)) {
		  outfile << text << endl;
		}
		// Close the files
		newf.close();
		outfile.close();
		//delete old file
		remove("temp3.txt");
	}
	
	//operators overloaded to use as a find function
	bool operator == (string n){
	if(name==n)
		return true;
	else
		return false;
	}
	
	bool operator == (int id){
	if(employeeID==id)
		return true;
	else
		return false;
	}
	
};
int Staff::totalWorkers=6;

class Receptionist:public Staff{
	public:
		//constructors
		//default
		Receptionist(){}
		
		//parameterized
		Receptionist(int employeeID,string name,string position,string hiredate, int hoursworked):Staff(employeeID,name,position,hiredate,hoursworked){}
		
		//member functions
		void viewRooms();
		
		void viewCustomers();
		
		void display(){	//overriding function
		cout<<endl<<"----------------RECEPTIONIST DETAILS---------------------\n";
		cout<<"Receptionist ID = "<<employeeID<<endl;
		cout<<"Receptionist name = "<<name<<endl;
		cout<<"Receptionist position = "<<position<<endl;
		cout<<"Receptionist hire date = "<<hiredate<<endl;
		cout<<"Receptionist hours worked = "<<hoursworked<<endl<<endl;
	}
};

class Manager:public Staff{
	
	public:		
		//constructors
		//default
		Manager(){}
		
		//parameterized
		Manager(int employeeID,string name,string position,string hiredate,int hoursworked):Staff(employeeID,name,position,hiredate,hoursworked){
		
		}
		
		//member functions
		void viewStaff(){
			string text;
			// Read from the text file
			ifstream s("Staff.txt");
			cout<<"EMPLOYEE      ID	NAME		POSITION   HIRE DATE	HOURS WORKED"<<endl;
			// Use a while loop together with the getline() function to read the file line by line
			while (getline (s, text)) {
			  // Output the text from the file
			  cout << text << endl;
			}
			// Close the file
			s.close();	
		}
		
		void addStaff(Staff &s){
			string id, name, position, hiredate;
			cout<<"Enter employee ID: ";
			cin>>id;
			cout<<"Enter name: ";
			cin>>name;
			cout<<"Enter position: ";
			cin>>position;
			cout<<"Enter hire date: ";
			cin>>hiredate;
			totalWorkers++;
			ofstream file;
			file.open("Staff.txt",ios::app);
			file<<"Employee"<<totalWorkers<<"|"<<"   "<<id<<"	"<<name<<"		"<<position<<"	   "<<hiredate<<"	  "<<"0"<<endl;
			file.close();
			s.set_employeeID(stoi(id)); s.set_name(name); s.set_position(position); s.set_hiredate(hiredate); s.set_hoursworked(0);
			cout<<endl<<"EMPLOYEE ADDED!"<<endl<<"Press any key to go back"<<endl;
			getch();
			system("cls");
		}
		
		void deleteStaff(){
			string id; int flag=0;
			cout<<"Enter ID of the employee you want to fire: ";
			cin>>id;
			
			ifstream file;
			file.open("Staff.txt");
    		string text, a1,a2,a3,a4,a5;
  			// create new file to store staff records 
 			ofstream newf;
			newf.open("temp3.txt");
    		while (file>>text){
   			 	file>>a1; file>>a2; file>>a3; file>>a4; file>>a5; 
				if(a1==id){
    				//skip this employee
    				flag=1;
				}
				else{
					//read from old file and input in temporary file
					newf<<text<<"   "<<a1<<"	"<<a2<<"		"<<a3<<"	   "<<a4<<"	  "<<a5<<endl;
				}
			}
			//close files
			file.close();
			newf.close();
			ifstream infile;
			infile.open("temp3.txt");
			ofstream outfile;
			outfile.open("Staff.txt", ios::trunc);
			//copy records from temp file back to staff file
			while (getline (infile, text)) {
			  outfile << text << endl;
			}
			// Close the files
			newf.close();
			outfile.close();
			//delete old file
			remove("temp3.txt");
			
			//check if employee was found and deleted
			if(flag==0){
				cout<<endl<<"Employee not found. Enter a valid employee ID."<<endl;
				sleep(1);
			}
			else{
				cout<<endl<<"EMPLOYEE "<<id<<" DELETED!"<<endl;
				totalWorkers--;
				cout<<"Press any key to go back";
				getch();	//holds screen
				system("cls");
			}
		}
		
		void addRoom(){
			string number, type, cost;
			cout<<"Enter room number: ";
			cin>>number;
			cout<<"Enter room type: ";
			cin>>type;
			cout<<"Enter cost per day: ";
			cin>>cost;
			Room::add_room();
			ofstream file;
			file.open("Rooms.txt",ios::app);
			file<<"Room"<<Room::get_noOfRooms()<<"|"<<"	 "<<number<<"	"<<type<<"		"<<"1"<<"         "<<cost<<"		"<<"-"<<endl;
			file.close();
			cout<<endl<<"ROOM ADDED!"<<endl<<"Press any key to go back"<<endl;
			getch();
			system("cls");
		}
		
		void deleteRoom(){
			string num; int flag=0;
			cout<<"Enter room number you want to delete: ";
			cin>>num;
			
			ifstream file;
			file.open("Rooms.txt");
    		string text, filename, a1,a2,a3,a4,a5;
  			// create new file to store room records 
 			ofstream newf("temp2.txt");
    
    		while (file>>text){
    			//read data from old file
   			 	file>>a1; file>>a2; file>>a3; file>>a4; file>>a5; 
				if(a1==num){
    				//skip this room
    				flag=1;
				}
				else{
					//read from old file and input in temporary file
					newf<<text<<"	 "<<a1<<"	"<<a2<<"		"<<a3<<"         "<<a4<<"		"<<a5<<endl;
				}
			}
			// Close the files
			newf.close();
			file.close();
			//rename temp file and delete old room file
			remove("Rooms.txt");
			rename("temp2.txt", "Rooms.txt");
			
			//check if room number was found and deleted
			if(flag==0){
				cout<<endl<<"Room not found. Enter a valid room number."<<endl;
				sleep(1);
			}
			else{
				cout<<endl<<"ROOM "<<num<<" DELETED!"<<endl;
				Room::del_room();
				cout<<"Press any key to go back";
				getch();	//holds screen
				system("cls");
			}
		}
		
		friend class Receptionist;
		//member functions to access the functions of friend class
		void viewRooms(){
			Receptionist r;	//make object of friend class to call its functions
			r.viewRooms();
		}
		void viewCustomers(){
			Receptionist r;	//make object of friend class to call its functions
			r.viewCustomers();
		}
};

void Receptionist::viewCustomers(){
	string text;
	// Read from the text file
	ifstream s("Customers.txt");
	cout<<"CUSTOMER     NAME     GENDER   DAYS STAYING	BILL   ROOM SERVICE ORDER    ROOM NUMBER"<<endl;
	// Use a while loop together with the getline() function to read the file line by line
	while (getline (s, text)) {
  		// Output the text from the file
  		cout << text << endl;
	}
	// Close the file
	s.close();
}

void Receptionist::viewRooms(){
	string text;
	// Read from the text file
	ifstream r("Rooms.txt");
	cout<<"ROOMS   NUMBER	TYPE	   AVAILABILITY	 COST PER DAY	CUSTOMER"<<endl;
	// Use a while loop together with the getline() function to read the file line by line
	while (getline (r, text)) {
	  // Output the text from the file
	  cout << text << endl;
	}
	// Close the file
	r.close();	
}

void Customer::checkIn(string t){
	fstream file;
    string word, text, filename, a1, a2, a3, a4, a5;

    // filename of the file
    filename = "Rooms.txt";
  
    // opening file
    file.open(filename.c_str());
    
    // extracting words from the file
    while (file >> word)
    {
        file>>a1; file>>a2; file>>a3; file>>a4; file>>a5;
		
        if(a2==t&&(a3=="1")){	//check if the room type matches the input and if the room is available
        	//assign room to customer if condition is fulfilled
			room.set_roomno(stoi(a1));
        	room.set_type(a2);
        	room.set_avail(false);
        	room.set_cost(stod(a4));
        	room.set_customername(name);
			set_bill();
			
			// create new file to store customer records 
 			ofstream newf("temp.txt");
			
			string text;
			// Read from old customer file
			ifstream oldf("Customers.txt");

			while (getline (oldf, text)) {
  			//write data from old file to new file
  				newf<<text<<endl; 
			}
			
			//input data of new customer into new customer file
			newf<<"Customer"<<noOfCustomers<<"|   "<<name<<"	"<<gender<<"	  "<<days_staying<<"	        "<<bill<<"	     "<<roomServiceOrders<<"	             "<<room.get_roomno();
			
			// Close the files
			newf.close();
 			oldf.close();
 			
 			//rename temp file and delete old customers file
 			remove("Customers.txt");
  			rename("temp.txt", "Customers.txt");
  			
   			file.close();
   			changeAvailability(false,word,name);	//change availability of the room booked
   			noOfCustomers++;
   			
  			cout<<endl<<"--ROOM BOOKED!--";
  			sleep(2);
  			system("cls");
			cout<<"Please remember your room details-"<<endl<<endl;
  			cout<<"Name: "<<name<<endl<<"Room Number: "<<room.get_roomno()<<endl<<"Days Staying: "<<days_staying<<endl;
  			cout<<endl<<"CHECK IN COMPLETE!"<<endl<<"Press any key to go back";
  			getch();	//holds the screen until any key is pressed
  			system("cls");
  			return;
		}
    }
    //goes back to input if no rooms satisfy the condition
    cout<<"No rooms available. Try a different type of room."<<endl;
    noOfCustomers--;
	sleep(2);
	system("cls");
	return;
}

inline void displayBill(string n,string d, string b,string o, string r){	//global function to display bill at checkout
	cout<<"---BILL---"<<endl;
	cout<<"Customer Name: "<<n;
	cout<<endl<<"Room Number: "<<r<<endl;
	cout<<"Days Stayed: "<<d<<endl;
	cout<<"Number of Room Service Orders: "<<o;
	cout<<endl<<"TOTAL BILL: Rs. "<<b<<endl;
	cout<<endl<<"Please pay at the counter."<<endl;
}


void checkOut(string n, int r){	//friend function of class Customer to check out of a room
	fstream file1;
    string text, filename, a1,a2,a3,a4,a5,a6;
    filename = "Customers.txt";
  	// create new file to store customer records 
 	ofstream newf("temp.txt");

    file1.open(filename.c_str());
    
    while (file1 >> text){
    	file1>>a1; file1>>a2; file1>>a3; file1>>a4; file1>>a5; file1>>a6;
		if(a1==n&&stoi(a6)==r){	//checks the room number for the customer who is checking out
			string t="Room"+a6+"|";
    		changeAvailability(true,t,"-");	//change availability of the room freed
			sleep(1);
			system("cls");
			displayBill(a1,a3,a4,a5,a6);
		}
		else{
			//inputs info of other customers into new file
			newf<<text<<"   "<<a1<<"	"<<a2<<"	  "<<a3<<"	        "<<a4<<"	     "<<a5<<"	             "<<a6<<endl;
		}
	}
	// Close the files
	newf.close();
	file1.close();
	//rename temp file and delete old customers file
	remove("Customers.txt");
	rename("temp.txt", "Customers.txt");

	cout<<endl<<"CHECK OUT COMPLETE!"<<endl;
	Customer::noOfCustomers--;
	cout<<"Press any key to go back";
	getch();	//holds screen
	system("cls");
}

void Customer::orderRoomService(){
	int check;
	while(1){
		cout<<endl<<"Choose type of room service: "<<endl<<"1. Room Cleaning\tRs.5000"<<endl;
		cout<<"2. Food Delivery\tRs.2000"<<endl;
		cin>>check;
		if(check==1){
			bill+=5000;
			roomServiceOrders++;
			cout<<endl<<"Room Cleaning Order Successful"<<endl<<"Press 1 if you would like to place another order"<<endl;
			cin>>check;
			if(check==1){
				system("cls");
			}
			else{
				break;
			}
		}
		else if(check==2){
			bill+=2000;
			roomServiceOrders++;
			cout<<endl<<"Food Delivery Order Successful. Press 1 if you would like to place another order"<<endl;
			cin>>check;
			if(check==1){
				system("cls");
			}
			else{
				break;
			}
		}
		else{
			cout<<"Invalid input, try again.";
			system("cls");
		}	
	}
	fstream file1;
    string text, filename, a1,a2,a3,a4,a5,a6;
    filename = "Customers.txt";
  	// create new file to store customer records 
 	ofstream newf("temp.txt");

    file1.open(filename.c_str());
    
    while (file1 >> text){
    	file1>>a1; file1>>a2; file1>>a3; file1>>a4; file1>>a5; file1>>a6;
		if(a1==name&&stoi(a3)==days_staying){	//checks the name and days staying for the customer who ordered room service
			newf<<text<<"   "<<a1<<"	"<<a2<<"	  "<<a3<<"	        "<<bill<<"	     "<<roomServiceOrders<<"	             "<<a6<<endl;
			
		}
		else{
			//inputs info of other customers into new file
			newf<<text<<"   "<<a1<<"	"<<a2<<"	  "<<a3<<"	        "<<a4<<"	     "<<a5<<"	             "<<a6<<endl;
		}
	}
	// Close the files
	newf.close();
	file1.close();
	//rename temp file and delete old customers file
	remove("Customers.txt");
	rename("temp.txt", "Customers.txt");
}

void changeAvailability(bool av,string check,string name){	//global function to change availability of a room
	fstream file;
    string text, filename, a1,a2,a3,a4,a5;
    filename = "Rooms.txt";
  	// create new file to store room records 
 	ofstream newf("temp2.txt");

    file.open(filename.c_str());
    
    while (file >> text){
    	//input data of new customer into new room file
		if(text==check){
    		newf<<text;
			file>>a1; file>>a2; file>>a3; file>>a4; file>>a5;
			if(av==true){	
				//for checking out
				newf<<"	 "<<a1<<"	"<<a2<<"		"<<"1"<<"         "<<a4<<"		"<<name<<endl;
			}
			else{
				//for checking in
				newf<<"	 "<<a1<<"	"<<a2<<"		"<<"0"<<"         "<<a4<<"		"<<name<<endl;	
			}
		}
		else{
			//read from old file and input in temporary file
			newf<<text;
			file>>a1; file>>a2; file>>a3; file>>a4; file>>a5;
			newf<<"	 "<<a1<<"	"<<a2<<"		"<<a3<<"         "<<a4<<"		"<<a5<<endl;
		}
	}
	// Close the files
	newf.close();
	file.close();
	//rename temp file and delete old room file
	remove("Rooms.txt");
	rename("temp2.txt", "Rooms.txt");
}

Customer validation(string n, int r){
	fstream file1;
    string text, filename, a1,a2,a3,a4,a5,a6;
    filename = "Customers.txt";

    file1.open(filename.c_str());
    
    while (file1 >> text){
    	file1>>a1; file1>>a2; file1>>a3; file1>>a4; file1>>a5; file1>>a6;
		if(a1==n&&stoi(a6)==r){	//checks the name and room number to find matching customer
			Customer c(a1,a2[0],stoi(a3),stoi(a5),stod(a4));
			file1.close();
			return c;
		}
	}
}

bool boolvalidation(string n, int r){
	fstream file1;
    string text, filename, a1,a2,a3,a4,a5,a6;
    filename = "Customers.txt";

    file1.open(filename.c_str());
    
    while (file1 >> text){
    	file1>>a1; file1>>a2; file1>>a3; file1>>a4; file1>>a5; file1>>a6;
		if(a1==n&&stoi(a6)==r){	//checks the name and room number to find matching customer
			return 1;
		}
	}
	cout<<"Customer does not exist in our records. Please try again."<<endl;
	// Close the file
	file1.close();
	return 0;
}

int main()
{
	string n, text, a1,a2,a3,a4,a5,name,rms[5]={"Single","Double","Queen","King","Suite"},prices[5]={"Rs.5000","Rs.7000","Rs.12,000","\tRs.15,000","Rs.20,000"}; 
	char g; int check,a,num,id,d,c=0, i=0, flag=0; char password[5];
	ifstream file;
    file.open("Staff.txt");
    //make array of objects based on total number of workers
    Staff obj[100]; Staff o; Receptionist *rec=(Receptionist*)(&o); Manager man;
    //inputs data of staff from file to object array
    for(int i=0;i<Staff::get_totalworkers();i++){
    	file>>text; file>>a1; file>>a2; file>>a3; file>>a4; file>>a5;
    	obj[i].set_employeeID(stoi(a1));
    	obj[i].set_name(a2);
    	obj[i].set_position(a3);
    	obj[i].set_hiredate(a4);
    	obj[i].set_hoursworked(stoi(a5));
	}
	cout<<endl<<endl<<"\t\t\t\t\t\tWELCOME TO OUR HOTEL!"<<endl<<endl;
	sleep(3);
	system("cls");
Home:
	cout<<"\t\t\t\t-----Hotel Management System-----"<<endl<<endl;
	cout<<"\t\t\t\tPress 1 if you are a customer"<<endl<<"\t\t\t\tPress 2 if you are an employee"<<endl;
	cin>>check;
	if(check==1){
		system("cls");
		goto CustView;
	}
	else if(check==2){
		system("cls");
		while(1){
			cout<<"\t\t\t\t\t-----EMPLOYEE LOGIN-----"<<endl<<endl<<"\t\t\t\tEnter password: ";
			while(1){				//Makes * appear instead of characters of password
			password[i]=getch();
			if(password[i]=='\r'){
				break;
			}
			else{
				printf("*");
			}
			i++;
			}
			i=0;
			//only redirects to staff view if password 'admin' is entered
			if(password[0]=='a'&&password[1]=='d'&&password[2]=='m'&&password[3]=='i'&&password[4]=='n'){
				system("cls");
				goto StaffView;	}
			else{
				cout<<endl<<"\t\t\t\tIncorrect password. Try again.";
				sleep(1);
				system("cls");	}
		}
	}
	else{
		cout<<"\t\t\t\tInvalid input. Try again.";
		sleep(1);
		system("cls");
		goto Home;
	}
CustView:
	cout<<"-----Customer View-----"<<endl<<endl;
	cout<<"1. Check in to a room"<<endl<<"2. Check out of a room"<<endl<<"3. Order Room Service"<<endl<<"4. Go back"<<endl<<"5. Exit"<<endl<<endl<<"Enter choice: ";
	cin>>check;
	if(check==1){
		sleep(1);
		system("cls");
		goto Booking;
	}
	else if(check==2){
		sleep(1);
		system("cls");
		goto CheckOut;
	}
	else if(check==3){
		sleep(1);
		system("cls");
		cout<<"-----ORDER ROOM SERVICE-----"<<endl;
		cout<<endl<<"Enter your name: ";
		cin>>n;
		cout<<endl<<"Enter your room number: ";
		cin>>d;
		{
			if(boolvalidation(n,d)){
				Customer c(validation(n,d));
				c.orderRoomService();
			}
			sleep(1);
			system("cls");
			goto CustView;
		}
	}
	else if(check==4){
		sleep(1);
		system("cls");
		goto Home;
	}
	else if(check==5){
		sleep(1);
		system("cls");
		goto Exit;
	}
	else{
		cout<<"Invalid input. Try again.";
		sleep(2);
		system("cls");
		goto CustView;
	}
Booking:
	//take input for customer details
	cout<<"-----CHECK IN-----"<<endl;
	cout<<endl<<"Enter your name: ";
	cin>>n;
	cout<<endl<<"Enter your gender: ";
	cin>>g;
	cout<<endl<<"TYPES OF ROOMS IN THE HOTEL AND THEIR COST PER DAY-"<<endl;
	for(int i=0;i<5;i++)
		cout<<i+1<<". "<<rms[i]<<"\t\t"<<prices[i]<<endl;
	while(1){
		//validity check to make sure a valid room type is selected
		cout<<endl<<"Enter the number for the type of room you want: ";
		cin>>c;
		if(c==1||c==2||c==3||c==4||c==4||c==5){
			break;
		}
		else{
			cout<<"Invalid input."<<endl;
		}
	}
	cout<<endl<<"Enter number of days you will be staying: ";
	cin>>d;
	//checkIn function called to book a room
	{Customer c1(n, g, d);
	c1.checkIn(rms[c-1]);
	c=0;}
	goto CustView;
CheckOut:
	//take input for customer details
	cout<<"-----CHECK OUT-----"<<endl;
	cout<<endl<<"Enter your name: ";
	cin>>n;
	cout<<endl<<"Enter your room number: ";
	cin>>d;
	if(boolvalidation(n,d)){
		checkOut(n,d);
	}
	sleep(1);
	system("cls");
	goto CustView;
StaffView:
	cout<<endl<<"\t\t\t\tPress 1 if you are a receptionist"<<endl<<"\t\t\t\tPress 2 if you are a manager"<<endl<<"\t\t\t\tPress 3 to go back"<<endl;
	cin>>a;
	if(a==1){
		system("cls");
		goto ReceptionistView;
	}
	else if(a==2){
		system("cls");
		goto ManagerView;
	}
	else if(a==3){
		system("cls");
		goto Home;
	}
	else{
		cout<<"Invalid input. Try again.";
		sleep(1);
		goto StaffView;
	}	

ReceptionistView:
	cout<<"-----Receptionist View-----"<<endl<<endl;
	cout<<"1. Display Employee Details"<<endl<<"2. Add Hours Worked"<<endl<<"3. View Rooms"<<endl<<"4. View Customers";
	cout<<endl<<"5. Go back"<<endl<<"6. Exit"<<endl<<endl<<"Enter choice: ";
	cin>>check;
	sleep(1);
	system("cls");
	if(check==1){
		cout<<endl<<"Enter your employee ID: ";
		cin>>id;
		for(int i=0;i<Staff::get_totalworkers();i++){
			if(obj[i]==id){	//check which object satisfies condition and call its display
				obj[i].display();
				break;
			}
		}
		cout<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ReceptionistView;
	}
	else if(check==2){
		cout<<"Adding Hours Worked"<<endl<<endl<<"Enter your employee ID: ";
		cin>>id;
		cout<<"1. Add today's shift"<<endl<<"2. Add more hours"<<endl;
		while(flag==0){
			cin>>check;
			if(check==1){
				flag=1;
				for(int i=0;i<Staff::get_totalworkers();i++){
					if(obj[i]==id){	//check which object satisfies condition and add hours to it
						obj[i].addHours();
						cout<<"Shift added.";
						break;
					}
				}
			}
			else if(check==2){
				flag=1;
				cout<<endl<<"How many hours do you want to add? ";
				cin>>num;
				for(int i=0;i<Staff::get_totalworkers();i++){
					if(obj[i]==id){	//check which object satisfies condition and add hours to it
						obj[i].addHours(num);
						cout<<"Hours added.";
						break;
					}
				}
			}
			else{
				cout<<"Invalid input. Try again."<<endl;
			}
		}
		flag=0;
		sleep(1);
		system("cls");
		goto ReceptionistView;	
	}
	else if(check==3){
		cout<<"-----Display Rooms-----"<<endl<<endl;	
		rec->viewRooms();
		cout<<endl<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ReceptionistView;
	}
	else if(check==4){
		cout<<"-----Display Customers-----"<<endl<<endl;	
		rec->viewCustomers();
		cout<<endl<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ReceptionistView;
	}
	else if(check==5){
		goto StaffView;
	}
	else if(check==6){
		goto Exit;
	}
	else{
		cout<<"Invalid input. Try again";
			sleep(1);
			system("cls");
			goto ReceptionistView;
	}

ManagerView:
	cout<<"-----Manager View-----"<<endl<<endl;
	cout<<"1. Display Employee Details"<<endl<<"2. Add Hours Worked"<<endl<<"3. View Rooms"<<endl<<"4. View Customers";
	cout<<endl<<"5. View Staff"<<endl<<"6. Add Room"<<endl<<"7. Delete Room"<<endl<<"8. Add Employee"<<endl<<"9. Fire Employee";
	cout<<endl<<"10. Go back"<<endl<<"11. Exit"<<endl<<"Enter choice: ";
	cin>>check;
	sleep(1);
	system("cls");
	if(check==1){
		cout<<endl<<"Enter name of employee you want to view: ";
		cin>>name;
		for(int i=0;i<Staff::get_totalworkers();i++){
			if(obj[i]==name){	//check which object satisfies condition and call its display
				obj[i].display();
				break;
			}
		}
		cout<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ManagerView;
	}
	else if(check==2){
		cout<<"Adding Hours Worked"<<endl<<endl<<"Enter name of employee you want to add hours to: ";
		cin>>name;
		cout<<"1. Add today's shift"<<endl<<"2. Add more hours"<<endl;
		while(flag==0){
			cin>>check;
			if(check==1){
				flag=1;
				for(int i=0;i<Staff::get_totalworkers();i++){
					if(obj[i]==name){	//check which object satisfies condition and add hours to it
						obj[i].addHours();
						cout<<"Shift added.";
						break;
						}
					}
			}
			else if(check==2){
				flag=1;
				cout<<endl<<"How many hours do you want to add? ";
				cin>>num;
				for(int i=0;i<Staff::get_totalworkers();i++){
					if(obj[i]==name){	//check which object satisfies condition and add hours to it
						obj[i].addHours(num);
						cout<<"Hours added.";
						break;
					}
				}
			}
			else{
				cout<<"Invalid input. Try again."<<endl;
			}
		}
		flag=0;
		sleep(1);
		system("cls");
		goto ManagerView;
	}
	else if(check==3){
		cout<<"-----Display Rooms-----"<<endl<<endl;	
		man.viewRooms();
		cout<<endl<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ManagerView;
	}
	else if(check==4){
		cout<<"-----Display Customers-----"<<endl<<endl;	
		man.viewCustomers();
		cout<<endl<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ManagerView;
	}
	else if(check==5){
		cout<<"-----Display Employees-----"<<endl<<endl;	
		man.viewStaff();
		cout<<endl<<"Press any key to go back"<<endl;
		getch();
		system("cls");
		goto ManagerView;
	}
	else if(check==6){
		cout<<"-----Adding Room-----"<<endl<<endl;	
		man.addRoom();
		goto ManagerView;
	}
	else if(check==7){
		cout<<"-----Deleting Room-----"<<endl<<endl;	
		man.deleteRoom();
		goto ManagerView;
	}
	else if(check==8){
		cout<<"-----Adding Employee-----"<<endl<<endl;	
		man.addStaff(obj[Staff::get_totalworkers()]);
		goto ManagerView;
	}			
	else if(check==9){
		cout<<"-----Firing Employee-----"<<endl<<endl;	
		man.deleteStaff();
		goto ManagerView;
	}
	else if(check==10){
		goto StaffView;
	}
	else if(check==11){
		goto Exit;
	}
	else{
		cout<<"Invalid input. Try again";
		sleep(1);
		system("cls");
		goto ManagerView;
	}
Exit:
	cout<<endl<<endl<<"\t\t\t\t\tTHANK YOU FOR STAYING WITH US!"<<endl<<endl;
}

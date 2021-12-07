/*                         PROBLEM STATEMENT

Develop  a  program  in  C++  to  create  a  database  of  student’s information system
containing the following information: Name, Roll  number,  Class,  Division,  Date  of  Birth,
Blood  group, Contact  address,  Telephone  number,  Driving  license  no.  and other.
Construct the database with suitable member functions. Make use of constructor, default constructor,
copy constructor, destructor,  static  member  functions,  friend  class,  this  pointer, inline code
and  dynamic  memory  allocation  operators-new  and delete as well as exception handling.

*/

#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <sstream>
#include <ctype.h>
using namespace std;

class student			//creating class
{
	string *name, *addr, *year, *dob, *bg, *drilic, *phone;		//declaring pointers to variables
	int *div;
	long int *roll;
public:
	static int count;		//declaring static variable to keep count of the records
	student()				//default constructor
	{
		name=new string;	//using new operator to allocate memory
		addr=new string;
		year=new string;
		dob=new string;
		bg=new string;
		drilic=new string;
		div=new int;
		roll=new long int;
		phone=new string;
	}

	student(student &obj)	//copy constructor
	{
		this->name=obj.name;	//using this operator.The this pointer is an implicit parameter to all member functions. Therefore,
		this->addr=obj.addr;	//inside a member function, this may be used to refer to the invoking object.
		this->year=obj.addr;
		this->dob=obj.dob;
		this->bg=obj.bg;
		this->drilic=obj.drilic;
		this->div=obj.div;
		this->roll=obj.roll;
		this->phone=obj.phone;
	}

	~student()			//destructor
	{
		delete name;	//using delete operator to deallocate the memory
		delete addr;
		delete year;
		delete dob;
		delete bg;
		delete drilic;
		delete div;
		delete roll;
		delete phone;
	}

	static void showcount()		//static function to display the number of records
	{
		cout<<"\nTotal number of records are:"<<count<<endl;
	}

	 void getdata();	//function to accept data
	 void dispdata();	//function to display data
	 friend void update(student &obj);		//friend function for updating data
	 friend void update_roll(student &obj);	//friend function for updation of only roll no.
};

inline void student::getdata()	//defining inline function to get data.Inline function is a function that is expanded in line when
{								//it is called. When the inline function is called whole code of the inline function gets inserted
	string temp;				//or substituted at the point of inline function call.
	cout<<"Enter name:";
	while(true)
	{
		try						//Exception handling for name
	    {
	    	string temp;
	        getline(cin, temp);
	        for (char i : temp)
	        {
	        	if (!(isalpha(i) || isblank(i)))
	            {
	        		throw "Name can only contain alphabets!! Please enter again:";
	                break;
	            }
	        }
	        *name = temp;
	        break;
	    }
	    catch (const char *msg)
	    {
	    	cout << msg;
	    }
	}
	cout<<"Enter class(FE,SE,TE,BE):";
	while(true)									//Exception handling for class
	{
		cin>>temp;
		if (temp=="FE"|| temp=="Fe" || temp=="fe" || temp=="SE" || temp=="Se" || temp=="se" || temp=="TE" || temp=="Te" || temp=="te" || temp=="BE" || temp=="Be" || temp=="be")
		{
			*year=temp;
			break;
		}
		else
		{
			cout<<"There is no such class!! Please enter again:";
		}
	}
	cout<<"Enter division:";
	while(true)						//Exception handling for division
	{
		if(cin>>*this->div)
		{
    		if(*this->div>=1 and *this->div<=11)
    		{
    			break;
    		}
    		else
    		{
    		     cout<<"There are only 11 divisions!! Please enter again:";
    		     continue;
    		}
		}
		else
		{
			cout<<"Invalid division!! Please enter again:";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	long int a;
	cout<<"Enter Roll no:";
	while(true)					//Exception handling for roll no.
	{
		if(cin >> a)
		{
		    *roll = a;
			break;
		}
		else
		{
			cout << "Invalid Roll no number!! Please enter again:";
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		}
	}
	cout<<"Enter address:";
	cin.ignore();
	getline(cin, temp);
	*addr=temp;
	time_t ttime = time(nullptr);			//to find local time
	tm *local_time = localtime(&ttime);
	int year = 1900 + local_time->tm_year;
	int month = 1 + local_time->tm_mon;
	int day = local_time->tm_mday;
	string todayDate = to_string(day) + '/' + to_string(month) + '/' + to_string(year);
	while (true)							//Exception handling for date of birth
    {
        try
        {
            cout << "Enter your birthday (dd/mm/yyyy): ";
            cin >> temp;
            int dayInt;
            int monthInt;
            int yearInt;
            if (temp[2] != '/' || temp[5] != '/' || temp.length()!=10)
            {
                throw "Invalid birthdate format";
            }
            stringstream dayStream, monthStream, yearStream;
            dayStream << temp.substr(0, 2);
            dayStream >> dayInt;
            monthStream << temp.substr(3, 2);
            monthStream >> monthInt;
            yearStream << temp.substr(6, 4);
            yearStream >> yearInt;
            if (temp[2] != '/' || temp[5] != '/')
            {
                throw "Invalid birthdate format";
            }
            else if(yearInt==00 && monthInt==00 && dayInt==00){
				throw "Invalid birthdate format";
			}
            else if (yearInt > year)
            {
                throw "You cannot be born in the future!";
            }
            else if (yearInt == year && monthInt > month)
            {
                throw "You cannot be born in the future!";
            }
            else if (monthInt == month && dayInt > day && yearInt == year)
            {
                throw "You cannot be born in the future!";
            }
            *dob = temp;
            break;
        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }
    }
	while (true)				//Exception handling for blood group
	{
	    cout << "Enter blood group(Eg:AB-,O+):";
	    try
	    {
	        cin >> *this->bg;
	        if (*this->bg == "A+" || *this->bg == "A-" || *this->bg == "B+" || *this->bg == "B-" || *this->bg == "AB+" || *this->bg == "AB+" || *this->bg == "O+" || *this->bg == "O-")
	        {
	            break;
	        }
	        else
	        {
	            throw "Blood group is not valid\n";
	        }
	    }
	    catch (const char *msg)
	    {
	        cout << msg;
	    }
	}
	cout<<"Enter driving license:";
	cin>>*drilic;
	while (true)		//Exception handling for phone number
	{
		cout << "Enter your phone number:";
	    try
	    {
	    	string temp;
	        cin >> temp;
	        if (temp.length() != 10)
	        {
	        	throw "Phone number must be 10 characters long\n";
	        }
	        for (char i : temp)
	        {
	        	if (!isdigit(i))
	            {
	        		throw "Phone no must be a digit\n";
	                break;
	            }
	        }
	        *phone = temp;
	        break;
	    }
	    catch (const char *msg)
	    {
	    	cout << msg;
	    }
	}
	cin.ignore();
}

inline void student::dispdata()		//Defining inline function to display data
{
	cout<<"********************************************************"<<endl;
	cout<<"Name:"<<*name<<endl;
	cout<<"Address:"<<*addr<<endl;
	cout<<"Class:"<<*year<<endl;
	cout<<"Division:"<<*div<<endl;
	cout<<"Roll No:"<<*roll<<endl;
	cout<<"Date of birth:"<<*dob<<endl;
	cout<<"Blood Group:"<<*bg<<endl;
	cout<<"Driving license number:"<<*drilic<<endl;
	cout<<"Phone number:"<<*phone<<endl;
	cout<<"********************************************************"<<endl;
}

void update(student &obj)		//Defining friend function for updating data
{
    string temp;
    int a;
    long int b;
    cout<<"Update name (previous name:"<<*obj.name<<") for previous press -1:"<<endl;
    cin.ignore();
    getline(cin, temp);
    if(temp!="-1")
    {
        *obj.name = temp;
    }
    cout<<"Update address (previous address:"<<*obj.addr<<") for previous press -1:"<<endl;
    getline(cin, temp);
    if(temp!="-1")
    {
        *obj.addr = temp;
    }
    cout<<"Update class (previous class:"<<*obj.year<<") for previous press -1:"<<endl;
    cin>>temp;
    cin.ignore();
    if(temp!="-1")
    {
        *obj.year = temp;
    }
    cout<<"Update division (previous division:"<<*obj.div<<") for previous press -1:"<<endl;
    cin>>a;
    cin.ignore();
    if(a!=-1)
    {
        *obj.div = a;
    }
    cout<<"Update roll no (previous roll no:"<<*obj.roll<<") for previous press -1:"<<endl;
    cin>>b;
    cin.ignore();
    if(b!=-1)
    {
        *obj.roll = b;
    }
    cout<<"Update date of birth (previous date of birth:"<<*obj.dob<<") for previous press -1:"<<endl;
    getline(cin, temp);
    if(temp!="-1")
    {
        *obj.dob = temp;
    }
    cout<<"Update blood group (previous blood group:"<<*obj.bg<<") for previous press -1:"<<endl;
    getline(cin, temp);
    if(temp!="-1")
    {
        *obj.bg = temp;
    }
    cout<<"Update driving license number (previous driving license number:"<<*obj.drilic<<") for previous press -1:"<<endl;
    getline(cin, temp);
    if(temp!="-1")
    {
        *obj.drilic = temp;
    }
    cout<<"Update phone number (previous number:"<<*obj.phone<<") for previous press -1:"<<endl;
    getline(cin, temp);
    if(temp!="-1")
    {
        *obj.phone = temp;
    }
}

void update_roll(student &obj)		//Defining friend function for updating only roll no
{
    long int b;
    cout<<"Update roll no:";
    cin>>b;
    *obj.roll = b;
}

int student::count;		//Initialize static variable
int main()				//Main program
{
	student stud[100];	//Creating array of objects
	int n=0, choice, pos, a, b;
	while(true)			//Menu driven Program
	{
	    cout<<"***********Main Menu***********"<<endl;
	    cout<<"1.Create record"<<endl;
	    cout<<"2.Delete record"<<endl;
	    cout<<"3.Copy record"<<endl;
	    cout<<"4.Display record"<<endl;
	    cout<<"5.Update record"<<endl;
	    cout<<"6.Exit"<<endl;
	    cout<<"Enter the number corresponding to the operation that you want to perform";
	    cin>>choice;
	    cin.ignore();
	    if(choice==1)		//For accepting data from user
	    {
	        cout<<"********************************************************"<<endl;
	        n++;
	        stud[n].getdata();
	        student::count++;
	        cout<<"********************************************************"<<endl;
	        student::showcount();
	        cout<<"********************************************************"<<endl;
	    }
	    else if(choice==2)		//For deleting data
	    {
	        cout<<"Press 1 to delete a particular record or 2 delete all records!!";
	        while(true)
	        {
	            cin>>a;
	            if(a==1)
	            {
	                cout<<"Which record do you want to delete?";
	                while(true)
	                {
	                    cin>>pos;
	                    if(pos>=1 and pos<=n)
	                    {
	                        cout<<"Press 1 to confirm!!";		//taking confirmation
	                        cin>>b;
	                        if(b==1)
	                        {
	                            stud[pos].~student();//DESTRUCTOR CALLED HERE
	                            cout<<"Record deleted successfully!!!"<<endl;
	                            student::count--;
	                            for(int i=pos; i<=n-1; i++)
	                            {
	                            	stud[i] = stud[i+1];
	                            }
	                            cout<<"********************************************************"<<endl;
	                            student::showcount();
	                            cout<<"********************************************************"<<endl;
	                            n--;
	                        }
	                        break;
	                    }
	                    else
	                    {
	                        cout<<"Record does not exist!! Please enter again:"<<endl;
	                    }
	                }
	                break;
	            }
	            else if(a==2)
	            {
	                cout<<"Press 1 to confirm!!";		//Taking confirmation
	                cin>>b;
	                if(b==1)
	                {
	                    for(int i=1; i<=n; i++)
	                    {
	                        stud[i].~student();
	                    }
	                    cout<<"Records deleted successfully"<<endl;
	                    student::count = 0;
	                    n=0;
	                    student::showcount();
	                }
	                break;
	            }
	            else
	            {
	                cout<<"Please enter either 1 or 2:"<<endl;
	            }
	        }
	    }

	    else if(choice==3)		//To copy record form a position
	    {
	        cout<<"Enter the position from which you want to copy record:";
	        while(true)
	        {
	            cin>>pos;
	            if(pos>=1 and pos<=n)
	            {
	            	n++;
	            	stud[n] = stud[pos];//COPY CONSTRUCTOR CALLED HERE
	            	update_roll(stud[n]);
	            	student::count++;
	                cout<<"Record copied successfully!!"<<endl;
	                break;
	            }
	            else
	            {
	                cout<<"There is no record at this position!!Please enter again:";
	            }
	        }
	        student::showcount();
	    }

	    else if(choice==4)		//for diplaying record
	    {
	        cout<<"Press 1 to display a particular record or 2 to display all records";
	        while(true)
	        {
	            cin>>a;
	            if(a==1)
	            {
	                cout<<"Enter the position of record which you want to display:";
	                cin>>pos;
	                if(pos>=1 and pos<=n)
	                {
	                    stud[pos].dispdata();
	                    break;
	                }
	                else
	                {
	                	cout<<"There is no record at this position!!Please enter again:";
	                }
	            }
	            else if(a==2)
	            {
	                for(int i=1; i<=n; i++)
	                {
	                    stud[i].dispdata();
	                }
	                break;
	            }
	            else
	            {
	                cout<<"Please enter either 1 or 2!!";
	            }
	        }
	        student::showcount();
	    }

	    else if(choice==5)		//For updating record
	    {
	    	cout<<"Enter the position of the record that you want to update";
	    	while(true)
	    	{
	    		cin>>pos;
	    		if(pos>=1 and pos<=n)
	    		{
	    			update(stud[pos]);
	    			cout<<"Record updated successfully!"<<endl;
	    			break;
	    		}
	    		else
	    		{
	    			cout<<"There is no record at this position! Please enter again:";
	    		}
	    	}
	    }

	    else if(choice==6)		//To exit from the program
	    {
	        cout<<"Thank You!!!";
	        break;
	    }
	}
	return 0;
}

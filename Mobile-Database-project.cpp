#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include <time.h> 
#include<math.h>
#include<string.h>
using namespace std;
int counter = 0;//counting the number of users
class wifi//an abstract class for user
{
public:
	char _wifi;
	wifi()
	{
		_wifi = 'n';
	}

};
class intl//an abstract class for user
{
public:
	char _intl;
	intl()
	{
		_intl = 'n';
	}

};
class user :public wifi, public intl// the main class with all the members
{
	char name[20], sex[5], location[20];//private data
	int age;
public:
	char* getname()//member function to access data
	{
		return(name);
	}
	char* getgender()
	{
		return(sex);
	}
	char* getlocation()
	{
		return(location);
	}
	int getage()
	{
		return(age);
	}

	void new_user()// creates a new user
	{
		balance = 80;
		srand(time(NULL));//generates random time seed so values are not repeted
		phone_num = rand() % 10;
		std::cout << "\NEW DATA ENTRY CREATED" << "\n";
		std::cout << "\nEnter name";
		std::cin >> name;
		std::cout << "\nEnter gender(m/f)";
		std::cin >> sex;
		std::cout << "\nEnter location";
		std::cin >> location;
		cout << "\n EXECUTED SUCCESSFULLY....writing to system...\n";
		for(int i = 0; i < 32; i++)
			cout << "-";
		cout << "\n RECHECKING INFO...";
		show_data();
		

	}
	void show_data()//displays all the data
	{
		
		std::cout << "\n" << balance << "\n" << name << "\n" << sex << "\n" << location;
		std::cout << "\nyour number is" << phone_num << "\n";
		for (int i = 0; i < 32; i++)
			cout << "-";
		
	}
	void get_wifi()// subscribes users to wifi after checking their balance
	{
		std::cout << "\n wifi will cost 50/- (Y/N)";
		char temp;
		std::cin >> temp;
		if (temp == 'y')
		{
			if (balance >= 50)
			{
				balance -= 50;
				_wifi = 'y';
				cout << "\nEXECUTION SUCCESSFULL\n";

				for (int i = 0; i < 32; i++)
					cout << "-";
			}
			else
			{
				std::cout << "\n insufficent funds";
			}

		}

	}
	void get_intl()// subscribes users to international service after checking their balance
	{
		std::cout << "\n INTERNATIONAL will cost 80/- (Y/N)";
		char temp;
		std::cin >> temp;
		if (temp == 'y')
		{
			if (balance >= 80)
			{
				balance -= 80;
				_intl = 'y';
				cout << "\nEXECUTION SUCCESSFULL\n";
				for (int i = 0; i < 32; i++)
					cout << "-";
			}
			else
			{
				std::cout << "\n insufficent funds";
			}

		}

	}
	void recharge()// recharges balance
	{
		std::cout << "\n enter the amount";
		int amt;
		cin >> amt;
		balance += amt;
		std::cout << "\n successfully completed the procress";
		show_data();
	}
	int balance;
	int phone_num;
};
void new_user()
{
	fstream fphone;
	fphone.open("phone.dat", ios::out | ios::app);
	user x;
	x.new_user();
	fphone.seekp(fphone.eof());
	fphone.write((char*)&x, sizeof(x));
	std::cout << "\ndone";
	fphone.close();

}// creates new user if already created appends
void get_wifi()
{
	fstream fphone;
	fphone.open("phone.dat", ios::in | ios::out);
	std::cout << "\nenter your phone number";
	int p;
	int flag = 1, i = 0;
	user s;
	cin >> p;
	while (fphone.read((char*)&s, sizeof(s)))
	{
		i++;
		if (s.phone_num == p)
		{
			flag = 0;
			s.get_wifi();
			fphone.seekp(i*(sizeof(s)), ios::beg);
			fphone.write((char*)&s, sizeof(s));
			break;

		}
		

	}
	if(flag==1)
	{
		cout << "\n number not found";
		
	}
	cout << "\n returing to main menu....";
	system("pause");
	fphone.close();
}//class the member function get_wifi
void get_intl()//class the member function get_intl
{
	fstream fphone;
	fphone.open("phone.dat", ios::in | ios::out);
	std::cout << "\nenter your phone number";
	int p;
	int flag = 1, i = 0;
	user s;
	cin >> p;
	while (fphone.read((char*)&s, sizeof(s)))
	{
		i++;
		if (s.phone_num == p)
		{
			flag = 0;
			s.get_intl();
			fphone.seekp(i*(sizeof(s)), ios::beg);
			fphone.write((char*)&s, sizeof(s));
			break;

		}
		

	}
	if (flag == 1)
	{
		cout << "\n number not found";
		
	}
	cout << "\n returing to main menu....";
	system("pause");
	fphone.close();
	cout << "\nWRITING TO SYSTEM SUCCESSFULL... REDIRECTING";
}
void recharge()// calls recharge
{
	fstream fphone;
	fphone.open("phone.dat", ios::in | ios::out);
	cout << "\nenter your phone number";
	int p;
	int flag = 1, i = 0;
	user s;
	cin >> p;
	while (fphone.read((char*)&s, sizeof(s)))
	{
		i++;
		if (s.phone_num == p)
		{
			flag = 0;
			s.recharge();
			fphone.seekp(i*(sizeof(s)), ios::beg);

			fphone.write((char*)&s, sizeof(s));
			break;

		}
	}
		if (flag == 1)
		{
			cout << "\n number not found";

		}
		cout << "\n returing to main menu....";
		system("pause");		

	
	fphone.close();
}
void all_user()
{
	user s;
	fstream fphone;
	fphone.open("phone.dat", ios::in);
	while (fphone.read((char*)&s, sizeof(s)))
		s.show_data();
	fphone.close();

}// displays all users
void sort_user_by_bal()
{
	user u[30], temp;
	fstream fstud("phone.dat", ios::in);
	int i = 0, n = 0;
	while (fstud.read((char*)&u[i++], sizeof(user)))
		n = i;
	for (i = 1; i < n; i++)
	{
		if (u[i - 1].balance> u[i].balance)
		{
			temp = u[i];
			u[i] = u[i - 1];
			u[i - 1] = temp;
		}

	}
	fstud.close();
	fstud.open("phone.dat", ios::out);
	for (i = 0; i < n; i++)
	{
		fstud.write((char*)&u[i], sizeof(user));
	}

}//uses bubble sort to sort all the users by balance
void sort_user_by_name()
{
	user u[30], temp;
	fstream fstud("phone.dat", ios::in);
	int i = 0, n;
	while (fstud.read((char*)&u[i++], sizeof(user)))
		n = i;
	for (i = 1; i < n; i++)
	{
		if (_strcmpi(u[i - 1].getname(), u[i].getname())>0)
		{
			temp = u[i];
			u[i] = u[i - 1];
			u[i - 1] = temp;
		}
		
	}
	fstud.close();
	fstud.open("phone.dat", ios::out);
	for (i = 0; i < n; i++)
	{
		fstud.write((char*)&u[i], sizeof(user));
	}
	

} // uses bubble sort to sort all the users by name
void sort_user_by_location()
{
	user u[30], temp;
	fstream fstud("phone.dat", ios::in);
	int i = 0, n;
	while (fstud.read((char*)&u[i++], sizeof(user)))
		n = i;
	for (i = 1; i < n; i++)
	{
		if (_strcmpi(u[i - 1].getlocation(), u[i].getlocation())>0)
		{
			temp = u[i];
			u[i] = u[i - 1];
			u[i - 1] = temp;
		}

	}
	fstud.close();
	fstud.open("phone.dat", ios::out);
	for (i = 0; i < n; i++)
	{
		fstud.write((char*)&u[i], sizeof(user));
	}
	
} // uses bubble sort to sort all the users by location
void display_wifi()
{
	user s;
	fstream fphone;
	fphone.open("phone.dat", ios::in);
	while (fphone.read((char*)&s, sizeof(s)))
		if (s._wifi == 'y')
			s.show_data();
	fphone.close();
	cout << "\nall user data done";

}//displays users with wifi
void display_intl()
{
	user s;
	fstream fphone;
	fphone.open("phone.dat", ios::in);
	while (fphone.read((char*)&s, sizeof(s)))
		if (s._intl == 'y')
			s.show_data();
	fphone.close();
	cout << "\nall user data done";
}//displays users with international
void main()
{
	cout << "\n BSNL ADMINISTRATOR SERVICES\n";
	for (int i = 0; i < 32; i++)
		cout << "-";
	char c = 'n';
	int ch;
	cout << "\n";
	do
	{
		cout << "1.new user\n2.get wifi\n3.get international\n4.display all users\n5.sort all by balance\n6.sort all by name\n7.sort all by location\n8.display all with wifi \n9.display all with international\n10.recharge\n\t";
		cout << "\nWAITING FOR INPUT...";
		cin >> ch;
		
		switch (ch)
		{
		case 1:new_user();
			goto lable;
		case 2:get_wifi();
			goto lable;
		case 3:get_intl();
			goto lable;
		case 4:all_user();
			goto lable;
		case 5:sort_user_by_bal();
			goto lable;
		case 6:sort_user_by_name();
			goto lable;
		case 7:sort_user_by_location();
			goto lable;
		case 8:display_wifi();
			goto lable;
		case 9:display_intl();
			goto lable;
		case 10:recharge();
			goto lable;
		default:
			cout << "INVALID INPUT BREAKING SEQUENCE....";
			system("pause");
		}
		lable:		
		cout << "\n do you wish to continue?(y/n)";
		cin >> c;

	} while (c == 'y');


}//main progream
















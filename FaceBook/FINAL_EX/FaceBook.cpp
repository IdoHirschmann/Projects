#include "FaceBook.h"
//this func "runs" facebook by the choise of the user
void FaceBook::initiate()
{
	while (choice != 12)
	{
		printMenu();
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		try
		{


				switch (choice)
				{
				case 1:
				{
					//addfriend
					this->addingUserToFaceBook();
					break;
				}
				case 2:
				{
					//add fan page
					this->addingPageToFaceBook();
					break;
				}
				case 3:
				{
					//adding status to a user/fan page
					int choosing = 0;
					while (choosing != 1 && choosing != 2)
					{
						cout << "Enter 1 if you want to add status to a user" << endl;
						cout << "Enter 2 if you want to add status to a fan page" << endl;
						cin >> choosing;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						switch (choosing)
						{
						case 1:
							this->addStatusToUser();
							break;
						case 2:
							this->addStatusToFanPage();
							break;
						default:
							cout << "Re-enter your choice" << endl;
							break;
						}
					}
					break;
				}
				case 4:
				{
					//printing all the friend's/fan page's statuses
					int choosing = 0;
					while (choosing != 1 && choosing != 2)
					{
						cout << "Enter 1 if you want to print all the statuses of a user" << endl;
						cout << "Enter 2 if you want to print all the statuses of a fan page" << endl;
						cin >> choosing;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						switch (choosing)
						{
						case 1:
							this->printUserStatuses();
							break;
						case 2:
							this->printFanPagesStatuses();
							break;
						default:
							cout << "Re-enter your choice" << endl;
							break;
						}
					}
					break;
				}
				case 5:
				{
					//printing the last 10 statuses of a specific user's friends
					printingLastTenStatusesOfMyFriedns();
					break;
				}
				case 6:
				{
					//making 2 users to be friends
					createFriendship();
					break;
				}
				case 7:
				{
					//cancelling friendship
					cancellingFriendship();
					break;
				}
				case 8:
				{
					//adding fan to a fan page
					addingFanToFanPage();
					break;
				}
				case 9:
				{
					//remove fan from fan page
					removeFanFromFanPage();
					break;
				}
				case 10:
				{
					//printing all the object that on FaceBook
					printAllObjects();
					break;
				}
				case 11:
				{
					//printing all someone's friends/page's followers
					int choosing = 0;
					while (choosing != 1 && choosing != 2)
					{
						cout << "Enter 1 if you want to print someone's friedns" << endl;
						cout << "Enter 2 if you want to print page's fans" << endl;
						cin >> choosing;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');

						switch (choosing)
						{
						case 1:
							this->printUserFriends();
							break;
						case 2:
							this->printPageFans();
							break;
						default:
							cout << "Re-enter your choice" << endl;
							break;
						}
					}
					break;
				}
				case 12:
				{
					//exiting from FaceBook
					updateUsersDB("Users.txt", "UsersFriends.txt", "LikedPages.txt", "UsersStatuses.txt");
					updateFanPagesDB("FanPages.txt", "FanPagesStatuses.txt");
					cout << "Bye Bye" << endl;
					exit(1);
					break;
				}
				default:
					cout << "The choice you entered is not legitimate, please enter another one" << endl;
					break;

				}

		}
		catch (exception & ex)
		{
			cout << ex.what();
		}
	}

}
//printing the menu
void FaceBook::printMenu()
{
	cout << "" << endl;
	cout << "Hi,please choose from the following options: " << endl;
	cout << "Please enter number between 1-12 " << endl;
	cout << "Enter 1 for adding a user to the system" << endl;
	cout << "Enter 2 for adding a fan page to the system" << endl;
	cout << "Enter 3 for adding a status to a friend/fan page" << endl;
	cout << "Enter 4 for printing all friend's/fan page's statuses" << endl;
	cout << "Enter 5 for printing the last 10 statuses for all the friends of specific user" << endl;
	cout << "Enter 6 for making 2 users to be friends" << endl;
	cout << "Enter 7 for cancelling friendship between 2 friends" << endl;
	cout << "Enter 8 for adding fan to a fan page" << endl;
	cout << "Enter 9 for removing fan from a fan page" << endl;
	cout << "Enter 10 for printing all the object that are on FaceBook" << endl;
	cout << "Enter 11 for showing someon's friends/page's fans" << endl;
	cout << "Enter 12 for exiting" << endl;
}
//adding new user page to facebook
void FaceBook::addingUserToFaceBook()
{
	string name;
	int day, month, year;
	User* isUser;

	cout << "Please enter user's name:" << endl;
	getline(cin, name);

	isUser = searchUser(name);
	if (isUser == nullptr)
	{
		cout << "Please enter user's birth date (day, month, year):" << endl;
		cin >> day >> month >> year;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		User* user;
		user = new User(name, day, month, year);

		usersArr.push_back(user);
	}
	else
	{
		throw nameAlreadyExist(name);
	}
}
//adding new fan page to facebook
void FaceBook::addingPageToFaceBook()
{
	FanPage* isPageExist;
	string name;
	cout << "Please enter page's name" << endl;
	getline(cin, name);
	FanPage* page;
	page = new FanPage(name);

	isPageExist = searchFanPage(name);
	if (isPageExist == nullptr)
	{
		fanPagesArr.push_back(page);
	}
	else
	{
		throw nameAlreadyExist(name);
	}
}
//adding status to user
void FaceBook::addStatusToUser()
{
	printAllUsers();
	string name;
	cout << "Please enter the user's name:" << endl;
	getline(cin, name);
	User* found = searchUser(name);
	if (found == nullptr)
	{
		throw userDoesntExist(name);
	}
	else
	{
		cout <<"Enter Type of status (Reg, Video,Image), data for the status, and additional data (image or video name) if needed:" << endl;
		string type, data, additional;
		StatusFactory factory;

		getline(cin, type);
		getline(cin, data);
		getline(cin, additional);

		Status* status =  factory.CreateStatus(data, type, additional);
		found->addStatus(status);
	}

}
//adding status to fan page
void FaceBook::addStatusToFanPage()
{
	printAllFanPages();
	string pageName;
	cout << "Please enter the page's name:" << endl;
	getline(cin,pageName);
	FanPage* found = searchFanPage(pageName);
	if (found == nullptr)
	{
		throw pageDoesntExist(pageName);
	}
	else
	{
		cout << "Enter Type of status (Reg, Video,Image), data for the status, and additional data (image or video name) if needed:" << endl;
		string type, data, additional;
		StatusFactory factory;

		getline(cin, type);
		getline(cin, data);
		getline(cin, additional);
		Status* status = factory.CreateStatus(data, type, additional);
		found->addStatus(status);
	}

}
//prints all users in facebook
void FaceBook::printAllUsers()
{
	cout << "These are all the system's users:" << endl;
	for (int i = 0; i < usersArr.size(); i++)
	{
		usersArr[i]->printUser();
	}
	cout << "" << endl;
}
//prints all fan pages in facebook
void FaceBook::printAllFanPages()
{
	cout << "These are all the system's fan pages:" << endl;
	for (int i = 0; i < fanPagesArr.size(); i++)
	{
		fanPagesArr[i]->printPage();
	}
	cout << "" << endl;
}
//searching user in user arr by name
User* FaceBook::searchUser(const string name)
{
	bool found = false;
	User* res = nullptr;
	for (int i = 0; i < usersArr.size() && !found; i++)
	{
		if (usersArr[i]->getName()== name)
		{
			found = true;
			res = usersArr[i];
		}
	}
	return res;
}
//searching fan page in fan page arr by name
FanPage* FaceBook::searchFanPage(const string name)
{
	bool found = false;
	FanPage* res = nullptr;
	for (int i = 0; i < fanPagesArr.size() && !found; i++)
	{
		if (fanPagesArr[i]->getName()== name)
		{
			found = true;
			res = fanPagesArr[i];
		}
	}
	return res;
}
//printing all chosen user statuses
void FaceBook::printUserStatuses()
{
	printAllUsers();
	string name;
	cout << "Please enter the user's name:" << endl;
	getline(cin, name);
	User* found = searchUser(name);
	if (found == nullptr)
	{
		throw userDoesntExist(name);
	}
	else
	{
		found->printStatuses();		
	}
}
//printing all chosen fan page statuses
void FaceBook::printFanPagesStatuses()
{
	printAllFanPages();
	string pageName;
	cout << "Please enter the page's name:" << endl;
	getline(cin, pageName);
	FanPage* found = searchFanPage(pageName);
	if (found == nullptr)
	{
		throw pageDoesntExist(pageName);
	}
	else
	{
		found->printStatuses();
	}
}
//printing all chosen user's last ten statuses  
void FaceBook::printingLastTenStatusesOfMyFriedns()
{
	printAllUsers();
	string name;
	cout << "Please enter the user's name:" << endl;
	getline(cin, name);
	User* found = searchUser(name);
	if (found == nullptr)
	{
		throw userDoesntExist(name);
	}
	else
	{
		found->printMyFriendsStatuses();
	}

}
//making two users friends
void FaceBook::createFriendship()
{
	printAllUsers();
	cout << "Enter 2 names of users that will be frieds" << endl;
	string firstUserName;
	string secondUserName;
	getline(cin, firstUserName);
	User* firstUser = searchUser(firstUserName);
	if (!firstUser)
		throw userDoesntExist(firstUserName);
	getline(cin, secondUserName);
	User* secondUser = searchUser(secondUserName);
	if(!secondUser)
		throw userDoesntExist(secondUserName);
	else
	{
			firstUser->addFriend(secondUser);
			secondUser->addFriend(firstUser);	
	}

}
// unfriending two users
void FaceBook::cancellingFriendship()
{
	printAllUsers();
	cout << "Enter the user's name that you want to delete friend from" << endl;
	string userName;
	getline(cin, userName);
	User* user = searchUser(userName);
	if (user != nullptr)
	{
		cout << "Enter the friend's name that you want to delete from the friends list" << endl;
		user->printFriends();
		string userToDelete;
		getline(cin, userToDelete);
		User* secondUser = searchUser(userToDelete);
		if (!secondUser)
			throw userDoesntExist(userToDelete);

		user->removeFriend(userToDelete);
		secondUser->removeFriend(userName);
	}
	else
	{
		throw userDoesntExist(userName);
	}

}
//making chosen user like page
void FaceBook::addingFanToFanPage()
{
	printAllFanPages();
	cout << "Enter name of a fan page" << endl;
	string fanPageName;
	getline(cin, fanPageName);
	FanPage* page = searchFanPage(fanPageName);
	if (page == nullptr)
	{
		throw pageDoesntExist(fanPageName);

	}
	else
	{
		printAllUsers();
		cout << "Enter name of a user" << endl;
		string userName;
		getline(cin, userName);
		User* user = searchUser(userName);
		if (user == nullptr)
		{
			throw userDoesntExist(userName);
		}
		else
		{
			page->addFan(user);
			user->likePage(page);
		}
	}


}
//removes chosen user from liking a chosen page
void FaceBook::removeFanFromFanPage()
{
	printAllFanPages();
	cout << "Enter the page's name that you want to delete fan from" << endl;
	string pageName;
	getline(cin, pageName);
	FanPage* page = searchFanPage(pageName);
	if (page != nullptr)
	{
		cout << "Enter user's name that you want to delete from fans list" << endl;
		page->printFans();
		string userToRemove;
		getline(cin, userToRemove);
		User* user = searchUser(userToRemove);
		if (!user)
			throw userDoesntExist(userToRemove);
		page->removeFan(userToRemove);		
		user->unlikePage(pageName);
	}
	else
	{
		throw pageDoesntExist(pageName);
	}


}
//prints all users and pages in facebook
void FaceBook::printAllObjects()
{
	printAllUsers();
	cout << "" << endl;
	printAllFanPages();
}
//prints all chosen user friends
void FaceBook::printUserFriends()
{
	printAllUsers();
	cout << "Enter the user you want to print all his friends" << endl;
	string name;
	getline(cin, name);
	User* user = searchUser(name);
	if (user != nullptr)
	{
		user->printFriends();
	}
	else
	{
		throw userDoesntExist(name);
	}
}
//prints all page fans
void FaceBook::printPageFans()
{
	printAllFanPages();
	cout << "Enter the page that you want to print all his fans" << endl;
	string name;
	getline(cin, name);
	FanPage* page = searchFanPage(name);
	if (page != nullptr)
	{

		page->printFans();
	}
	else
	{
		throw pageDoesntExist(name);
	}
}


//add data to facebook when created
void FaceBook :: addDefData()
{
	User* u1, * u2, * u3;
	FanPage* f1, * f2, * f3;
	Status* u1s1, * u1s2, * u2s1, * u2s2, * u3s1, * u3s2;
	Status* f1s1, * f1s2, * f2s1, * f2s2, * f3s1, * f3s2;

	u1 = new User("Ronaldo", 5, 2, 1985);
	u1s1 = new Status("Hey my name is Ronaldo and this is my first status!");
	u1s2 = new Status("Hey my name is Ronaldo and i am the best!");
	u1->addStatus(u1s1);
	u1->addStatus(u1s2);


	u2 = new User("Messi", 24, 6, 1987);
	u2s1 = new Status("Hey my name is Messi and this is my first status!");
	u2s2 = new Status("Hey my name is Messi and i am the best!");
	u2->addStatus(u2s1);
	u2->addStatus(u2s2);

	u3 = new User("Neymar", 5, 2, 1992);
	u3s1 = new Status("Hey my name is Neymar and this is my first status!");
	u3s2 = new Status("Hey my name is Neymar and i am the best!");
	u3->addStatus(u3s1);
	u3->addStatus(u3s2);

	f1 = new FanPage("Ronaldo'S FANS");
	f1s1 = new Status("Hello! we are fans! This is our first status!");
	f1s2 = new Status("We belive that Ronaldo is the best!");
	f1->addStatus(f1s1);
	f1->addStatus(f1s2);

	f2 = new FanPage("Messi'S FANS");
	f2s1 = new Status("Hello! we are Messi fans! This is our first status!");
	f2s2 = new Status("We belive that Messi is the best!");
	f2->addStatus(f2s1);
	f2->addStatus(f2s2);

	f3 = new FanPage("Neymar'S FANS");
	f3s1 = new Status("Hello! we are Neymar fans! This is our first status!");
	f3s2 = new Status("We belive that Neymar is the best!");
	f3->addStatus(f3s1);
	f3->addStatus(f3s2);

	u1->addFriend(u2);
	u1->likePage(f1);
	f1->addFan(u1);

	u2->addFriend(u1);
	u2->addFriend(u3);
	u2->likePage(f2);
	f2->addFan(u2);

	u3->addFriend(u2);
	u3->likePage(f3);
	f3->addFan(u3);

	
	cout << "the next lines are meant to check the operators we wrote: " << endl;
	cout << "before +=: " << endl;
	u1->printFriends();
	u3->printFriends();
	cout << "after +=: " << endl;
	*u1 += *u3; // Makes Neymar and Ronaldo friends 
	 u1->printFriends();
	 u3->printFriends();
	 cout << "before +=: " << endl;
	 f1->printFans();
	 cout << "after +=: " << endl;
	*f1 += *u2;// Makes Messi fan of Ronaldos fanpage
	 f1->printFans();

	User* tester = new User("tester", 1, 1, 2000);//empty user

	if (*u1 > *tester)
	{
		cout << u1->getName() << " has more friends!" << endl;
	}
	if (*f1 > *f2)
	{
		cout << f1->getName() << " has more friends!" << endl;
	}
	if (*f1 > *tester)
	{
		cout << f1->getName() << " has more friends!" << endl;
	}
	if (*u1 > *f2)
	{
		cout << u1->getName() << " has more friends!" << endl;
	}

	if (u1s1 == u1s1)
	{
		cout << "statuses have the same data!" << endl;
	}
	if (u1s1 != u1s2)
	{
		cout << "statuses dont have the same data!" << endl;
	}

	cout << '\n' << endl;

	delete tester;

	this->usersArr.push_back(u1);
	this->usersArr.push_back(u2);
	this->usersArr.push_back(u3);

	this->fanPagesArr.push_back(f1);
	this->fanPagesArr.push_back(f2);
	this->fanPagesArr.push_back(f3);

	
}

void FaceBook::loadFaceBook(string userF, string fanPageF, string usersFriends, string likedPages, string UsersStatuses, string fanPagesStatuses)
{
	loadUsers(userF);
	loadFanPages(fanPageF);
	loadFriendships(usersFriends);
	loadLikedPages(likedPages);
	loadUsersStatuses(UsersStatuses);
	loadFanPagesStatuses(fanPagesStatuses);
}
//loading users from users db
void FaceBook::loadUsers(string userF)
{
	ifstream userFile(userF, ios_base::in);

	string name;
	string day, month, year;
	int _day, _month, _year;
	User* temp;

	while (getline(userFile, name))
	{
		getline(userFile, day);
		getline(userFile, month);
		getline(userFile, year);

		_day = stoi(day);
		_month = stoi(month);
		_year = stoi(year);

		temp = new User(name, _day, _month, _year);
		usersArr.push_back(temp);
	}
	userFile.close();
}
//loading fp from fp db
void FaceBook :: loadFanPages(string fanPageF)
{
	ifstream fanPageFile(fanPageF, ios_base::in);

	string name;

	FanPage* temp;

	while (getline(fanPageFile, name))
	{
		temp = new FanPage(name);
		fanPagesArr.push_back(temp);
	}
	fanPageFile.close();
}

void FaceBook::loadFriendships(string fName)
{
	ifstream friendships(fName, ios_base::in);

	string num,name;
	int curr, index =0;
	while (getline(friendships, num))
	{
		curr = stoi(num);

		for (int i = 0; i < curr; i++)
		{
			getline(friendships, name);
			usersArr[index]->addFriend(searchUser(name));
		}
		index++;
	}
	friendships.close();
}

void FaceBook::loadLikedPages(string fName)
{
	ifstream likedPages(fName, ios_base::in);

	string num, name;
	int curr, index = 0;
	FanPage* temp;
	while (getline(likedPages, num))
	{
		curr = stoi(num);

		for (int i = 0; i < curr; i++)
		{
			getline(likedPages, name);
			temp = searchFanPage(name);
			usersArr[index]->likePage(temp);
			temp->addFan(usersArr[index]);
		}
		index++;
	}
	likedPages.close();
}

void  FaceBook::loadUsersStatuses(string fName)
{
	ifstream statuses(fName, ios_base::in);
	StatusFactory factory;

	string num,type,data,additional,date;
	int curr, index = 0;
	while (getline(statuses, num))
	{
		curr = stoi(num);
		for (int i = 0; i < curr; i++)
		{
			getline(statuses, type);
			getline(statuses, data);
			if(type!="Reg")//vid or img
				getline(statuses, additional);
			getline(statuses, date);

			Status* status = factory.CreateStatus(data, type, additional);
			status->setTime(date);
			usersArr[index]->addStatus(status);
		}
		index++;
	}
	statuses.close();
}

void FaceBook::loadFanPagesStatuses(string fName)
{
	ifstream statuses(fName, ios_base::in);
	StatusFactory factory;

	string num, type, data, additional, date;
	int curr, index = 0;
	while (getline(statuses, num))
	{
		curr = stoi(num);
		for (int i = 0; i < curr; i++)
		{
			getline(statuses, type);
			getline(statuses, data);
			if (type != "Reg")//vid or img
				getline(statuses, additional);
			getline(statuses, date);

			Status* status = factory.CreateStatus(data, type, additional);
			status->setTime(date);
			fanPagesArr[index]->addStatus(status);
		}
		index++;
	}
	statuses.close();
}

void FaceBook:: updateUsersDB(string userF, string usersFriends, string likedPages, string UsersStatuses)
{
	ofstream users(userF, ios_base::out);
	ofstream friends(usersFriends, ios_base::out);
	ofstream liked(likedPages, ios_base::out);
	ofstream statuses(UsersStatuses, ios_base::out);
	const Status* tempStatus;

	for (int i = 0; i < usersArr.size(); i++)
	{
		int numOfFriends = usersArr[i]->getNumOfFriends();
		int numOfFanPages = usersArr[i]->getNumOfLiked();
		int numOfStatuses = usersArr[i]->getNumOfStatuses();

		users << usersArr[i]->getName() << endl;
		users << usersArr[i]->getBirthday() << endl;
		friends << numOfFriends <<endl;
		liked << numOfFanPages <<endl;
		statuses << numOfStatuses << endl;

		for (int j = 0; j < numOfFriends; j++)
		{
			friends << usersArr[i]->getFriendName(j)<<endl;
		}
		for (int j = 0; j < numOfFanPages; j++)
		{
			liked << usersArr[i]->getPageName(j) << endl;
		}
		for (int j = 0; j < numOfStatuses; j++)
		{
			tempStatus = usersArr[i]->getStatus(j);
			string type = tempStatus->getType();

			statuses << type<< endl;
			statuses << tempStatus->getData()<<endl;

			if (strcmp(type.c_str(), "Reg") != 0)
			{
				statuses << tempStatus->getAddData()<<endl;
			}


			statuses << tempStatus->getStatusTime()<<endl;
		}
	}
	users.close();
	liked.close();
	friends.close();
	statuses.close(); 
}
void FaceBook:: updateFanPagesDB(string fanPageF,string fanPagesStatuses)
{
	ofstream fanPages(fanPageF, ios_base::out);
	ofstream statuses(fanPagesStatuses, ios_base::out);
	const Status* tempStatus;

	for (int i = 0; i < fanPagesArr.size(); i++)
	{
		fanPages << fanPagesArr[i]->getName() << endl;

		int numOfStatuses = fanPagesArr[i]->getNumOfStatuses();

		statuses << numOfStatuses << endl;

		for (int j = 0; j < numOfStatuses; j++)
		{
			tempStatus = fanPagesArr[i]->getStatus(j);

			string type = tempStatus->getType();

			statuses << type << endl;
			statuses << tempStatus->getData() << endl;
			if (strcmp(type.c_str(), "Reg") != 0)
			{
				statuses << tempStatus->getAddData() << endl;
			}

			statuses << tempStatus->getStatusTime()<<endl;
		}
	}
	fanPages.close();
	statuses.close();
}
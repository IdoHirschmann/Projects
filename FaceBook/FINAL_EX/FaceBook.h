#pragma once
#include "User.h"
#include "FanPage.h"
#include "StatusFactory.h"
#include <fstream>
#include <vector>


class FaceBook
{
	vector<User*> usersArr;
	vector<FanPage*> fanPagesArr;
	int choice = 0;

public:
	FaceBook()
	{
		//addDefData();
		loadFaceBook("Users.txt", "FanPages.txt","UsersFriends.txt","LikedPages.txt", "UsersStatuses.txt","FanPagesStatuses.txt");
		cout << "Welcome to facebbok!" << endl;
	}
	void initiate();
	~FaceBook()
	{

		for (int i = 0; i < usersArr.size(); i++)
		{
			delete usersArr[i];
		}

		for (int i = 0; i < fanPagesArr.size(); i++)
		{
			delete fanPagesArr[i];
		}

	}



	class userDoesntExist : public exception
	{
		string exp;

	public:
		userDoesntExist(const string name)
		{
			exp = "The user " + name + " doesnt exist in the db.\n";
		}

		char const* what() const noexcept
		{
			return exp.c_str();
		}
	};

	class pageDoesntExist : public exception
	{
		string exp;

	public:
		pageDoesntExist(const string name)
		{
			exp = "The page " + name + " doesnt exist in the db.\n";
		}

		char const* what() const noexcept
		{
			return exp.c_str();
		}
	};

	class nameAlreadyExist : public exception
	{
		string exp;

	public:
		nameAlreadyExist(const string name)
		{
			exp = "The name " + name + " already exists in the db.\n";
		}

		char const* what() const noexcept
		{
			return exp.c_str();
		}
	};






private:
	void addDefData();
	void printMenu();
	void addingUserToFaceBook();
	void addingPageToFaceBook();
	void addStatusToUser();
	void addStatusToFanPage();
	void printAllUsers();
	void printAllFanPages();
	User* searchUser(const string name);
	FanPage* searchFanPage(const string name);
	void printFanPagesStatuses();
	void printUserStatuses();
	void printingLastTenStatusesOfMyFriedns();
	void createFriendship();
	void cancellingFriendship();
	void addingFanToFanPage();
	void removeFanFromFanPage();
	void printAllObjects();
	void printUserFriends();
	void printPageFans();
	void loadFaceBook(string userF, string fanPageF, string usersFriends,string likedPages, string UsersStatuses, string fanPagesStatuses);
	void loadUsers(string userF);
	void loadFanPages(string fanPageF);
	void loadFriendships(string fName);
	void loadLikedPages(string fName);
	void loadUsersStatuses(string fName);
	void loadFanPagesStatuses(string fName);
	void updateUsersDB(string userF, string usersFriends, string likedPages, string UsersStatuses);
	void updateFanPagesDB(string fanPageF,string fanPagesStatuses);

};


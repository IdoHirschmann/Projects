#ifndef PROJECT1_USER_H
#define PROJECT1_USER_H
#define _CRT_SECURE_NO_WARNINGS
#include "Status.h"
#include "Date.h"
#include<iostream>
#include <vector>

const int TEN = 10;
class FanPage;

class User
{
    string name;
    vector < User *> friendsArr;
    vector < FanPage*> fanPagesArr;
    vector <Status *> statusArr;
    Date birthday;

public:

    //Default cto'r
    User() = default;

    User(const string name, int day, int month, int year)
    {
        birthday = Date(day, month, year);
        this->name = name;
    }

    void addStatus(Status* stat);

    void printStatuses()
    {
        if (statusArr.size() == 0)
        {
            throw(noUserStatuses(this->name));
        }
        for (int i = 0; i < statusArr.size(); i++)
        {
            cout << "Status number: " << i + 1 << "\n" << endl;
            this->statusArr[i]->printStatus();
        }
    }

    void printLastTenStat();

    void addFriend(User* newFriend);

    bool isFriend(string user);

    void printUser();
    void printFanPages();
    void printFriends();
    void printMyFriendsStatuses();

    void removeFriend(const string fToRemove);

    void likePage(FanPage* pageToLike);

    void unlikePage(string fpToUnlike);
    string getFriendName(int index);
    string getPageName(int index);
    const Status* getStatus(int index);
    bool isFollowing(FanPage * fp);

    User& operator += (User& user);
    bool operator > (const User& user);
    bool operator > (FanPage & fp);

    const int getNumOfFriends()
    {
        return friendsArr.size();
    }
    const int getNumOfLiked()
    {
        return fanPagesArr.size();
    }
    const int getNumOfStatuses()
    {
        return statusArr.size();
    }
    const string getName()
    {
        return name;
    }
    
    const string getBirthday()
    {
        string res;
        
        res = to_string(birthday.getDay()) + '\n' + to_string(birthday.getMonth()) + '\n' + to_string(birthday.getYear());
 
        return res;
    }
    
    class noUserStatuses : public exception
    {
        string exp;
    public:
        noUserStatuses(const string name)
        {
            exp = "There are no statuses for ";
            exp += name;
            exp += ". \n";
        }
        char const* what() const noexcept
        {
            return exp.c_str();
        }

    };

    class addFriendThatAlreadyExist : public exception
    {
        string exp;

    public:
        addFriendThatAlreadyExist(string thisName, string otherName)
        {
            exp = "The user ";
            exp += thisName;
            exp += " is already a friend with ";
            exp += otherName;
            exp += ".\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class noFriendsExp : public exception
    {
        string exp;

    public:
        noFriendsExp()
        {
            exp = "This user has no friends.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class noFanPagesExp : public exception
    {
        string exp;

    public:
        noFanPagesExp()
        {
            exp = "This user dont like any pages.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class addFPThatAlreadyExist : public exception
    {
        string exp;

    public:
        addFPThatAlreadyExist(string name)
        {
            exp = "The user ";
            exp += name;
            exp += " is already a following this page.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };


    class fanPagesArrEmpty : public exception
    {
        string exp;

    public:
        fanPagesArrEmpty(string name)
        {
            exp = "The user ";
            exp += name;
            exp += " is not following any fan pages.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class fanPageDoesNotExist : public exception
    {
        string exp;

    public:
        fanPageDoesNotExist(string userName, string fpName )
        {
            exp = "The user ";
            exp += userName;
            exp += " is not following ";
            exp += fpName;
            exp += ".\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };


    class friendDoesNotExist : public exception
    {
        string exp;

    public:
        friendDoesNotExist(string thisname, string othername)
        {
            exp = "The user ";
            exp += thisname;
            exp += " is not friend with " + othername + ".\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    ~User()
    {
        for (int i = 0; i < statusArr.size(); i++)
        {
            delete statusArr[i];
        }
    }

};




#endif //PROJECT1_USER_H
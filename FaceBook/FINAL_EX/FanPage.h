#ifndef PROJECT1_FANPAGE_H
#define PROJECT1_FANPAGE_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Status.h"
#include <vector>
using namespace std;

class User;

class FanPage
{
    string name;
    vector<User*> fansArr;
    vector<Status*> statusArr;


public:
    FanPage() = default;

    FanPage(string name)
    {
        this->name = name;
    }

    void addStatus(Status* stat);

    void printStatuses() const
    {
        if (statusArr.size() == 0)
        {
            throw(noFanPageStatuses());
        }
        for (int i = 0; i < statusArr.size(); i++)
        {
            cout << "Status number: " << i + 1 << "\n" << endl;
            this->statusArr[i]->printStatus();
        }
    }

    const int getNumOfFans()
    {
        return fansArr.size();
    }

    const int getNumOfStatuses()
    {
        return statusArr.size();
    }

    void printPage()
    {
        cout << name << endl;
    }
    void addFan(User* newFan);
    bool isFan(User* user);
    void printFans() const;
    void operator += (User& user);
    bool operator > (FanPage& fp);
    bool operator > (User& user);

    void removeFan(const string fToRemove);

    const string getName()
    {
        return this->name;
    }
    const Status* getStatus(int index);
    
    class addFanThatAlreadyExist : public exception
    {
        string exp;

    public:
        addFanThatAlreadyExist(string name)
        {
            exp = "The user ";
            exp += name;
            exp += " is already a fan of this page.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class noFansExp : public exception
    {
        string exp;

    public:
        noFansExp()
        {
            exp = "The page has no fans.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };
    
    class fanNotExist : public exception
    {
        string exp;

    public:
        fanNotExist(const string name)
        {
            exp = "The user ";
            exp += name;
            exp += " is not a fan of this page.\n";
        }

        char const* what() const noexcept
        {
            return exp.c_str();
        }
    };

    class noFanPageStatuses: public exception
    {
        string exp;
    public:
        noFanPageStatuses()
        {
            exp = "There are no statuses in this page! \n";
        }
        char const* what() const noexcept
        {
            return exp.c_str();
        }

    };

    ~FanPage()
    {
        for (int i = 0; i < statusArr.size(); i++)
        {
            delete statusArr[i];
        }
    }



};




#endif //PROJECT1_FANPAGE_H

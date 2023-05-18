#ifndef PROJECT1_STATUS_H
#define PROJECT1_STATUS_H
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <iostream>
#include <string.h>
#include<string>
#include <ctime>

using namespace std;


class Status
{
    //statusType type;
    //date
    //time
    //data
    string data;
    string statusTime;

public:
    
    Status(const string _data)
    {
        data = _data;
        statusTime = createTime();
        statusTime = statusTime.substr(0, statusTime.size() - 1);
    }

    string getStatusTime() const 
    {
        return this->statusTime;
    }
    const Status* getStatus() const
    {
        return this;
    }

    string getData() const
    {
        return data;
    }
    virtual string getAddData() const
    {
        return "";
    }

    virtual bool operator ==(const Status& s);
    bool operator !=(const Status& s);

    string getType() const;

    virtual void printStatus()
    {
        cout << this->data << "\nDate and Time: " << this->statusTime << endl;
    }

    virtual void printColor()
    {
        cout << "This status is printed in black & white" << endl;
    }

    void setTime(string newTime)
    {
        statusTime = newTime;
    }
    virtual ~Status() = default;

private:
    char* createTime();

};

#endif //PROJECT1_STATUS_H
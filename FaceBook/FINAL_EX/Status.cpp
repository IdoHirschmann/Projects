

#include "Status.h"
//creating the string that contains time and date of status using ctime
char* Status::createTime()
{
    char* res;
    time_t curr_time;
    curr_time = time(NULL);
    char* tm = ctime(&curr_time);
    res = new char[strlen(tm)];
    res = tm;
    return res;
}


bool Status :: operator ==(const Status& s)
{
    if (typeid(*this).name() != typeid(s).name())
        return false;
    return (this->data == s.data);
}
bool Status ::operator !=(const Status& s)
{
    return !(*this == s);
}

string Status:: getType() const 
{
    string res;
    string type = typeid(*this).name();

    if (strcmp(type.c_str(),"class Status") == 0)
    {
        res = "Reg";
    }
    else if (strcmp(type.c_str(), "class StatusVid") == 0)
    {
        res = "Video";
    }
    else
    {
        res = "Image";
    }     
    return res;
}

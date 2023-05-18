
#include "FanPage.h"
#include "User.h"
//adding status to this
void FanPage::addStatus(Status* stat)
{
    statusArr.push_back(stat);
}
//remones fan from this fans arr
void FanPage::removeFan(const string fToRemove)//need to be fixed
{
    bool found = false;

    for (int i = 0; i < fansArr.size() && !found; i++)
    {
        if (fToRemove ==  fansArr[i]->getName())
        {
            found = true;
            //found him!
            fansArr.erase(fansArr.begin() + i);
        }
    }
    if (!found)
    {
        throw(fanNotExist(fToRemove));
    }
}
//adding fan to this fans arr
void FanPage::addFan(User* newFan)
{
    bool flag = isFan(newFan);
    if (!flag)
    {
        fansArr.push_back(newFan);
    }
    else
    {
        throw(addFanThatAlreadyExist(newFan->getName()));
    }
}
//prints all this fans
void FanPage::printFans() const 
{
    if (fansArr.size() == 0)
    {
        throw(noFansExp());
    }
    else
    {
        cout << '\n' << "Fans of " << name << " are: " << endl;
        for (int i = 0; i < fansArr.size(); i++)
        {
            (this->fansArr[i])->printUser();
        }
        cout << endl;
    }

}
//chaeck if given user is fan of this
bool FanPage::isFan(User* user)
{
    bool found = false;

    for (int i = 0; i < fansArr.size() && !found; i++)
    {
        if (fansArr[i]->getName()== user->getName())
        {
            found = true;
        }
    }
    return found;
}

//operator += returns void because you cannot add pages to one another,
//and if you try to do mulipule assignments you will end up conncting user unintentionaly 
//so insted you can only add one fan to a page at the time
void FanPage :: operator += (User& user)
{
    this->addFan(&user);
    user.likePage(this);
}


bool FanPage:: operator > (FanPage& fp)
{
    return (this->fansArr.size() > fp.fansArr.size());
}
bool FanPage:: operator > (User& user)
{
    return (this->fansArr.size() > user.getNumOfFriends());

}

// returns specific status by given index
const Status* FanPage::getStatus(int index)
{
    return statusArr[index];
}

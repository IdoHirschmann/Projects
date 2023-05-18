#include "User.h"
#include "FanPage.h"

class FanPage;
//add status to this
void User::addStatus(Status* stat)
{
    statusArr.push_back(stat);
}
//prints the last ten statuses of this friends
void User::printMyFriendsStatuses()
{
    if (friendsArr.size() == 0)
    {
        throw(noFriendsExp());
    }
    else
    {
        for (int i = 0; i < friendsArr.size(); i++)
        {
            try 
            {
            cout << "The statuses of " << friendsArr[i]->getName() << endl;
            friendsArr[i]->printLastTenStat();
            }
            catch(noUserStatuses & ex)
            {
                cout << ex.what();
            }
         }
    }
    
}
//printing last ten status of this
void User::printLastTenStat()
{
    if (statusArr.size() == 0)
    {
        throw(noUserStatuses(this->name));
    }
    for (int i = 0; i < TEN && i < statusArr.size(); i++)
    {
        cout << "Status number: " << i + 1 << "\n" << endl;
        this->statusArr[i]->printStatus();
    }
}
//removes given friend from users friend arr
void User::removeFriend(const string fToRemove)
{
    bool found = false;
    if (friendsArr.size() == 0)
    {
        throw(noFriendsExp());
    }
    for (int i = 0; i < friendsArr.size() && !found; i++)
    {
        if (fToRemove == friendsArr[i]->getName())
        {
            found = true;
            //found him!
            friendsArr.erase(friendsArr.begin() + i);
        }
    }
    if (!found)
    {
        throw(friendDoesNotExist(name,fToRemove));
    }
}
//add friend to this
void User::addFriend(User* user)
{
    bool flag = isFriend(user->getName());
    if (!flag)
    {
        friendsArr.push_back(user);
    }
    else
    {
        throw(addFriendThatAlreadyExist(name,user->getName()));
    }
}
//prints all users friends
void User::printFriends()
{
    if (friendsArr.size() == 0)
    {
        throw(noFriendsExp());
    }
    else
    {
        cout <<'\n'<< "Friends of " << name << " are: " << endl;
        for (int i = 0; i < friendsArr.size(); i++)
        {
            this->friendsArr[i]->printUser();
        }
        cout << endl;
    }
}
//likes page
void User::likePage(FanPage* pageToLike)
{
    if (isFollowing(pageToLike))
    {
        throw(addFPThatAlreadyExist(name));
    }
    fanPagesArr.push_back(pageToLike);
}
//unlikes liked page of user
void User::unlikePage(string fpToUnlike)
{
    bool found = false;
    if (fanPagesArr.size() == 0)
    {
        throw(fanPagesArrEmpty(name));
    }
    for (int i = 0; i < fanPagesArr.size() && !found; i++)
    {
        if (fpToUnlike == fanPagesArr[i]->getName())
        {
            found = true;
            //found him!
            fanPagesArr.erase(fanPagesArr.begin() + i);
        }
    }
    if (!found)
    {
        throw(fanPageDoesNotExist(name,fpToUnlike));
    }
}

//prints users name
void User::printUser()
{
    cout << this->name << endl;
}
//check if given user is friend with this
bool User::isFriend(string user)
{
    bool found = false;

    for (int i = 0; i < friendsArr.size() && !found; i++)
    {
        if (friendsArr[i]->getName() == user)
        {
            found = true;
        }
    }
    return found;
}

//bool func that checks if user is following page
bool User::isFollowing(FanPage* fp)
{
    bool found = false;

    for (int i = 0; i < fanPagesArr.size() && !found; i++)
    {
        if (friendsArr[i]->getName() == fp->getName())
        {
            found = true;
        }
    }
    return found;
}
//opeartor += overloading that makes two users friends 
User& User:: operator += (User& user)
{
    this->addFriend(&user);
    user.addFriend(this);
    return *this;
}

bool User:: operator > (const User & user)
{
    return (this->friendsArr.size() > user.friendsArr.size());
}
bool User:: operator > (FanPage& fp)
{
    return (this->friendsArr.size() >fp.getNumOfFans());

}
//prints all the pages user likes
void User::printFanPages()
{
    if (fanPagesArr.size() == 0)
    {
        throw(noFanPagesExp());
    }
    else
    {
        cout << '\n' << "The liked pages of " << name << " are: " << endl;
        for (int i = 0; i < fanPagesArr.size(); i++)
        {
            this->fanPagesArr[i]->printPage();
        }
        cout << endl;
    }
}
// returns specific friend by given index
string User:: getFriendName(int index)
{
    return friendsArr[index]->getName();
}
// returns specific fan page by given index
string User::getPageName(int index)
{
    return fanPagesArr[index]->getName();
}
// returns specific status by given index
const Status* User::getStatus(int index)
{
    return statusArr[index];
}
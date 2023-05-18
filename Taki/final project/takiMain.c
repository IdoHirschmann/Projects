//WRITTEN BY: Ido Hirschmann 211329883
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//const declaration
#define MAX_NAME_LEN 20
#define STARTING_CARD_NUM 4
#define NUM_OF_CARDS 14
#define PLUS 10
#define STOP 11
#define CHANGE_DIRECTION 12
#define TAKI 13
#define COLOR 14

struct card
{
    int type;
    int color;
};
typedef struct card CARD;

struct player
{
    char name[MAX_NAME_LEN];
    CARD * cards;
    int physSize;
    int logSize;
};
typedef struct player PLAYER;

struct statistics
{
    int type;
    int count;
};
typedef struct statistics STATISTICS;

//func declaration
void printWelcome();
PLAYER * getPlayerData(int numOfPlayers, STATISTICS stats[]);
void setPlayerData(PLAYER * newPlayer, int ind, STATISTICS stats[]);
void drawFirstCard(int* ptype, int* pcolor);
void drawCard(int* ptype, int* pcolor,STATISTICS stats[]);
void printCard(int type, int color);
void printPlayersCards(PLAYER *players, int playerTurn);
CARD * myRealloc(CARD * playersCard ,int * pPsize, int logSize);
void setStatistic(STATISTICS arr[]);
int colorCard();
CARD *removeCardFromPlayer(CARD * playersHand, int cardToRemove, int *pLogSize, int phySize);
bool roundOfPlay(PLAYER players[],int size ,int i, CARD* upperCard, int * pplayersChoice,STATISTICS stats[]);
CARD *addCardToPlayerHand(CARD * playersHand, int *pLogSize, int *pphySize,STATISTICS stats[]);
bool isChoiceValid(CARD* playersHand, int playersChoice, CARD upperCard, int logSize, int phySize);
int takiCard( int logSize);
void mergerSort(STATISTICS stats[], int size);
STATISTICS * merge(STATISTICS a1[], int size1, STATISTICS a2[], int size2);
void copyArr(STATISTICS dest[], STATISTICS src[], int size);
void printStatistic(STATISTICS statistics[], int size);


void main()
{
    int i;
    int winnerInd;
    int numOfPlayers;
    int upperType, upperColor;
    int currentPlayer;
    int inc;
    int playersChoice;
    srand(time(NULL));
    PLAYER * players;

    STATISTICS stats[NUM_OF_CARDS];
    setStatistic(stats);

    bool winner = false;
    CARD upperCard;
    drawFirstCard(&upperType, &upperColor);
    upperCard.type = upperType;
    upperCard.color = upperColor;

    printf("Please enter the number of players:\n");
    scanf("%d", &numOfPlayers);

    players = getPlayerData(numOfPlayers,stats);
    inc = 1;
    i = 0;

    while(winner == false)
    {
        printf("Upper card:\n");
        printCard(upperCard.type,upperCard.color);
        printf("\n");

        currentPlayer = i % numOfPlayers ;
        winner = roundOfPlay(players,numOfPlayers,currentPlayer,&upperCard,&playersChoice,stats);
        if(upperCard.type == PLUS && playersChoice != 0)//gives the curr player another turn
            i -= inc;
        if(upperCard.type == STOP && playersChoice != 0)//jumping over the next players turn due to stop card played
            i+= inc;
        if(upperCard.type == CHANGE_DIRECTION && playersChoice != 0)// changes the direction of the play by turning the counting index.
            inc *= -1;

        i += inc;

        if(i < 0 && inc < 0)//keeps i positive
            i=numOfPlayers - 1;

        if(winner == true)
            winnerInd = currentPlayer;
    }

    printf("The winner is... %s! Congratulations!\n", players[winnerInd].name);

    mergerSort(stats, NUM_OF_CARDS);

    printStatistic(stats,NUM_OF_CARDS);

}

//prints welcome
void printWelcome()
{
    printf("************ Welcome to TAKI game !!! ************\n");
}

//gets the number of players and player names
PLAYER * getPlayerData(int numOfPlayers, STATISTICS stats[])
{
    int i;
    PLAYER * players = NULL;

    players = (PLAYER*) malloc(numOfPlayers * sizeof(PLAYER));

    if(players == NULL)
    {
        printf("allocation failed!!\n");
        exit(1);
    }

    for(i = 0; i < numOfPlayers; i++)
    {
        setPlayerData(players + i, i, stats);
    }

    return players;
}

//set the player array and data
void setPlayerData(PLAYER * newPlayer, int ind, STATISTICS stats[])
{
    int i,type, color;
    printf("Please enter the first name of player #%d:\n", ind+1);
    scanf("%s", newPlayer->name);
    newPlayer->cards = (CARD*) malloc(STARTING_CARD_NUM* sizeof(CARD));
    if(newPlayer->cards == NULL)
    {
        printf("allocation failed!!\n");
        exit(1);
    }
    for(i = 0; i < STARTING_CARD_NUM; i++)
    {
        drawCard(&type, &color,stats);
        stats[type].count++;
        newPlayer->cards[i].type = type;
        newPlayer->cards[i].color = color;
    }
    newPlayer->physSize = STARTING_CARD_NUM;
    newPlayer->logSize = STARTING_CARD_NUM;
}

//drew the first card of the game
void drawFirstCard(int* ptype, int* pcolor)
{
    int type,color;
    type = rand()%9 +1;
    color = rand()%4 + 1;

    *ptype = type;
    *pcolor = color;
}

//drew a random type and color for onr card
void drawCard(int* ptype, int* pcolor,STATISTICS stats[])
{
    int type,color;
    type = rand()%14 +1;
    color = rand()%4 + 1;
    if(type == 14)
        color = -1;
    stats[type].count++;
    *ptype = type;
    *pcolor = color;
}

// prints a single card
void printCard(int type, int color)
{
    char cardType[10];
    char cardColor[2]=" ";

    switch (type)
    {
        case 1:
            strcpy(cardType,"  1   ");
            break;
        case 2:
            strcpy(cardType,"  2   ");
            break;
        case 3:
            strcpy(cardType,"  3   ");
            break;
        case 4:
            strcpy(cardType,"  4   ");
            break;
        case 5:
            strcpy(cardType,"  5   ");
            break;
        case 6:
            strcpy(cardType,"  6   ");
            break;
        case 7:
            strcpy(cardType,"  7   ");
            break;
        case 8:
            strcpy(cardType,"  8   ");
            break;
        case 9:
            strcpy(cardType,"  9   ");
            break;
        case 10:
            strcpy(cardType,"  +   ");
            break;
        case 11:
            strcpy(cardType," STOP ");
            break;
        case 12:
            strcpy(cardType," <->  ");
            break;
        case 13:
            strcpy(cardType," TAKI ");
            break;
        case 14:
            strcpy(cardType,"COLOR ");
            break;
        default:
            break;
    }


    switch(color)
    {
        case 1:
            strcpy(cardColor,"Y");
            break;
        case 2:
            strcpy(cardColor,"R");
            break;
        case 3:
            strcpy(cardColor,"B");
            break;
        case 4:
            strcpy(cardColor,"G");
            break;
        default:
            strcpy(cardColor," ");
            break;
    }


    printf("*********\n"
           "*       *\n"
           "* %s*\n"
           "*   %s   *\n"
           "*       *\n"
           "*********", cardType,cardColor);
}

//prints a single player cards array
void printPlayersCards(PLAYER *players, int playerTurn)
{
    int i;
    printf("%s's turn:\n\n",players[playerTurn].name);

    for(i=0; i< players[playerTurn].logSize;i++)
    {
        printf("Card #%d:\n", i+1);
        printCard(players[playerTurn].cards[i].type, players[playerTurn].cards[i].color);
        printf("\n\n");
    }
}

// creates a new CARD array for a player in case that he needs to drew card while his card array is full
CARD * myRealloc(CARD * playersCard,int * pPsize, int logSize)
{
    int i;
    int phySize = *pPsize;
    CARD *tmp = NULL;

    phySize*=2;

    tmp = (CARD*) malloc(phySize*sizeof(CARD));
    if(tmp == NULL)
    {
        printf("allocation failed!!\n");
        exit(1);
    }
    for(i=0;i<logSize;i++)
    {
        tmp[i]=playersCard[i];
    }
    free(playersCard);
    playersCard=tmp;
    *pPsize = phySize;
    return playersCard;

}

//set the base stats array- type.
void setStatistic(STATISTICS arr[])
{
    int i;
    for(i=0;i<NUM_OF_CARDS;i++)
    {
        arr[i].type = i+1;
        arr[i].count=0;
    }
}

//gets the desired color from the user.
int colorCard()
{
    int changeToColor;
    printf("Please enter your color choice:\n"
           "1 - Yellow\n"
           "2 - Red\n"
           "3 - Blue\n"
           "4 - Green\n");
    scanf("%d", &changeToColor);

    while(changeToColor < 1 || changeToColor > 4)
    {
        printf("Invalid choice! Try again.\n");
        scanf("%d",&changeToColor);
    }
    return changeToColor;
}

//remove card from players cards array
CARD *removeCardFromPlayer(CARD * playersHand, int cardToRemove, int *pLogSize, int phySize)
{
    int logSize = *pLogSize;

    int i;
    CARD * tmp = NULL;
    tmp = (CARD*) malloc(phySize * sizeof(CARD));

    if(tmp == NULL)
    {
        printf("allocation failed!!\n");
        exit(1);
    }

    playersHand[cardToRemove-1] = playersHand[logSize-1];
    logSize--;
    for(i = 0; i< logSize; i++)
    {
        tmp[i] = playersHand[i];
    }
    free(playersHand);
    playersHand = tmp;

    *pLogSize = logSize;
    return playersHand;
}

//a single round of the game
bool roundOfPlay(PLAYER players[], int size ,int i, CARD* upperCard,int * pplayersChoice,STATISTICS stats[])
{
    int playersChoice,changeToColor, takiFall;
    printPlayersCards(players,i);
    printf("Please enter 0 if you want to take a card from the deck\n"
           "or 1-%d if you want to put one of your cards in the middle:\n", players[i].logSize);
    scanf("%d",&playersChoice);
    while(isChoiceValid(players[i].cards, playersChoice,*upperCard, players[i].logSize,players[i].physSize) == false)
    {
        printf("Invalid choice! Try again.\n");
        printf("Please enter 0 if you want to take a card from the deck\n"
               "or 1-%d if you want to put one of your cards in the middle:\n", players[i].logSize);
        scanf("%d",&playersChoice);
    }
    if(playersChoice == 0)
    {
        players[i].cards = addCardToPlayerHand(players[i].cards, &players[i].logSize, &players[i].physSize,stats);
    }
    else if((players[i].cards[playersChoice-1].color == upperCard->color || players[i].cards[playersChoice-1].type == upperCard->type) && ((players[i].cards[playersChoice-1].type < 10 && players[i].cards[playersChoice-1].type > 1)||players[i].cards[playersChoice-1].type ==CHANGE_DIRECTION))
    {
        upperCard->type = players[i].cards[playersChoice-1].type;
        upperCard->color = players[i].cards[playersChoice-1].color;
        players[i].cards = removeCardFromPlayer(players[i].cards, playersChoice, &players[i].logSize, players[i].physSize);
        printf("\n");
    }
    else if(players[i].cards[playersChoice-1].type == PLUS && players[i].cards[playersChoice-1].color == upperCard->color)//+
    {
        upperCard->type = PLUS;
        upperCard->color = players[i].cards[playersChoice-1].color;
        players[i].cards = removeCardFromPlayer(players[i].cards, playersChoice, &players[i].logSize, players[i].physSize);
        if(players[i].logSize == 0)//if you put '+' as last card you need to draw another card from the deck
        {
            players[i].cards = addCardToPlayerHand(players[i].cards, &players[i].logSize, &players[i].physSize,stats);
        }
    }
    else if(players[i].cards[playersChoice-1].type == STOP && players[i].cards[playersChoice-1].color == upperCard->color)//STOP
    {
        upperCard->type = STOP;
        upperCard->color = players[i].cards[playersChoice-1].color;
        players[i].cards = removeCardFromPlayer(players[i].cards, playersChoice, &players[i].logSize, players[i].physSize);
        if(players[i].logSize == 0 && size == 2)//if you put STOP as last card and there only two players you need to draw another card from the deck
        {
            players[i].cards = addCardToPlayerHand(players[i].cards, &players[i].logSize, &players[i].physSize,stats);
        }
    }
    else if(players[i].cards[playersChoice-1].type == TAKI && players[i].cards[playersChoice-1].color == upperCard->color)//TAKI
    {
        upperCard->type = TAKI;
        upperCard->color = players[i].cards[playersChoice-1].color;
        players[i].cards = removeCardFromPlayer(players[i].cards, playersChoice, &players[i].logSize, players[i].physSize);
        printf("Upper card:\n");
        printCard(upperCard->type, upperCard->color);
        printf("\n");

        takiFall = takiCard(players[i].logSize);

        while(takiFall != 0)
        {
            if(players[i].cards[takiFall-1].color == upperCard->color)
            {
                upperCard->type = players[i].cards[takiFall-1].type;
                players[i].cards = removeCardFromPlayer(players[i].cards, takiFall, &players[i].logSize, players[i].physSize);
            }
            printf("Upper card:\n");
            printCard(upperCard->type, upperCard->color);
            printf("\n");
            takiFall = takiCard(players[i].logSize);
        }
        playersChoice = takiFall;
    }

    else if(players[i].cards[playersChoice-1].type == COLOR)
    {
        changeToColor = colorCard();
        upperCard->type = COLOR;
        upperCard->color = changeToColor;
        players[i].cards = removeCardFromPlayer(players[i].cards, playersChoice, &players[i].logSize, players[i].physSize);
        printf("\n");
    }


    *pplayersChoice = playersChoice;

    if(players[i].logSize == 0)
    {
        return true;
    }
    else return false;
}

//add card to players card array
CARD *addCardToPlayerHand(CARD * playersHand, int *pLogSize, int *pphySize,STATISTICS stats[])
{
    int logSize = *pLogSize;
    int phySize = *pphySize;
    int type,color;

    drawCard(&type, &color,stats);

    if(logSize < phySize)
    {
        playersHand[logSize].type = type;
        playersHand[logSize].color = color;
        logSize++;
    }
    else
    {
        playersHand = myRealloc(playersHand, &phySize,logSize);
        playersHand[logSize].type = type;
        playersHand[logSize].color = color;
        logSize++;
    }

    *pLogSize = logSize;
    *pphySize = phySize;
    return playersHand;
}

//checks if players choice of card is valid
bool isChoiceValid(CARD* playersHand, int playersChoice,CARD upperCard, int logSize, int phySize)
{
    bool valid;
    if(playersChoice == 0 || playersHand[playersChoice-1].type == COLOR)
        valid = true;
    else if(playersChoice < 0|| playersChoice>logSize || (playersHand[playersChoice-1].color != upperCard.color && playersHand[playersChoice-1].type != upperCard.type))
        valid = false;
    else valid =true;
    return valid;
}

//operates the taki "fall"
int takiCard( int logSize)
{
    int playersChoice;

    printf("Please enter 0 if you want to finish your turn\n"
           "or 1-%d if you want to put one of your cards in the middle:\n", logSize);
    scanf("%d",&playersChoice);

    while(playersChoice !=0 && playersChoice < 1 && playersChoice > logSize)
    {
        printf("Invalid choice! Try again.\n");
        printf("Please enter 0 if you want to finish your turn\n"
               "or 1-%d if you want to put one of your cards in the middle:\n", logSize);
        scanf("%d",&playersChoice);
    }
    return playersChoice;
}

//sort the stats array in n*log(n)
void mergerSort(STATISTICS stats[], int size)
{
    STATISTICS * tempArr = NULL;
    if(size<=1)
        return;

    mergerSort(stats, size/2);
    mergerSort(stats + size/2, size-(size/2));

    tempArr = merge(stats,size/2,stats + size/2,size-(size/2));

    if(tempArr != NULL)
    {
        copyArr(stats,tempArr,size);
        free(tempArr);
    }
    else
    {
        printf("Memory allocation failure!!\n");
        exit(1);
    }
}

//gets two arrays and merges them sorted into oa new one, then returns it
STATISTICS * merge(STATISTICS a1[], int size1, STATISTICS a2[], int size2)
{
    int ind1,ind2,resInd;
    STATISTICS *res = (STATISTICS *)malloc((size1 + size2) * sizeof(STATISTICS));

    if(res)
    {
        ind1=ind2=resInd=0;

        while((ind1<size1) && (ind2<size2))
        {
            if(a1[ind1].count <= a2[ind2].count)
            {
                res[resInd] = a1[ind1];
                ind1++;
            }
            else{
                res[resInd] = a2[ind2];
                ind2++;
            }
            resInd++;
        }
        while(ind1<size1)
        {
            res[resInd] = a1[ind1];
            ind1++;
            resInd++;
        }
        while(ind2< size2)
        {
            res[resInd] = a2[ind2];
            ind2++;
            resInd++;
        }
    }
    return res;
}

//copy an array into a dest array
void copyArr(STATISTICS dest[], STATISTICS src[], int size)
{
    int i;

    for(i =0; i< size; i++)
    {
        dest[i] = src[i];
    }
}

//prints the stats array
void printStatistic(STATISTICS statistics[], int size)
{
    int i;
    char cardType[10];
    printf("************ Game Statistic ************\n");
    printf("Card # | Frequency\n\n__________________\n");

    for(i=NUM_OF_CARDS-1;i>0;i--)
    {
        switch (statistics[i].type)
        {
            case 1:
                strcpy(cardType,"  1   ");
                break;
            case 2:
                strcpy(cardType,"  2   ");
                break;
            case 3:
                strcpy(cardType,"  3   ");
                break;
            case 4:
                strcpy(cardType,"  4   ");
                break;
            case 5:
                strcpy(cardType,"  5   ");
                break;
            case 6:
                strcpy(cardType,"  6   ");
                break;
            case 7:
                strcpy(cardType,"  7   ");
                break;
            case 8:
                strcpy(cardType,"  8   ");
                break;
            case 9:
                strcpy(cardType,"  9   ");
                break;
            case 10:
                strcpy(cardType,"  +   ");
                break;
            case 11:
                strcpy(cardType," STOP ");
                break;
            case 12:
                strcpy(cardType," <->  ");
                break;
            case 13:
                strcpy(cardType," TAKI ");
                break;
            case 14:
                strcpy(cardType,"COLOR ");
                break;
            default:
                break;
        }
        printf("%s|    %d    \n",cardType,statistics[i].count);
    }
}
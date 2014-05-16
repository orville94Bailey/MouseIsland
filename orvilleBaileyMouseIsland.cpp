#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
#include <stdlib.h>




using namespace std;


class animal
{
public:
    int getX()
        {
            return x;
        }
    int getY()
        {
            return y;
        }
    void setX(int X)
        {
            x = X;
        }
    void setY(int Y)
        {
            y = Y;
        }
    bool hasGone()
        {
            isGone = true;
        }
private:
    int x, y;
    bool isGone = false;
};

class Mouse : public animal
{
public:

    void hasStarved();
    void wasDrowned();
    void foundHole();
    void gotEaten();
    bool isDead();
    int timeLeft();
private:
    int starveTimer = 100;
    bool isStarved = false, isDrowned = false, inHole = false,
         isEaten = false, dead = false;
};

class Cat : public animal
{

};

class Simulator
{
public:
    void readFile();
    void printMap();
    int getRunTimes();
    void findMouse();
    void findCat();
    void moveMouse();
    void moveCat();
private:
    Mouse   Jerry;
    Cat     Tom;
    int islandMap[20][20]
    ,   RunTimes
    ,   width
    ,   height;
    string MapName;
};

int main()///////////////////////////////////////////////////////////////////MAIN/////////////////////////////////////////////////////////
{
    int seed, island[20][20];
    seed = time(NULL);
    srand(seed);
    Simulator test;
    test.readFile();
    test.printMap();

}


////////////////////////////////////////////////////////////////////////////Functions//////////////////////////////////////////////////////
void Simulator::readFile()
{
    string fileToRead="";
    int x,y, islandArray[20][20];
    fstream ReadFile,WriteFile;

    for(int x=0;x<20;x++)
    {
        for(int y=0;y<20;y++)
        {
            islandArray[x][y]=0;
        }
    }

    cout<<"Enter the filename: ";
    cin>>fileToRead;
    ReadFile.open(fileToRead.c_str());
    getline(ReadFile,MapName);
    ReadFile>>RunTimes;
    ReadFile>>x;
    ReadFile>>y;

    width = x;
    height = y;



    for(int xpos=0;xpos<x;xpos++)
    {
        for(int ypos=0;ypos<y;ypos++)
        {
            ReadFile>>islandArray[xpos][ypos];
        }
    }

    for(int xpos=0;xpos<x;xpos++)
    {
        for(int ypos=0;ypos<y;ypos++)
        {
            islandMap[xpos][ypos]=islandArray[xpos][ypos];
        }
    }

}

void Simulator::printMap()
{
    cout<<MapName<<endl;
    for(int xpos=0;xpos<width;xpos++)
    {
        for(int ypos=0;ypos<height;ypos++)
        {
            if(islandMap[xpos][ypos]!=-1)
            {
                cout<<" "<<islandMap[xpos][ypos];
            }
            else
            {
                cout<<islandMap[xpos][ypos];
            }

        }
        cout<<endl;
    }
}

int Simulator::getRunTimes()
{
    return RunTimes;
}

void Simulator::findCat()
{
    for(int xpos=0;xpos<width;xpos++)
    {
        for(int ypos=0;ypos<height;ypos++)
        {
            if(islandMap[xpos][ypos]==2)
            {
                Tom.setX(xpos);
                Tom.setY(ypos);
            }

        }
    }
}

void Simulator::findMouse()
{
    for(int xpos=0;xpos<width;xpos++)
    {
        for(int ypos=0;ypos<height;ypos++)
        {
            if(islandMap[xpos][ypos]==1)
            {
                Jerry.setX(xpos);
                Jerry.setY(ypos);
            }

        }
    }
}

void Simulator::moveCat()
{
    bool valid=false;
    int direction;

    do
    {
        direction = rand()%4;
        if((direction==0&&Tom.getY()==0)||
            (direction==1&&Tom.getX()==width-1)||
            (direction==2&&Tom.getY()==height-1)||
            (direction==3&&Tom.getX()==0))
        {

        }
        else
        {
            valid = true;
        }
    }while(!valid);

    if((Tom.getY()==0)||(Tom.getX()==width-1)||
        (Tom.getY()==height-1)||(Tom.getX()==0))
    {
        Tom.hasGone();
    }

    if(Tom.getX()==Jerry.getX())
    {
        if(Tom.getY()==Jerry.getY())
        {
            Jerry.gotEaten();
        }
    }


    //0 is up
    //1 is right
    //2 is down
    //3 is left




}

void Simulator::moveMouse()
{
    int direction;
    direction = rand()%4;
    //0 is up
    //1 is right
    //2 is down
    //3 is left
}

////////////Mouse Functions/////////////////////////////////////////////////
void Mouse::hasStarved()
{
    isStarved = true;
    starveTimer = -1;
    dead = true;
}

void Mouse::wasDrowned()
{
    isDrowned = true;
    starveTimer = -1;
    dead = true;
}

void Mouse::foundHole()
{
    starveTimer = -1;
    inHole = true;
}

void Mouse::gotEaten()
{
    isEaten = true;
    starveTimer = -1;
    dead = true;
}

bool Mouse::isDead()
{
    return dead;
}

int Mouse::timeLeft()
{
    return starveTimer;
}

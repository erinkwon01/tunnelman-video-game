#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <list>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const int GO_UP = 0;
const int GO_DOWN = 1;
const int GO_RIGHT = 2;
const int GO_LEFT = 3;

class Point
{
public:
    Point(int x, int y, int distance) : col(x), row(y), dist(distance) {}
    int getCol() {
        return col;
    }
    int getRow() {
        return row;
    }
    int getDist() {
        return dist;
    }
    void setCol(int colNum) {
        col = colNum;
    }
    void setRow(int rowNum) {
        row = rowNum;
    }
    void setDist(int distNum) {
        dist = distNum;
    }
    void setDir(int direc) {
        dir = direc;
    }
    int getDir() {
        return dir;
    }
    
private:
    int col;
    int row;
    int dist;
    int dir;
};

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
        : GameWorld(assetDir), didWorldChange(false), protesterTick(0)
    {
    }

    virtual ~StudentWorld() {}
    
    Earth* getEarth(int x, int y);
    
    void squirtAction(Squirt* squirtObj);
    
    void sonarView(int x, int y);
    
    void tunnelManInventory(int action);
    
    bool isCompletedLvl();
    
    bool blockingBoulder(int x, int y);
    
    bool blockingEarth(int x, int y);
    
    bool facingTunnelMan(int Px, int Py, GraphObject::Direction dir);
    
    void annoyTunnelMan(int action);
    
    void annoyProtester(int x, int y, int action);
    
    void retrieveGold(int x, int y);
    
    bool tunnelManNear(int x, int y);
    
    bool canProtesterTurn(int x, int y);
    
    bool boulderTunnelManNear(int x, int y);
    
    bool tunnelManPickUp(int x, int y);
    
    bool tunnelManHorizontalYLine(int Px, int Py);
    
    bool tunnelManVerticalXLine(int Px, int Py);
    
    GraphObject::Direction regProtesterTM(int Px, int Py);
    
    void setExitDirDisArrays(int x, int y, int world[64][61]);
    
    void setTMDirDisArrays(int x, int y, int world[64][61]);
    
    int getTMx() {
        return tunnelManPtr->getX();
    }
    
    int getTMy() {
        return tunnelManPtr->getY();
    }
    
    void placeNuggetOnGround(int x, int y);
    
    bool tunnelManHere(int x, int y);
    
    bool protesterNear(int x, int y);
    
    bool isHardCore();
    
    void removeDeadGameObjects();
    
    int numBoulders();
    
    int numGold();
    
    int numOil();
    
    void setDisplayText();
    
    bool getWorldChange() {
        return didWorldChange;
    }
    
    void setChangeWorld(bool shouldIChange) {
        didWorldChange = shouldIChange;
    }
    
    GraphObject::Direction getDirectionToExit(int Px, int Py);
    GraphObject::Direction getDirectionToTM(int Px, int Py);
    int getDistanceToTM(int Px, int Py);
    
    std::string formatString(int level, int lives, int health, int squirts, int gold, int barrelsLeft, int sonar, int score);
    
    void eraseEarth(int x, int y) // calls when tunnelMan digs through Earth objects
    {
        getEarth(x, y)->setVisible(false);
        getEarth(x, y)->setEvisible(false);
    }
    
    virtual int init();

    virtual int move();

    virtual void cleanUp();

private:
    std::vector<Actor*> vectorOfActors; // vector of pointers to Actor objects
    TunnelMan* tunnelManPtr; // pointer to TunnelMan object
    Earth* earthPtrs[VIEW_WIDTH][VIEW_HEIGHT]; // 2D vector for Earth layout
    std::vector<Goodies*> vectorOfGoodies; // vector of pointers to Goodies objects
    std::vector<Boulder*> vectorOfBoulders; // vector of pointers to Boulder objects
    std::vector<Protester*> vectorOfProtesters; // vector of pointers to Protester objects
    GraphObject::Direction exitDirectionArray[64][61];
    int exitDistanceArray[64][61];
    GraphObject::Direction TMDirectionArray[64][61];
    int TMDistanceArray[64][61];
    bool didWorldChange;
    int protesterTick;
};

#endif // STUDENTWORLD_H_

#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <queue>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

Earth* StudentWorld::getEarth(int x, int y)
{
    return earthPtrs[x][y];
}

bool StudentWorld::blockingBoulder(int x, int y)
{
    for (int i = 0; i < vectorOfBoulders.size(); i++)
    {
        if (vectorOfBoulders[i]->isBVisibleCheck() == true)
        {
            if (x >= vectorOfBoulders[i]->getX() && x <= vectorOfBoulders[i]->getX()+3 && y >= vectorOfBoulders[i]->getY() && y <= vectorOfBoulders[i]->getY()+3)
            {
                return true; // true as in there is a boulder blocking
            }
        }
    }
    return false;
}

bool StudentWorld::blockingEarth(int x, int y)
{
    if (earthPtrs[x][y] == nullptr || earthPtrs[x][y]->isEVisibleCheck() == false) {
        return false;
    }
    return true;
}

bool StudentWorld::canProtesterTurn(int x, int y)
{
    if (x < 0 || x > 60) {
        return false;
    }
    if (y < 0 || y > 60) {
        return false;
    }
    for (int col = x; col < x+4; col++) {
        for (int row = y; row < y+4; row++) {
            if (earthPtrs[col][row] != nullptr && earthPtrs[col][row]->isEVisibleCheck() == true) {
                return false;
            }
        }
    }
    return true;
}

bool StudentWorld::tunnelManHere(int x, int y) // tunnelMan's location
{
    if (tunnelManPtr->getX() == x && tunnelManPtr->getY() == y) {
        return true;
    }
    return false;
}

bool StudentWorld::tunnelManNear(int x, int y)
{
    int xDiffSquared = (x-(tunnelManPtr->getX()))*(x-(tunnelManPtr->getX()));
    int yDiffSquared = (y-(tunnelManPtr->getY()))*(y-(tunnelManPtr->getY()));
    if (xDiffSquared+yDiffSquared <= 16)
    {
        return true;
    }
    return false;
}

bool StudentWorld::tunnelManPickUp(int x, int y)
{
    int xDiffSquared = (x-(tunnelManPtr->getX()))*(x-(tunnelManPtr->getX()));
    int yDiffSquared = (y-(tunnelManPtr->getY()))*(y-(tunnelManPtr->getY()));
    if (xDiffSquared+yDiffSquared <= 9)
    {
        return true;
    }
    return false;
}

bool StudentWorld::facingTunnelMan(int Px, int Py, GraphObject::Direction dir)
{
    if (dir == GraphObject::Direction::right) {
        if (tunnelManPtr->getX() >= Px) {
            return true;
        }
        return false;
    }
    if (dir == GraphObject::Direction::left) {
        if (tunnelManPtr->getX() <= Px) {
            return true;
        }
        return false;
    }
    if (dir == GraphObject::Direction::up) {
        if (tunnelManPtr->getY() >= Py) {
            return true;
        }
        return false;
    }
    if (dir == GraphObject::Direction::down) {
        if (tunnelManPtr->getY() <= Py) {
            return true;
        }
        return false;
    }
    return false;
}

bool StudentWorld::tunnelManHorizontalYLine(int Px, int Py) {
    if (tunnelManPtr->getY() == Py) {
        if (tunnelManPtr->getX() < Px) {
            for (int i = tunnelManPtr->getX(); i < Px; i++) {
                for (int j = Py; j < Py+4; j++) {
                    if (earthPtrs[i][j] != nullptr && earthPtrs[i][j]->isEVisibleCheck() == true) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < vectorOfBoulders.size(); i++) {
                if (vectorOfBoulders[i]->getX() > tunnelManPtr->getX() && vectorOfBoulders[i]->getX() < Px) {
                    if (vectorOfBoulders[i]->getY() < Py+4 && vectorOfBoulders[i]->getY() > Py-4 ) {
                        return false;
                    }
                }
            }
            return true;
        }
        if (tunnelManPtr->getX() > Px) {
            for (int i = Px; i < tunnelManPtr->getX(); i++) {
                for (int j = Py; j < Py+4; j++) {
                    if (earthPtrs[i][j] != nullptr && earthPtrs[i][j]->isEVisibleCheck() == true) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < vectorOfBoulders.size(); i++) {
                if (vectorOfBoulders[i]->getX() < tunnelManPtr->getX() && vectorOfBoulders[i]->getX() > Px) {
                    if (vectorOfBoulders[i]->getY() < Py+4 && vectorOfBoulders[i]->getY() > Py-4 ) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool StudentWorld::tunnelManVerticalXLine(int Px, int Py) {
    if (tunnelManPtr->getX() == Px) {
        if (tunnelManPtr->getY() < Py) {
            for (int j = tunnelManPtr->getY(); j < Py; j++) {
                for (int i = Px; i < Px+4; i++) {
                    if (earthPtrs[i][j] != nullptr && earthPtrs[i][j]->isEVisibleCheck() == true) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < vectorOfBoulders.size(); i++) {
                if (vectorOfBoulders[i]->getY() > tunnelManPtr->getY() && vectorOfBoulders[i]->getY() < Py) {
                    if (vectorOfBoulders[i]->getX() < Px+4 && vectorOfBoulders[i]->getX() > Px-4 ) {
                        return false;
                    }
                }
            }
            return true;
        }
        if (tunnelManPtr->getX() > Py) {
            for (int j = Py; j < tunnelManPtr->getY(); j++) {
                for (int i = Px; i < Px+4; i++) {
                    if (earthPtrs[i][j] != nullptr && earthPtrs[i][j]->isEVisibleCheck() == true) {
                        return false;
                    }
                }
            }
            for (int i = 0; i < vectorOfBoulders.size(); i++) {
                if (vectorOfBoulders[i]->getY() < tunnelManPtr->getY() && vectorOfBoulders[i]->getY() > Py) {
                    if (vectorOfBoulders[i]->getX() < Px+4 && vectorOfBoulders[i]->getX() > Px-4 ) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

void StudentWorld::annoyTunnelMan(int action) {
    if (action == REG_PROTESTER_SHOUT) {
        tunnelManPtr->hitPointsDecrement(2);
    }
    if (action == BOULDER_FALL) {
        tunnelManPtr->hitPointsDecrement(100);
    }
    if (action == PRESSED_ESCAPE) {
        tunnelManPtr->hitPointsDecrement(100);
    }
    if (tunnelManPtr->getHitPoints() <= 0) {
        tunnelManPtr->setVisible(false);
        tunnelManPtr->setDead(true);
        decLives();
    }
}



void StudentWorld::annoyProtester(int x, int y, int action) {
    if (action == SQUIRT_ATTACK) {
        for (int i = 0; i < vectorOfProtesters.size(); i++)
        {
            int xDiffSquared = (x-(vectorOfProtesters[i]->getX()))*(x-(vectorOfProtesters[i]->getX()));
            int yDiffSquared = (y-(vectorOfProtesters[i]->getY()))*(y-(vectorOfProtesters[i]->getY()));
            if (xDiffSquared+yDiffSquared <= 9 && vectorOfProtesters[i]->getLeaveOil() == false)
            {
                vectorOfProtesters[i]->decrementHitPoints(2);
                if (vectorOfProtesters[i]->getHitPoints() <= 0) {
                    vectorOfProtesters[i]->setStunnedStatus(false);
                    vectorOfProtesters[i]->setLeaveOil(true);
                    playSound(SOUND_PROTESTER_GIVE_UP);
                    if (vectorOfProtesters[i]->isRegular() == true) {
                        increaseScore(100);
                    }
                    if (vectorOfProtesters[i]->isRegular() == false) {
                        increaseScore(250);
                    }
                    vectorOfProtesters[i]->setRandomTicks(0);
                }
                else if (vectorOfProtesters[i]->getLeaveOil() == false) {
                    playSound(SOUND_PROTESTER_ANNOYED);
                    vectorOfProtesters[i]->setStunnedStatus(true);
                    vectorOfProtesters[i]->setRandomTicks(1);
                }
            }
        }
    }
    if (action == BOULDER_FALL) {
        for (int i = 0; i < vectorOfProtesters.size(); i++)
        {
            int xDiffSquared = (x-(vectorOfProtesters[i]->getX()))*(x-(vectorOfProtesters[i]->getX()));
            int yDiffSquared = (y-(vectorOfProtesters[i]->getY()))*(y-(vectorOfProtesters[i]->getY()));
            if (xDiffSquared+yDiffSquared <= 9)
            {
                vectorOfProtesters[i]->decrementHitPoints(100);
                if (vectorOfProtesters[i]->getHitPoints() <= 0 && vectorOfProtesters[i]->getLeaveOil() == false) {
                    playSound(SOUND_PROTESTER_GIVE_UP);
                    increaseScore(500);
                    vectorOfProtesters[i]->setLeaveOil(true);
                    vectorOfProtesters[i]->setRandomTicks(0);
                }
            }
        }
    }
    
}

bool StudentWorld::protesterNear(int x, int y) {
    for (int i = 0; i < vectorOfProtesters.size(); i++)
    {
        int xDiffSquared = (x-(vectorOfProtesters[i]->getX()))*(x-(vectorOfProtesters[i]->getX()));
        int yDiffSquared = (y-(vectorOfProtesters[i]->getY()))*(y-(vectorOfProtesters[i]->getY()));
        if (xDiffSquared+yDiffSquared <= 9 && vectorOfProtesters[i]->getLeaveOil() == false)
        {
            return true;
        }
    }
    return false;
}

void StudentWorld::retrieveGold(int x, int y) {
    for (int i = 0; i < vectorOfProtesters.size(); i++)
    {
        int xDiffSquared = (x-(vectorOfProtesters[i]->getX()))*(x-(vectorOfProtesters[i]->getX()));
        int yDiffSquared = (y-(vectorOfProtesters[i]->getY()))*(y-(vectorOfProtesters[i]->getY()));
        if (xDiffSquared+yDiffSquared <= 9 && vectorOfProtesters[i]->getLeaveOil() == false)
        {
            if (vectorOfProtesters[i]->isRegular() == true) {
                increaseScore(25);
                vectorOfProtesters[i]->setLeaveOil(true);
            }
            else if (vectorOfProtesters[i]->isRegular() == false) {
                increaseScore(50);
                vectorOfProtesters[i]->setStunnedStatus(true);
            }
        }
    }
}

bool StudentWorld::isHardCore() {
    int probabilityOfHardcore = fmin(90, (getLevel() * 10) + 30);
    int checker = rand() % 101;
    if (checker <= probabilityOfHardcore) {
        return true;
    }
    else {
        return false;
    }
}

void StudentWorld::sonarView(int x, int y) {
    for (int i = 0; i < vectorOfActors.size(); i++)
    {
        int xDiffSquared = (x-(vectorOfActors[i]->getX()))*(x-(vectorOfActors[i]->getX()));
        int yDiffSquared = (y-(vectorOfActors[i]->getY()))*(y-(vectorOfActors[i]->getY()));
        if (xDiffSquared+yDiffSquared <= 141)
        {
            vectorOfActors[i]->setVisible(true);
        }
    }
    for (int i = 0; i < vectorOfGoodies.size(); i++) {
        int xDiffSquared = (x-(vectorOfGoodies[i]->getX()))*(x-(vectorOfGoodies[i]->getX()));
        int yDiffSquared = (y-(vectorOfGoodies[i]->getY()))*(y-(vectorOfGoodies[i]->getY()));
        if (xDiffSquared+yDiffSquared <= 141)
        {
            vectorOfGoodies[i]->setGoodiesVisible(true);
        }
    }
    playSound(SOUND_SONAR);
}

void StudentWorld::placeNuggetOnGround(int x, int y) {
    Goodies* tempPtr = new GoldNugget(x, y, this, true, false, false);
    vectorOfActors.push_back(tempPtr);
    vectorOfGoodies.push_back(tempPtr);
}

void StudentWorld::tunnelManInventory(const int action) {
    if (action == 0) // pick up goldnug
    {
        tunnelManPtr->incrementGold();
    }
    if (action == 1) // pick up sonar
    {
        tunnelManPtr->incrementSonar();
    }
    if (action == 2) // pick up water
    {
        tunnelManPtr->incrementWater();
    }
    if (action == 3) // pick up oil
    {
        tunnelManPtr->decrementOil();
    }
}

bool StudentWorld::isCompletedLvl() {
    if (tunnelManPtr->getOil() < 1) {
        return true;
    }
    return false;
}

void StudentWorld::squirtAction(Squirt *squirtObj) {
    vectorOfActors.push_back(squirtObj); // adding to vector of actors
    vectorOfGoodies.push_back(squirtObj); // adding to vector of goodies
}

int StudentWorld::numBoulders() {
    return fmin(getLevel()/2 + 2, 9);
}

int StudentWorld::numGold() {
    return fmax(5-getLevel()/2, 2);
}

int StudentWorld::numOil() {
    return fmin(2+getLevel(), 21);
}

int StudentWorld::init()
{
    tunnelManPtr = new TunnelMan(this);
    int column = 0;
    int row = 0;
    while (column < 64) // filling out the arena with Earth objects, leaving room for tunnel
    {
        if (column >= 30 && column <= 33) // only rows 4-59 are free
        {
            row = 0;
            while (row < 4)
            {
                earthPtrs[column][row] = new Earth(column, row, this);
                // set the corresponding Earth object (to the coordinate) pointed to by the pointer to setVisible(true);
                row++;
            }
            while (row >= 4 && row < 64) // setting tunnel as nullptr to prevent bad access
            {
                earthPtrs[column][row] = nullptr;
                row++;
            }
        }
        else // all rows (from 0 to 59) in these columns are filled
        {
            row = 0;
            while (row <= 59)
            {
                earthPtrs[column][row] = new Earth(column, row, this);
                // set the corresponding Earth object (to the coordinate) pointed to by the pointer to setVisible(true);
                row++;
            }
            while (row >= 60 && row < 64)
            {
                earthPtrs[column][row] = nullptr;
                row++;
            }
        }
        column++;
    }
    int B = numBoulders();
    int G = numGold();
    int L = numOil();
    int i = 0;
    
    while (i < B)
    {
        int colB = rand() % 61;
        int rowB = rand() % 37 + 20;
        bool canExist = true;
        for (int j = 0; j < vectorOfActors.size(); j++) // going through each actor object to check if another one exists within 6 squares
        {
            int colDiffSquared = (colB-vectorOfActors[j]->getX())*(colB-vectorOfActors[j]->getX());
            int rowDiffSquared = (rowB-vectorOfActors[j]->getY())*(rowB-vectorOfActors[j]->getY());
            if (colDiffSquared+rowDiffSquared < 36) {
                canExist = false;
            }
        }
        if (colB >= 27 && colB <= 33 && rowB >= 4 && rowB < 64) // accounting for tunnel
        {
            canExist = false;
        }
        if (canExist == true)
        {
            Boulder* tempPtr = new Boulder(colB, rowB, this);
            vectorOfActors.push_back(tempPtr);
            vectorOfBoulders.push_back(tempPtr);
            B--;
            int checkEarthCol = colB;
            int checkEarthRow = rowB;
            while (checkEarthCol < colB+4) // check 4x4 box
            {
                while (checkEarthRow < rowB+4)
                {
                    if (getEarth(checkEarthCol, checkEarthRow) != nullptr && getEarth(checkEarthCol, checkEarthRow)->isEVisibleCheck() == true) // there exists a visible earth object,
                    {
                        getEarth(checkEarthCol, checkEarthRow)->setVisible(false); // make it disappear
                        getEarth(checkEarthCol, checkEarthRow)->setEvisible(false);
                    }
                    checkEarthRow++;
                }
                checkEarthRow = rowB;
                checkEarthCol++;
            }
        }
        else {
            continue;
        }
    }
    
    i = 0;
    
    while (i < G)
    {
        int colG = rand() % 61;
        int rowG = rand() % 57;
        bool canExist = true;
        for (int j = 0; j < vectorOfActors.size(); j++) // going through each actor object to check if another one exists within 6 squares
        {
            int colDiffSquared = (colG-vectorOfActors[j]->getX())*(colG-vectorOfActors[j]->getX());
            int rowDiffSquared = (rowG-vectorOfActors[j]->getY())*(rowG-vectorOfActors[j]->getY());
            if (colDiffSquared+rowDiffSquared < 36) {
                canExist = false;
            }
        }
        if (canExist == true)
        {
            int checkEarthCol = colG;
            int checkEarthRow = rowG;
            while (checkEarthCol < colG+4) // check 4x4 box
            {
                while (checkEarthRow < rowG+4)
                {
                    if (getEarth(checkEarthCol, checkEarthRow) == nullptr || getEarth(checkEarthCol, checkEarthRow)->isEVisibleCheck() == false) // there does not exist a visible Earth object
                    {
                        canExist = false;
                    }
                    if (canExist == false)
                    {
                        break;
                    }
                    checkEarthRow++;
                }
                checkEarthRow = rowG;
                checkEarthCol++;
            }
        }
        if (canExist == true)
        {
            Goodies* tempPtr = new GoldNugget(colG, rowG, this, false, true, true);
            vectorOfActors.push_back(tempPtr);
            vectorOfGoodies.push_back(tempPtr);
            G--;
        }
        else {
            continue;
        }
    }
    
    i = 0;
    
    while (i < L)
    {
        int colL = rand() % 61;
        int rowL = rand() % 57;
        bool canExist = true;
        for (int j = 0; j < vectorOfActors.size(); j++) // going through each actor object to check if another one exists within 6 squares
        {
            int colDiffSquared = (colL-vectorOfActors[j]->getX())*(colL-vectorOfActors[j]->getX());
            int rowDiffSquared = (rowL-vectorOfActors[j]->getY())*(rowL-vectorOfActors[j]->getY());
            if (colDiffSquared+rowDiffSquared < 36) {
                canExist = false;
            }
        }
        if (canExist == true)
        {
            int checkEarthCol = colL;
            int checkEarthRow = rowL;
            while (checkEarthCol < colL+4) // check 4x4 box
            {
                while (checkEarthRow < rowL+4)
                {
                    if (getEarth(checkEarthCol, checkEarthRow) == nullptr || getEarth(checkEarthCol, checkEarthRow)->isEVisibleCheck() == false) // there does not exist a visible Earth object
                    {
                        canExist = false;
                    }
                    if (canExist == false)
                    {
                        break;
                    }
                    checkEarthRow++;
                }
                checkEarthRow = rowL;
                checkEarthCol++;
            }
        }
        if (canExist == true)
        {
            Goodies* tempPtr = new BarrelOfOil(colL, rowL, this);
            vectorOfActors.push_back(tempPtr);
            vectorOfGoodies.push_back(tempPtr);
            L--;
        }
        else {
            continue;
        }
    }
    int world[64][61];
    setExitDirDisArrays(60, 60, world);
    setTMDirDisArrays(tunnelManPtr->getX(), tunnelManPtr->getY(), world);
    protesterTick = 0;
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::removeDeadGameObjects() {
    std::vector<Actor*>::iterator actorItr = vectorOfActors.begin();
    while (actorItr != vectorOfActors.end())
    {
        if ((*actorItr)->isDead() == true) { // if the current Actor is dead
            delete *actorItr; // deletes Actor object from the vector
            actorItr = vectorOfActors.erase(actorItr); // deletes the pointer to the object and makes iterator point to next object
        }
        else {
            actorItr++;
        }
    }
    std::vector<Goodies*>::iterator goodiesItr = vectorOfGoodies.begin();
    while (goodiesItr != vectorOfGoodies.end())
    {
        if ((*goodiesItr)->isDead() == true) {
            goodiesItr = vectorOfGoodies.erase(goodiesItr);
        }
        else {
            goodiesItr++;
        }
    }
    std::vector<Boulder*>::iterator bouldersItr = vectorOfBoulders.begin();
    while (bouldersItr != vectorOfBoulders.end())
    {
        if ((*bouldersItr)->isDead() == true) {
        bouldersItr = vectorOfBoulders.erase(bouldersItr);
        }
        else {
            bouldersItr++;
        }
    }
    std::vector<Protester*>::iterator protestersItr = vectorOfProtesters.begin();
    while (protestersItr != vectorOfProtesters.end())
    {
        if ((*protestersItr)->isDead() == true) {
            protestersItr = vectorOfProtesters.erase(protestersItr);
        }
        else {
            protestersItr++;
        }
    }
}

void StudentWorld::setExitDirDisArrays(int x, int y, int world[64][61])
{
    bool dontCheck[64][61];
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 61; j++)
        {
            if (canProtesterTurn(i, j) == false || blockingBoulder(i, j) == true)
                dontCheck[i][j] = true;
            else
                dontCheck[i][j] = false;
        }
    }
    Point currPt(x, y, 0); // allows x y of exit and tunnelman
    queue<Point> queueOfPoints;
    queueOfPoints.push(currPt);
    dontCheck[currPt.getCol()][currPt.getRow()] = true;
    exitDirectionArray[x][y] = GraphObject::Direction::right;
    exitDistanceArray[x][y] = 0;
    while (queueOfPoints.empty() == false) {
        Point firstPoint = queueOfPoints.front();
        queueOfPoints.pop();

        if (firstPoint.getRow()+1 < 61 && dontCheck[firstPoint.getCol()][(firstPoint.getRow())+1] == false) { // go up
            Point nextAdd = Point(firstPoint.getCol(), firstPoint.getRow()+1, firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            exitDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::down;
            exitDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
        if (firstPoint.getRow()-1 > -1 && dontCheck[firstPoint.getCol()][(firstPoint.getRow())-1] == false) { // go down
            Point nextAdd = Point(firstPoint.getCol(), firstPoint.getRow()-1, firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            exitDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::up;
            exitDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
        if (firstPoint.getCol()-1 > -1 && dontCheck[firstPoint.getCol()-1][(firstPoint.getRow())] == false) { // go left
            Point nextAdd = Point(firstPoint.getCol()-1, firstPoint.getRow(), firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            exitDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::right;
            exitDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
        if (firstPoint.getCol()+1 < 61 && dontCheck[firstPoint.getCol()+1][(firstPoint.getRow())] == false) { // go right
            Point nextAdd = Point(firstPoint.getCol()+1, firstPoint.getRow(), firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            exitDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::left;
            exitDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
    }
}

void StudentWorld::setTMDirDisArrays(int x, int y, int world[64][61])
{
    bool dontCheck[64][61];
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 61; j++)
        {
            if (canProtesterTurn(i, j) == false  || blockingBoulder(i, j) == true)
                dontCheck[i][j] = true;
            else
                dontCheck[i][j] = false;
        }
    }
    Point currPt(x, y, 0); // allows x y of exit and tunnelman
    queue<Point> queueOfPoints;
    queueOfPoints.push(currPt);
    dontCheck[currPt.getCol()][currPt.getRow()] = true;
    TMDirectionArray[x][y] = GraphObject::Direction::right;
    TMDistanceArray[x][y] = 0;
    while (queueOfPoints.empty() == false) {
        Point firstPoint = queueOfPoints.front();
        queueOfPoints.pop();

        if (firstPoint.getRow()+1 < 61 && dontCheck[firstPoint.getCol()][(firstPoint.getRow())+1] == false) { // go up
            Point nextAdd = Point(firstPoint.getCol(), firstPoint.getRow()+1, firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            TMDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::down;
            TMDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
        if (firstPoint.getRow()-1 > -1 && dontCheck[firstPoint.getCol()][(firstPoint.getRow())-1] == false) { // go down
            Point nextAdd = Point(firstPoint.getCol(), firstPoint.getRow()-1, firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            TMDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::up;
            TMDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
        if (firstPoint.getCol()-1 > -1 && dontCheck[firstPoint.getCol()-1][(firstPoint.getRow())] == false) { // go left
            Point nextAdd = Point(firstPoint.getCol()-1, firstPoint.getRow(), firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            TMDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::right;
            TMDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
        if (firstPoint.getCol()+1 < 61 && dontCheck[firstPoint.getCol()+1][(firstPoint.getRow())] == false) { // go right
            Point nextAdd = Point(firstPoint.getCol()+1, firstPoint.getRow(), firstPoint.getDist() + 1);
            queueOfPoints.push(nextAdd);
            dontCheck[nextAdd.getCol()][nextAdd.getRow()] = true;
            TMDirectionArray[nextAdd.getCol()][nextAdd.getRow()] = GraphObject::Direction::left;
            TMDistanceArray[nextAdd.getCol()][nextAdd.getRow()] = nextAdd.getDist();
        }
    }
}

GraphObject::Direction StudentWorld::getDirectionToExit(int Px, int Py) {
    return (exitDirectionArray[Px][Py]);
}

GraphObject::Direction StudentWorld::getDirectionToTM(int Px, int Py) {
    return (TMDirectionArray[Px][Py]);
}

int StudentWorld::getDistanceToTM(int Px, int Py) {
    return (TMDistanceArray[Px][Py]);
}

GraphObject::Direction StudentWorld::regProtesterTM(int Px, int Py) {
    if (Px > tunnelManPtr->getX()) {
        return GraphObject::left;
    }
    if (Px < tunnelManPtr->getX()) {
        return GraphObject::right;
    }
    if (Py < tunnelManPtr->getY()) {
        return GraphObject::up;
    }
    if (Py > tunnelManPtr->getY()) {
        return GraphObject::down;
    }
    return GraphObject::right; // random value to prevent error but this should never happen
}

string StudentWorld::formatString(int level, int lives, int health, int squirts, int gold, int barrelsLeft, int sonar, int score) {
    string levelString = to_string(level);
    string livesString = to_string(lives);
    string healthString = to_string(health);
    string squirtsString = to_string(squirts);
    string goldString = to_string(gold);
    string oilString = to_string(barrelsLeft);
    string sonarString = to_string(sonar);
    string scoreString = to_string(score);
    
    if (level < 10) {
        levelString = " " + to_string(level);
    }
    if (health < 10) {
        healthString = "  " + to_string(health);
    }
    if (health >= 10 && health <= 99) {
        healthString = to_string(health);
    }
    if (squirts < 10) {
        squirtsString = " " + to_string(squirts);
    }
    if (gold < 10) {
        goldString = " " + to_string(gold);
    }
    if (barrelsLeft < 10) {
        oilString = " " + to_string(barrelsLeft);
    }
    if (sonar < 10) {
        sonarString = " " + to_string(sonar);
    }
    if (score < 10) {
        scoreString = "00000" + to_string(score);
    }
    if (score >= 10 && score < 100) {
        scoreString = "0000" + to_string(score);
    }
    if (score >= 100 && score < 1000) {
        scoreString = "000" + to_string(score);
    }
    if (score >= 1000 && score < 10000) {
        scoreString = "00" + to_string(score);
    }
    if (score >= 10000 && score < 100000) {
        scoreString = "0" + to_string(score);
    }
    return "Lvl: " + levelString + "  Lives: " + livesString + "  Hlth: " + healthString + "%  Wtr: " + squirtsString + "  Gld: " + goldString + "  Oil Left: " + oilString + "  Sonar: " + sonarString + "  Scr: " + scoreString;
}

void StudentWorld::setDisplayText()
{
    int level = getLevel();
    int lives = getLives();
    int health = (tunnelManPtr->getHitPoints())*10;
    int squirts = tunnelManPtr->getSquirts();
    int gold = tunnelManPtr->getGoldNugs();
    int barrelsLeft = tunnelManPtr->getOil();
    int sonar = tunnelManPtr->getSonar();
    int score = getScore();
    // Next, create a string from your statistics, of the form:
    // Lvl: 52 Lives: 3 Hlth: 80% Wtr: 20 Gld: 3 Oil Left: 2 Sonar: 1 Scr: 321000
    string s = formatString(level, lives, health, squirts, gold, barrelsLeft, sonar, score);
    // Finally, update the display text at the top of the screen with your
    // newly created stats
    setGameStatText(s); // calls our provided GameWorld::setGameStatText
}

int StudentWorld::move()
{
    // Update the Game Status Line
    setDisplayText(); // update the score/lives/level text at screen top
    // The term “Actors” refers to all Protesters, the player, Goodies,
    // Boulders, Barrels of oil, Holes, Squirts, the Exit, etc.
    // Give each Actor a chance to do something
    
    // Adding new Actors:
    
    int T = fmax(25, 200 - getLevel());
    int P = fmin(15, 2 + getLevel() * 1.5);

    if (vectorOfProtesters.size() < P) {
        if (protesterTick == 0 || protesterTick % T == 0) {
            if (isHardCore() == true) {
                HardcoreProtester* tempPtr = new HardcoreProtester(60, 60, this);
                vectorOfActors.push_back(tempPtr);
                vectorOfProtesters.push_back(tempPtr);
            }
            else {
                RegularProtester* tempPtr = new RegularProtester(60, 60, this);
                vectorOfActors.push_back(tempPtr);
                vectorOfProtesters.push_back(tempPtr);
            }
        }
    }
    protesterTick++;
    
    
    if (rand() % ((getLevel()*25)+300) == 0) {
        if (rand() % 5 == 0) { // add sonar 1/5
            Goodies* tempPtr = new SonarKit(0, 60, this);
            vectorOfActors.push_back(tempPtr);
            vectorOfGoodies.push_back(tempPtr);
        }
        else {
            bool tryAgain = false;
            while (tryAgain == false) {
                int col = rand() % 61;
                int row = rand() % 57;
                bool canExist = true;
                int checkEarthCol = col;
                int checkEarthRow = row;
                while (checkEarthCol < col+4) // check 4x4 box
                {
                    while (checkEarthRow < row+4)
                    {
                        if (getEarth(checkEarthCol, checkEarthRow) != nullptr && getEarth(checkEarthCol, checkEarthRow)->isEVisibleCheck() == true) // there does not exist a visible Earth object
                        {
                            canExist = false;
                            tryAgain = true;
                            break;
                        }
                        checkEarthRow++;
                    }
                    if (canExist == false) {
                        break;
                    }
                    checkEarthRow = row;
                    checkEarthCol++;
                }
                for (int i = 0; i < vectorOfBoulders.size(); i++) {
                    if (vectorOfBoulders[i]->getX() == col || vectorOfBoulders[i]->getY() == row) {
                        canExist = false;
                    }
                }
                if (canExist == true)
                {
                    Goodies* tempPtr = new WaterPool(col, row, this);
                    vectorOfActors.push_back(tempPtr);
                    vectorOfGoodies.push_back(tempPtr);
                    break;
                }
                else {
                    tryAgain = false;
                    continue;
                }
            }
        }
    }
    tunnelManPtr->doSomething();
    for (int i = 0; i < vectorOfActors.size(); i++)
    {
        if (vectorOfActors[i]->isDead() == false)
        {
            // ask each actor to do something (e.g. move)
            vectorOfActors[i]->doSomething();
            if (tunnelManPtr->isDead() == true)
            {
                return GWSTATUS_PLAYER_DIED;
            }
            if (isCompletedLvl() == true)
            {
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    // Remove newly-dead actors after each tick
    removeDeadGameObjects(); // delete dead game objects
    // return the proper result
    if (tunnelManPtr->isDead() == true)
    {
        return GWSTATUS_PLAYER_DIED;
    }
    // If the player has collected all of the Barrels on the level, then
    // return the result that the player finished the level
    if (isCompletedLvl() == true)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    // the player hasn’t completed the current level and hasn’t died
    // let them continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete tunnelManPtr;
    std::vector<Actor*>::iterator actorItr = vectorOfActors.begin();
    while (actorItr != vectorOfActors.end())
    {
        delete *actorItr;
        actorItr = vectorOfActors.erase(actorItr);
    }
    std::vector<Goodies*>::iterator goodiesItr = vectorOfGoodies.begin();
    while (goodiesItr != vectorOfGoodies.end())
    {
        goodiesItr = vectorOfGoodies.erase(goodiesItr);
    }
    std::vector<Boulder*>::iterator bouldersItr = vectorOfBoulders.begin();
    while (bouldersItr != vectorOfBoulders.end())
    {
        bouldersItr = vectorOfBoulders.erase(bouldersItr);
    }
    std::vector<Protester*>::iterator protestersItr = vectorOfProtesters.begin();
    while (protestersItr != vectorOfProtesters.end())
    {
        protestersItr = vectorOfProtesters.erase(protestersItr);
    }
    for (int column = 0; column < VIEW_WIDTH; column++)
    {
        for (int row = 0; row < VIEW_HEIGHT; row++)
        {
            if (earthPtrs[column][row] != nullptr) {
                delete earthPtrs[column][row];
            }
        }
    }
}

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

const int PICK_UP_GOLDNUG = 0;
const int PICK_UP_SONAR = 1;
const int PICK_UP_WATER = 2;
const int PICK_UP_OIL = 3;

const int REG_PROTESTER_SHOUT = 0;
const int SQUIRT_ATTACK = 1;
const int BOULDER_FALL = 2;
const int PRESSED_ESCAPE = 3;

class Actor : public GraphObject
{
public:
    // constructor
    Actor(int imageID, int startX, int startY, StudentWorld* studPt, Direction dir = right, double size = 1.0, unsigned int depth = 0) : GraphObject(imageID, startX, startY, dir, size, depth), ptrToStudentWorld(studPt), m_dead(false) {
        setVisible(true);
    }
    // destructor
    virtual ~Actor() {}
    virtual void doSomething() = 0;
    StudentWorld* getWorld() {
        return ptrToStudentWorld;
    }
    bool isDead() {
        return m_dead;
    }
    void setDead(bool amIDead) {
        m_dead = amIDead;
    }
private:
    StudentWorld* ptrToStudentWorld;
    bool m_dead;
};

class TunnelMan: public Actor
{
public:
    TunnelMan(StudentWorld* studPt) : Actor(TID_PLAYER, 30, 60, studPt, right, 1.0, 0), hitPoints(10), waterUnits(5), sonarCharge(1), goldNuggets(0) {
        setOilBarrels();
        setVisible(true);
    }
    void incrementSonar() {
        sonarCharge = sonarCharge+2;
    }
    void incrementGold() {
        goldNuggets++;
    }
    void incrementWater() {
        waterUnits = waterUnits+5;
    }
    void decrementOil() {
        oilBarrels--;
    }
    int getSquirts() {
        return waterUnits;
    }
    int getGoldNugs() {
        return goldNuggets;
    }
    int getSonar() {
        return sonarCharge;
    }
    int getOil() {
        return oilBarrels;
    }
    void hitPointsDecrement(int num) {
        hitPoints = hitPoints - num;
    }
    int getHitPoints() {
        return hitPoints;
    }
    void setOilBarrels();
    virtual ~TunnelMan() {}
    virtual void doSomething();
 private:
    int hitPoints;
    int waterUnits;
    int sonarCharge;
    int goldNuggets;
    int oilBarrels;
};

class Earth : public Actor
{
public:
    Earth(int x, int y, StudentWorld* studPt) : Actor(TID_EARTH, x, y, studPt, right, 0.25, 3), Evisible(true) {
        setVisible(true);
    }
    virtual ~Earth() {}
    virtual void doSomething() {}
    void setEvisible(bool amIVisible) {
        Evisible = amIVisible;
    }
    bool isEVisibleCheck() {
        return Evisible;
    }
    
private:
    bool Evisible;
};

class Boulder : public Actor
{
public:
    Boulder(int x, int y, StudentWorld* studPt) : Actor(TID_BOULDER, x, y, studPt, down, 1.0, 1), tickPass(0), Bvisible(true) {
        setVisible(true);
        status = 0; // 0 is stable
    }
    virtual void doSomething();
    void setBvisible(bool amIVisible) {
        Bvisible = amIVisible;
    }
    bool isBVisibleCheck() {
        return Bvisible;
    }
    virtual ~Boulder() {}
    
private:
    int status; // 0 is stable, 1 is waiting, 2 is falling
    int tickPass; // when 30 and is waiting state, boulder becomes falling state
    int Bvisible;
};

class Goodies : public Actor
{
public:
    Goodies(int imageID, int startX, int startY, StudentWorld* studPt, bool show, Direction dir = right, double size = 1.0, unsigned int depth = 0) : Actor(imageID, startX, startY, studPt, dir, size, depth), goodiesVisible(show) {
    }
    bool NearAction();
    bool PickUpAction();
    virtual void doSomething() = 0;
    void setGoodiesVisible(bool amIVisible) {
        goodiesVisible = amIVisible;
    }
    bool isGoodiesVisibleCheck() {
        return goodiesVisible;
    }
    virtual ~Goodies() {}
private:
    bool goodiesVisible;
};

class SonarKit : public Goodies
{
public:
    SonarKit(int x, int y, StudentWorld* studPt) : Goodies(TID_SONAR, x, y, studPt, true, right, 1.0, 2), ticks(0)
    {
        setVisible(true);
    }
    virtual void doSomething();
    virtual ~SonarKit() {}
    
private:
    int ticks;
};

class BarrelOfOil : public Goodies
{
public:
    BarrelOfOil(int x, int y, StudentWorld* studPt) : Goodies(TID_BARREL, x, y, studPt, false, right, 1.0, 2) {
        setVisible(false);
    }
    virtual void doSomething();
    virtual ~BarrelOfOil() {}
//private:

};

class GoldNugget : public Goodies
{
public:
    GoldNugget(int x, int y, StudentWorld* studPt, bool shouldIAppear, bool pickUpTunnelMan, bool state) : Goodies(TID_GOLD, x, y, studPt, shouldIAppear, right, 1.0, 2), pickUppableTM(pickUpTunnelMan), permanentState(state), ticks(0) {
        setVisible(shouldIAppear); // visibility depends on code that creates the nugget depending on the context
    }
    virtual void doSomething();
    virtual ~GoldNugget() {}
    
private:
    bool pickUppableTM;
    bool permanentState;
    int ticks;
};

class WaterPool : public Goodies
{
public:
    WaterPool(int x, int y, StudentWorld* studPt) : Goodies(TID_WATER_POOL, x, y, studPt, true, right, 1.0, 2), ticks(0) {
        setVisible(true);
    }
    virtual void doSomething();
    virtual ~WaterPool() {}
private:
    int ticks;
};

class Squirt : public Goodies
{
public:
    Squirt(int x, int y, StudentWorld* studPt, Direction dir) : Goodies(TID_WATER_SPURT, x, y, studPt, true, dir, 1.0, 1), m_tDistance(4), m_direction(dir), ticks(0) {
        setVisible(true);
    }
    virtual void doSomething();
    virtual ~Squirt() {}
    
private:
    int m_tDistance;
    int m_direction;
    int ticks;
};

class Protester : public Actor
{
public:
    Protester(int imageID, int startX, int startY, StudentWorld* studPt, int hitPt, Direction dir = left, double size = 1.0, unsigned int depth = 0) : Actor(imageID, startX, startY, studPt, dir, size, depth), hitPoints(hitPt), leaveOil(false), randomTicks(0), shoutTicks(0), perpTicks(0), hasShouted(false), isStunned(false) {
        numSquaresToMoveCurrDir = rand() % 53 + 8;
        setVisible(true);
    }
    int getRandomTicks() {
        return randomTicks;
    }
    void incrementRandomTicks() {
        randomTicks++;
    }
    void setRandomTicks(int num) {
        randomTicks = num;
    }
    bool getStunnedStatus() {
        return isStunned;
    }
    void setStunnedStatus(bool amIStunned) {
        isStunned = amIStunned;
    }
    int getShoutTicks() {
        return shoutTicks;
    }
    void setShoutTicks(int howMany) {
        shoutTicks = howMany;
    }
    void incrementShoutTicks() {
        shoutTicks++;
    }
    int getPerpTicks() {
        return perpTicks;
    }
    void incrementPerpTicks() {
        perpTicks++;
    }
    void setPerpTicks(int num) {
        perpTicks = num;
    }
    bool didShout() {
        return hasShouted;
    }
    void setShout(bool didIShout) {
        hasShouted = didIShout;
    }
    int getHitPoints() {
        return hitPoints;
    }
    void setHitPoints(int settingNum) {
        hitPoints = settingNum;
    }
    void decrementHitPoints(int byHowMuch) {
        hitPoints = hitPoints - byHowMuch;
    }
    int getNumSquaresToMoveCurrDir() {
        return numSquaresToMoveCurrDir;
    }
    bool getLeaveOil() {
        return leaveOil;
    }
    void setLeaveOil(bool settingBool) {
        leaveOil = settingBool;
    }
    void setNumSquaresToMoveCurrDir(int settingNum) {
        numSquaresToMoveCurrDir = settingNum;
    }
    void decrementNumSquares() {
        numSquaresToMoveCurrDir--;
    }
    virtual bool isRegular() {
        return true;
    }
    virtual ~Protester() {}
    virtual void doSomething();
    
private:
    int numSquaresToMoveCurrDir;
    int hitPoints;
    bool leaveOil;
    int randomTicks;
    int shoutTicks;
    int perpTicks;
    bool hasShouted;
    bool isStunned;
};

class RegularProtester : public Protester
{
public:
    RegularProtester(int x, int y, StudentWorld* studPt) : Protester(TID_PROTESTER, x, y, studPt, 5, left, 1.0, 0)
    {}
    virtual ~RegularProtester() {}
};

class HardcoreProtester : public Protester
{
public:
    HardcoreProtester(int x, int y, StudentWorld* studPt) : Protester(TID_HARD_CORE_PROTESTER, x, y, studPt, 20, left, 1.0, 0)
    {}
    virtual bool isRegular() {
        return false;
    }
    virtual ~HardcoreProtester() {}
public:

};

#endif // ACTOR_H_

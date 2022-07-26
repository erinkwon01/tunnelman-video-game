#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

// TunnelMan Implementation
void TunnelMan::doSomething()
{
    if (isDead() == true) // if TunnelMan is dead
    {
        return; // immediately return
    }
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
    // user hit a key this tick!
    switch (ch)
        {
            case KEY_PRESS_LEFT:
                if (getDirection() == left && getX() > 0)
                {
                    int xPos = getX()-1;
                    int yPos = getY();
                    int stop = yPos+4;
                    bool dig = false;
                    bool dontMove = false;
                    if (yPos < 60)
                    {
                        while (yPos < stop)
                        {
                            if (getWorld()->blockingBoulder(xPos, yPos) == true) {
                                dontMove = true;
                            }
                            if (getWorld()->getEarth(xPos, yPos) == nullptr) // tunnel area
                            {
                                yPos++;
                                continue;
                            }
                            else if (getWorld()->getEarth(xPos, yPos)->isEVisibleCheck() == true) // if there exists a visible Earth object at this coordinate,
                            {
                                getWorld()->eraseEarth(xPos, yPos); // set the Earth object to invisible
                                dig = true;
                            }
                            yPos++;
                        }
                    }
                    if (dontMove == true) {
                        break;
                    }
                    if (dig == true)
                    {
                        getWorld()->playSound(SOUND_DIG); // play the sound to dig
                    }
                    moveTo(getX()-1, getY());
                    getWorld()->setChangeWorld(true);
                }
                else
                {
                    setDirection(left);
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection() == right && getX() < 60)
                {
                    bool dontMove = false;
                    int xPos = getX()+4;
                    int yPos = getY();
                    int stop = yPos+4;
                    bool dig = false;
                    if (yPos < 60)
                    {
                        while (yPos < stop)
                        {
                            if (getWorld()->blockingBoulder(xPos, yPos) == true) {
                                dontMove = true;
                            }
                            if (getWorld()->getEarth(xPos, yPos) == nullptr) // tunnel area
                            {
                                yPos++;
                                continue;
                            }
                            else if (getWorld()->getEarth(xPos, yPos)->isEVisibleCheck() == true) // if there exists a visible Earth object at this coordinate,
                            {
                                getWorld()->eraseEarth(xPos, yPos); // set the Earth object to invisible
                                dig = true;
                            }
                            yPos++;
                        }
                    }
                    if (dontMove == true) {
                        break;
                    }
                    if (dig == true)
                    {
                        getWorld()->playSound(SOUND_DIG); // play the sound to dig
                    }
                    moveTo(getX()+1, getY());
                    getWorld()->setChangeWorld(true);
                }
                else
                {
                    setDirection(right);
                }
                break;
            case KEY_PRESS_UP:
                if (getDirection() == up && getY() < 60)
                {
                    bool dontMove = false;
                    int xPos = getX();
                    int yPos = getY()+4;
                    int stop = xPos+4;
                    bool dig = false;
                    if (xPos < 64)
                    {
                        while (xPos < stop)
                        {
                            if (getWorld()->blockingBoulder(xPos, yPos) == true) {
                                dontMove = true;
                            }
                            if (getWorld()->getEarth(xPos, yPos) == nullptr) // tunnel area
                            {
                                xPos++;
                                continue;
                            }
                            else if (getWorld()->getEarth(xPos, yPos)->isEVisibleCheck() == true) // if there exists a visible Earth object at this coordinate,
                            {
                                getWorld()->eraseEarth(xPos, yPos); // set the Earth object to invisible
                                dig = true;
                            }
                            xPos++;
                        }
                    }
                    if (dontMove == true) {
                        break;
                    }
                    if (dig == true)
                    {
                        getWorld()->playSound(SOUND_DIG); // play the sound to dig
                    }
                    moveTo(getX(), getY()+1);
                    getWorld()->setChangeWorld(true);
                }
                else
                {
                    setDirection(up);
                }
                break;
            case KEY_PRESS_DOWN:
                if (getDirection() == down && getY() > 0)
                {
                    bool dontMove = false;
                    int xPos = getX();
                    int yPos = getY()-1;
                    int stop = xPos+4;
                    bool dig = false;
                    if (xPos < 64)
                    {
                        while (xPos < stop)
                        {
                            if (getWorld()->blockingBoulder(xPos, yPos) == true) {
                                dontMove = true;
                            }
                            if (getWorld()->getEarth(xPos, yPos) == nullptr) // tunnel area
                            {
                                xPos++;
                                continue;
                            }
                            else if (getWorld()->getEarth(xPos, yPos)->isEVisibleCheck() == true) // if there exists a visible Earth object at this coordinate,
                            {
                                getWorld()->eraseEarth(xPos, yPos); // set the Earth object to invisible
                                dig = true;
                            }
                            xPos++;
                        }
                    }
                    if (dontMove == true) {
                        break;
                    }
                    if (dig == true)
                    {
                        getWorld()->playSound(SOUND_DIG); // play the sound to dig
                    }
                    moveTo(getX(), getY()-1);
                    getWorld()->setChangeWorld(true);
                }
                else
                {
                    setDirection(down);
                }
                break;
            case KEY_PRESS_ESCAPE:
                getWorld()->annoyTunnelMan(PRESSED_ESCAPE);
                break;
            case KEY_PRESS_SPACE: // squirting water
                if (waterUnits > 0) { // water to squirt
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT); // regardless, squirt water
                    if (getDirection() == right) {
                        bool showImage = true;
                        if (getX()+8 > 63) { // checking out-of-bounds or not
                            showImage = false;
                        }
                        else {
                            for (int i = getX()+4; i < getX()+8; i++) { // there exists no Earth objects in the way
                                for (int j = getY(); j < getY()+4; j++) {
                                    if (getWorld()->getEarth(i, j) != nullptr && getWorld()->getEarth(i, j)->isEVisibleCheck() == true) {
                                        showImage = false;
                                    }
                                    if (getWorld()->blockingBoulder(i, j) == true) {
                                        showImage = false;
                                    }
                                }
                            }
                        }
                        if (showImage == true) {
                            getWorld()->squirtAction(new Squirt(getX()+4, getY(), getWorld(), right)); // adding to vector of actors
                        }
                    }
                    if (getDirection() == left) {
                        bool showImage = true;
                        if (getX()-4 < 0) {
                            showImage = false;
                        }
                        else {
                            for (int i = getX(); i < getX()-4; i++) { // there exists no Earth objects in the way
                                for (int j = getY(); j < getY()+4; j++) {
                                    if (getWorld()->getEarth(i, j) != nullptr && getWorld()->getEarth(i, j)->isEVisibleCheck() == true) {
                                        showImage = false;
                                    }
                                    if (getWorld()->blockingBoulder(i, j) == true) {
                                        showImage = false;
                                    }
                                }
                            }
                        }
                        if (showImage == true) {
                            getWorld()->squirtAction(new Squirt(getX()-4, getY(), getWorld(), left)); // adding to vector of actors
                        }
                    }
                    if (getDirection() == up) {
                        bool showImage = true;
                        if (getY()+8 > 63) {
                            showImage = false;
                        }
                        else {
                            for (int i = getX(); i < getX()+4; i++) { // there exists no Earth objects in the way
                                for (int j = getY()+4; j < getY()+8; j++) {
                                    if (getWorld()->getEarth(i, j) != nullptr && getWorld()->getEarth(i, j)->isEVisibleCheck() == true) {
                                        showImage = false;
                                    }
                                    if (getWorld()->blockingBoulder(i, j) == true) {
                                        showImage = false;
                                    }
                                }
                            }
                        }
                        if (showImage == true) {
                            getWorld()->squirtAction(new Squirt(getX(), getY()+4, getWorld(), up)); // adding to vector of actors
                        }
                    }
                    if (getDirection() == down) {
                        bool showImage = true;
                        if (getY()-4 < 0) {
                            showImage = false;
                        }
                        else {
                            for (int i = getX(); i < getX()+4; i++) { // there exists no Earth objects in the way
                                for (int j = getY(); j < getY()-4; j++) {
                                    if (getWorld()->getEarth(i, j) != nullptr && getWorld()->getEarth(i, j)->isEVisibleCheck() == true) {
                                        showImage = false;
                                    }
                                    if (getWorld()->blockingBoulder(i, j) == true) {
                                        showImage = false;
                                    }
                                }
                            }
                        }
                        if (showImage == true) {
                            getWorld()->squirtAction(new Squirt(getX(), getY()-4, getWorld(), down)); // adding to vector of actors
                        }
                    }
                    waterUnits--;
                }
                break;
            case KEY_PRESS_TAB:
                if (goldNuggets > 0) {
                    getWorld()->placeNuggetOnGround(getX(), getY());
                    goldNuggets--;
                }
                break;
            case 'z':
            case 'Z':
                if (sonarCharge > 0) {
                    getWorld()->sonarView(getX(), getY());
                    sonarCharge--;
                }
                break;
        }
    }
}

void TunnelMan::setOilBarrels() {
    oilBarrels = getWorld()->numOil();
}

// Boulder Implementation

void Boulder::doSomething() {
    if (isDead() == true) // if Boulder is "dead"
    {
        return; // immediately return
    }
    if (status == 0) // 0 stable
    {
        int i = 0;
        while (i < 4)
        {
            if (getWorld()->getEarth(getX()+i, getY()-1) != nullptr && getWorld()->getEarth(getX()+i, getY()-1)->isEVisibleCheck() == true) // there exists Earth objects below
            {
                status = 0; // maintain status
                break;
            }
            else // there does not exist Earth objects below
            {
                status = 1; // change status
                tickPass = 0;
            }
            i++;
        }
        return;
    }
    if (status == 1 && tickPass < 30) // waiting state, increment ticks
    {
        tickPass++;
        return;
    }
    if (status == 1 && tickPass == 30) // waiting state, ticks are complete
    {
        status = 2; // 2 is falling state
        getWorld()->playSound(SOUND_FALLING_ROCK);
    }
    if (status == 2) // falling state
    {
        int seekingYPos = getY()-1; // direction it wants to fall to
        int curXPos = getX();
        int i = 0;
        bool fallDown = true; // bool to check if boulder can fall down
        while(i < 4)
        {
            if (getWorld()->getEarth(curXPos+i, seekingYPos) != nullptr && getWorld()->getEarth(curXPos+i, seekingYPos)->isEVisibleCheck() == true) // there exists Earth below
            {
                fallDown = false; // don't fall
            }
            if (getWorld()->blockingBoulder(curXPos+i, seekingYPos) == true) // there exists another boulder
            {
                fallDown = false; // don't fall
            }
            i++;
        }
        if(fallDown == true) // if you can fall down,
        {
            moveTo(getX(), seekingYPos); // go to the seeking Y position
            getWorld()->setChangeWorld(true);
            
        }
        if (fallDown == false || seekingYPos < 0) // if you cannot,
        {
            setDead(true); // stop the fall and delete Boulder
            getWorld()->setChangeWorld(true);
        }

        if (getWorld()->protesterNear(getX(), getY()) == true) {
            getWorld()->annoyProtester(getX(), getY(), BOULDER_FALL);
        }
        if (getWorld()->tunnelManHere(getX(), getY()) == true) {
            getWorld()->annoyTunnelMan(BOULDER_FALL);
        }
    }
}

bool Goodies::NearAction() {
    if (isGoodiesVisibleCheck() == false && getWorld()->tunnelManNear(getX(), getY()) == true)
    {
        setVisible(true);
        setGoodiesVisible(true);
        return true;
    }
    else
    {
        return false;
    }
}

bool Goodies::PickUpAction() {
    if (isGoodiesVisibleCheck() == true && getWorld()->tunnelManPickUp(getX(), getY()) == true)
    {
        setDead(true);
        return true;
    }
    else
    {
        return false;
    }
}

// Squirt Implementation

void Squirt::doSomething() {
    if (getWorld()->protesterNear(getX(), getY()) == true) {
        getWorld()->annoyProtester(getX(), getY(), SQUIRT_ATTACK);
        setDead(true);
    }
    if (m_tDistance == 0)
    {
        setDead(true);
        return;
    }
    if (m_direction == right)
    {
        if (getX()+4 > 63 || getWorld()->blockingBoulder(getX()+4, getY()) == true)
        {
            setDead(true);
            return;
        }
        else if (getWorld()->getEarth(getX()+4, getY()) != nullptr && getWorld()->getEarth(getX()+4, getY())->isEVisibleCheck() == true)
        {
            setDead(true);
            return;
        }
        else {
            moveTo(getX()+1, getY());
            m_tDistance--;
            return;
        }
    }
    if (m_direction == left)
    {
        if (getX()-1 < 0 || getWorld()->blockingBoulder(getX()-1, getY()) == true)
        {
            setDead(true);
            return;
        }
        else if (getWorld()->getEarth(getX()-1, getY()) != nullptr && getWorld()->getEarth(getX()-1, getY())->isEVisibleCheck() == true)
        {
            setDead(true);
            return;
        }
        else {
            moveTo(getX()-1, getY());
            m_tDistance--;
            return;
        }
    }
    if (m_direction == up)
    {
        if (getY()+4 > 63 || getWorld()->blockingBoulder(getX(), getY()+4) == true)
        {
            setDead(true);
            return;
        }
        else if (getWorld()->getEarth(getX(), getY()+4) != nullptr && getWorld()->getEarth(getX(), getY()+4)->isEVisibleCheck() == true)
        {
            setDead(true);
            return;
        }
        else {
            moveTo(getX(), getY()+1);
            m_tDistance--;
            return;
        }
    }
    if (m_direction == down)
    {
        if (getY()-1 < 0 || getWorld()->blockingBoulder(getX(), getY()-1) == true)
        {
            setDead(true);
            return;
        }
        else if (getWorld()->getEarth(getX(), getY()-1) != nullptr && getWorld()->getEarth(getX(), getY()-1)->isEVisibleCheck() == true)
        {
            setDead(true);
            return;
        }
        else {
            moveTo(getX(), getY()-1);
            m_tDistance--;
            return;
        }
    }
}

// Barrel of Oil Implementation

void BarrelOfOil::doSomething() {
    if (isDead() == true)
    {
        return;
    }
    if (NearAction() == true) {
        return;
    }
    if (PickUpAction() == true) {
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()->increaseScore(1000);
        getWorld()->tunnelManInventory(PICK_UP_OIL);
        if (getWorld()->isCompletedLvl() == true) {
            return;
        }
    }
}

// Gold Nugget Implementation

void GoldNugget::doSomething() {
    if (isDead() == true)
    {
        return;
    }
    if (pickUppableTM == false && getWorld()->protesterNear(getX(), getY()) == true) {
        setDead(true);
        getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
        getWorld()->retrieveGold(getX(), getY());
        return;
    }
    if (pickUppableTM == false && ticks >= 100) {
        setDead(true);
        return;
    }
    if (pickUppableTM == false) {
        ticks++;
        return;
    }
    if (NearAction() == true) {
        return;
    }
    if (PickUpAction() == true && pickUppableTM == true) {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(10);
        getWorld()->tunnelManInventory(PICK_UP_GOLDNUG);
    }
}

// Sonar Kit Implementation

void SonarKit::doSomething() {
    if (isDead() == true) {
        return;
    }
    if (PickUpAction() == true) {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->tunnelManInventory(PICK_UP_SONAR);
        getWorld()->increaseScore(75);
    }
    if (ticks >= fmax(100, 300-(10*getWorld()->getLevel()))) { // starts at 0 so must be 1 less
        setDead(true);
    }
    ticks++;
}

// Water Pool Implementation

void WaterPool::doSomething() {
    if (isDead() == true) {
        return;
    }
    if (PickUpAction() == true) {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->tunnelManInventory(PICK_UP_WATER);
        getWorld()->increaseScore(100);
    }
    if (ticks >= fmax(100, 300 - (10*getWorld()->getLevel()))) { // starts at 0 so must be 1 less
        setDead(true);
    }
    ticks++;
}

// Protesters Implementation

void Protester::doSomething() {
    if (isDead() == true) {
        return;
    }
    int numTimesOfRest = fmax(0, 3-((getWorld()->getLevel())/4));
    if (getStunnedStatus() == true) {
        numTimesOfRest = fmax(50, 100 - getWorld()->getLevel()*10);
    }
    if (getRandomTicks() % numTimesOfRest != 0) {
        incrementRandomTicks();
        return;
    }
    else {
        if (getStunnedStatus() == true) {
            setStunnedStatus(false);
            setRandomTicks(0);
        }
        incrementRandomTicks();
        incrementShoutTicks();
        incrementPerpTicks();
        // exit strategy
        if (getLeaveOil() == true) {
            if (getX() == 60 && getY() == 60) {
                setDead(true);
                return;
            }
            else {
                int world[64][61];
                if (getWorld()->getWorldChange() == true) { // checking if world changed from before
                    getWorld()->setExitDirDisArrays(60, 60, world);
                }

                if (getWorld()->getDirectionToExit(getX(), getY()) == up) { // checking what direction to go
                    if (getDirection() != up) {
                        setDirection(up);
                    }
                    moveTo(getX(), getY()+1);
                }
                else if (getWorld()->getDirectionToExit(getX(), getY()) == down) {
                    if (getDirection() != down) {
                        setDirection(down);
                    }
                    moveTo(getX(), getY()-1);
                }
                else if (getWorld()->getDirectionToExit(getX(), getY()) == right) {
                    if (getDirection() != right) {
                        setDirection(right);
                    }
                    moveTo(getX()+1, getY());
                }
                else if (getWorld()->getDirectionToExit(getX(), getY()) == left) {
                    if (getDirection() != left) {
                        setDirection(left);
                    }
                    moveTo(getX()-1, getY());
                }
                return;
            }
        }
    }
    if (getWorld()->tunnelManNear(getX(), getY()) == true && getWorld()->facingTunnelMan(getX(), getY(), getDirection()) == true && getShoutTicks() >= 15) {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        getWorld()->annoyTunnelMan(REG_PROTESTER_SHOUT);
        setShoutTicks(0);
        return;
    }
    if (isRegular() == false) {
        if (getWorld()->tunnelManNear(getX(), getY()) == false) {
            int M = 16 + (getWorld()->getLevel())*2;
            int world[64][61];
            int TMx = getWorld()->getTMx();
            int TMy = getWorld()->getTMy();
            if (getWorld()->getWorldChange() == true) { // checking if world changed from before
                getWorld()->setTMDirDisArrays(TMx, TMy, world);
            }
            if (getWorld()->getDistanceToTM(getX(), getY()) <= M) {
                if (getWorld()->getDirectionToTM(getX(), getY()) == up) { // checking what direction to go
                    if (getDirection() != up) {
                        setDirection(up);
                    }
                    moveTo(getX(), getY()+1);
                }
                else if (getWorld()->getDirectionToTM(getX(), getY()) == down) {
                    if (getDirection() != down) {
                        setDirection(down);
                    }
                    moveTo(getX(), getY()-1);
                }
                else if (getWorld()->getDirectionToTM(getX(), getY()) == right) {
                    if (getDirection() != right) {
                        setDirection(right);
                    }
                    moveTo(getX()+1, getY());
                }
                else if (getWorld()->getDirectionToTM(getX(), getY()) == left) {
                    if (getDirection() != left) {
                        setDirection(left);
                    }
                    moveTo(getX()-1, getY());
                }
                return;
            }
        }
    }
    if (getWorld()->tunnelManVerticalXLine(getX(), getY()) == true && getWorld()->tunnelManNear(getX(), getY()) == false) {
        if (getWorld()->regProtesterTM(getX(), getY()) == up) { // checking what direction to go
            if (getDirection() != up) {
                setDirection(up);
            }
            moveTo(getX(), getY()+1);
        }
        else if (getWorld()->regProtesterTM(getX(), getY()) == down) {
            if (getDirection() != down) {
                setDirection(down);
            }
            moveTo(getX(), getY()-1);
        }
        setNumSquaresToMoveCurrDir(0);
        return;
    }
    if (getWorld()->tunnelManHorizontalYLine(getX(), getY()) == true && getWorld()->tunnelManNear(getX(), getY()) == false) {
        if (getWorld()->regProtesterTM(getX(), getY()) == right) {
            if (getDirection() != right) {
                setDirection(right);
            }
            moveTo(getX()+1, getY());
        }
        else if (getWorld()->regProtesterTM(getX(), getY()) == left) {
            if (getDirection() != left) {
                setDirection(left);
            }
            moveTo(getX()-1, getY());
        }
        setNumSquaresToMoveCurrDir(0);
        return;
    }
    else { // can't see TM
        decrementNumSquares();
        if (getNumSquaresToMoveCurrDir() <= 0) {
            bool tryAgain = true;
            while (tryAgain == true) {
                int chooseDir = rand() % 4;
                if (chooseDir == 0) { // up
                    if (getWorld()->canProtesterTurn(getX(), getY()+4) == false || getWorld()->blockingBoulder(getX(), getY()+4) == true) {
                        tryAgain = true;
                    }
                    else {
                        tryAgain = false;
                        setDirection(up);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        break;
                    }
                }
                else if (chooseDir == 1) { // down
                    if (getWorld()->canProtesterTurn(getX(), getY()-4) == false || getWorld()->blockingBoulder(getX(), getY()-1) == true) {
                        tryAgain = true;
                    }
                    else {
                        tryAgain = false;
                        setDirection(down);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        break;
                    }
                }
                else if (chooseDir == 2) { // left
                    if (getWorld()->canProtesterTurn(getX()-4, getY()) == false || getWorld()->blockingBoulder(getX()-1, getY()) == true) {
                        tryAgain = true;
                    }
                    else {
                        tryAgain = false;
                        setDirection(left);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        break;
                    }
                }
                else if (chooseDir == 3) { // right
                    if (getWorld()->canProtesterTurn(getX()+4, getY()) == false || getWorld()->blockingBoulder(getX()+4, getY()) == true) {
                        tryAgain = true;
                    }
                    else {
                        tryAgain = false;
                        setDirection(right);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        break;
                    }
                }
            }
        }
        else {
            if (getPerpTicks() > 200) { // perpendicular direction
                if (getDirection() == up || getDirection() == down) {
                    if (getWorld()->canProtesterTurn(getX()-4, getY()) == true && getWorld()->blockingBoulder(getX()-1, getY()) == false && getWorld()->canProtesterTurn(getX()+4, getY()) == true && getWorld()->blockingBoulder(getX()+4, getY()) == false) {
                        int d = rand() % 2;
                        if (d == 0) { // left
                            setDirection(left);
                        }
                        else { // right
                            setDirection(right);
                        }
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        setPerpTicks(0);
                    }
                    else if (getWorld()->canProtesterTurn(getX()-4, getY()) == true && getWorld()->blockingBoulder(getX()-1, getY()) == false) {
                        setDirection(left);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        setPerpTicks(0);
                    }
                    else if (getWorld()->canProtesterTurn(getX()+4, getY()) == true && getWorld()->blockingBoulder(getX()+4, getY()) == false) {
                        setDirection(right);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        setPerpTicks(0);
                    }
                }
                else if (getDirection() == right || getDirection() == left) {
                    if (getWorld()->canProtesterTurn(getX(), getY()-4) == true && getWorld()->blockingBoulder(getX(), getY()-1) == false && getWorld()->canProtesterTurn(getX(), getY()+4) == true && getWorld()->blockingBoulder(getX(), getY()+4) == false) {
                        int d = rand() % 2;
                        if (d == 0) { // up
                            setDirection(up);
                        }
                        else { // down
                            setDirection(down);
                        }
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        setPerpTicks(0);
                    }
                    else if (getWorld()->canProtesterTurn(getX(), getY()-4) == true && getWorld()->blockingBoulder(getX(), getY()-1) == false) {
                        setDirection(down);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        setPerpTicks(0);
                    }
                    else if (getWorld()->canProtesterTurn(getX(), getY()+4) == true && getWorld()->blockingBoulder(getX(), getY()+4) == false) {
                        setDirection(up);
                        int num = rand() % 53 + 8;
                        setNumSquaresToMoveCurrDir(num);
                        setPerpTicks(0);
                    }
                }
            }
        }
        if (getDirection() == up) {
            if (getY()+1 > 61 || getWorld()->blockingEarth(getX(), getY()+4) == true || getWorld()->blockingBoulder(getX(), getY()+4) == true) {
                setNumSquaresToMoveCurrDir(0);
            }
            else {
                moveTo(getX(), getY()+1);
            }
        }
        else if (getDirection() == down) {
            if (getY()-1 < 0 || getWorld()->blockingEarth(getX(), getY()-1) == true || getWorld()->blockingBoulder(getX(), getY()-1) == true) {
                setNumSquaresToMoveCurrDir(0);
            }
            else {
                moveTo(getX(), getY()-1);
            }
        }
        else if (getDirection() == right) {
            if (getX()+1 > 61 || getWorld()->blockingEarth(getX()+4, getY()) == true || getWorld()->blockingBoulder(getX()+4, getY()) == true) {
                setNumSquaresToMoveCurrDir(0);
            }
            else {
                moveTo(getX()+1, getY());
            }
        }
        else if (getDirection() == left) {
            if (getX()-1 < 0 || getWorld()->blockingEarth(getX()-1, getY()) == true || getWorld()->blockingBoulder(getX()-1, getY()) == true) {
                setNumSquaresToMoveCurrDir(0);
            }
            else {
                moveTo(getX()-1, getY());
            }
        }
    }
}

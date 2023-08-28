#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;
const byte USERCAP = 10;
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {16, 15, 6, 7};
byte colPins[COLS] = {8, 9, 10, 13};

Keypad keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo myservo;

int lockAngle = 90;
int unlockAngle = 0;

int userPass[USERCAP];
bool isUser[USERCAP];

int id = 0;
int currUser = 0;
int pointer = 0;
int currState = 0;
int currOp = 0;
// int nextState = 0;

void fillData();
void AddUser(int id, int pass);
void RemoveUser(int id);
void clearSL();
void keyPressed(char c);
void CheckANS(int state, int val);
void ChangeState(int nextState);
void Lock();
void Unlock();

void setup()
{
    lcd.begin(16, 2);
    myservo.attach(A3);
    fillData();
    AddUser(0, 567);
    AddUser(1, 161);
    AddUser(2, 4890);
    ChangeState(0);
}

void loop()
{
    char key = keypad.getKey();

    if (key)
    {
        keyPressed(key);
        delay(100);
    }
}

void fillData()
{
    for (int i = 0; i < USERCAP; i++)
    {
        userPass[i] = 0;
        isUser[i] = false;
    }
}

void AddUser(int id, int pass)
{
    userPass[id] = pass;
    isUser[id] = true;
}

void RemoveUser(int id)
{
    isUser[id] = false;
}

void clearSL()
{
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++)
    {
        lcd.write(' ');
    }
}

void keyPressed(char c)
{
    switch (c)
    {
    case 'A':
        CheckANS(currState, id);
        break;
    case 'B':
        currUser = 0;
        if (currState != 0 && currState != 4)
        {
            ChangeState(currState - 1);
        }
        if (currState == 4)
        {
            currOp = 0;
            ChangeState(0);
        }
        break;
    case 'C':
        currUser = 0;
        currOp = 1;
        ChangeState(4);
        break;
    case 'D':
        currUser = 0;
        currOp = 2;
        ChangeState(4);
        break;
    case '*':
        clearSL();
        break;
    case '#':
        id /= 10;
        pointer--;
        lcd.setCursor(pointer, 1);
        lcd.print(' ');
        break;
    default:
        id *= 10;
        id += c - '0';
        lcd.setCursor(pointer, 1);
        lcd.print(c);
        pointer++;
    }
}

void CheckANS(int state, int val)
{
    switch (state)
    {
    case 0:
        if (isUser[val])
        {
            currUser = val;
            ChangeState(1);
        }
        else
        {
            clearSL();
            lcd.setCursor(0, 1);
            lcd.print("INVALID INPUT!");
            delay(2000);
            clearSL();
        }
        pointer = 0;
        id = 0;
        break;

    case 1:
        if (userPass[currUser] == val)
        {
            ChangeState(2);
        }
        else
        {
            clearSL();
            lcd.setCursor(0, 1);
            lcd.print("INVALID INPUT!");
            delay(2000);
            clearSL();
        }
        pointer = 0;
        id = 0;
        break;

    case 4:
        if (userPass[0] == val)
        {
            ChangeState(5);
        }
        else
        {
            clearSL();
            lcd.setCursor(0, 1);
            lcd.print("INVALID INPUT!");
            delay(2000);
            clearSL();
        }
        pointer = 0;
        id = 0;
        break;

    case 5:
        switch (currOp)
        {
        case 1:
            currUser = val;
            pointer = 0;
            id = 0;
            ChangeState(6);
            break;

        case 2:
            if (isUser[val])
            {
                RemoveUser(val);
                clearSL();
                lcd.setCursor(0, 1);
                lcd.print("User Deleted!");
                delay(2000);
                ChangeState(0);
            }
            else
            {
                clearSL();
                lcd.setCursor(0, 1);
                lcd.print("INVALID INPUT!");
                delay(2000);
                clearSL();
            }
            pointer = 0;
            id = 0;
            break;

        default:
            break;
        }
        break;

    case 6:
        AddUser(currUser, val);
        pointer = 0;
        id = 0;
        clearSL();
        lcd.setCursor(0, 1);
        lcd.print("User Added!");
        delay(2000);
        ChangeState(0);
        break;

    default:
        break;
    }
}

void ChangeState(int nextState)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (nextState)
    {
    case 0:
        Lock();
        lcd.print("Enter USER ID");
        currState = 0;
        break;

    case 1:
        lcd.print("Enter Passcode");
        currState = 1;
        break;

    case 2:
        Unlock();
        lcd.print("Unlocked!");
        currState = 2;
        delay(5000);
        currUser = 0;
        ChangeState(0);
        break;

    case 4:
        lcd.print("Master Passcode");
        currState = 4;
        break;

    case 5:
        lcd.print("Enter USER ID");
        currState = 5;
        break;

    case 6:
        lcd.print("New Passcode");
        currState = 6;
        break;

    default:
        break;
    }
}

void Lock()
{
    for (int pos = unlockAngle; pos <= lockAngle; pos += 1){
        myservo.write(pos); 
        delay(10);          
    }
}

void Unlock()
{
    for (int pos = lockAngle; pos >= unlockAngle; pos -= 1){
        myservo.write(pos); 
        delay(10);          
    }
}
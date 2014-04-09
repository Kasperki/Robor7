//-----------------
//Defines

#define FULL_SPEED 199
#define HALF_SPEED 80
#define SLOW_SPEED 65


//----------------------
//Prototypes

void InitPWM(void);
void MoveForward(int pusle);
void MoveBackward(int pulse);
void TurnLeft(int pulse);
void TurnRight(int pulse);
void Stop(void);
void TestTurnLeft(int pulse);
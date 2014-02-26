//-----------------
//Defines

#define FULL_SPEED 199
#define HALF_SPEED 125
#define SLOW_SPEED 75


//----------------------
//Prototypes

void InitPWM();
void MoveForward(int pusle);
void MoveBackward(int pulse);
void TurnLeft(int pulse);
void TurnRight(int pulse);
void Stop();
void TestTurnRight(int pulse);
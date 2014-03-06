//-----------------
//Defines

#define FULL_SPEED 199
#define HALF_SPEED 100
#define SLOW_SPEED 50


//----------------------
//Prototypes

void InitPWM();
void MoveForward(int pusle);
void MoveBackward(int pulse);
void TurnLeft(int pulse);
void TurnRight(int pulse);
void Stop();
void TestTurnLeft(int pulse);
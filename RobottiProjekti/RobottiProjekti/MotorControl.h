//-----------------
//Defines

#define FULL_SPEED 199
#define TURN_SPEED 115
#define HALF_SPEED 80
#define SLOW_SPEED 70


//----------------------
//Prototypes

void InitPWM(void);
void MoveForward(int pusle);
void MoveForward2(int pulse, float kerroinVasen, float kerroinOikea);
void MoveBackward(int pulse);
void TurnLeft(int pulse);
void TurnRight(int pulse);
void Stop(void);
void TestTurnLeft(int pulse);
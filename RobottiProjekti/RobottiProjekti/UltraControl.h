//-----------------
//Defines
#define SERVO_LEFT 25
#define SERVO_MIDDLE 15
#define SERVO_RIGHT 8


//-----------
//Prototypes
void InitUA();
int getDataUA();
void ControlTrigger(int *);
int ControlServo(int pulse);
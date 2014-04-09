//-----------------
//Defines
#define SERVO_LEFT 25
#define SERVO_MIDDLE 16
#define SERVO_RIGHT 8


//-----------
//Prototypes
void InitUAServo(void);
int getDataUA(void);
void ControlTrigger(int *);
int ControlServo(int pulse);
void sendTrigPulse(int *);
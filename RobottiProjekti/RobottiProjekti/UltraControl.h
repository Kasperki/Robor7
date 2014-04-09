//-----------------
//Defines
#define SERVO_LEFT 50
#define SERVO_MIDDLE 33
#define SERVO_RIGHT 16


//-----------
//Prototypes
void InitUAServo(void);
int getDataUA(void);
void ControlTrigger(int *);
int ControlServo(int pulse);
void sendTrigPulse(int *);
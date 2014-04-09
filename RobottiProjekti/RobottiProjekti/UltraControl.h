//-----------------
//Defines
#define SERVO_LEFT 50
#define SERVO_MIDDLE 33
#define SERVO_MIDDLE_FROM_RIGHT 31
#define SERVO_MIDDLE_FROM_LEFT 34
#define SERVO_RIGHT 17


//-----------
//Prototypes
void InitUAServo(void);
int getDataUA(void);
void ControlTrigger(int *);
int ControlServo(int pulse);
void sendTrigPulse(int *);
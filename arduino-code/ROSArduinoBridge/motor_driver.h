#ifdef L298_MOTOR_DRIVER

#define LEFT_MOTOR_FORWARD 8
#define LEFT_MOTOR_BACKWARD 9
#define RIGHT_MOTOR_FORWARD 10
#define RIGHT_MOTOR_BACKWARD 11
#define LEFT_MOTOR_ENABLE 5
#define RIGHT_MOTOR_ENABLE 6

#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);

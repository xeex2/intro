/* Define single-letter commands that will be sent by the PC over the
   serial link.
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define ANALOG_READ 'a'
#define GET_BAUDRATE 'b'
#define PIN_MODE 'c'
#define DIGITAL_READ 'd'
#define READ_ENCODERS 'e'
#define MOTOR_SPEEDS 'm'
#define MOTOR_RAW_PWM 'o'
#undef PING
#define PING 'p'
#define RESET_ENCODERS 'r'
#define SERVO_WRITE 's'
#define SERVO_READ 't'
#define UPDATE_PID 'u'
#define DIGITAL_WRITE 'w'
#define ANALOG_WRITE 'x'
#define GET_CURRENT_PID 'g'
#define LEFT 0
#define RIGHT 1
#define TURN_LEFT 'L'
#define TURN_RIGHT 'R'
#define GO_FORWARD 'F'
#define GO_BACKWARD 'B'

#endif

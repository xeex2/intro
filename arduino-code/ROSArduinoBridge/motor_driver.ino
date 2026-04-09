#ifdef USE_BASE

#if defined L298_MOTOR_DRIVER
void initMotorController() {
  digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
  digitalWrite(LEFT_MOTOR_ENABLE, HIGH);

  // from here I added
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
  pinMode(LEFT_MOTOR_ENABLE, OUTPUT);

  /* For PWM frequency. Somehow, using a different frequency
   alters the robot speed, I have no idea why, also https://nerdytechy.com/how-to-change-the-pwm-frequency-of-arduino/ says
   if you change the frequency on pins D5 and D6, you will lose the time functions (millis(), delay(), pulseIn(), setTimeout(), etc.), 
   they will not work correctly. Also, the libraries that use them will stop working!*/

  // TCCR0B = TCCR0B & B11111000 | B00000001;  //  62500.00 Hz
  // TCCR0B = TCCR0B & B11111000 | B00000010;  //  7812.50 Hz
  // TCCR0B = TCCR0B & B11111000 | B00000011;  //  (default) 976.56 Hz
  // TCCR0B = TCCR0B & B11111000 | B00000100;  //  244.14 Hz
  // TCCR0B = TCCR0B & B11111000 | B00000101;  //  61.04 Hz
}


void setMotorSpeed(int motor, int speed) {

  if (motor == RIGHT) {
    pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

    // send 999 or -999 to brake
    // if (abs(speed) == 999) {
    //   digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
    //   digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
    // }

    // 0 for off
    if (speed == 0) {
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
    }

    // forward
    else if (speed > 0) {
      digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
      analogWrite(RIGHT_MOTOR_ENABLE, abs(speed) <= 255 ? abs(speed) : 255);
    }

    // reverse
    else {
      digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
      digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
      analogWrite(RIGHT_MOTOR_ENABLE, abs(speed) <= 255 ? abs(speed) : 255);
    }
  }

  else if (motor == LEFT) {

    pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);

    // send 999 or -999 to brake
    // if (abs(speed) == 999) {
    //   digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    //   digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    // }

    // 0 for off
    if (speed == 0) {
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    }

    // forward
    else if (speed > 0) {
      digitalWrite(LEFT_MOTOR_FORWARD, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
      analogWrite(LEFT_MOTOR_ENABLE, abs(speed) <= 255 ? abs(speed) : 255);
    }

    // reverse
    else {
      digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
      analogWrite(LEFT_MOTOR_ENABLE, abs(speed) <= 255 ? abs(speed) : 255);
    }
  }
}


void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#else
#error A motor driver must be selected!
#endif

#endif

#ifdef USE_BASE

#ifdef OURENCODER

volatile bool acR = 0;
volatile bool bcR = 0;
volatile bool acL = 0;
volatile bool bcL = 0;

volatile double revCountR = 0;
volatile double revCountL = 0;

void countRShort() {
  acR = digitalRead(RIGHT_ENC_PIN_A);
  bcR = digitalRead(RIGHT_ENC_PIN_B);

  if (bcR == LOW) {
    if (acR == HIGH)
      revCountR++;
    else
      revCountR--;
  } else {
    if (acR == HIGH)
      revCountR--;
    else
      revCountR++;
  }
}

void countLShort() {
  acL = digitalRead(LEFT_ENC_PIN_A);
  bcL = digitalRead(LEFT_ENC_PIN_B);

  if (bcL == LOW) {
    if (acL == HIGH)
      revCountL++;
    else
      revCountL--;
  } else {
    if (acL == HIGH)
      revCountL--;
    else
      revCountL++;
  }
}


void resetEncoder(int wheel) {

  if (wheel == LEFT) {
    revCountR = 0;
  }

  else if (wheel == RIGHT) {
    revCountL = 0;
  }
}


long readEncoder(int wheel) {
  if (wheel == RIGHT) {
    return revCountR;
  }

  else /* if (wheel == LEFT) */ {
    return revCountL;
  }
}


#else
#error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif

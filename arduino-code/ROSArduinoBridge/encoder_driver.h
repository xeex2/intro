// 988 cpr

#ifdef OURENCODER

// at least one interrupt-capable pin per motor
#define LEFT_ENC_PIN_A 3
#define LEFT_ENC_PIN_B 7
#define RIGHT_ENC_PIN_A 2
#define RIGHT_ENC_PIN_B 4


#endif
void countRShort();
void countLShort();
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

/*
 *- Các tập lệnh AT cho HC-06 ----------------------------|
 *    AT            kiểm tra kết nối                      |
 *    AT+NAME...    thay đổi tên                          |--> name: Car_HC-06
 *    AT+BAUD...    với 1 set to 1200 bps                 |
 *                      2 set to 2400   bps               |
 *                      3 set to 4800   bps               |
 *                      4 set to 9600   bps (mặc định)    |--> baud rate: 9600 bps
 *                      5 set to 19200  bps               |
 *                      6 set to 38400  bps               |
 *                      7 set to 57600  bps               |
 *                      8 set to 115200 bps               |
 *    AT+PIN...   cài đặt mã PIN (mặc định: 1234)         |--> pass: 1234
 *--------------------------------------------------------|
 *
 *- Các tín hiệu gửi liên tục ------------------------------------|
 *    S       Ko làm gì (stop)  |   . Xe đứng yên                 |
 *    F       Tiến              |   . (Chiều dọc) - Đi tới        |
 *    B       Lùi               |   . (Chiều dọc) - Đi lùi        |
 *    L       Trái              |   . (Chiều ngang) - Đi qua trái |
 *    R       Phải              |   . (Chiều ngang) - Đi qua phải |
 *  --------------------------- KO QUAY XE -----------------------|
 *    G       Tiến + Trái       | . Đi hướng Tây-Bắc              |
 *    I       Tiến + Phải       | . Đi hướng Đông-Bắc             |
 *    H       Lùi  + Trái       | . Đi hướng Tây-Nam              |
 *    J       Lùi  + Phải       | . Đi hướng Đông-Nam             |
 *----------------------------------------------------------------|
 *
 *- Các tín hiệu gửi 1 lần -|
 *    0     Tốc độ MIN      |
 *    1     ...             |
 *    2     ...             |
 *    3     ...             |
 *    4     ...             |
 *    5     ...             |
 *    6     ...             |
 *    7     ...             |
 *    8     ...             |
 *    9     ...             |
 *    q     Tốc độ MAX      |
 *  ------------------------|
 *    W       Bật đèn trước |
 *    w       Tắt đèn trước |
 *    U       Bật đèn sau   |
 *    u       Tắt đèn sau   |
 *    V       Bật còi       |
 *    v       Tắt còi       |
 *  ------------------------|
 *    X       Bật cảnh báo  |
 *    x       Tắt cảnh báo  |
 *  ------------------------|-------------------|
 *    D       Tắt hết tất cả (stop everything)  |
 *----------------------------------------------|
 */


/*
 *  SƠ ĐỒ HƯỚNG LẮP BÁNH CỦA XE
 * 
 *              ^
 *      FL      |      FR
 *       \      |      /
 *        \-----|-----/
 *        |\         /|
 *        |           |
 *        |           |
 *        |     .     |
 *        |           |
 *        |           |
 *        |/         \|
 *        /-----------\
 *       /             \
 *      BL             BR
 */

// --------------------------------------------------------------------------------------------------------------------------------- //
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#define DEFAULT_SPEED 150
#define FAST_SPEED 255
#define SLOW_SPEED 100

/* -------------- L298 1st floor, for two wheels (BR) and (BL) -------------- */
#define MOTOR_BR_ENA 11
#define MOTOR_BR_IN1 A0
#define MOTOR_BR_IN2 A1
#define MOTOR_BL_IN3 A2
#define MOTOR_BL_IN4 A3
#define MOTOR_BL_ENB 10

/* -------------- L298 2nd floor, for two wheels (FR) and (FL) -------------- */
#define MOTOR_FR_ENA 6
#define MOTOR_FR_IN1 12
#define MOTOR_FR_IN2 9
#define MOTOR_FL_IN3 8
#define MOTOR_FL_IN4 7
#define MOTOR_FL_ENB 5

char t;
int speed,s;

/* -------------------------------------------------------------------------- */
/*                                CONFIG MOTORS                               */
/* -------------------------------------------------------------------------- */

/* ----------------------- Motors are Stopped (Brakes) ---------------------- */

void motor_BR_stop()
{
  digitalWrite(MOTOR_BR_IN1, LOW);
  digitalWrite(MOTOR_BR_IN2, LOW);
}

void motor_BL_stop()
{
  digitalWrite(MOTOR_BL_IN3, LOW);
  digitalWrite(MOTOR_BL_IN4, LOW);
}

void motor_FR_stop()
{
  digitalWrite(MOTOR_FR_IN1, LOW);
  digitalWrite(MOTOR_FR_IN2, LOW);
}

void motor_FL_stop()
{
  digitalWrite(MOTOR_FL_IN3, LOW);
  digitalWrite(MOTOR_FL_IN4, LOW);
}

/* -------------------------------- Motor BR -------------------------------- */

void motor_BR_forward(int speed)  // Turn Clockwise (CW)
{
  analogWrite(MOTOR_BR_ENA, speed);

  digitalWrite(MOTOR_BR_IN1, HIGH);
  digitalWrite(MOTOR_BR_IN2, LOW);
}

void motor_BR_backward(int speed) // Turn Counter-Clockwise (CCW)
{
  analogWrite(MOTOR_BR_ENA, speed);

  digitalWrite(MOTOR_BR_IN1, LOW);
  digitalWrite(MOTOR_BR_IN2, HIGH);
}

/* -------------------------------- Motor BL -------------------------------- */

void motor_BL_forward(int speed)  // Turn Counter-Clockwise (CCW)
{
  analogWrite(MOTOR_BL_ENB, speed);

  digitalWrite(MOTOR_BL_IN3, HIGH);
  digitalWrite(MOTOR_BL_IN4, LOW);
}

void motor_BL_backward(int speed) // Turn Clockwise (CW)
{
  analogWrite(MOTOR_BL_ENB, speed);

  digitalWrite(MOTOR_BL_IN3, LOW);
  digitalWrite(MOTOR_BL_IN4, HIGH);
}

/* -------------------------------- Motor FR -------------------------------- */

void motor_FR_forward(int speed)  // Turn Clockwise (CW)
{
  analogWrite(MOTOR_FR_ENA, speed);

  digitalWrite(MOTOR_FR_IN1, HIGH);
  digitalWrite(MOTOR_FR_IN2, LOW);
}

void motor_FR_backward(int speed) // Turn Counter-Clockwise (CCW)
{
  analogWrite(MOTOR_FR_ENA, speed);

  digitalWrite(MOTOR_FR_IN1, LOW);
  digitalWrite(MOTOR_FR_IN2, HIGH);
}

/* -------------------------------- Motor FL -------------------------------- */

void motor_FL_forward(int speed)  // Turn Counter-Clockwise (CCW)
{
  analogWrite(MOTOR_FL_ENB, speed);

  digitalWrite(MOTOR_FL_IN3, HIGH);
  digitalWrite(MOTOR_FL_IN4, LOW);
}

void motor_FL_backward(int speed) // Turn Clockwise (CW)
{
  analogWrite(MOTOR_FL_ENB, speed);

  digitalWrite(MOTOR_FL_IN3, LOW);
  digitalWrite(MOTOR_FL_IN4, HIGH);
}

/* -------------------------------------------------------------------------- */
/*                                 CONFIG CAR                                 */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- STOP! --------------------------------- */
void stop()
{
  motor_BR_stop();
  motor_BL_stop();
  motor_FR_stop();
  motor_FL_stop();
}

/* ----------------------------------- ⇧⇧⇧ ---------------------------------- */
void go_forward(int speed)
{
  motor_BR_forward(speed);
  motor_BL_forward(speed);
  motor_FR_forward(speed);
  motor_FL_forward(speed);
}

/* ----------------------------------- ⇩⇩⇩ ---------------------------------- */
void go_backward(int speed)
{
  motor_BR_backward(speed);
  motor_BL_backward(speed);
  motor_FR_backward(speed);
  motor_FL_backward(speed);
}

/* ----------------------------------- ↻↻↻ ---------------------------------- */
void turn_CW(int speed)
{
  motor_BR_backward(speed);
  motor_BL_forward(speed);
  motor_FR_backward(speed);
  motor_FL_forward(speed);
}

/* ----------------------------------- ↺↺↺ ---------------------------------- */
void turn_CCW(int speed)
{
  motor_BR_forward(speed);
  motor_BL_backward(speed);
  motor_FR_forward(speed);
  motor_FL_backward(speed);
}


void setup() {
/* -------------- L298 1st floor, for two wheels (BR) and (BL) -------------- */
  pinMode(MOTOR_BR_IN1, OUTPUT);  
  pinMode(MOTOR_BR_IN2, OUTPUT);  
  pinMode(MOTOR_FL_IN3, OUTPUT);  
  pinMode(MOTOR_BL_IN4, OUTPUT);  
  pinMode(MOTOR_BR_ENA, OUTPUT);
  pinMode(MOTOR_BL_ENB, OUTPUT);

/* -------------- L298 2nd floor, for two wheels (FR) and (FL) -------------- */
  pinMode(MOTOR_FR_ENA, OUTPUT);  
  pinMode(MOTOR_FR_IN1, OUTPUT);  
  pinMode(MOTOR_FR_IN2, OUTPUT);  
  pinMode(MOTOR_FL_IN3, OUTPUT);  
  pinMode(MOTOR_FL_IN4, OUTPUT); 
  pinMode(MOTOR_FL_ENB, OUTPUT);  

  //servo.attach(8);
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);
}

void loop() {
  Dabble.processInput();
  // put your main code here, to run repeatedly:
  if (GamePad.isUpPressed())
  {
    go_forward(DEFAULT_SPEED);
  }

  if (GamePad.isDownPressed())
  {
    go_backward(DEFAULT_SPEED);
  }

  if (GamePad.isLeftPressed())
  {
    turn_CCW(DEFAULT_SPEED)
  }

  if (GamePad.isRightPressed())
  {
    turn_CW(DEFAULT_SPEED);
  }
  else{
    stop();
  }
}

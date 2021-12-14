/*-----------------------------------------------------------------------------------------------------
  ----------------------------------------------------------------------------------------------------
  ---------------------------------------------------------------------------------------------------

            _____   ____   _____ ____ ____  __  ___
           |  __ \ / __ \ / ____/ __ \___ \/_ |/ _ \
           | |__) | |  | | |   | |  | |__) || | (_) |
           |  _  /| |  | | |   | |  | |__ < | |> _ <
           | | \ \| |__| | |___| |__| |__) || | (_) |
           |_|  \_\\____/ \_____\____/____/ |_|\___/
                    SIMPLE SERVO CONTROLLER

  This is some super simple code for controlling servos via id and angle values.
  This has been made for the Arduino Nano with a PCA9685 16 channel i2c PWM breakout board.

                         -:Wiring:-
                ARDUINO NANO --->    PCA9685
                     A5      --->      SCL
                     A4      --->      SDA
                    GND      --->      GND
                     5V      --->      VCC

  THIS CODE UTILISES THE ADAFRUIT PWM SERVO DRIVER LIBRARY, TO ADD IT TO YOUR ARDUINO IDE:
  - Click on; Sketch
  - Click on; Include Library
  - Click on; Manage Libraries...
  - In the search bar that appears, type in "Adafruit PWM Servo Driver" and click install on the one that appears with the same name.
  Now you have the neccessary libraries to run the following code.

                     -:USING THE CODE:-
                      ----------------
  When uploaded you can then send simple commands to the board to control your servos.
  It must be in the following format:
    ServoNumber,ServoAngle

    So for example:

    UpdateServo(6, 90);

    This will move servo number 6 to an angle of 90 degrees.

  That is everything you need to know to use the board

  Debugging:

  If you send your servo an angle value and it does not line up, then you may need to calibrate the servo minimum and maximum pulse lengths
  Currently they have been calibrated for a range of 0 to 180 degrees for the Towerpro MG996R
  #define SERVOMIN  135 // This is the 'minimum' pulse length count (out of 4096) For the MG996R this wants to be 135
  #define SERVOMAX  482 // this is the 'maximum' pulse length count (out of 4096) For the MG996R this wants to be 482

  ------------------------------------------------------------------------------------------------
  -------------------------------------------------------------------------------------------------
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  135 // This is the 'minimum' pulse length count (out of 4096) For the MG996R this wants to be 135
#define SERVOMAX  482 // this is the 'maximum' pulse length count (out of 4096) For the MG996R this wants to be 482


Adafruit_PWMServoDriver PCA9685 = Adafruit_PWMServoDriver();

int ServoPositions[16][5]; //you can use this to make a 2D array of values for your 16 servos positions for each point of your walking gait

// Name different motors
int backLeftHip = 13;
int backLeftKnee = 14;
int backLeftAnkle = 15;

int frontLeftHip = 10;
int frontLeftKnee = 11;
int frontLeftAnkle = 12;

int backRightHip = 7;
int backRightKnee = 6;
int backRightAnkle = 5;

int frontRightHip = 3;
int frontRightKnee = 2;
int frontRightAnkle = 1;

//Different angles

int angle1 = 90;
int angle2 = 90;
int angle3 = 90;

int angle4 = 90;
int angle5 = 90;
int angle6 = 90;

int angle7 = 90;
int angle8 = 90;
int angle9 = 90;

int angle10 = 90;
int angle11 = 90;
int angle12 = 90;

//----------------------------------------------------------------------------//
void setup() {
  Serial.begin(115200); //Nice faster speed
  PCA9685.begin();
  PCA9685.setPWMFreq(50); //Maximum speed this can be set to is 1600
  Wire.setClock(400000); // Fast 400khz I2C Mode
  Serial.println("PCA9685 Servo Controller Connected & Ready");
}


/*----------------------------------------------------------------------------
   __  __          _____ _   _
  |  \/  |   /\   |_   _| \ | |
  | \  / |  /  \    | | |  \| |
  | |\/| | / /\ \   | | | . ` |
  | |  | |/ ____ \ _| |_| |\  |
  |_|  |_/_/    \_\_____|_| \_|
  ----------------------------------------------------------------------------*/
void loop() {

//  for (int ServoNumber = 1; ServoNumber <= 16; ServoNumber++) // set all servos to 90 degrees
//  {
//    UpdateServo(ServoNumber, 90);
//  }
//  delay(1000);
    

    // Set initial position for all the motors 
    UpdateServo(backLeftAnkle, 90); 
    UpdateServo(frontLeftAnkle, 90); 
    UpdateServo(backRightAnkle, 90); 
    UpdateServo(frontRightAnkle, 90); 
    UpdateServo(backLeftKnee, 90);
    UpdateServo(frontLeftKnee, 90); 
    UpdateServo(backRightKnee, 90); 
    UpdateServo(frontRightKnee, 90); 
    UpdateServo(frontLeftHip, 100); 
    UpdateServo(frontRightHip, 80); 
    UpdateServo(backLeftHip, 70); 
    UpdateServo(backRightHip, 100); 
    delay(1000);

    while(true)
    {

    touchFloorRight(backRightKnee, backRightAnkle);
    touchFloorLeft(backLeftKnee, backLeftAnkle);
    delay(200);
    
    touchFloorLeft(frontLeftKnee, frontLeftAnkle);
    touchFloorRight(frontRightKnee, frontRightAnkle);
    delay(200);
    
    stand(backLeftKnee, backLeftAnkle);
    stand(backRightKnee, backRightAnkle);
    delay(200);

    stand(frontLeftKnee, frontLeftAnkle);
    stand(frontRightKnee, frontRightAnkle);
    delay(200);
    
    
    
    }
//    //Step back left
//    while(1)
//    {
//        
//        touchFloorLeft(backLeftKnee, backLeftAnkle);
//        nextStepLeft(frontLeftKnee, frontLeftAnkle);
//        touching2Right(backRightKnee, backRightAnkle);
//        UpdateServo(backRightHip, 90);
//        touching1Right(frontRightKnee, frontRightAnkle);
//        UpdateServo(frontRightHip, 70);
//        delay(500);
//
//        touching1Left(backLeftKnee, backLeftAnkle);
//        UpdateServo(backLeftHip, 60);
//        touchFloorLeft(frontLeftKnee, frontLeftAnkle);
//        nextStepRight(backRightKnee, backRightAnkle);
//        touching2Right(frontRightKnee, frontRightAnkle);
//        UpdateServo(frontRightHip, 90);
//        delay(500);
//
//        touching2Left(backLeftKnee, backLeftAnkle);
//        UpdateServo(backLeftHip, 70);
//        touching1Left(frontLeftKnee, frontLeftAnkle);
//        UpdateServo(frontLeftHip, 80);
//        touchFloorRight(backRightKnee, backRightAnkle);
//        nextStepRight(frontRightKnee, frontRightAnkle);
//        delay(500);
//
//        nextStepLeft(backLeftKnee, backLeftAnkle);
//        touching2Left(frontLeftKnee, frontLeftAnkle);
//        UpdateServo(frontLeftHip, 100);
//        touching1Right(backRightKnee, backRightAnkle);
//        UpdateServo(backRightHip, 80);
//        touchFloorRight(frontRightKnee, frontRightAnkle);
//        delay(500);
//    }


}
//End of Main
//----------------------------------------------------------------------------//






/*----------------------------------------------------------------------------
   ______ _    _ _   _  _____ _______ _____ ____  _   _  _____
  |  ____| |  | | \ | |/ ____|__   __|_   _/ __ \| \ | |/ ____|
  | |__  | |  | |  \| | |       | |    | || |  | |  \| | (___
  |  __| | |  | | . ` | |       | |    | || |  | | . ` |\___ \
  | |    | |__| | |\  | |____   | |   _| || |__| | |\  |____) |
  |_|     \____/|_| \_|\_____|  |_|  |_____\____/|_| \_|_____/
  ----------------------------------------------------------------------------*/
void UpdateServo (int Id, int Angle) {

  double pulselength = map(Angle, 0, 180, SERVOMIN, SERVOMAX); //map the degree value to pulselength value
  PCA9685.setPWM(Id, 0, pulselength); //Send the angle to the appropiate servo

}
void touchFloorLeft(int knee, int ankle)
{
  UpdateServo(knee, 35);
  UpdateServo(ankle, 50);
}
void touching1Left(int knee, int ankle)
{
  UpdateServo(knee, 80);
  UpdateServo(ankle, 90);
}
void touching2Left(int knee, int ankle)
{
  UpdateServo(knee, 110);
  UpdateServo(ankle, 70);
}
void nextStepLeft(int knee, int ankle)
{
  UpdateServo(ankle, 125);
  delay(50);
  UpdateServo(knee, 35);
}


void touchFloorRight(int knee, int ankle)
{
  UpdateServo(knee, 145);
  UpdateServo(ankle, 130);
}
void touching1Right(int knee, int ankle)
{
  UpdateServo(knee, 100);
  UpdateServo(ankle, 90);
}
void touching2Right(int knee, int ankle)
{
  UpdateServo(knee, 70);
  UpdateServo(ankle, 110);
}
void nextStepRight(int knee, int ankle)
{
  UpdateServo(ankle, 55);
  delay(75);
  UpdateServo(knee, 145);
}
void stand(int knee, int ankle)
{
  UpdateServo(knee, 90);
  UpdateServo(ankle, 90);
}
void startPosition(void)
{

  
}

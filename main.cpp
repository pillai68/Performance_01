#include <FEHUtility.h>
#include <FEHServo.h>
#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHLCD.h>

//Declaring encoders and motors
DigitalEncoder right_encoder(FEHIO::P0_1);
DigitalEncoder left_encoder(FEHIO::P0_0);

FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);

FEHServo buttonServo(FEHServo::Servo0); //declaring the servo to port 0.
AnalogInputPin cds(FEHIO::P2_0); //declaring cds cell

void changeMiniServo();
void move_forward(int percent, int counts);
void turn_right(int percent, int counts);
void turn_left(int percent, int counts);

// ***************************************************************************
int main()
{
    while(true){
      move_forward(25, 10);
    }

  /* yeet
    //Code to make robot read the start light to move
    while(!(cds.Value()>0.300 && cds.Value()<0.358));

    //Moving Robot to jukebox
    int motor_percent = 25; //intializes motor percent
    int counts = 40.49; //intializes encoder counts

    //Portion of code used to navigate the robot from the start area to the jukebox
    move_forward(motor_percent, counts*13.5); //robot moves forward for around 13.5 inches
    turn_left(motor_percent,counts*3); //robot makes a 45 degree left turn
    move_forward(motor_percent,counts*8); //robot moves foward for around 8 inches
    turn_right(motor_percent,counts*6); //robot makes a 90 degree right turn9

    //code to make robot read the light, approach the to press jukebox button
    move_forward(-motor_percent,counts*6); //robot moves backward around 4 inches

    //Moving robot closer to jukebox
    move_forward(-motor_percent,counts*2); //robot moves backward for 2 inches
    //Changing the orientation of buttonServo to read light
    buttonServo.SetMin(525);
    buttonServo.SetMax(2410);
    changeMiniServo();

    //moving robot to Ramp
    move_forward(-motor_percent,counts*2); //robot moves backwards for about 2 inches
    turn_left(motor_percent,counts*6); //makes a 90 degree left turn that's about 6 inches
    move_forward(motor_percent,counts*8); //robot moves forward around 8 inches
    turn_left(motor_percent,counts*6); //makes a 90 degree left turn that's about 6
    move_forward(motor_percent*3,counts*30); //robot moves forward around 30 inches up the ramp
*/
}
//*****************************************************************************

void changeMiniServo(){
    LCD.Clear();
    LCD.WriteLine("CDS Value: " );
    LCD.Write(cds.Value());
    float x = cds.Value();
    if(x>0.170 && x<0.470) { //if cdS cell picks up red
      buttonServo.SetDegree(525);
    }else{
      buttonServo.SetDegree(2410);
    }
}

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

   //Set both motors to desired percent
    right_motor.SetPercent(-percent); //right motor is oriented backwards, so negative means forward
    left_motor.SetPercent(percent);

   //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

   //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int percent, int counts) {
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

   //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

}

//This is the function used to turn the robot counterclockwise.
void turn_left(int percent, int counts) {
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

   //Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(-percent);

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

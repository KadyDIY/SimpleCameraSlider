
#include <AccelStepper.h>
#include <MultiStepper.h>
MultiStepper steppers;

// Define the Pins used
#define home_switchX 9 // x end switch
// Define some steppers and the pins the will use


AccelStepper stepperX(1, 2, 5);
AccelStepper stepperY(1, 3, 6);

long initial_homing=-1;  // Used to Home Stepper at startup


void setup()
{ 
   pinMode(8, OUTPUT);
   digitalWrite(8, LOW);

    pinMode(home_switchX, INPUT_PULLUP);

    delay(5);  // Wait for EasyDriver wake up

    Serial.begin(115200);
    stepperX.setMaxSpeed(3000.0);
    stepperX.setAcceleration(1000.0);
       
    // homeing x
     while (digitalRead(home_switchX))
     {  // Make the Stepper move CCW until the switch is activated   
        stepperX.moveTo(initial_homing);  // Set the position to move to
        initial_homing--;  // Decrease by 1 for next move if needed
        stepperX.run();  // Start moving the stepper
       // delay(1);
     }
      stepperX.setCurrentPosition(0);  // Set the current position as zero for now
      initial_homing=1;
      while (!digitalRead(home_switchX))
      { // Make the Stepper move CW until the switch is deactivated
         stepperX.moveTo(initial_homing); 
         stepperX.run();
         initial_homing++;
         //delay(2);
      }
 
    stepperX.setCurrentPosition(0);

    stepperX.setMaxSpeed(1000);
    stepperX.setAcceleration(1000);

    stepperY.setMaxSpeed(1000);
    stepperY.setAcceleration(1000);

    steppers.addStepper(stepperX);
    steppers.addStepper(stepperY);
}

void loop()
{
 long positions[2];

    if(digitalRead(home_switchX)) //end switch abused as input to move between position 1 and 12000
    {
    delay(100);
    positions[0] = 0;
    positions[1] = 0;
    steppers.moveTo(positions);

    steppers.runSpeedToPosition();

    delay(100);
    positions[0] = 3200 * 8;
    positions[1] =  -1400;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
    }

}

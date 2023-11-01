#include "ROBUSMovement.hpp"


//ErrorSum values will be recorded through
//multiple PIDs to adjust through time
float errorSumStraight = 0.0f;
float errorSumTurn = 0.0f;

//These parameters are reused and reset
// every time a new movement is started
float currentPulseRight = 0.0f;
float currentPulseLeft  = 0.0f;
float rightPulse   = 0.0f;
float leftPulse    = 0.0f;
unsigned long previousInterval_ms = 0;
float previousValue = 0.0f;

double SpeedLeftTrigo  = 0.0;
double SpeedRightTrigo = 0.0;

int speedStatus = STATUS_STOPPED;

double wantedPulse = 0.0;
double wantedPulseDiff = 0.0;

double currentSpeed = 0.0;

float ratioContinuous = 0.0f;

double currentPulseRight_continuous = 0;



/**
 * @brief Stops the robot by putting
 * the speed of both motors at 0.
 * 
 * @return void 
 */
void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
  speedStatus = STATUS_STOPPED;
  currentSpeed = 0;
}

/**
 * @brief Basic math allowing to return the number
 * of pulses needed to reach the desired distance
 * (in centimeters). Based on the formula :
 * 
 * wanted distance/wanted pulse = circumference_wheel/
 * pulse of 1 rotation
 * 
 * @param distance_cm
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return float 
 */
float ROBUSMovement_moveStraight_math(int distance_cm)
{
  float pulse = ((float)distance_cm / CIRCUMFERENCE_WHEEL) * 3200.0f;
  return pulse;
}

/**
 * @brief Basic PID function that returns an
 * adjusted value over time based on a wanted
 * value. P,I,D numbers are used to tune the
 * responsiveness of the PID and varies
 * depending on its applications.
 * 
 * For example, to tune the difference
 * between 2 motors that should be the same,
 * you would first get the difference between
 * the 2, knowing you want it to be 0, and
 * then call he function as following:
 * speedCorrection = PID(p, i, d, difference, 0);
 * 
 * @param proportional 
 * the P value of the PID. The increase of the
 * number the further it is from wanted value.
 * @param integral 
 * the I value of the PID. In other words, the
 * small corrections done over time if there's
 * oscillaton.
 * @param derivative
 * The D value of the PID. When the value
 * begins to reach the wanted value, this
 * will deaccelerate the PID.
 * @param currentValue 
 * @param wantedValue 
 * @return float 
 */
float PID(float baseValue, float proportional, float integral, float derivative, float currentValue, float wantedValue, float* errorSum, float* previousValue)
{
  float error = wantedValue-currentValue;
  float derivativeError = currentValue-(*previousValue);
  *errorSum += error;

  float PID = baseValue + proportional*error + integral*(*errorSum) + derivative*(derivativeError);

  *previousValue = currentValue;

  return PID;
}

/**
 * @brief Trigonpometry math that uses sin and
 * cos to control the ratio of movement between
 * the two motors, thus changin the arc.
 * 
 * @param angle 
 *  
 * @param direction 
 *  
 * @return void 
 */
void ROBUSMovement_trigoMath(double angle)
{
  angle = (angle+DIRECTION_FORWARD) * PI / 180.0;
  SpeedLeftTrigo  = sin(angle);
  SpeedRightTrigo = cos(angle);
}

/**
 * @brief Function used in all movement
 * functions to have a global speed and 
 * avoid wasting time stopping after
 * each movement.
 * 
 * @return void 
 */
void ROBUSMovement_acceleration(){
  if      ((currentSpeed <  MAXSPEED)  && (speedStatus == STATUS_ACCELERATING)) currentSpeed+=0.01;
  else if ((currentSpeed >= MAXSPEED)  && (speedStatus == STATUS_ACCELERATING)) speedStatus = STATUS_MAXSPEED;
  else if ((currentSpeed >  STOPSPEED) && (speedStatus == STATUS_DECELERATING)) currentSpeed-=0.03;
  else if ((currentSpeed <= STOPSPEED) && (speedStatus == STATUS_DECELERATING)) {
    currentSpeed = 0;
    speedStatus = STATUS_STOPPED;
  }
  else if ((currentSpeed >  STOPSPEED) && (speedStatus == STATUS_EMERGENCYSTOP)) currentSpeed-=0.08;
  else if ((currentSpeed <= STOPSPEED) && (speedStatus == STATUS_EMERGENCYSTOP)) {
    currentSpeed = 0;
    speedStatus = STATUS_STOPPED;
  }
}

/**
 * @brief Produit croisé to
 * calculate the movement according 
 * to the wanted movement
 * 
 * @param arcangle
 *  
 * @return void 
 */
void ROBUSMovement_arcPulse(double arcangle){
  wantedPulseDiff = arcangle*ARC_PULSE_DIFFERENCE/90;
}



/**
 * @brief Stops the robot abruptly
 * without letting it topple over 
 *  
 * @return void 
 */
void ROBUSMovement_EmergencyStop(){
  speedStatus = STATUS_EMERGENCYSTOP;
  int currentInterval_ms = millis();
  while(speedStatus != STATUS_STOPPED){
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      ROBUSMovement_acceleration();
      MOTOR_SetSpeed(RIGHT_MOTOR, SpeedRightTrigo*currentSpeed);
      MOTOR_SetSpeed(LEFT_MOTOR, SpeedLeftTrigo*currentSpeed);
      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms = millis();
  }
}

/**
 * @brief Sets the movement of
 * the robot according to the desired 
 * movement. 
 * 
 * Turns are considered arcs. If the
 * angle is set to 0, it will go straight.
 * 
 * @param color
 * depending on which color the robot is,
 * the arc radius will change.
 * 
 * @param arcangle
 * determines how much the robot moves
 * according the the arc radius. Based on 90°.
 * Only used for turning movements, not straight.
 * 
 * @param direction
 * Determines whether the robot will go
 * right, left, forward or backward.
 * 
 * @param distance
 * This is only used when the robot goes
 * straight. Determines how long the robot
 * will move for before going out of the
 * function.
 * 
 * @return void 
 */
void ROBUSMovement_arcMove_global(int color, double arcangle, int direction, int turnDirection, double distance_cm){
  speedStatus = STATUS_ACCELERATING;

  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  double offSet = 0.0;
  if (direction == BACKWARD) offSet = 180.0;
  else if (direction == 2) offSet = 90.0;
  else if (direction == 3) offSet = 270.0;

  int requirement = 0;
  double theta = offSet;

  //if an arcangle of 0: go straight
  if (arcangle == 0) {
    wantedPulse = (ROBUSMovement_moveStraight_math(distance_cm));
    //Serial.println(wantedPulse);
    requirement = REQUIREMENT_STRAIGHT_CM;
    theta += 0;
  }
  //otherwise, travel the specified arc according to the color
  else { 
    
    requirement = REQUIREMENT_TURN;

    if (color == COLOR_GREEN)  {
      theta += THETA_GREEN;
      arcangle+=2;
    }
    else if (color == COLOR_YELLOW) {
      theta += THETA_YELLOW;
      //arcangle -=1;
    }
    else if (color == COLOR_BLUE) {
      theta += THETA_BLUE;
    }
    else if (color == COLOR_PURPLE) {
      theta += THETA_PURPLE;
    }

    theta = theta*turnDirection;

    if (arcangle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
    else ROBUSMovement_arcPulse(arcangle);
    //Serial.println(wantedPulseDiff);
  }

  ROBUSMovement_trigoMath(theta);

  double speedLeft  = currentSpeed*SpeedLeftTrigo;
  double speedRight = currentSpeed*SpeedRightTrigo;
  float ratio = SpeedLeftTrigo/SpeedRightTrigo;

  double currentPulseLeft  = 0;
  double currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;

  unsigned long currentInterval_ms = millis();
  
  while(ROBUSMovement_whileStopRequirement(requirement, currentPulseRight, currentPulseLeft)){
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      ROBUSMovement_acceleration();

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(currentSpeed, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      MOTOR_SetSpeed(RIGHT_MOTOR, SpeedRightTrigo*currentSpeed);
      
      previousInterval_ms = currentInterval_ms;

    }

    currentInterval_ms  = millis();
  }
  
}

/**
 * @brief Sets the movement of
 * the robot according to the desired 
 * movement. Returns 1 if the robot should continue
 * and returns 0 if the robot has finished its movement
 * 
 * @param requirement
 * determines what the ending movement condition is.
 * If 0 (REQUIREMENT_TURN), the movement is a turn
 * and the difference of pulses between the motors
 * is used to determine when it finishes.
 * If 1 (REQUIREMENT_STRAIGHT_CM), the movement
 * is straight. It stops when the right encoder
 * reads more than the required value calculated
 * 
 * @param currentPulseRight, currentPulseLeft
 * These parameters are used to verify if the
 * robot should stop the movement.
 * 
 * @return bool 
 */
bool ROBUSMovement_whileStopRequirement(int requirement, double currentPulseRight, double currentPulseLeft){
  switch(requirement){
    case REQUIREMENT_TURN:
      if (abs(currentPulseLeft-currentPulseRight)>wantedPulseDiff) return 0;
      break;
    case REQUIREMENT_STRAIGHT_CM:
      if (abs(currentPulseRight) >= wantedPulse) {
        return 0;
      }
      break;      
  }
  return 1;
}


/**
 * @brief This function needs to be called
 * before any movement loop with an ending
 * condition that is another function.
 * 
 * @return void 
 */
void ROBUSMovement_continuousPID_begin(int direction){
  speedStatus = STATUS_ACCELERATING;

  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  double angle = 0.0;
  if (direction == BACKWARD) angle = 180.0;
  ROBUSMovement_trigoMath(angle, 1);

  double speedLeft  = currentSpeed*SpeedLeftTrigo;
  double speedRight = currentSpeed*SpeedRightTrigo;
  ratioContinuous = SpeedLeftTrigo/SpeedRightTrigo;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
}



/**
 * @brief This function needs to be called
 * before any movement loop with an ending
 * condition that is another function.
 * It can also allow for a distance ending
 * poition. If that is the case, the ending 
 * condition needs to be added in the loop
 * using the 
 * "ROBUSMovement_whileStopRequirement(REQUIREMENT_STRAIGHT_CM, currentPulseRight, 0)"
 *  function
 * 
 * @param distance_cm
 * Distance for ending condition
 * 
 * @return void 
 */
void ROBUSMovement_continuousPID_begin_cm(double distance_cm){

  wantedPulse = (ROBUSMovement_moveStraight_math(abs(distance_cm)));

  speedStatus = STATUS_ACCELERATING;

  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  double angle = 0.0;
  if (distance_cm < 0) angle = 180.0;
  ROBUSMovement_trigoMath(angle);

  double speedLeft  = currentSpeed*SpeedLeftTrigo;
  double speedRight = currentSpeed*SpeedRightTrigo;
  ratioContinuous = SpeedLeftTrigo/SpeedRightTrigo;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
  currentPulseRight_continuous = 0;
}

/**
 * @brief This function needs to be called
 * during any movement loop with an ending
 * condition that is another function.
 * It can also allow for a distance ending
 * position. If that is the case, the ending 
 * condition needs to be added in the loop
 * using the 
 * "ROBUSMovement_stopRequirementContinuous()" 
 * function.
 * 
 * @return void 
 */
void ROBUSMovement_momentaryPID_inwhile(){
  if((millis()-previousInterval_ms)>PID_INTERVAL_MS){
    ROBUSMovement_acceleration();

    rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
    leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
    currentPulseRight_continuous += abs(rightPulse);

    MOTOR_SetSpeed(LEFT_MOTOR, SpeedLeftTrigo*PID(currentSpeed, KP, KI, 0, (abs(leftPulse)), (ratioContinuous*abs(rightPulse)), &errorSumTurn, 0));

    MOTOR_SetSpeed(RIGHT_MOTOR, SpeedRightTrigo*currentSpeed);
    
    previousInterval_ms = millis();
  }  
}

/**
 * @brief This function needs to be called
 * inside any movement loop with an ending
 * condition that is another function AND
 * needs to have a maximum distance.
 * 
 * @param 0
 * distance has been reached
 * @param 1
 * movement should continue
 * 
 * @return bool 
 */
bool ROBUSMovement_stopRequirementContinuous(){
  if (abs(currentPulseRight_continuous) >= wantedPulse) return 0;
  else return 1;    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

float ROBUSMovement_turn_math(double degrees)
{
  float pulse = DISTANCE_BT_WHEEL * PI * (float)degrees;
  pulse = pulse / (360.0f);
  return pulse;
}

int requirement = 0;
double theta = 0.0;
double speedLeft = 0.0;
double speedRight = 0.0;
double ratio = 0.0;

void ROBUSMovement_arcMove_straight(int direction, double distance_cm){
  double offSet = 0.0;
  if (direction == BACKWARD) offSet = 180.0;
  if (direction == STRAIGHT_LEFT_TURN) offSet = 90.0;
  if (direction == STRAIGHT_RIGHT_TURN) offSet = 270.0;
  requirement = 0;
  theta = offSet;

  wantedPulse = (ROBUSMovement_moveStraight_math(distance_cm));

  requirement = REQUIREMENT_STRAIGHT_CM;
  
  ROBUSMovement_ArcMove_Init();
  ROBUSMovement_arcMove(requirement);
}

void ROBUSMovement_arcMove_turn(int color, int direction, int directionTurn, double arcAngle){

  double offSet = 0.0;
  if (direction == BACKWARD) offSet = 180.0;
  theta += offSet;

  requirement = REQUIREMENT_TURN;

  if (color == COLOR_GREEN)  {
    theta += THETA_GREEN;
    arcAngle+=2;
  }
  else if (color == COLOR_YELLOW) {
    theta += THETA_YELLOW;
    //arcangle -=1;
  }
  else if (color == COLOR_BLUE) {
    theta += THETA_BLUE;
  }

  theta = theta*directionTurn;

  if (arcAngle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
  else ROBUSMovement_arcPulse(arcAngle);

  
  ROBUSMovement_ArcMove_Init();
  ROBUSMovement_arcMove(requirement);

}

void ROBUSMovement_ArcMove_Init(){
	ROBUSMovement_trigoMath(theta);

  speedLeft  = currentSpeed*SpeedLeftTrigo;
  speedRight = currentSpeed*SpeedRightTrigo;
  ratio = abs(SpeedLeftTrigo)/abs(SpeedRightTrigo);
  
  speedStatus = STATUS_ACCELERATING;

  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  currentPulseLeft  = 0;
  currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
}

void ROBUSMovement_arcMove(int requirement){
  
	while(ROBUSMovement_whileStopRequirement(requirement, currentPulseRight, currentPulseLeft)){
    if((millis()-previousInterval_ms)>PID_INTERVAL_MS){
      ROBUSMovement_acceleration();

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(currentSpeed, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      MOTOR_SetSpeed(RIGHT_MOTOR, SpeedRightTrigo*currentSpeed);
      
      previousInterval_ms = millis();
	  }
	}
  
}


/////////////////////////////
/////////////////////////////
/////////////////////////////
/////////////////////////////
///// UNUSED  FUNCTIONS /////
/////////////////////////////
/////////////////////////////
/////////////////////////////
/////////////////////////////

/**
 * @brief Resets the movement parameters
 * affecting the PID (when different
 * movements)
 * 
 * @return void 
 */
void ROBUSMovement_resetParameters()
{
  errorSumStraight = 0.0f;
  errorSumTurn = 0.0f;
}
/**
 * @brief Basic math allowing to return the number
 * of pulses needed to reach the desired angle
 * (in centimeters). Based on the formula :
 * 
 * (deg/360) * DISTANCE_BT_WHEEL * (3200/(DIAMETER_WHEEL*pi))
 *  or 
 * (deg*DISTANCE_BT_WHEEL*3200)/(360*DIAMETER_WHEEL)
 * 
 * @param degrees
 * Number of degrees the robot wants to turn. 
 * @return float 
 */
float ROBUSMovement_turnOnSelf_math(int degrees)
{
  float pulse = DISTANCE_BT_WHEEL * (float)degrees * 3200.0f;
  pulse = pulse / (360.0f*DIAMETER_WHEEL);
  return pulse;
}


/**
 * @brief Resets the movement variables
 * affecting the PID (every movement).
 * Is called in every movement function.
 * 
 * Resets the encoders
 * Sets the current pulses,
 * pulses, previous intervals
 * and previous variables to 0.
 * 
 * @return void 
 */
void ROBUSMovement_initMovement()
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);
  currentPulseRight = 0.0f;
  currentPulseLeft  = 0.0f;
  rightPulse   = 0.0f;
  leftPulse    = 0.0f;
  previousInterval_ms = 0;
  previousValue = 0.0f;
}

/**
 * @brief Basic movement function that allows the
 * robot to go in a straight line according to a
 * set distance in centimeters.
 * 
 * @param direction 
 * The direction determines whether the robot will
 * go forward or backwards. It is multiplied by
 * the speed to set the motors' speed & direction.
 * @param speed_pct 
 * The speed at which the robot should move. Can
 * be anything from 0 (not moving) to 1 (max speed).
 * @param distance_cm
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return void 
 */
void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm)
{
  float wantedPulse = (ROBUSMovement_moveStraight_math(distance_cm));
  //float wantedPulse = 3200;
  //Serial.println(wantedPulse);

  speed_pct = direction*speed_pct;
  float newSpeed = speed_pct;

  //ROBUSMovement_initMovement();

  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);
  currentPulseRight = 0.0f;
  currentPulseLeft  = 0.0f;
  rightPulse   = 0.0f;
  leftPulse    = 0.0f;
  previousInterval_ms = 0;
  previousValue = 0.0f;
  //int previousEncoderInterval_ms = 0;

  //float pulsePIDLeft = 0.0f;
  //float pulsePIDRight = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, speed_pct);
  MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct);  

  unsigned long currentInterval_ms  = millis();
  while (currentPulseRight <= wantedPulse)
  {
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft += abs(leftPulse);

      if((newSpeed < 0.4f) && (newSpeed > -0.4f)) MOTOR_SetSpeed(LEFT_MOTOR, PID(speed_pct, KP, KI, KD, abs(leftPulse), abs(rightPulse), &errorSumStraight, &previousValue));

      //pulsePIDRight = 0.0f;
      //pulsePIDLeft = 0.0f;

      previousInterval_ms = currentInterval_ms;
      
    }
  
    

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  
  Serial.print("RIGHT :");
  Serial.println(currentPulseRight);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSumStraight);
  //Serial.print("derivative :");
  //Serial.println((pulsePIDLeft-(previousValue)));
  
}

/* DEBUGGING COPY PASTE
Serial.print("RIGHT : ");
Serial.println(SpeedRightTrigo*currentSpeed);
Serial.print("LEFT : ");
Serial.println(speedLeft);
      */

/*
void ROBUSMovement_arcMove(double speed_pct, int color, int arcangle, int direction){
  if (arcangle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
  else ROBUSMovement_arcPulse(arcangle);

  

  double theta = 0;
  if      (color == COLOR_GREEN)  theta = THETA_GREEN;
  else if (color == COLOR_YELLOW) theta = THETA_YELLOW;
  else if (color == COLOR_BLUE)   theta = THETA_BLUE;

  ROBUSMovement_trigoMath(theta, direction);

  double speedLeft  = speed_pct*SpeedLeftTrigo;
  double speedRight = speed_pct*SpeedRightTrigo;
  float ratio = SpeedLeftTrigo/SpeedRightTrigo;

  double currentPulseLeft  = 0;
  double currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
  unsigned long currentInterval_ms = millis();

  while(abs(currentPulseLeft-currentPulseRight)<wantedPulseDiff){

    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(speed_pct, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();

}*/

/**
 * @brief Basic movement function that allows the
 * robot to go in a straight line according to a
 * set distance in centimeters.
 * 
 * @param direction 
 * The direction determines whether the robot will
 * go forward or backwards. It is multiplied by
 * the speed to set the motors' speed & direction.
 * @param speed_pct 
 * The speed at which the robot should move. Can
 * be anything from 0 (not moving) to 1 (max speed).
 * @param degrees
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return void 
 */
/*void ROBUSMovement_turnOnSelf(float direction, float speed_pct, float degrees)
{
  float wantedPulse = ROBUSMovement_turnOnSelf_math(degrees);
  Serial.println(wantedPulse);

  float speedRight = -1.0f*direction*speed_pct;
  float newSpeedLeft  = direction*speed_pct;

  //ROBUSMovement_initMovement();
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);
  currentPulseRight = 0.0f;
  currentPulseLeft  = 0.0f;
  rightPulse   = 0.0f;
  leftPulse    = 0.0f;
  previousInterval_ms = 0;
  previousValue = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  unsigned long currentInterval_ms  = millis();
  while (abs(currentPulseRight) <= wantedPulse)
  {

    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft += abs(leftPulse);
      
      newSpeedLeft = PID(speed_pct, KP, KI, KD, abs(leftPulse), abs(rightPulse), &errorSumTurn, &previousValue);

      if((newSpeedLeft < 0.6f) && (newSpeedLeft > -0.6f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);

      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  
  
}*/

///////////////////////

/**
 * @brief Basic math allowing to return the number
 * of pulses needed to reach the desired distance
 * (in centimeters). Based on the formula :
 * 
 * wanted distance/wanted pulse = circumference_wheel/
 * pulse of 1 rotation
 * 
 * @param distance_cm
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return float 
 */
/*float ROBUSMovement_arcPulse_math(float arc_R, float arc_L)
{
  float pulse_R = (arc_R / CIRCUMFERENCE_WHEEL) * 3200.0f;
  float pulse_L = (arc_L / CIRCUMFERENCE_WHEEL) * 3200.0f;
  return pulse_R, pulse_L;
}

void ROBUSMovement_arcPulse(int arcangle){
  wantedPulseDiff = arcangle*ARC_PULSE_DIFFERENCE/90;
}

void ROBUSMovement_arcMove(double speed_pct, int color, int arcangle, int direction){
  if (arcangle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
  else ROBUSMovement_arcPulse(arcangle);

  double theta = 0;
  if      (color == COLOR_GREEN)  theta = THETA_GREEN;
  else if (color == COLOR_YELLOW) theta = THETA_YELLOW;

  ROBUSMovement_trigoMath(theta, direction);

  double speedLeft  = speed_pct*SpeedLeftTrigo;
  double speedRight = speed_pct*SpeedRightTrigo;
  float ratio = SpeedLeftTrigo/SpeedRightTrigo;

  double currentPulseLeft  = 0;
  double currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
  unsigned long currentInterval_ms = millis();

  while(abs(currentPulseLeft-currentPulseRight)<wantedPulseDiff){

    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(speed_pct, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();

}

void ROBUSMovement_EmergencyStop(){
  speedStatus = STATUS_EMERGENCYSTOP;
  int currentInterval_ms = millis();
  while(speedStatus != STATUS_STOPPED){
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      ROBUSMovement_acceleration();
    }

    currentInterval_ms  = millis();
  }
}

void ROBUSMovement_arcMoveTEST(int color, int arcangle, int direction){
  speedStatus = STATUS_ACCELERATING;

  if (arcangle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
  else ROBUSMovement_arcPulse(arcangle);

  double theta = 0;
  if      (color == COLOR_GREEN)  theta = THETA_GREEN;
  else if (color == COLOR_YELLOW) theta = THETA_YELLOW;

  ROBUSMovement_trigoMath(theta, direction);

  double speedLeft  = currentSpeed*SpeedLeftTrigo;
  double speedRight = currentSpeed*SpeedRightTrigo;
  float ratio = SpeedLeftTrigo/SpeedRightTrigo;

  double currentPulseLeft  = 0;
  double currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
  unsigned long currentInterval_ms = millis();

  while(abs(currentPulseLeft-currentPulseRight)<wantedPulseDiff){
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      ROBUSMovement_acceleration();

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(currentSpeed, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      MOTOR_SetSpeed(RIGHT_MOTOR, abs(SpeedRightTrigo*currentSpeed));

      Serial.println(SpeedRightTrigo*currentSpeed);

      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_EmergencyStop();

}*/

*/


#pragma once
#include <LibRobus.h>

#define CIRCUMFERENCE_WHEEL (3.1416 * DIAMETER_WHEEL)
#define DISTANCE_BT_WHEEL 18.6f // diamètre entre les deux roues en cm  //18.6f A et 19.2f B
#define DIAMETER_WHEEL 7.7f     // diametre de la roue (cm)

// ROBUS CONSTANTS
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1

// MOVEMENT CONSTANTS
// #define FORWARD 1.0f
#define FORWARD 0
#define BACKWARD -1.0f
#define RIGHT_TURN 1.0f
#define LEFT_TURN -1.0f

// PID CONSTANTS
#define PID_INTERVAL_MS 25.0l // 25

#define KU 0.004f // 0.03
#define TU 40.0f  // 50.0f STRAIGHT

#define TI (TU / 2.0f)
#define TD (TU / 8.0f)
#define KP (KU / 2.5f)
#define KI (KU / TI)
#define KD 0.0005 //(KU*TD) to be added in later after more testing.

#define STATUS_STOPPED 0
#define STATUS_ACCELERATING 1
#define STATUS_DECELERATING 2
#define STATUS_MAXSPEED 3
#define STATUS_EMERGENCYSTOP 4

#define MAXSPEED 0.75
#define STOPSPEED 0.0

#define ARC_PULSE_DIFFERENCE 3865

#define COLOR_GREEN 1
#define COLOR_BLUE 2
#define COLOR_YELLOW 3
#define COLOR_PURPLE 4

#define THETA_GREEN 11
#define THETA_YELLOW 6.8
#define THETA_BLUE 18
#define THETA_SMALLRADIUS 25

#define DIRECTION_FORWARD 45
#define DIRECTION_BACKWARD 135

#define REQUIREMENT_TURN 0
#define REQUIREMENT_STRAIGHT_CM 1

#define NOT_USED 0

#define STRAIGHT_8_FT 243.84
#define STRAIGHT_2_FT 53.34 // 60.96cm is too long so 1.75ft

// FUNCTIONS

void ROBUSMovement_stop();

void ROBUSMovement_resetParameters();

void ROBUSMovement_initMovement();

float ROBUSMovement_turnOnSelf_math(int degrees);

float ROBUSMovement_moveStraight_math(int distance_cm);

float PID(float baseValue, float proportional, float integral, float derivative, float currentValue, float wantedValue, float *errorSum, float *previousValue);

void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm);

void ROBUSMovement_turnOnSelf(float direction, float speed_pct, float degrees);

// ARC FUNCTIONS

void ROBUSMovement_trigoMath(double angle, int turnDirection);

void ROBUSMovement_acceleration(double currentSpeed);

void ROBUSMovement_arcPulse(double arcangle);

void ROBUSMovement_arcMove(double speed_pct, int color, int arcangle, int direction);

void ROBUSMovement_arcMove_global(int color, double arcangle, int direction, int turnDirection, double distance_cm);

void ROBUSMovement_EmergencyStop();

bool ROBUSMovement_whileStopRequirement(int requirement, double currentPulseRight, double currentPulseLeft);

void ROBUSMovement_momentaryPID_inwhile();

// Continuous movement

bool ROBUSMovement_stopRequirementContinuous();

void ROBUSMovement_continuousPID_begin_cm(double distance_cm);

void ROBUSMovement_continuousPID_begin();

bool ROBUSMovement_stopRequirementContinuous();

/// TEST

void ROBUSMovement_arcMove_straight(int direction, double distance_cm);
void ROBUSMovement_arcMove_turn(int color, int direction, int directionTurn, double arcAngle);
void ROBUSMovement_ArcMove_Init();
void ROBUSMovement_arcMove(int requirement);

void ROBUSMovement_turnOnSelf_deg(float direction, float speed_pct, float degrees);
void ROBUSMovement_turnOnSelf_cedric(float direction, float speed_pct, int turn_degrees); // à revoir
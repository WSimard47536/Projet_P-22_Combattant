#include "Resolution/ChallengeSolver.hpp"

RobotPosition currentRobotPosition;

void ChallengeSolver_Init()
{
    currentRobotPosition.positionX_pulses = 0; //START POSITION_x

}

float GetRobotOrientation()
{
    // Faire arctan pour avoir en degrés
    return (position.positionX_pulses % FULL_ROTATIONS_PULSES) / (position.positionY_pulses % FULL_ROTATIONS_PULSES);
}

void ChallengeSolver_ExecuteAllSteps()
{

}

void ChallengeSolver_ExecuteFirstLap()
{
    // Turn Right (zone 1)
    // Tourner en arc de 90 degrés à droite (rayon dépendant de la zone assignée)

    // Straight (zone 2)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, 60.96f); // MESURER LA DISTANCE SUR LE PARCOURS

    // Turn Right (zone 3)
    // Tourner en arc de 90 degrés à droite (rayon dépendant de la zone assignée)

    // Move Straight and Whack the cup (zone 4 - 5)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, 243.84f); // MESURER LA DISTANCE SUR LE PARCOURS

    // Turn Right on self or other (zone 6)
    ROBUSMovement_turnOnSelf(RIGHT_TURN, 0.25f, 25);
    // Go forward until center line follower detects line (zone 6)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, 25.0f); // REVOIR LA DISTANCE

    // Follow line until ball is found (zone 6 - 7 - 8)
    // SUIVRE LA LIGNE
    // Drop cup on ball
    // DROP LE CUP

    // Go to zone 9 (zone 6 - 7 - 8)
    // GO TO ZONE 9

    // Go to start with jump (zone 9 - 0)
    ROBUSMovement_moveStraight(FORWARD, 0.40f, 121.92f); // MESURER LA DISTANCE ET AJUSTER AVEC JUMP
    ROBUSMovement_moveStraight(FORWARD, 0.25f, 121.92f); // MESURER LA DISTANCE
}

void ChallengeSolver_ExecuteSecondLap()
{
    // Turn Right (zone 1)
    // Tourner en arc de 90 degrés à droite (zone bleue)

    // Straight (zone 2)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, 60.96f); // MESURER LA DISTANCE + 1 pied si zone jaune

    // Turn Right (zone 3)
    // Tourner en arc de 90 degrés à droite (zone bleue)

    // Straight (zone 4 - 5)
    ROBUSMovement_moveStraight(FORWARD, 0.25f, 121.92f); // MESURER LA DISTANCE

    // Turn Right (zone 6)
    // Tourner en arc de 90 degrés à droite (4 - 2.6 pieds de rayon) MESURER LES VRAIES VALEURS

    // Straight (zone 6 - 9)
    // Avancer la distance à mesurer pour aller jusqu'à la zone verte

    // Turn Right ()
}

void ChallengerSolver_ExecuteRace()
{

}
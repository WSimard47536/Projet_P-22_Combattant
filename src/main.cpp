#include "ROBUSMovement.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  InitializeProximitySensors();
}

void loop()
{
  //waitForWhistle();

  /*if (ROBUS_IsBumper(3))
  {
    MazeSolver_init();
    while (!MazeSolver_hasCompletedMaze())
    {
      if (GetWall())
      {
        MazeSolver_setObstacle();
      }
      MazeSolver_setNextMoves();
      MazeSolver_executeNextMoves();
    }
  }*/
  //ROBUSMovement_turnOnSelf(LEFT_TURN, 0.15f, 90);
  //delay(1500);
  //ROBUSMovement_turnOnSelf(RIGHT_TURN, 0.15f, 90);
  //delay(1500);
  //ROBUSMovement_moveStraight(FORWARD, 20, 50);
}
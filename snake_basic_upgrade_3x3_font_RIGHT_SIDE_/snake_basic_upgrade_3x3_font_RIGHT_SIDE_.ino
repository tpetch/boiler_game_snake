
/* Libraries Used */

#include "pitches.h"
#include <FastLED.h>
#include <LinkedList.h>
#include <arduino-timer.h>

/* Button Pins */

//#define START_PIN 19  // Yellow Wire
#define UP_PIN 1     // Green Wire
#define DOWN_PIN 23  // Orange Wire
#define LEFT_PIN 17  // White Wire
#define RIGHT_PIN 0  // Red Wire

/* Direction Definitions */

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

/* LED Definitions */

#define NUM_LEDS 1120
#define LED_PIN 2
#define LED_BACK_PIN 14
#define SPEAKER_PIN 19
int rows = 12;
int columns = 6;
CRGB leds[NUM_LEDS];
//CRGB leds2[NUM_LEDS];

/* Create a timer */

auto timerOne = timer_create_default();

/* Assorted Global Variables */

int bot = 5;
int top = 0;
int gameOn = 0;
int loopTimer = 10000;
int snakeStartY = 3;
int snakeScore = 0;
int Apple2Enabled = 0;
int soundOn = 0;
int soundTimer = 0;
int resetDelay = 250;

/* Game State Variables */

#define MAX_SPEED 100
#define MIN_SPEED 600
#define SPEED_LOSS 100
int speedCap = 0;
int gameSpeed = MIN_SPEED;
int timer = 0;
int currDirection = DIR_LEFT;

/* Game Element Color Definitions */

CRGB appleColor = CRGB(90, 7, 5);
CRGB snakeColor = CRGB(5, 30, 30);
CRGB emptyColor = CRGB(3, 5, 2);
CRGB solidColor = CRGB(20, 10, 15);


/* Class that represents a point on the matrix. Indexed starting at 0 */

class Point {
private:
  byte x;
  byte y;
public:
  Point(byte x, byte y) {
    this->x = x;
    this->y = y;
  }
  byte getX() {
    return x;
  }
  byte getY() {
    return y;
  }
  boolean isEqual(int x, int y) {
    return this->x == x && this->y == y;
  }
};

/* Body of the snake, last element representing the tail, first element representing the head */

LinkedList<Point *> snakePositions = LinkedList<Point *>();

/* Where the apple is located */

Point *applePosition;
Point *apple2Position;

/* Initial setup */

void setup() {
  Serial.begin(9600);


  /* Initialize pins */

  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(SPEAKER_PIN, OUTPUT);

  /* Pick initial apple positions */

  applePosition = getApplePosition();
  apple2Position = getApple2PositionDefault();

  /* Set up WS2812b leds */

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_BACK_PIN, GRB>(leds, NUM_LEDS);

  /* Make sure speaker is off. */

  noTone(SPEAKER_PIN);

  /* Set created timer to refresh background every 8 seconds */

  timerOne.every(8000, backgroundBasicSmall);
}

void loop() {


  /* Game functions on following basic structure:
    When game boots or ends, gameOn is set to 0. This tells the game to turn off the speaker (just in case), and put up a new backgound, which changes gameOn to 1
    When gameOn is 1, the game continuously checks for a start button press and occasionally changes the background. If start is pressed, the check function starts the game.
    When gameOn is 2, the game is running. When the player loses, an end of game sequence happens to show the score and reset the game, and gameOn is set back to 0. */


  if (gameOn == 0) {


    backgroundBasic();
    noTone(SPEAKER_PIN);


  } else if (gameOn == 1) {


    gameOnCheckandStart();

    /* Timer ticks every millisecond during default state, such that a new background will only trigger without a game running */
    timerOne.tick();


  } else if (gameOn == 2) {


    /* Get next snake position */
    Point *nextPoint = getNextPosition();

    /* check if we are still valid and continue the game, otherwise end game */
    if (isNextPointValid(nextPoint)) {

      playGame(nextPoint);

    } else {

      resetGame();

    }


  }
}



void column(int columnNum) {  //column infatiuation
  int whiteOrnot = random(0, 18);

  if (whiteOrnot < 3) {

    for (int i = 0; i < 17; i++) {

      //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
      leds[i + ((columnNum)*16)].r = 20;
      leds[i + ((columnNum)*16)].g = 20;
      leds[i + ((columnNum)*16)].b = 20;
    }
  } else if (whiteOrnot > 3 && whiteOrnot < 9) {

    for (int i = 0; i < 17; i++) {


      //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
      leds[i + ((columnNum)*16)].r = 12 * 0.1;
      leds[i + ((columnNum)*16)].g = 107 * 0.1;
      leds[i + ((columnNum)*16)].b = 237 * 0.1;
    }
  } else if (whiteOrnot > 9 && whiteOrnot < 14) {

    for (int i = 0; i < 17; i++) {


      //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
      leds[i + ((columnNum)*16)].r = 0 * 0.1;
      leds[i + ((columnNum)*16)].g = 162 * 0.1;
      leds[i + ((columnNum)*16)].b = 253 * 0.1;
    }
  } else if (whiteOrnot > 14 && whiteOrnot < 18) {

    for (int i = 0; i < 17; i++) {


      //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
      leds[i + ((columnNum)*16)].r = 100 * 0.1;
      leds[i + ((columnNum)*16)].g = 215 * 0.1;
      leds[i + ((columnNum)*16)].b = 255 * 0.1;
    }
  } else {

    for (int i = 0; i < 17; i++) {


      //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
      leds[i + ((columnNum)*16)].r = 12 * 0.1;
      leds[i + ((columnNum)*16)].g = 107 * 0.1;
      leds[i + ((columnNum)*16)].b = 237 * 0.1;
    }
  }
}

// void column(int columnNum) {  //column infatiuation
//   int whiteOrnot = random(0, 25);

//   if (whiteOrnot < 18) {

//     for (int i = 0; i < 17; i++) {

//       //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
//       leds[i + ((columnNum)*16)].r = random(10, 50)*0.15;
//       leds[i + ((columnNum)*16)].g = random(60, 120)*0.15;
//       leds[i + ((columnNum)*16)].b = random(0, 50)*0.15;
//     }
//   } else if (whiteOrnot > 17) {

//     for (int i = 0; i < 17; i++) {


//       //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
//       leds[i + ((columnNum)*16)].r = random(30, 100)*0.3;
//       leds[i + ((columnNum)*16)].g = random(0, 20)*0.3;
//       leds[i + ((columnNum)*16)].b = random(0, 20)*0.3;
//     }
//   }
// }

// void backgroundBasic() {

//   for (int i = 0; i < 72; i++) {
//     //for (int i = 0; i < NUM_LEDS; i++) {
//     //leds[i].r = 30;
//     //leds[i].b = 6;
//     //leds[i].g = 0;
//     column(i);
//   }

//   FastLED.show();
//   gameOn = 1;
// }

void backgroundBasic() {

  for (int i = 0; i < 72; i++) {
    column(i);
  }

  FastLED.show();
  gameOn = 1;
}

void backgroundBasicSmall() {

  if (gameOn == 1) {
    for (int i = 0; i < 7; i++) {

      column(random(0, 72));
      column(random(0, 72));
    }

    FastLED.show();
  }
}



// always start the game in the same spot
Point *getStartingPosition() {
  return new Point(3, snakeStartY);
}

Point *snakeStart1() {
  return new Point(2, snakeStartY);
}

Point *snakeStart2() {
  return new Point(1, snakeStartY);
}

// generate the position of the apple so it is not out of bounds or within the snake
Point *getApplePosition() {
  int x = random(3, 10);
  int y = random(1, 6);

  // make sure to generate an apple that is not in the same position as the snake
  while (snakeContainsPosition(x, y)) {
    x = random(3, 10);
    y = random(1, 6);
  }
  return new Point(x, y);
}

Point *getApple2Position() {
  int appleSwitch = random(1, 3);
  int x = 0;
  int y = 0;

  if (appleSwitch == 1) {
    x = random(0, 3);
    y = random(1, 5);
  } else {
    x = random(10, 12);
    y = random(1, 5);
  }


  // make sure to generate an apple that is not in the same position as the snake
  while (snakeContainsPosition(x, y)) {
    if (appleSwitch == 1) {
      x = random(0, 3);
      y = random(1, 5);
    } else {
      x = random(10, 12);
      y = random(1, 5);
    }
  }
  return new Point(x, y);
}

Point *getApple2PositionDefault() {
  int x = 0;
  int y = 0;


  x = 12;
  y = 12;


  return new Point(x, y);
}

// check if the x y coordinates are covered by a part of the snake
boolean snakeContainsPosition(int x, int y) {
  for (int i = 0; i < snakePositions.size(); i++) {
    if (snakePositions.get(i)->isEqual(x, y)) {
      return true;
    }
  }

  return false;
}

// read direction from analog stick
int getCurrentDirection() {
    int oldDir = currDirection;

    if ((digitalRead(UP_PIN) == 0) && (digitalRead(DOWN_PIN) == 1) && (digitalRead(LEFT_PIN) == 1) && (digitalRead(RIGHT_PIN) == 1)) {
      if (oldDir == DIR_DOWN) {
        return oldDir;
      } else {
        return DIR_UP;
      }
    } else if ((digitalRead(RIGHT_PIN) == 0) && (digitalRead(DOWN_PIN) == 1) && (digitalRead(LEFT_PIN) == 1) && (digitalRead(UP_PIN) == 1)) {
      if (oldDir == DIR_LEFT) {
        return oldDir;
      } else {
        return DIR_RIGHT;
      }
    } else if ((digitalRead(LEFT_PIN) == 0) && (digitalRead(DOWN_PIN) == 1) && (digitalRead(UP_PIN) == 1) && (digitalRead(RIGHT_PIN) == 1)) {
      if (oldDir == DIR_RIGHT) {
        return oldDir;
      } else {
        return DIR_LEFT;
      }
    } else if ((digitalRead(DOWN_PIN) == 0) && (digitalRead(UP_PIN) == 1) && (digitalRead(LEFT_PIN) == 1) && (digitalRead(RIGHT_PIN) == 1)) {
      if (oldDir == DIR_UP) {
        return oldDir;
      } else {
        return DIR_DOWN;
      }
    } else {
      return oldDir;
    }
}

Point *getHead() {
  return snakePositions.get(0);
}

Point *getTail() {
  return snakePositions.get(snakePositions.size() - 1);
}

void addToBeginning(Point *p) {
  snakePositions.add(0, p);
}

void removeTail() {
  delete (snakePositions.pop());
}

// calculate the next position based on the current head position and the current direction
Point *getNextPosition() {
  Point *head = getHead();
  int x = head->getX();
  int y = head->getY();
  switch (currDirection) {
    case DIR_UP:
      return new Point(head->getX(), head->getY() - 1);
    case DIR_DOWN:
      return new Point(head->getX(), head->getY() + 1);
    case DIR_LEFT:
      return new Point(head->getX() + 1, head->getY());
    case DIR_RIGHT:
      return new Point(head->getX() - 1, head->getY());
    default:
      return new Point(-9, -9);
  }
}

// make sure the next point for the head of the snake is in a valid position
boolean isNextPointValid(Point *p) {
  int x = p->getX();
  int y = p->getY();

  // check if within boundary or if we are in the snake
  if (x < 0 || x >= 12 || y < 0 || y >= 6 || snakeContainsPosition(x, y)) {
    return false;
  } else if (x == 0 && y == 5) {

    return false;
  } else if (x == 11 && y == 5) {

    return false;
  } else {

    return true;
  }
}


// draw the apple
void renderApple() {
  int varApple = getIndexForPoint(applePosition);
  for (int i = 0; i < 15; i++) {
    leds[(varApple * 16) + i] = appleColor;  //isGamePaused ? pausedAppleColor :
    //leds2[(varApple * 16) + i] = appleColor;
  }
}

void renderApple2() {
  int varApple2 = getIndexForPoint(apple2Position);
  for (int i = 0; i < 15; i++) {
    leds[(varApple2 * 16) + i] = appleColor;  //isGamePaused ? pausedAppleColor :
    //leds2[(varApple2 * 16) + i] = appleColor;
  }
}

// draw the snake
void renderSnake() {
  Point *p;
  for (int i = 0; i < snakePositions.size(); i++) {
    p = snakePositions.get(i);
    int index = getIndexForPoint(p);
    int varSnake = getIndexForPoint(p);
    int x = p->getX();
    int y = p->getY();
    for (int i = 0; i < 15; i++) {
      leds[(varSnake * 16) + i] = snakeColor;  //isGamePaused ? pausedSnakeColor :
      //leds2[(varSnake * 16) + i] = snakeColor;
    }
  }
}

// for a point in the matrix, map it to the index in the string
int getIndexForPoint(Point *p) {
  int x = p->getX();
  int y = p->getY();
  int xCheck = p->getX();
  int yCheck = p->getY();

  //boolean oddColumn = y % 2 == 1;

  // handle serpentine pattern
  // if(oddRow){
  //   return (x + 1) * columns - y - 1;
  // }

  if (xCheck == 1 || xCheck == 3 || xCheck == 5 || xCheck == 7 || xCheck == 9) {
    return ((((x + 1) * 6) - y) - 1) - 1;
  } else if (xCheck == 2 || xCheck == 4 || xCheck == 6 || xCheck == 8 || xCheck == 10 || xCheck == 12) {
    return ((x * 6) + y) - 1;
  } else if (xCheck == 0) {
    if (y == 0) {
      return 0;
    } else if (y == 1) {
      return 1;
    } else if (y == 2) {
      return 2;
    } else if (y == 3) {
      return 3;
    } else if (y == 4) {
      return 4;
    } else if (y == 5) {
      return 200;
    }
  } else if (xCheck == 11) {
    if (y == 0) {
      return 69;
    } else if (y == 1) {
      return 68;
    } else if (y == 2) {
      return 67;
    } else if (y == 3) {
      return 66;
    } else if (y == 4) {
      return 65;
    } else if (y == 5) {
      return 200;
    }
  }

  // if (x == 1) {
  //   if (y == 0) {
  //     return 10;
  //   } else if (y == 1) {
  //     return 9;
  //   } else if (y == 2) {
  //     return 8;
  //   } else if (y == 3) {
  //     return 7;
  //   } else if (y == 4) {
  //     return 6;
  //   } else if (y == 5) {
  //     return 5;
  //   }
  // }
  // if (x == 2) {
  //   if (y == 0) {
  //     return 11;
  //   } else if (y == 1) {
  //     return 12;
  //   } else if (y == 2) {
  //     return 13;
  //   } else if (y == 3) {
  //     return 14;
  //   } else if (y == 4) {
  //     return 15;
  //   } else if (y == 5) {
  //     return 16;
  //   }
  // }
  // if (x == 3) {
  //   if (y == 0) {
  //     return 22;
  //   } else if (y == 1) {
  //     return 21;
  //   } else if (y == 2) {
  //     return 20;
  //   } else if (y == 3) {
  //     return 19;
  //   } else if (y == 4) {
  //     return 18;
  //   } else if (y == 5) {
  //     return 17;
  //   }
  // }
  // if (x == 4) {
  //   if (y == 0) {
  //     return 23;
  //   } else if (y == 1) {
  //     return 24;
  //   } else if (y == 2) {
  //     return 25;
  //   } else if (y == 3) {
  //     return 26;
  //   } else if (y == 4) {
  //     return 27;
  //   } else if (y == 5) {
  //     return 28;
  //   }
  // }
  // if (x == 5) {
  //   if (y == 0) {
  //     return 34;
  //   } else if (y == 1) {
  //     return 33;
  //   } else if (y == 2) {
  //     return 32;
  //   } else if (y == 3) {
  //     return 31;
  //   } else if (y == 4) {
  //     return 30;
  //   } else if (y == 5) {
  //     return 29;
  //   }
  // }
  // if (x == 6) {
  //   if (y == 0) {
  //     return 35;
  //   } else if (y == 1) {
  //     return 36;
  //   } else if (y == 2) {
  //     return 37;
  //   } else if (y == 3) {
  //     return 38;
  //   } else if (y == 4) {
  //     return 39;
  //   } else if (y == 5) {
  //     return 40;
  //   }
  // }
  // if (x == 7) {
  //   if (y == 0) {
  //     return 46;
  //   } else if (y == 1) {
  //     return 45;
  //   } else if (y == 2) {
  //     return 44;
  //   } else if (y == 3) {
  //     return 43;
  //   } else if (y == 4) {
  //     return 42;
  //   } else if (y == 5) {
  //     return 41;
  //   }
  // }
  // if (x == 8) {
  //   if (y == 0) {
  //     return 47;
  //   } else if (y == 1) {
  //     return 48;
  //   } else if (y == 2) {
  //     return 49;
  //   } else if (y == 3) {
  //     return 50;
  //   } else if (y == 4) {
  //     return 51;
  //   } else if (y == 5) {
  //     return 52;
  //   }
  // }
  // if (x == 9) {
  //   if (y == 0) {
  //     return 58;
  //   } else if (y == 1) {
  //     return 57;
  //   } else if (y == 2) {
  //     return 56;
  //   } else if (y == 3) {
  //     return 55;
  //   } else if (y == 4) {
  //     return 54;
  //   } else if (y == 5) {
  //     return 53;
  //   }
  // }
  // if (x == 10) {
  //   if (y == 0) {
  //     return 59;
  //   } else if (y == 1) {
  //     return 60;
  //   } else if (y == 2) {
  //     return 61;
  //   } else if (y == 3) {
  //     return 62;
  //   } else if (y == 4) {
  //     return 63;
  //   } else if (y == 5) {
  //     return 64;
  //   }
  // }
}

void renderEmptyScreen() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = emptyColor;
    //leds2[i] = emptyColor;
  }
}

void renderSolidScreen() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = solidColor;
    //leds2[i] = solidColor;
  }
}

void playGame(Point *nextPoint) {
  // clear screen
  renderEmptyScreen();

  // if we land on an apple grow the snake
  if (applePosition->isEqual(nextPoint->getX(), nextPoint->getY())) {
    growSnake(nextPoint);

  } else if (apple2Position->isEqual(nextPoint->getX(), nextPoint->getY())) {

    if (Apple2Enabled > 0) {

      grow2Snake(nextPoint);
    } else {

      moveSnake(nextPoint);
    }

  } else {

    moveSnake(nextPoint);
  }

  renderSnake();
  renderApple();

  if (Apple2Enabled > 0) {

    renderApple2();
  }

  FastLED.show();

  //delay(gameSpeed);
  for (int i = 0; i < gameSpeed / 2; i = i + 10) {
    currDirection = getCurrentDirection();
    delay(10);
  }
  for (int i = 0; i < gameSpeed / 2; i = i + 10) {
    currDirection = getCurrentDirection();
    tone(SPEAKER_PIN, NOTE_E3);
    delay(10);
  }

  noTone(SPEAKER_PIN);
}

void moveSnake(Point *p) {
  addToBeginning(p);
  removeTail();
}

void growSnake(Point *p) {
  addToBeginning(p);
  resetApple();
  increaseSpeed();
  snakeScore++;
  if (snakeScore > 4) {
    if (Apple2Enabled == 0) {
      resetApple2();
      Apple2Enabled = 1;
    }
  }
}

void grow2Snake(Point *p) {
  addToBeginning(p);
  resetApple2();
  increaseSpeed();
  snakeScore++;
}

void growSnakeStart(Point *p) {
  addToBeginning(p);
  snakeScore++;
}

void increaseSpeed() {
  int oldGameSpeed = gameSpeed;
  if (speedCap < 7) {
    gameSpeed = (oldGameSpeed - 60);
    speedCap++;
  }
}



void gameOnCheckandStart() {
  //int startButton = digitalRead(START_PIN);
  int startButton = digitalRead(LEFT_PIN);
  if (gameOn == 1) {
    if (digitalRead(LEFT_PIN) == 0) {  // == 0  && digitalRead(DOWN_PIN) == 1 && digitalRead(LEFT_PIN) == 1 && digitalRead(RIGHT_PIN) == 1) {

      renderEmptyScreen();
      FastLED.show();
      resetSnake();
      resetApple();
      //resetApple2();
      //delete (apple2Position);
      currDirection = DIR_LEFT;
      snakeStart();
      gameOn = 2;


      FastLED.show();
    }
  }
}

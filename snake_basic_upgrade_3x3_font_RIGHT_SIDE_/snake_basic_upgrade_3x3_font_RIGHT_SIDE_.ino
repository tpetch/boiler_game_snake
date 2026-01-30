
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

  timerOne.every(8000, backgroundBasic);
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

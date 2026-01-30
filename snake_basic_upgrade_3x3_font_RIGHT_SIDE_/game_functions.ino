//Functions related to the game running

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

Point *getHead() {
  return snakePositions.get(0);
}

Point *getTail() {
  return snakePositions.get(snakePositions.size() - 1);
}


// create a three length snake
void snakeStart() {
  snakeStartY = random(1, 3);
  snakePositions.add(getStartingPosition());
  snakePositions.add(snakeStart1());
  snakePositions.add(snakeStart2());
}

// Function deletes the snake and 

void resetSnake() {
  while (snakePositions.size() > 0) {
    delete (snakePositions.pop());
  }
  //snakePositions.add(getStartingPosition());
  //snakeStart();
}

// delete the current position and draw a new apple
void resetApple() {
  delete (applePosition);
  applePosition = getApplePosition();

  for (int i = 0; i < gameSpeed / 3; i++) {
    //currDirection = getCurrentDirection();
    tone(SPEAKER_PIN, NOTE_B4);
    delay(1);
  }

  noTone(SPEAKER_PIN);
}

void resetApple2() {
  delete (apple2Position);
  apple2Position = getApple2Position();

  for (int i = 0; i < gameSpeed / 3; i++) {
    //currDirection = getCurrentDirection();
    tone(SPEAKER_PIN, NOTE_A4);
    delay(1);
  }

  noTone(SPEAKER_PIN);
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

// show an end screen and reset the game state
void resetGame() {
  resetSnake();
  //snakeStart();
  resetApple();
  apple2Position = getApple2PositionDefault();
  //resetApple2();
  //delete (apple2Position);

  renderSolidScreen();
  FastLED.show();
  delay(resetDelay);
  renderEmptyScreen();
  //showScore();
  FastLED.show();
  delay(resetDelay);
  renderSolidScreen();
  FastLED.show();
  delay(resetDelay);
  renderEmptyScreen();
  //showScore();
  FastLED.show();
  delay(resetDelay);
  renderSolidScreen();
  FastLED.show();
  delay(resetDelay);
  renderEmptyScreen();
  showScore();
  FastLED.show();

  for (int i = 0; i < 5000; i++) {
    delay(1);
    if (digitalRead(1) == 0) {  //readd START pin
      i = 4990;
    }
  }

  gameSpeed = MIN_SPEED;
  currDirection = DIR_LEFT;
  speedCap = 0;
  gameOn = 0;
  snakeScore = 0;
  Apple2Enabled = 0;
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
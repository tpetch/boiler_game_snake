//Functions related to the game running



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
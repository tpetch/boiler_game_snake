/* Functions related to display while game is not playing */


/* Function that sets a pixel to a random color, this version set to the blues from Infatuation. 
   Function picks a random number, then sets color based on that (colors are weighted to appear more often or not.)  */
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

/* Basic function that sets each pixel to a random number. Changes gameOn to 1 if it's 0. */

void backgroundBasic() {

  for (int i = 0; i < 72; i++) {
    column(i);
  }

  FastLED.show();
  if (gameOn == 0) {
    gameOn = 1;
  }
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
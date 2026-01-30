/* Kept just in case */

// void boilerTextureStart(){

//     for(int i=0; i<NUMPIXELS; i++) {
//     leds[i].r = 30;
//     leds[i].g = 6;
//     leds[i].b = 0;

//   }
// }

// void column(int columnNum) {

//   int randomTube = random(0, 7);

//   for (int i = 0; i < 17; i++) {

//     int randomRed = random(35, 70);
//     int randomGreen = random(5, 25);
//     if (randomGreen > randomRed) {
//       randomGreen = 0;
//     }

//     //CRBG columnColor = CRBG(randomRed * 0.7, randomGreen * 0.85, 0);
//     leds[i + ((columnNum)*16)].r = randomRed * 0.65;
//     leds[i + ((columnNum)*16)].g = randomGreen * 0.80;
//     leds[i + ((columnNum)*16)].b = 0;
//     leds2[i + ((columnNum)*16)].r = randomRed * 0.65;
//     leds2[i + ((columnNum)*16)].g = randomGreen * 0.8;
//     leds2[i + ((columnNum)*16)].b = 0;
//   }
// }

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
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
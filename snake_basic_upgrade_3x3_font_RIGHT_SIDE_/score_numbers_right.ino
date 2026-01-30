//Functions related to showing the score on screen

//Function called at end of game to display score.

void showScore() {
  renderNumber(snakeScore);
}

//Function which takes score number and calls two seprate functions to display that score, one for the 10's number and one for the 1's number. Could be done much more elegantly!

void renderNumber(int numNum) {


  if (numNum == 0) {
    render0x();
    renderx0();
  } else if (numNum == 1) {
    render0x();
    renderx1();
  } else if (numNum == 2) {
    render0x();
    renderx2();
  } else if (numNum == 3) {
    render0x();
    renderx3();
  } else if (numNum == 4) {
    render0x();
    renderx4();
  } else if (numNum == 5) {
    render0x();
    renderx5();
  } else if (numNum == 6) {
    render0x();
    renderx6();
  } else if (numNum == 7) {
    render0x();
    renderx7();
  } else if (numNum == 8) {
    render0x();
    renderx8();
  } else if (numNum == 9) {
    render0x();
    renderx9();
  } else if (numNum == 10) {
    render1x();
    renderx0();
  } else if (numNum == 11) {
    render1x();
    renderx1();
  } else if (numNum == 12) {
    render1x();
    renderx2();
  } else if (numNum == 13) {
    render1x();
    renderx3();
  } else if (numNum == 14) {
    render1x();
    renderx4();
  } else if (numNum == 15) {
    render1x();
    renderx5();
  } else if (numNum == 16) {
    render1x();
    renderx6();
  } else if (numNum == 17) {
    render1x();
    renderx7();
  } else if (numNum == 18) {
    render1x();
    renderx8();
  } else if (numNum == 19) {
    render1x();
    renderx9();
  } else if (numNum == 20) {
    render2x();
    renderx0();
  } else if (numNum == 21) {
    render2x();
    renderx1();
  } else if (numNum == 22) {
    render2x();
    renderx2();
  } else if (numNum == 23) {
    render2x();
    renderx3();
  } else if (numNum == 24) {
    render2x();
    renderx4();
  } else if (numNum == 25) {
    render2x();
    renderx5();
  } else if (numNum == 26) {
    render2x();
    renderx6();
  } else if (numNum == 27) {
    render2x();
    renderx7();
  } else if (numNum == 28) {
    render2x();
    renderx8();
  } else if (numNum == 29) {
    render2x();
    renderx9();
  } else if (numNum == 30) {
    render3x();
    renderx0();
  } else if (numNum == 31) {
    render3x();
    renderx1();
  } else if (numNum == 32) {
    render3x();
    renderx2();
  } else if (numNum == 33) {
    render3x();
    renderx3();
  } else if (numNum == 34) {
    render3x();
    renderx4();
  } else if (numNum == 35) {
    render3x();
    renderx5();
  } else if (numNum == 36) {
    render3x();
    renderx6();
  } else if (numNum == 37) {
    render3x();
    renderx7();
  } else if (numNum == 38) {
    render3x();
    renderx8();
  } else if (numNum == 39) {
    render3x();
    renderx9();
  }
}

// Function that sets a single pixel, used only for scoring right now. Takes four arguments: pixel number, and RGB colors values (in that order).

void renderPixel(int pixelNumber, int lCr, int lCg, int lCb) {
  for (int i = 0; i < 17; i++) {
    leds[i + ((pixelNumber)*16)].r = lCr;
    leds[i + ((pixelNumber)*16)].g = lCg;
    leds[i + ((pixelNumber)*16)].b = lCb;
  }
}

// All of the following functions set the pixels to display a specific number. Functions "(number)x" set the 10's number, "x(number)" set the 1's place.

void render0x() {

  renderPixel(48, 50, 20, 1);
  renderPixel(49, 50, 20, 1);
  renderPixel(50, 50, 20, 1);
  renderPixel(51, 50, 20, 1);
  renderPixel(45, 50, 20, 1);
  renderPixel(42, 50, 20, 1);
  renderPixel(37, 50, 20, 1);
  renderPixel(38, 50, 20, 1);
  renderPixel(36, 50, 20, 1);
  renderPixel(39, 50, 20, 1);
}

void render1x() {
  renderPixel(39, 50, 20, 1);
  renderPixel(48, 50, 20, 1);
  renderPixel(42, 50, 20, 1);
  renderPixel(43, 50, 20, 1);
  renderPixel(44, 50, 20, 1);
  renderPixel(45, 50, 20, 1);
  renderPixel(51, 50, 20, 1);
}

void render3x() {

  renderPixel(48, 50, 20, 1);
  renderPixel(51, 50, 20, 1);
  renderPixel(42, 50, 20, 1);
  renderPixel(44, 50, 20, 1);
  renderPixel(45, 50, 20, 1);
  renderPixel(36, 50, 20, 1);
  renderPixel(37, 50, 20, 1);
  renderPixel(38, 50, 20, 1);
  renderPixel(39, 50, 20, 1);
}

void render2x() {
  renderPixel(54, 50, 20, 1);
  renderPixel(55, 50, 20, 1);
  renderPixel(57, 50, 20, 1);
  renderPixel(48, 50, 20, 1);
  renderPixel(50, 50, 20, 1);
  renderPixel(51, 50, 20, 1);
  renderPixel(42, 50, 20, 1);
  renderPixel(44, 50, 20, 1);
  renderPixel(45, 50, 20, 1);
}

void renderx0() {
  renderPixel(24, 50, 20, 1);
  renderPixel(25, 50, 20, 1);
  renderPixel(26, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx1() {
  renderPixel(24, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(19, 50, 20, 1);
  renderPixel(20, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx2() {
  renderPixel(24, 50, 20, 1);
  renderPixel(26, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(19, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx3() {
  renderPixel(24, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(20, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx4() {
  renderPixel(24, 50, 20, 1);
  renderPixel(25, 50, 20, 1);
  renderPixel(26, 50, 20, 1);
  renderPixel(19, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx5() {
  renderPixel(24, 50, 20, 1);
  renderPixel(25, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(20, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx6() {
  renderPixel(24, 50, 20, 1);
  renderPixel(25, 50, 20, 1);
  renderPixel(26, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(19, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx7() {
  renderPixel(19, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(24, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx8() {
  renderPixel(24, 50, 20, 1);
  renderPixel(25, 50, 20, 1);
  renderPixel(26, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(20, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}

void renderx9() {
  renderPixel(24, 50, 20, 1);
  renderPixel(25, 50, 20, 1);
  renderPixel(27, 50, 20, 1);
  renderPixel(18, 50, 20, 1);
  renderPixel(20, 50, 20, 1);
  renderPixel(21, 50, 20, 1);
  renderPixel(12, 50, 20, 1);
  renderPixel(13, 50, 20, 1);
  renderPixel(14, 50, 20, 1);
  renderPixel(15, 50, 20, 1);
}


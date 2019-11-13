void Display_init(void) {
  P.begin();
  P.setIntensity(brightd);
  (fontUsed==0?P.setFont(_6bite_rus):fontUsed==1?P.setFont(_5bite_rus):fontUsed==2?P.setFont(_font_rus):P.setFont(_6bite_rus));
  P.setInvert(false);
  MP.begin();
}

void displayTime(bool lastShow) { //lastShow need for effect with last show
  static bool flasher = true;
  static uint32_t  lastDot = 0;
  if (!lastShow) {
    if (P.displayAnimate()) {  
      P.displayText(szTime, PA_CENTER, 75, 0, PA_PRINT, PA_NO_EFFECT);
      if (millis() - lastDot >= 750) {
        lastDot = millis();
        getTimeDisp(szTime, flasher);
        flasher = !flasher;
        if (displayClockFirst) {displayClockCount =millis(); displayClockFirst = false;}
        P.displayReset();     
      }  
    }
  }
  else { 
    P.displayText(szTime, PA_CENTER, 75, 0, PA_PRINT, PA_SCROLL_UP_RIGHT);        
  }
}

//return true if string was played
bool showText(String sText, textPosition_t t_pos, uint16_t t_speed, uint16_t t_pause, textEffect_t  t_effectBegin, textEffect_t  t_effectEnd) {
  if  (P.displayAnimate()) {
    Serial.print("sText: "); Serial.println(sText);
    Serial.print("sText.length(): "); Serial.println(sText.length());
    if (sText.length() > 0) {
      sText.toCharArray(buf, 256);
      P.displayReset();
      P.displayText(buf, t_pos, t_speed, t_pause, t_effectBegin, t_effectEnd);
      //if (!P.displayAnimate()) disp = 3;
    }
    modeShow++;
    return true;
  }
  else {
    return false;
  }
}

uint8_t showTextUP(String sText, uint16_t t_speed, uint16_t t_pause, textEffect_t  t_effectBegin, textEffect_t  t_effectEnd, bool last) {
  if  (P.displayAnimate()) {
    Serial.print("sText: "); Serial.println(sText);
    Serial.print("sText.length(): "); Serial.println(sText.length());
    if (sText.length() > 0) {
      sText.toCharArray(buf, 256);
      P.displayReset();
      P.displayText(buf, PA_CENTER, t_speed, t_pause, t_effectBegin, t_effectEnd);
      //if (!P.displayAnimate()) disp = 3;
    }
    if (last) modeShow++;
    return 1;
  }
  return 0;
}  


/*void bounce(void) {  // Animation of a bouncing ball
  const uint16_t  DELAYTIME = 50;  // in milliseconds
  const uint16_t minX = 0;
  const uint16_t maxX = MP.getXMax();
  const uint16_t minY = 0;
  const uint16_t maxY = MP.getYMax();
  uint16_t  nCounter = 0;
  uint16_t  y = random(maxY/2) + maxY/2, x = random(maxX/2) + maxX/2;
  int8_t dy = 1, dx = 1;  // delta row and column
  MP.clear();
  while (nCounter++ < 100)  {
    MP.setPoint(x, y, false);
    x += dx;
    y += dy;
    MP.setPoint(x, y, true);
    delay(DELAYTIME/2);

    if ((x == minX) || (x == maxX))
      dx = -dx;
    if ((y == minY) || (y == maxY))
      dy = -dy;
  }
}*/

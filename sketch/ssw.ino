// Define some graphics, see contents later in file
extern const word graphic[];

void setup() {
  // Run standard startup procedure
  standardStartup();
  
  // Init display
  OLED.begin();
  OLED.fillScreen(0x5555);
  OLED.setTextColor(0xFFFF, 0x5555);
  OLED.setTextSize(1);
  OLED.drawSprite(92, 102, 34, 24, (void*)graphic);

  // Init stuff, show status
  OLED.setCursor(0, 0);
  OLED.print((char*)"PMU init...   ");
  if(Battery.begin()) OLED.println((char*)"OK"); else OLED.println((char*)"FAIL");
  OLED.print((char*)"PMU enable... ");
  if(Battery.enableCharging()) OLED.println((char*)"OK"); else OLED.println((char*)"FAIL");
  OLED.print((char*)"Touch init... ");
  if(Touch.begin()) OLED.println((char*)"OK"); else OLED.println((char*)"FAIL");

  DateTime.begin();
  if(!DateTime.isRunning()) {
    // RTC has lost power, we need to set a new time
    DateTime.setDateTime(13, 05, 03, 6, 20, 41, 00);
  }
  usb_debug1[0]=0;
  usb_debug2[0]=0;
  usb_debug3[0]=0;
  usb_debug4[0]=0;
  setupUSB();
}


void loop() {
  char text[32];

  // Clear before printing
  OLED.setCursor(0, 32);
/* USB Comunication seems to not work while this is enabled.
  // USB connected status
  OLED.print("USB connected: ");
  OLED.println((char*)(Battery.canCharge() ? "YES" : "NO "));

  digitalWrite(&PIN_PB1, Battery.canCharge());

  // PMU charging status
  OLED.print("PMU charging:  ");
  OLED.println((char*)(Battery.isCharging() ? "YES" : "NO "));
*/

  OLED.setCursor(0, 32);

  // Battery level as volts
  sprintf(text, "Battery: %.2fV", ((float)Battery.readMilliVolts()) / 1000.0);
  OLED.println(text);
  OLED.println("usb_debug:");
  OLED.println(usb_debug1);
  OLED.println(usb_debug2);
  OLED.println(usb_debug3);
  OLED.println(usb_debug4);

  /*
  // Light sensor level as %
  sprintf(text, "Sensor:  %u%%  ", (LightSensor.readRaw() * 100) / 4095);
  OLED.println(text);

  // Clock
  DateTime.update();
  sprintf(text, "Time: %02u:%02u:%02u", DateTime.hour(), DateTime.minute(), DateTime.second());
  OLED.println(text);

  // Touch information
  OLED.setCursor(0, 88);
  OLED.print("Touch: ");
 
  if(Touch.read()) {
    if(Touch.isTouched()) {
      sprintf(text, "%u, %u    ", Touch.getX(), Touch.getY());
    } else {
      sprintf(text, "NO      ");
    }
  } else {
    sprintf(text, "FAIL    ");
  }
  OLED.println(text);

  // Delay in low speed mode

  CPU.setSpeed(CPU_LS);
  delay(100);
  CPU.setSpeed(CPU_HS);
  */

  // Shut down if button is pressed
  if(digitalRead(BUTTON)) standardShutdown();

}

const word graphic[] = {
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0xBAAE, 0x799E, 0x5555, 0xFBBE,
  0x388E, 0xFBBE, 0xB66D, 0x1CC7, 0x1886, 0xFBBE, 0x3CCF, 0xBAAE,
  0x5555, 0xB66D, 0x1CC7, 0x3CCF, 0xF77D, 0xD775, 0x3CCF, 0x1CC7,
  0x1CC7, 0xF77D, 0xFBBE, 0x765D, 0xDBB6, 0x398E, 0xB66D, 0x3CCF,
  0x1CC7, 0xB66D, 0x5555, 0x5555, 0x5555, 0x5555, 0xBAAE, 0xDEF7,
  0x9DE7, 0xBEEF, 0x388E, 0xDEF7, 0x5DD7, 0xBEEF, 0x9665, 0xDEF7,
  0xDBB6, 0xBEEF, 0xDBB6, 0x3CCF, 0x7DDF, 0xBAAE, 0xBEEF, 0x9665,
  0xBAAE, 0xFFFF, 0x799E, 0x1886, 0xDEF7, 0x7A9E, 0xFFFF, 0xDBB6,
  0x7DDF, 0x1CC7, 0x3CCF, 0x7DDF, 0x5555, 0x5555, 0x5555, 0x5555,
  0xB66D, 0xBEEF, 0x7DDF, 0x3CCF, 0xF77D, 0xFFFF, 0x7DDF, 0xDEF7,
  0x1886, 0xDEF7, 0xD775, 0x1CC7, 0x5DD7, 0x5DD7, 0xDBB6, 0xF77D,
  0xBEEF, 0x5555, 0xD775, 0xFFFF, 0x5555, 0xD775, 0xDFF7, 0xBEEF,
  0xBEEF, 0xFBBE, 0xBEEF, 0x5996, 0x9AA6, 0xBEEF, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x9DE7, 0xFFFF, 0x1886, 0xF77D, 0xFFFF,
  0xBAAE, 0xFFFF, 0x799E, 0xDEF7, 0xFBBE, 0xBEEF, 0xFBBE, 0x5DD7,
  0xFBBE, 0x1886, 0xDEF7, 0xB66D, 0xDBB6, 0xFFFF, 0x9AA6, 0xF87D,
  0xFFFF, 0x7DDF, 0x1CC7, 0x1BC7, 0x7DDF, 0x3CCF, 0x5DD7, 0x9EE7,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x799E, 0x7DDF, 0x755D,
  0xD775, 0x7DDF, 0x9DE7, 0xFBBE, 0x9665, 0x5CD7, 0x9DE7, 0x1CC7,
  0x765D, 0xFBBE, 0x9AA6, 0xD775, 0x3CCF, 0x1886, 0x9EE7, 0x7DDF,
  0x7DDF, 0x1886, 0x7DDF, 0xF77D, 0x9AA6, 0x9AA6, 0xB76D, 0x7DDF,
  0x7DDF, 0xF77D, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0xB76D, 0x5996, 0x5996,
  0x1886, 0x755D, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0xF77D, 0x5996, 0x5996,
  0xF77D, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x9AA6, 0x9DE7, 0xDFF7,
  0xFFFF, 0xFFFF, 0xFFFF, 0xBEEF, 0x3CCF, 0xD775, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x9665, 0xFBBE, 0xBEEF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xBEEF, 0xFBBE, 0x9665, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x9665, 0x7DDF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xDFF7,
  0xBAAE, 0x5555, 0x5555, 0x5555, 0x5555, 0x388E, 0xBEEF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBEEF,
  0x1886, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x765D, 0x9DE7,
  0xFFFF, 0xFFFF, 0xFFFF, 0x5DD7, 0xBAAE, 0xBAAE, 0xFBBE, 0xBEEF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFBBE, 0x5555, 0x5555, 0x799E, 0xFFFF,
  0xFFFF, 0xFFFF, 0xDFF7, 0x3CCF, 0xBAAE, 0xBAAE, 0x1CC7, 0xDFF7,
  0xFFFF, 0xFFFF, 0xDFF7, 0xD775, 0x5555, 0x5555, 0x5555, 0x5555,
  0xFBBE, 0xFFFF, 0xFFFF, 0xBEEF, 0x1886, 0x5555, 0x5555, 0x5555,
  0x5555, 0x765D, 0xDBB6, 0xFFFF, 0xFFFF, 0xFFFF, 0xBAAE, 0xF77D,
  0xFFFF, 0xFFFF, 0xFFFF, 0x5DD7, 0xB66D, 0x5555, 0x5555, 0x5555,
  0x5555, 0xB66D, 0x7DDF, 0xFFFF, 0xFFFF, 0x7DDF, 0x5555, 0x5555,
  0x5555, 0x755D, 0xDEF7, 0xFFFF, 0xDFF7, 0xF77D, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x9AA6, 0xFFFF, 0xFFFF,
  0xDFF7, 0xDEF7, 0xFFFF, 0xFFFF, 0x3CCF, 0x5555, 0x5555, 0x5555,
  0xF77D, 0xB76D, 0x5555, 0x5555, 0x765D, 0x9EE7, 0xFFFF, 0xFFFF,
  0xF77D, 0x5555, 0x5555, 0x388E, 0xFFFF, 0xFFFF, 0xFBBE, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0xDBB6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x7DDF, 0x5555, 0x5555,
  0x5555, 0x9665, 0xFFFF, 0x3CCF, 0x5555, 0x5555, 0x5555, 0x5996,
  0xFFFF, 0xFFFF, 0xDBB6, 0x5555, 0x5555, 0x1CC7, 0xFFFF, 0xFFFF,
  0x5996, 0x5555, 0x755D, 0x3CCF, 0x7DDF, 0x7DDF, 0x7DDF, 0xFBBE,
  0x5555, 0x5555, 0x5555, 0x7DDF, 0xFFFF, 0xFFFF, 0xDEF7, 0xB66D,
  0x5555, 0x5555, 0xBAAE, 0x7DDF, 0xFFFF, 0xDEF7, 0x7DDF, 0xD775,
  0x5555, 0x9665, 0xDFF7, 0xFFFF, 0x3CCF, 0x5555, 0x5555, 0x1CC7,
  0xFFFF, 0xFFFF, 0x5996, 0x5555, 0x755D, 0x9DE7, 0xBEEF, 0xBEEF,
  0xBEEF, 0x3CCF, 0x5555, 0x5555, 0x5555, 0x3CCF, 0xFFFF, 0xFFFF,
  0x9EE7, 0x755D, 0x5555, 0x5555, 0xFBBE, 0xBEEF, 0xFFFF, 0xDFF7,
  0xBEEF, 0xF87D, 0x5555, 0x9665, 0xDEF7, 0xFFFF, 0x3CCF, 0x5555,
  0x5555, 0x799E, 0xFFFF, 0xFFFF, 0xBAAE, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5996, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFBBE, 0x5555, 0x5555, 0x5555, 0xB66D,
  0xFFFF, 0x5DD7, 0x5555, 0x5555, 0x5555, 0x1886, 0xFFFF, 0xFFFF,
  0x1BC7, 0x5555, 0x5555, 0x9665, 0xDFF7, 0xFFFF, 0xBEEF, 0x765D,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0xD775,
  0xDEF7, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x799E, 0x5555,
  0x5555, 0x765D, 0xDBB6, 0x5996, 0x5555, 0x5555, 0x5555, 0x3CCF,
  0xFFFF, 0xFFFF, 0x5996, 0x5555, 0x5555, 0x5555, 0x5DD7, 0xFFFF,
  0xFFFF, 0x5DD7, 0x765D, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x388E, 0xBEEF, 0xFFFF, 0xFFFF, 0x3CCF, 0xBAAE, 0xFFFF, 0xFFFF,
  0xFFFF, 0x9AA6, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0xDBB6, 0xFFFF, 0xFFFF, 0xBEEF, 0x755D, 0x5555, 0x5555, 0x5555,
  0xB76D, 0xDEF7, 0xFFFF, 0xFFFF, 0xBEEF, 0xBAAE, 0x1886, 0x1886,
  0x799E, 0x3CCF, 0xFFFF, 0xFFFF, 0xFFFF, 0x7DDF, 0x765D, 0x5555,
  0x1CC7, 0xFFFF, 0xFFFF, 0xFFFF, 0x7DDF, 0x9AA6, 0x1886, 0x1886,
  0x9AA6, 0x7DDF, 0xFFFF, 0xFFFF, 0xFFFF, 0x5996, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x1886, 0xDEF7, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x5DD7, 0x9665,
  0x5555, 0x5555, 0x5555, 0xDBB6, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBAAE, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0xB66D, 0x5CD7,
  0xDFF7, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xBEEF, 0x9AA6,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x388E, 0x7DDF,
  0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x7DDF, 0x1886,
  0x5555, 0x5DD7, 0x1886, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x9665, 0x799E, 0x3CCF, 0x3CCF, 0xDBB6, 0xF77D,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0xB76D, 0xBAAE, 0x3CCF, 0x3CCF, 0xBAAE, 0xD775,
  0x5555, 0x5555, 0x5555, 0x9665, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
  0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555,
};

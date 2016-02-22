/*
 * File:   lcd.h
 * Authors: Evelyn Hunten
 *
 * Created 2/16/16
 */

void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay); //done?
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower); //done?
void getTimeString ();
void initLCD(void); //done?
void clearLCD(void); //done?
void moveCursorLCD(unsigned char x, unsigned char y); //done?
void printCharLCD(char c); //Done?
void printStringLCD(const char* s); //TODO
void testLCD(); //provided
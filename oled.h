/** ----------------------------------------------------------------------------------------
 * File Author name : MALOLA SIMMAN SRINIVASAN KANNAN
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 11/26/22
 * File name : oled.h
 * Project Topic : Fire Safety System for Autonomous vehicle
 * Reference code : https://github.com/johrirj88/msp432_i2c_oledssd1306/tree/master/i2c_oled
 *  -----------------------------------------------------------------------------------------
 * In this file declaring OLED functions
   ---------------------------------------------------------------------------------------**/
#ifndef OLED_H_
#define OLED_H_
/** ------------------------------------------------------ /
                    MACROS
/ ------------------------------------------------------- **/
#define SLAVE_ADDR              0x3C
#define SSD1306_DISPLAYON       0xAF
#define SSD1306_DISPLAYOFF      0xAE
#define SSD1306_NORMALDISPLAY   0xA6
#define SSD1306_INVERTDISPLAY   0xA7
#define SSD1306_MULTIPLEX_RATIO 0xA8
#define SSD1306_CONTROL_REG     0x00
#define SSD1306_DATA_REG        0x40

/** ----------------------------------------------------- /
                FUNCTION DECLARATIONS
/ ------------------------------------------------------ **/
void oled_init(void);
void setupOLED();
void sendCommand(unsigned char cmd);
void write_display(unsigned char *data);
void sendData(unsigned char *data);
void Display_Logo(int x ,int y, unsigned char logo_val);
void draw_line(int x ,int y,unsigned char ascii_str[16]);
void display_on();
void display_off();
void display_clear();
void draw(int x, int y, unsigned char ascii);
void display_logos(int x, int y, unsigned char ascii_index);
void msdelay(int delay);

#endif /* OLED_H_ */

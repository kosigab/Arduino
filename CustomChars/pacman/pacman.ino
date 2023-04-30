//4x20 LCD with Pac-Man animation

// Using a 4x20 LCD to display text and a  Pac-Man animation

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);
  // set the LCD address to 0x27 for a 16 chars and 2 line display
#define screen_width 20         // Width of your device.
#define screen_height 4
#define BACKLIGHT_PIN 3
void setup() 
{
  lcd.begin(20,4);

}

void loop(){

  
  // Print a message to the LCD.
  
  lcd.setCursor(0,0);
  lcd.print("   Welcome to");
  delay(1550);
  lcd.setCursor(0,1);
  lcd.print("   Kosiview");
  delay(1550);  
  lcd.setCursor(0,2);
  lcd.print("   Projects");
  lcd.setCursor(0,3);
  delay(1550);   
  lcd.print("***bored emoji*****");
  delay(2000);

  lcd.clear();
  delay(1000);


  


int f=15;                  // Frame rate in frames/second
int s;

// These are kinda ad-hoc, I was using them to adjust on the fly. Don't judge me.
int message_row_1 = 1;          // First row of the message
int message_row_2 = 2;          // Second Row of the message

int first_row = 0;              // First row of the Pac-Man animation
int second_row = 3;             // Second row of the Pac-Man animation

int first_dc = 1;               // Column for the first dot
int last_dc = screen_width-1;   // Column for the last dot
int every_dc = 2;               // How many columns apart are the dots
int edge = screen_width-1;      // What is the far edge of the screen (as a zero-based index)


/* 
 * PAC-man characters taken from https://pastebin.com/88Zc1Py9
 */
byte pac1[8] = {
  B00000,
  B01110,
  B11011,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000
};
byte pac2[8] = {
  B00000,
  B01110,
  B10100,
  B11000,
  B11100,
  B01110,
  B00000,
  B00000
};
 
byte pac2b[8] = {
  B00000,
  B11110,
  B01011,
  B00111,
  B01111,
  B11110,
  B00000,
  B00000 };
 
 byte ghost[8] = {  
  B01110,
  B11111,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000,
  B00000 };
 
byte punkt[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
  B00000};

    // Turn on the backlight
//     lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  

    s=1000/f;            // Convert framerate into a delay in milliseconds
    /*****************************************
     *        Set your message here          *
     ****************************************/
    lcd.setCursor(0,message_row_1);
    lcd.print(" KOSVIEW");
    lcd.setCursor(0,message_row_2);
    lcd.print("  PROJECTS");
    
    // Populate the grid with power pellets
    lcd.createChar(6, punkt);
    for(int j = first_dc; j <= last_dc; j+= every_dc) {
        lcd.setCursor(j, first_row);
        lcd.write(6);
        delay(s);
    }
 
    for(int j = last_dc; j >= 0; j-= every_dc) {
        lcd.setCursor(j, second_row);
        lcd.write(6);

        delay(s); 
    }


    // Create the characters
    lcd.createChar(2, pac1);        // Closed mouth
    lcd.createChar(3, pac2);        // Open Mouth, facing right
    lcd.createChar(4, pac2b);       // Open Mouth, facing left
    lcd.createChar(5, ghost);       // Ghost
    lcd.createChar(6, punkt);       // Dot

    int k = 2;
    int ghost_pos = -1;

    /***************************************************
    **       PAC-Man moving to the Right, First Row   **
    ***************************************************/
    for(int j = first_dc; j <= edge+3; j+= every_dc) {  
        // If we're going to draw him (i.e. when we haven't overshot the edge
        // His mouth is closed when he's one _behind_ the dot  
        if(j-1 > 0 && j-1 <= edge) {
            lcd.setCursor(j-1, first_row);
            lcd.write(3);
            delay(s);
        }

        if (j - k - 1 >= 0 && j-k-1 <= edge) {
            if(ghost_pos >= 0 && ghost_pos <= edge) {
                lcd.setCursor(ghost_pos, first_row);
                lcd.write(" ");
                delay(s);
            }
            // Choose the ghost's new position and place it there.
            ghost_pos = j-k-1;
            lcd.setCursor(ghost_pos, first_row);
            lcd.write(5);
            delay(s);
        }
        
        // Pause 2 frames, then move on.
        delay(2*s);
        
        // If we've just drawn PAC-man, we want to erase him so he can move over one pixel.
        if(j-1 > 0 && j-1 <= edge) {
            lcd.setCursor(j-1, first_row);
            lcd.write(" ");
            delay(s);
        }
    
        // Draw him on top of the dot, mouth closed.
        if(j > 0 && j <= edge) {
            lcd.setCursor(j, first_row);
            lcd.write(2);
            delay(s);
        }

        // The ghost follows PAC-man, so same as before we move the ghost over one.
        if (j - k >= 0) {
            if (ghost_pos >= 0) {
                lcd.setCursor(ghost_pos, first_row);
                lcd.write(" ");
                delay(s);
            }
     
            ghost_pos = j-k;
            lcd.setCursor(ghost_pos, first_row);
            lcd.write(5);
            delay(s);
        }

        // Wait 2 more frames before we move on to the next animation.
        delay(2*s);

        lcd.setCursor(j, first_row);
        lcd.write(" ");                     // Erase PAC-man and the Ghost before we move on
        
        if(ghost_pos >= 0 && ghost_pos <= edge) {
            lcd.setCursor(ghost_pos, first_row);
            lcd.write(" ");
        }
    }

    /*
    for(int j = 0; j <= edge; j++) {
    lcd.setCursor(j, first_row);
    lcd.write(" ");
    } 
    */ 

    // Repopulate the first row again.
    for(int j = first_dc; j <= last_dc; j+= every_dc) {
        lcd.setCursor(j, first_row);
        lcd.write(6);
        delay(s);
    }

    /***************************************************
    **       PAC-Man moving to the Left, Second Row   **
    ***************************************************/

    for(int j = edge; j >= -3; j-= every_dc) {
        // Move in PAC-man, this time from the right.   
        if(j+1 > 0 && j+1 <= edge) {
            lcd.setCursor(j+1, second_row);
            lcd.write(4);
            delay(s);
        }
        
        // Followed again by the ghost.
        if (j + k + 1 >= 0 && j+k+1 <= edge) {
            if (ghost_pos >= 0 && ghost_pos <= edge) {
                lcd.setCursor(ghost_pos, second_row);
                lcd.write(" ");
                delay(s);
            }

            ghost_pos = j+k+1;
            lcd.setCursor(ghost_pos, second_row);
            lcd.write(5);
            delay(s);
        }

        delay(2*s);
        
        // Erase PAC-man again
        if(j+1 >= 0 && j+1 <= edge) {
            lcd.setCursor(j+1, second_row);
            lcd.write(" ");
            delay(s);
        }

        // He bites down on the power pellet.
        if(j >= 0 && j <= edge) {
            lcd.setCursor(j, second_row);
            lcd.write(2);
            delay(s);
        }

        // Move the ghost again.
        if (j+k >= 0 && j+k <= edge) {
            if (ghost_pos >= 0 && ghost_pos <= edge) {
            lcd.setCursor(ghost_pos, second_row);
            lcd.write(" ");
            delay(s);
            }

            ghost_pos = j+k;
            lcd.setCursor(ghost_pos, second_row);
            lcd.write(5);
            delay(s);
        }

        delay(2*s);
        
        // Erase PAC-man and the ghost again.
        if(j >= 0) {
            lcd.setCursor(j, second_row);
            lcd.write(" ");
        }
        
        if(ghost_pos >=0 && ghost_pos <= edge) {
            lcd.setCursor(ghost_pos, second_row);
            lcd.write(" ");
        }
        delay(s);
    }

    /*for(int j = edge; j >= 0; j--) {
        lcd.setCursor(j, second_row);
        lcd.write(" ");
    }*/

    // Re-populate the second row of power pellets
    for(int j = last_dc; j >= first_dc; j-= every_dc) {
        lcd.setCursor(j, second_row);
        lcd.write(6);

        delay(s); 
        lcd.clear();

    }
 }


/*---------------------------------------------------------------------------------


    Transparent window effect in mode 1 
    -- digifox


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "window.h"

#define REG_HDMA0 (*(vuint8 *)0x4300)
#define REG_HDMA1 (*(vuint8 *)0x4310)
#define REG_HDMA2 (*(vuint8 *)0x4320)
#define REG_HDMA3 (*(vuint8 *)0x4330)
#define REG_HDMA4 (*(vuint8 *)0x4340)
#define REG_HDMA5 (*(vuint8 *)0x4350)
#define REG_HDMA6 (*(vuint8 *)0x4360)
#define REG_HDMA7 (*(vuint8 *)0x4370)

const u8 tablelefttriangle[] = {
    128, 255, // y = 128
    80, 40, // x = 40, height = 80
    1, 255, // Set left=255
    0
};

const u8 tablerighttriangle[] = {
    128, 0, // y = 128
    80, 216, // width = 216, height = 80
    1, 0, // Set right=0
    0	
};

/*!\brief Create an HDMA transparent Window.
    \param bgNumber the background number where the transparent window is displayed.
    \param color the window color (BGR format, see REG_COLDATA).
    \param colorIntensity the window color intensity (max value is 0b00011111).
    \param colorMath the color math to use (Add/Subtract, Half, Backdrop - see REG_CGADSUB)
    \warning Only works on BG1 and BG2.
    \note This function must be improved to work on BG3 and BG4.
*/
void createTransparentWindow(u8 bgNumber, u8 color, u8 colorIntensity, u8 colorMath) {
    // Enable Color Math and Activate MathWindow (on REG_CGWSEL)
    // Activate the passed colorMath when Main Screen = bgNumber (on REG_CGADSUB)
    setColorEffect(0b00010000, colorMath | (bgNumber + 1));

    // Set color with an intensity
    REG_COLDATA = color | colorIntensity;

    // Create an HDMA Window using HDMA Channels 4 and 5
    // Activate Window1 on bgNumber (see: REG_W12SEL)
    switch(bgNumber) {
        case 0:
            setModeHdmaWindow(MSWIN_BG1, 
                MSWIN1_BG1MSKENABLE, 
                (u8 *) &tablelefttriangle, 
                (u8 *) &tablerighttriangle);
            break;

        case 1:
            setModeHdmaWindow(MSWIN_BG2, 
                MSWIN1_BG2MSKENABLE, 
                (u8 *) &tablelefttriangle, 
                (u8 *) &tablerighttriangle);
            break;
    }

    // Disable main screen windows
    REG_TMW = 0;

    // Activate Color Math on Window1 Area
    REG_WOBJSEL = 0b00100000;

    // Reset HDMA channels 4 and 5
    REG_HDMA4 = 0;
    REG_HDMA5 = 0;
}

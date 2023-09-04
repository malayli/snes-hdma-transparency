/*---------------------------------------------------------------------------------


    Transparent window effect in mode 1 
    -- digifox


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "window.h"

extern char backgroundPic, backgroundPic_end;
extern char backgroundPalette, backgroundPalette_end;
extern char backgroundMap, backgroundMap_end;

int main(void) {
    consoleInit();

    bgInitTileSet(1, 
        &backgroundPic, 
        &backgroundPalette, 
        0, 
        (&backgroundPic_end - &backgroundPic), 
        16*1*2, 
        BG_16COLORS, 
        0x4000);

    bgInitMapSet(1, 
        &backgroundMap, 
        (&backgroundMap_end - &backgroundMap), 
        SC_32x32, 
        0x0000);

    setMode(BG_MODE1, 0);
    bgSetDisable(0);
    bgSetEnable(1);
    bgSetDisable(2);
    setScreenOn();

    createTransparentWindow(1, 0b11100000, 0b00001100, 0b10000000);

    while (1) {
        WaitForVBlank();
    }

    return 0;
}

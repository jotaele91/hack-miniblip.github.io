// miniblip led matrix demo
/* Este programa enciende progresivamente todos los leds de la placa. El color en que lo hace en principio es rojo,
al llegar al final vuelve a repetir el proceso en color verde y posteriormente en azul. */

#include "mbed.h"
#include "neopixel.h"


// Matrix led output pin
#define DATA_PIN P0_9
#define NLEDS 25

void generate(neopixel::Pixel * out, uint32_t index, uintptr_t extra)
{ 
    uint32_t brightness = (index + extra) >> 3;
    out->red   = ((index + extra) & 0x1) ? brightness : 0;
    out->green = ((index + extra) & 0x2) ? brightness : 0;
    out->blue  = ((index + extra) & 0x4) ? brightness : 0;
}

neopixel::PixelArray array(DATA_PIN);
neopixel::Pixel buffer[NLEDS];

/* Enciende el pixel de la posición recibida con la intensidad de rojo, verde y azul recibidas
en valores que oscilan entre 0 y 255. */
void setPixel(uint32_t posicion, uint8_t red, uint8_t green, uint8_t blue) {
  buffer[posicion].red=red;
  buffer[posicion].green=green;
  buffer[posicion].blue=blue;
}


int COLOR = 0; // 0 - ROJO 1 - VERDE 2- AZUL

int main() {
 
    while (1) {
        for(int i=0; i<NLEDS;i++) {
            if(COLOR == 0)
                setPixel(i,60,0,0);
            else if (COLOR == 1) 
                setPixel(i,0,60,0);
            else if (COLOR == 2)
                setPixel(i,0,0,60);
                  
            array.update(buffer, NLEDS); // Aplica el color a los píxeles
            wait_ms(100);
        }
        COLOR = (COLOR+1)%3;
    }
}


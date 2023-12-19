
/* Kernel includes. */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

/* Library includes. */
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

/* SPI pico pins.  MISO=Pico RX*/
#define MISO 16
#define CS 17
#define SCK 18
/*#define MOSI 19*/

/* SPI pico port */
#define SPI_PORT spi0

int32_t temperature;
uint16_t buf16bit;

void vTemperatureTask() {                                             
  while (1) {                                                            
   gpio_put (CS, 0);
   vTaskDelay(1); 
   spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
   buf16bit <<= 8;
   spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
   printf("buf16bit = %x\n", buf16bit);
   gpio_put(CS, 1);
   if (buf16bit & 0x4) {
     printf("no thermocouple attached!");
    }
   else {
     buf16bit >>= 3;
     printf("buf16bitConvert = %x\n", buf16bit);
    }
   printf("Temp = %.2f C \n", buf16bit*0.25);
   vTaskDelay(200);     
  }

}

int main() {
 stdio_init_all(); // Initialise I/O for USB Serial
 spi_init(SPI_PORT, 500000); // Initialise spi0 at 500kHz
  
 //Initialise GPIO pins for SPI communication
 gpio_set_function(SCK, GPIO_FUNC_SPI);
 gpio_set_function(MISO, GPIO_FUNC_SPI);
 gpio_set_function(CS, GPIO_FUNC_SPI);

 // Configure Chip Select
 gpio_init(CS); //Initialise CS Pin
 gpio_set_dir(CS, GPIO_OUT); // Set CS as output
 gpio_put(CS, 1); //Set CS High to indicate no curent SPI communication 
 
 xTaskCreate(vTemperatureTask, "vTemperatureTask", 1024, NULL, 1, NULL);
 vTaskStartScheduler();        
    
 return 0;
}
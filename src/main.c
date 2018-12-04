//nRF24LE1 Receiver
#include "reg24le1.h"
#include "gpio.h"
#include "rf.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

void main()
{

    unsigned char datavar[5];

    //Setup LED diode pin
    gpio_pin_configure(GPIO_PIN_ID_P1_4, GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT | GPIO_PIN_CONFIG_OPTION_PIN_MODE_INPUT_BUFFER_ON_PULL_UP_RESISTOR);

    // Setup UART pins
    gpio_pin_configure(GPIO_PIN_ID_FUNC_RXD,
            GPIO_PIN_CONFIG_OPTION_DIR_INPUT |
            GPIO_PIN_CONFIG_OPTION_PIN_MODE_INPUT_BUFFER_ON_NO_RESISTORS);

    gpio_pin_configure(GPIO_PIN_ID_FUNC_TXD,
            GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT |
            GPIO_PIN_CONFIG_OPTION_OUTPUT_VAL_SET |
            GPIO_PIN_CONFIG_OPTION_PIN_MODE_OUTPUT_BUFFER_NORMAL_DRIVE_STRENGTH);

    uart_configure_8_n_1_9600();
    
   rf_configure_debug_lite(true, 5);
    delay_us(130);

    while (true) {


        if ((rf_irq_pin_active() && rf_irq_rx_dr_active())) {
            
            rf_read_rx_payload(&datavar[0], 5);
            gpio_pin_val_complement(GPIO_PIN_ID_P1_4);
           }

        if (rf_irq_rx_dr_active()) {
            printf("Humidity: %d.%d, Temperature: %d.%d\r\n", datavar[0], datavar[1], datavar[2], datavar[4]);
           
        }



        rf_irq_clear_all();

        delay_s(4);


    }


}

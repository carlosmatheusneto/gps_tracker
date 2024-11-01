#include <stdio.h>
#include "init_components/uart_sim.h"
#include <string.h>

void app_main(void)
{
	//
	uart_sim_init();
	vTaskDelay(3000/portTICK_PERIOD_MS);
	char *s = "AT\r\n";
	uart_write_bytes(UART_SIM_NUM, s, strlen(s));
	while(1){
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

#include "uart_sim.h"

QueueHandle_t uart_sim_queue;
uart_event_t uart_sim_event;
TaskHandle_t uart_sim_task_handler = NULL;
bool uart_sim_event_task_running = true;

void uart_sim_event_task(void *p){
	while(uart_sim_event_task_running){
		if(xQueueReceive(uart_sim_queue, &uart_sim_event, portMAX_DELAY)){
			char temp[uart_sim_event.size+1];
			switch(uart_sim_event.type){
				case UART_DATA:
					ESP_LOGI(TAG_UART_SIM, "UART DATA");
					uart_read_bytes(UART_SIM_NUM, temp, uart_sim_event.size, portMAX_DELAY);	
					temp[uart_sim_event.size] = '\0';
					ESP_LOGI("TAG_UART_SIM", "%s\n", temp);
				break;
				default:
					ESP_LOGI(TAG_UART_SIM, "UART_DEFAULT");
				break;
			}
		}
	}
}

void uart_sim_init(){
	const uart_config_t uart_sim_config = {
		.baud_rate = BAUD_RATE_SIM,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
	};

	esp_err_t err = uart_param_config(UART_SIM_NUM, &uart_sim_config);
	if(err != ESP_OK){
		ESP_LOGI(TAG_UART_SIM, "%s\n", esp_err_to_name(err));
		return;
	}
	err = uart_set_pin(UART_SIM_NUM, TX_SIM_PIN, RX_SIM_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	if(err != ESP_OK){
		ESP_LOGI(TAG_UART_SIM, "%s\n", esp_err_to_name(err));
		return;
	}
	err = uart_driver_install(UART_SIM_NUM, BUF_SIZE_SIM, BUF_SIZE_SIM, 1024, &uart_sim_queue, 0);
	if(err != ESP_OK){
		ESP_LOGI(TAG_UART_SIM, "%s\n", esp_err_to_name(err));
		return;
	}
	if(xTaskCreate(&uart_sim_event_task, "uart_sim_event_task", 2048, NULL, 10, &uart_sim_task_handler) != pdPASS){
		ESP_LOGI(TAG_UART_SIM, "Error creating uart_sim_event_task");
	}
}

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "dht11.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//??????
char *strx,*extstrx,*Readystrx;
char *strx1,*extstrx,*Readystrx;
char RxBuffer[1024],Rxcouter;
char *strstr(const char *, const char *);
uint8_t Res;
int len;
int number;
char *id;
double wendu;
double shidu;
char Wendu[10];
char Shidu[10];
char* info1;
char* info2;
char* info3;
int Len;
char * result;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Clear_Buffer(void)
{
 uint8_t i;
 
for(i=0;i<Rxcouter;i++)
 RxBuffer[i]=0;
 Rxcouter=0;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{ 
 UNUSED(huart); 
 
 if(huart->Instance ==USART1)
{ 
 RxBuffer[Rxcouter++] = Res; 
 HAL_UART_Receive_IT(&huart1, (uint8_t *)&Res, 1); 
 } 
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
	HAL_UART_Receive_IT(&huart1,&Res,1);
		while(1){
		printf("ATI\r\n");
		HAL_Delay(1000);
		strx=strstr((const char*)RxBuffer,(const char*)"Fibocom");
		if(strx==NULL)
		{
			Clear_Buffer();	
			printf("Fail Version");
			HAL_Delay(1000);
			printf("ATI\r\n");
		  HAL_Delay(1000);		
			strx=strstr((const char*)RxBuffer,(const char*)"Fibocom");
		}else{
			Clear_Buffer();
			printf("Sucessful\n");
			break;
		}
	}
	printf("AT+CPIN?\r\n");
	HAL_Delay(1000);
	strx=strstr((const char*)RxBuffer,(const char*)"READY");
	while(strx==NULL){
		Clear_Buffer();
		printf("SIM card Query failure");
		HAL_Delay(1000);
		strx=strstr((const char*)RxBuffer,(const char*)"READY");
	}
	Clear_Buffer();
	printf("SIM card Ok");
	HAL_Delay(1000);
	printf("AT+CSQ?\r\n");
	HAL_Delay(1000);
	strx=strstr((const char*)RxBuffer,(const char*)"+CSQ:");
	while(strx==NULL){
		Clear_Buffer();
		printf("Network failure");
		HAL_Delay(1000);
		strx=strstr((const char*)RxBuffer,(const char*)"+CSQ:");
	}
	Clear_Buffer();
	printf("Normal Network");
	HAL_Delay(1000);
	printf("AT+CGREG?\r\n");
	HAL_Delay(1000);
	strx=strstr((const char*)RxBuffer,(const char*)"0,1");
	while(strx==NULL){
		Clear_Buffer();
		printf("The injection network is unavailable");
		HAL_Delay(1000);
		strx=strstr((const char*)RxBuffer,(const char*)"0,1");
	}
	Clear_Buffer();
	printf("The injection network is OK");
	HAL_Delay(1000);
	printf("AT+MIPCALL=1\r\n");
	HAL_Delay(1000);
	printf("AT+MIPCALL?\r\n");
	HAL_Delay(1000);
	strx=strstr((const char*)RxBuffer,(const char*)"+MIPCALL: 1");
	while(strx==NULL)
		{
			Clear_Buffer();	
			printf("Fail IP");
			HAL_Delay(1000);
			printf("AT+MIPCALL=1\r\n");
			HAL_Delay(1000);
			strx=strstr((const char*)RxBuffer,(const char*)"+MIPCALL: ");
		}
	Clear_Buffer();
	printf("OK IP");
	HAL_Delay(1000);
	///*down code may kill
	printf("AT+HMCON=0,60,\"0da80bc5b9.st1.iotda-device.cn-south-1.myhuaweicloud.com\",\"1883\",\"66c9c8ded1ae3a6dd5fa9194_wenshidu\",\"20210804\",0\r\n");
	HAL_Delay(2000);
	strx=strstr((const char*)RxBuffer,(const char*)"+HMCON OK");
	strx1 = strstr((const char*)RxBuffer,(const char*)"+HMCON ERR:11");
	while(strx==NULL)
		{
			if(strx1!=NULL)break;
			Clear_Buffer();	
			printf("CONNECT HUAWEI fail");
			HAL_Delay(1000);
			printf("AT+HMCON=0,60,\"0da80bc5b9.st1.iotda-device.cn-south-1.myhuaweicloud.com\",\"1883\",\"66c9c8ded1ae3a6dd5fa9194_wenshidu\",\"20210804\",0\r\n");
			HAL_Delay(1000);
			strx=strstr((const char*)RxBuffer,(const char*)"+HMCON OK");
			strx1 = strstr((const char*)RxBuffer,(const char*)"+HMCON ERR:11");
		}
	Clear_Buffer();
	printf("Connect huawei ok");
	HAL_Delay(1000);	
	//upcode may kill*/


	while(DHT11_Init())													//???DHT11
			{
				printf("DHT11 fail!\r\n");
				HAL_Delay(500);
			}
	printf("DHT11 OK!\r\n");
	while (1)
  {
		uint8_t res = DHT11_Read_Data(&temperature,&humidity);		//?????
		if(res == 0)	//????????????
		 {
				DHT11_Read_Data(&temperature,&humidity); 	//???????
			  wendu = (temperature>>8)+0.1*(temperature&0xff);
			  shidu = (humidity>>8)+0.1*(humidity&0xff);
			  sprintf(Wendu, "%.1f", wendu);
			  sprintf(Shidu, "%.1f", shidu);
				//printf("DHT11 Temperature = %d.%d ?\r\n",temperature>>8,temperature&0xff);
				//printf("DHT11 Humidity = %d.%d%%\r\n",humidity>>8,humidity&0xff);
        //printf("AT+HMPUB=1,\"$oc/devices/66c9c8ded1ae3a6dd5fa9194_wenshidu/sys/properties/report\",66,\"{\\\"services\\\":[{\\\"service_id\\\":\\\"tellWSdu\\\",\\\"properties\\\":{\\\"switch\\\":1}}]}\"\r\n");
info1="AT+HMPUB=1,\"$oc/devices/66c9c8ded1ae3a6dd5fa9194_wenshidu/sys/properties/report\",81,\"{\\\"services\\\":[{\\\"service_id\\\":\\\"tellWSdu\\\",\\\"properties\\\":{\\\"wendu\\\":";
info2=",\\\"shidu\\\":";
info3="}}]}\"\r\n";
Len = strlen(info1) + strlen(Wendu) + strlen(info2) + strlen(Shidu)+ strlen(info3)+1;
result = (char *)malloc(Len * sizeof(char)); 
strcpy(result, info1);
strcat(result, Wendu);
strcat(result, info2);
strcat(result, Shidu);
strcat(result, info3);
printf("%s", result);
free(result);
result = NULL;
HAL_Delay(1000);
/*strx=strstr((const char*)RxBuffer,(const char*)"+HMPUB OK");
while(strx==NULL)
	{
			Clear_Buffer();	
			printf("Fail Up data");
			HAL_Delay(1000);
			printf("%s", result);
			HAL_Delay(1000);
			strx=strstr((const char*)RxBuffer,(const char*)"+HMPUB OK");
  }*/
		 }
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

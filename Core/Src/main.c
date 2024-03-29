/* ADC and DAC Lab (Uncomment as needed to obtain each version) */
/**CHASE GRISWOLD
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  SystemClock_Config();

//_____________________UNCOMMENT FOR ADC_SECTION____________
//	RCC->AHBENR |=  RCC_AHBENR_GPIOCEN;
//	
//	//LED RESET
//	GPIOC->MODER = 0;
//	GPIOC->PUPDR = 0;
//	GPIOC->OSPEEDR = 0;
//	GPIOC->OTYPER = 0;
//	
//	//LED SETUP
//	GPIOC->MODER |= (1 << 12);
//	GPIOC->MODER |= (1 << 14); 
//	GPIOC->MODER |= (1 << 16);
//	GPIOC->MODER |= (1 << 18);
//	
//	//Set GPIOC low
//	GPIOC->ODR = 0;
//	
//	//Set PC3 to Analog mode. (Connects to ADC_IN13)
//	GPIOC->MODER |= (3 << 6);
//	
//	// Enable the ADC1 in the RCC peripheral.
//	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
//	
//	//Configure the ADC to 8-bit resolution, continuous conversion mode, hardware triggers
//	//disabled (software trigger only).
//	ADC1->CFGR1 = 0; //Clear: Also Disables Hardware Triggers
//	ADC1->CFGR1 |= (1 << 13); //Continuous Conversion Mode
//	ADC1->CFGR1 |= (2 << 3); //8-Bit Resolution
//	
//	// Select/enable the input pin�s channel for ADC conversion
//	ADC1->CHSELR = 0; //Clear
//	ADC1->CHSELR |= (1 << 13); //Set Channel to ADC_IN13

//	// Perform a self-calibration, enable, and start the ADC.
//	ADC1->CR = 0; //Cal
//	ADC1->CR |= (1 << 31); //Enable
//	
//	//Wait:  ADCAL: ADC calibration bit 31 = 0
//	while (((ADC1->CR)>>31) != 0){
//		
//	}
//	
//	//Zero out the ADEN
//	ADC1->CR |= (1 << 0); //Set ADEN
//	
//	//Wait ADRDY Flag
//	while((ADC1->ISR && 0x1) != 1){ //ISR Bit 0: ADRDY
//	}
//	
//	//Set ADSTART: Start Conversion
//	ADC1->CR |= (1 << 2);
//	
//	uint16_t reso = 0;
//__________________________ADC_ABOVE_____________________




//_____________________DAC_SECTION_____________


	//Enable GPIOA in RCC
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Default GPIOA
	GPIOA->MODER = 0x28000000;
	GPIOA->OTYPER = 0;
	GPIOA->PUPDR = 0;
	//GPIOA->OSPEEDR;
	
	//Set PA4 to AF (DAC_OUT1)
	GPIOA->MODER |= (3 << 8);
	
	//Enable DAC in RCC
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	//DAC Setup
	//2. Set the used DAC channel to software trigger mode.
	DAC1->CR = 0; //Clear
	DAC1->CR |= (7 << 3); //SW Trigger Mode
	DAC1->SWTRIGR = 0;
	DAC1->SWTRIGR |= (1 << 0); //SW Channel 1 Trigger
	
	//3. Enable the used DAC channel.
	//Enable
	DAC1->CR |= (1 << 0);
	
	// Sine Wave: 8-bit, 32 samples/cycle
	const uint8_t sine_table[32] = {127,151,175,197,216,232,244,251,254,251,244,
	232,216,197,175,151,127,102,78,56,37,21,9,2,0,2,9,21,37,56,78,102};
	// Triangle Wave: 8-bit, 32 samples/cycle
	const uint8_t triangle_table[32] = {0,15,31,47,63,79,95,111,127,142,158,174,
	190,206,222,238,254,238,222,206,190,174,158,142,127,111,95,79,63,47,31,15};
	// Sawtooth Wave: 8-bit, 32 samples/cycle
	const uint8_t sawtooth_table[32] = {0,7,15,23,31,39,47,55,63,71,79,87,95,103,
	111,119,127,134,142,150,158,166,174,182,190,198,206,214,222,230,238,246};
	// Square Wave: 8-bit, 32 samples/cycle
	const uint8_t square_table[32] = {254,254,254,254,254,254,254,254,254,254,
	254,254,254,254,254,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//5. In the main application loop, use an index variable to write the next value in the wave-table
  //(array) to the appropriate DAC data register.
	// 6. Use a 1ms delay between updating the DAC to new values

//_____________________END_DAC_SECTION_____________________



  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		//______________DAC__________________
			for(int i = 0; i < 32; i++){
				DAC1->DHR8R1 = sine_table[i]; //Change this line to do triangle or saw.
				HAL_Delay(1);
			}
		//____________END_DAC___________________
		
				
				
				
		
		//_____________________Uncomment for ADC____________________
//		//8-bit ADC - 256 bits of resolution/4 LEDs = 64
//		//RED 6, BLUE 7, ORANGE 8, GREEN 9
//		
//		//Apply the DR stored value to a variable that can be used in the loop.	
//		reso = ADC1->DR;
//		
			
//		if (reso < 64){
//			GPIOC->ODR |= (1 << 6); //Red High
//			GPIOC->ODR &= ~((1 << 7) | (1 << 8) | (1 << 9));
//		}
//		else if (reso >= 64 && reso < 128){
//			GPIOC->ODR |= (1 << 7); // Blue High
//			GPIOC->ODR &= ~((1 << 8) | (1 << 9));
//		}
//		else if (reso >= 128 && reso < 192){
//			GPIOC->ODR |= (1 << 8); //Orange High
//			GPIOC->ODR &= ~(1 << 9);
//		}
//		else {
//			GPIOC->ODR |= (1 << 9); //Green High
//		}
//		
//		//Wait: End Sequence
//		while((ADC1->ISR & 0x4) != 4){
//			
//		}
//		//Reset: FLAG after each loop
//		ADC1->ISR |= (1 << 2);
//________________________ADC__ABOVE_________________________________


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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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

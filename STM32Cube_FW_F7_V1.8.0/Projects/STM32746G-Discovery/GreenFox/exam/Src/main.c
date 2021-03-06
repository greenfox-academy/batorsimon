/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef uart_handle;
GPIO_InitTypeDef gpio_init_structure;
TIM_HandleTypeDef TimHandle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

void EXTI15_10_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void TIM2_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void peripheral_init();

enum morsecode{a, c, i, s, o} morse;
char array[20];
uint8_t tim_counter = 0;
uint8_t short_signal = 0;
uint8_t long_signal = 0;
uint8_t space = 0;
int f = 0;


int main(void) {
    MPU_Config();
    CPU_CACHE_Enable();
    HAL_Init();
    SystemClock_Config();
    peripheral_init();

    printf("\n-----------------WELCOME-----------------\r\n");

    while (1) {   }

}

void TIM2_IRQHandler() {
    HAL_TIM_IRQHandler(&TimHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	tim_counter++;
}

void EXTI15_10_IRQHandler(){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

 	if (tim_counter > 10 && tim_counter < 140 ){    // tim_counter > 50 && tim_counter < 250
 		//printf("short signal! timer: %d \n", tim_counter);
 		short_signal++;
 		tim_counter = 0;

 	} else if (tim_counter > 140 && tim_counter < 210 ){   // tim_counter > 250 && tim_counter < 750
 		//printf("long signal. timer: %d\n", tim_counter);
 		long_signal++;
 		tim_counter = 0;

 	} else if (tim_counter > 210){   // tim_counter > 1000
 		printf("The word you morsed in: ");
 		for(int j = 0; j < f; j++){
 			printf("%c", array[j]);
 		}
 		printf("\nEnd of the word! \n\n");
 		tim_counter = 0;
 		f = 0;

 	} else {
 		printf("you moron!! Watch out for the right signal distance!! \n");
 		tim_counter = 0;
 	}


 	 if(short_signal == 1 && long_signal == 1) {
		   printf("a\n");
		   array[f] = 'a';
		   f++;
		  long_signal = 0;
		 short_signal = 0;

	   }

 	   if( long_signal == 2 &&  short_signal == 2) {
		   printf("c\n");
		  array[f] = 'c';
		   f++;
		  long_signal = 0;
		  short_signal = 0;

		}

 	  if(short_signal == 2 ) {
			printf("i\n");
			array[f] = 'i';
			f++;
			long_signal = 0;
			short_signal = 0;

		}

 	 if(short_signal == 3 ) {
		   printf("s\n");
		  array[f] = 's';
		   f++;
		  long_signal = 0;
		   short_signal = 0;

		}

 	if(long_signal == 3 ) {
		printf("o\n");
		array[f] = 'o';
		f++;
		long_signal = 0;
		short_signal = 0;

	}


/*
    switch(morse){
               case a:
                   if(short_signal == 1 && space == 1 && long_signal == 1) {
                	   printf("a\n");
                   } else {
                	   break;
                   }
                   break;

               case c:
            	   if( long_signal == 1 && space == 1&&  short_signal == 1 && space == 1 && long_signal == 1 &&  short_signal == 1) {
            		   printf("c\n");
					} else {
						break;
					}
            	   break;

               case i:
            	   if(short_signal == 1 && space == 1 && short_signal == 1) {
            		   printf("i\n");
					} else {
						break;
					}
            	   break;

               case s:
            	   if(short_signal == 1 && space == 1 && short_signal == 1 && space == 1 && short_signal == 1) {
            		   printf("s\n");
					} else {
						break;
					}
            	   break;

               case o:
            	   if(long_signal == 1 && space == 1 && long_signal == 1 && space == 1 && long_signal == 1) {
            		   printf("o\n");
					} else {
						break;
					}
            	   break;

               default:
                   break;
       }
*/

    if(morse == a || morse == c || morse == i || morse == s || morse == o){
           BSP_LED_Toggle(LED_GREEN);
       } else {
       	BSP_LED_Off(LED_GREEN);
       }

}
void peripheral_init(){
    __HAL_RCC_GPIOI_CLK_ENABLE();
    gpio_init_structure.Pin = GPIO_PIN_11;
    gpio_init_structure.Mode = GPIO_MODE_IT_RISING;
    gpio_init_structure.Speed = GPIO_SPEED_HIGH;
    gpio_init_structure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOI, &gpio_init_structure);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 15, 0);

    BSP_LED_Init(LED_GREEN);
    BSP_LED_On(LED_GREEN);

    __HAL_RCC_TIM2_CLK_ENABLE();
    uart_handle.Init.BaudRate = 115200;
    uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart_handle.Init.StopBits = UART_STOPBITS_1;
    uart_handle.Init.Parity = UART_PARITY_NONE;
    uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart_handle.Init.Mode = UART_MODE_TX_RX;
    BSP_COM_Init(COM1, &uart_handle);

    TimHandle.Instance = TIM2;  // 108 000 000  / 54 000 = 2000
    TimHandle.Init.Period = 1;    //   65535
    TimHandle.Init.Prescaler =  54000;   // 54000
    TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle.Init.RepetitionCounter = 0;
    HAL_TIM_Base_Init(&TimHandle);            //Configure the timer
    HAL_TIM_Base_Start_IT(&TimHandle);          // start the timer peripherial
    HAL_NVIC_SetPriority(TIM2_IRQn, 0x00, 0x00);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

// SYSTEM FILES    -----------------------------------------

PUTCHAR_PROTOTYPE {
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    HAL_UART_Transmit(&uart_handle, (uint8_t *) &ch, 1, 0xFFFF);
    return ch;
}
/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000
 *            HCLK(Hz)                       = 216000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432
 *            PLL_P                          = 2
 *            PLL_Q                          = 9
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void) {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /* activate the OverDrive to reach the 216 Mhz Frequency */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
        Error_Handler();
    }
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
        Error_Handler();
    }
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
    /* User may add here some code to deal with this error */
    while (1) {
    }
}
/**
 * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
 * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
 *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
 * @param  None
 * @retval None
 */
static void MPU_Config(void) {
    MPU_Region_InitTypeDef MPU_InitStruct;
    /* Disable the MPU */
    HAL_MPU_Disable();
    /* Configure the MPU attributes as WT for SRAM */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x20010000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    /* Enable the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void) {
    /* Enable I-Cache */
    SCB_EnableICache();
    /* Enable D-Cache */
    SCB_EnableDCache();
}
#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1)
    {
    }
}
#endif

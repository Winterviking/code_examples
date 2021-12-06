
#include "drv_clock.h"

volatile DWORD SYSCLK_1MS=0;

// EXT OSC SETUP
// внешний кварц
void drv_clock_config(void)
{
    //HAL_init(); // готовил переход полностью на HAL (специфика)

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
    __SYSCFG_CLK_ENABLE();
	__PWR_CLK_ENABLE();

  /* Configure Buffer cache, Flash prefetch,  Flash preread */
#if (BUFFER_CACHE_DISABLE != 0)
  __HAL_FLASH_BUFFER_CACHE_DISABLE();
#endif // BUFFER_CACHE_DISABLE

#if (PREREAD_ENABLE != 0)
  __HAL_FLASH_PREREAD_BUFFER_ENABLE();
#endif // PREREAD_ENABLE

#if (PREFETCH_ENABLE != 0)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif // PREFETCH_ENABLE

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;

	RCC_OscInitStruct.HSEState = RCC_HSE_ON;

	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_12;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);


	//  SysTick_IRQn interrupt configuration
	HAL_NVIC_SetPriority((IRQn_Type) SysTick_IRQn, 0, 0);

    // св€зано с задачей
    //__GPIOA_CLK_ENABLE();
	//__GPIOB_CLK_ENABLE();
	//__GPIOC_CLK_ENABLE();
}





// низкое потребление
void drv_clock_config_lp(void)
{

    __HAL_RCC_HSI_ENABLE();
	__PWR_CLK_ENABLE();
    __SYSCFG_CLK_DISABLE();

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Configure Buffer cache, Flash prefetch,  Flash preread */
#if (BUFFER_CACHE_DISABLE != 0)
  __HAL_FLASH_BUFFER_CACHE_DISABLE();
#endif // BUFFER_CACHE_DISABLE

#if (PREREAD_ENABLE != 0)
  __HAL_FLASH_PREREAD_BUFFER_ENABLE();
#endif // PREREAD_ENABLE

#if (PREFETCH_ENABLE != 0)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif // PREFETCH_ENABLE

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;

	RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_12;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

    HAL_SYSTICK_CLKSourceConfig(0);
	//HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	//  SysTick_IRQn interrupt configuration
	//HAL_NVIC_SetPriority((IRQn_Type) SysTick_IRQn, 0, 0);

    //__GPIOA_CLK_ENABLE();
	//__GPIOB_CLK_ENABLE();
}


void drv_clock_deinit()
{
    GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin      = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_15;
	GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull     = GPIO_NOPULL;
	GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.Pin      = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_15;
	GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull     = GPIO_NOPULL;
	GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}



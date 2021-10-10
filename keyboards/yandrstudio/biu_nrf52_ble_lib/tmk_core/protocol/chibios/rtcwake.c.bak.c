void RTC_Init()
{
  // enable backup and pwr clocks
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  PWR->CR |= PWR_CR_DBP;

  // reset RTC
  RCC->CSR |= RCC_CSR_RTCRST;
  RCC->CSR &= ~RCC_CSR_RTCRST;

  /* enable LSE and wait for it to stabilize
  RCC->CSR |= RCC_CSR_LSION;
  while (!(RCC->CSR & RCC_CSR_LSIRDY))
  {
    OsSleepMs(100);
    i++;
    if (i>50)
    {
      SysError("LSI did not stabilize.");
      break;
    }
    if (i%5) SysInfo("Waiting for LSI to stabilize...");
  }
  SysInfo("LSI stable."); */

  // reset RTC
  RCC->CSR |= RCC_CSR_RTCRST;
  RCC->CSR &= ~RCC_CSR_RTCRST;

  // enable RTC with external 32kHz xtal
  RCC->CSR |= RCC_CSR_RTCSEL_LSI;
  RCC->CSR |= RCC_CSR_RTCEN;

  //RTC->CR &= (uint16_t)~0x0008;
  //while (!(RTC->CR & 0x8));
  //while (!(RTC->CR & 0x20));
  //RTC->CR |= RTC_CR_ALRAIE;
  //while (!(RTC->CR & 0x20));
}

static uint32_t RCC_AHBENR_bk;
static uint32_t RCC_APB2ENR_bk;
static uint32_t RCC_APB1ENR_bk;
static uint32_t RCC_AHBLPENR_bk;
static uint32_t RCC_APB2LPENR_bk;
static uint32_t RCC_APB1LPENR_bk;
static uint32_t ADC1_CR2_bk;
static uint32_t USART1_CR1_bk;
static uint32_t USART2_CR1_bk;
static uint32_t USART3_CR1_bk;
static uint32_t OPAMP_CSR_bk;


static void lp_backup() {
  /* backup clock & periph settings */
  RCC_AHBENR_bk = RCC->AHBENR;
  RCC_APB2ENR_bk = RCC->APB2ENR;
  RCC_APB1ENR_bk = RCC->APB1ENR;
  RCC_AHBLPENR_bk = RCC->AHBLPENR;
  RCC_APB2LPENR_bk = RCC->APB2LPENR;
  RCC_APB1LPENR_bk = RCC->APB1LPENR;
  ADC1_CR2_bk = ADC1->CR2;
  USART1_CR1_bk = USART1->CR1;
  USART2_CR1_bk = USART2->CR1;
  USART3_CR1_bk = USART3->CR1;
  OPAMP_CSR_bk = OPAMP->CSR;

  /* disable clocks and peripherals */
  RCC->AHBENR = 0;
  RCC->APB2ENR = 0;
  RCC->APB1ENR = RCC_APB1ENR_PWREN;
  RCC->AHBLPENR = 0;
  RCC->APB2LPENR = 0;
  RCC->APB1LPENR = RCC_APB1LPENR_PWRLPEN;
  ADC1->CR2 = 0;
  USART1->CR1 = 0;
  USART2->CR1 = 0;
  USART3->CR1 = 0;
  OPAMP->CSR = OPAMP_CSR_OPA1PD | OPAMP_CSR_OPA2PD | OPAMP_CSR_S5SEL2 | OPAMP_CSR_S4SEL2;
}

static void lp_restore() {
  /* restore clock & periph settings */
  RCC->AHBENR = RCC_AHBENR_bk;
  RCC->APB2ENR = RCC_APB2ENR_bk;
  RCC->APB1ENR = RCC_APB1ENR_bk;
  RCC->AHBLPENR = RCC_AHBLPENR_bk;
  RCC->APB2LPENR = RCC_APB2LPENR_bk;
  RCC->APB1LPENR = RCC_APB1LPENR_bk;
  ADC1->CR2 = ADC1_CR2_bk;
  USART1->CR1 = USART1_CR1_bk;
  USART2->CR1 = USART2_CR1_bk;
  USART3->CR1 = USART3_CR1_bk;
  OPAMP->CSR = OPAMP_CSR_bk;
}

void RTC_DeepSleep(uint32_t seconds, bool periph)
{
  ADC_Stop();
  DbgConsoleShutdown();

  //nvicDisableVector(HANDLER_SYSTICK);
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

  if (periph) {
    for (int i = 0; i<16; i++) {
      modePinDirect(GPIOA,i,PAL_MODE_INPUT_ANALOG);
      modePinDirect(GPIOB,i,PAL_MODE_INPUT_ANALOG);
      modePinDirect(GPIOC,i,PAL_MODE_INPUT_ANALOG);
      modePinDirect(GPIOD,i,PAL_MODE_INPUT_ANALOG);
      modePinDirect(GPIOE,i,PAL_MODE_INPUT_ANALOG);
      modePinDirect(GPIOH,i,PAL_MODE_INPUT_ANALOG);
    }
    lp_backup();
  }

  /*
   * use ck_spre (1Hz internal clock)
   * WUCKSEL[2:1] = 10 (1s to 18h)
   * Clear WUTE in RTC_CR to disable wkup timer
   * Poll WUTWF until it is set in RTC_ISR to make sure the access
   *   to the wakeup auto-reload counter and to WUCKSEL[2:0] bits is allowed.
   *   This takes ~2RTCCLK cycles.
   * Program the wakeup auto-reload value WUT[15:0],
   *   and the wakeup clock selection (WUCKSEL[2:0] in RTC_CR).
   *   Set WUTE in RTC_CR to enable timer again.
   */

  // sleep up to 18h
  OsAssert(seconds < 65536,"RTC Assert");

  // unlock RTC regs
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  RTC->PRER |= RTC_PRER_PREDIV_A; // maximum async prediv
  RTC->PRER = (RTC->PRER & RTC_PRER_PREDIV_S) | 0x122; // 1Hz from 37kHz


  RTC->CR &= ~RTC_CR_WUTE;
  while (!(RTC->ISR & RTC_ISR_WUTWF)) {};
  RTC->WUTR = (RTC->WUTR & ~RTC_WUTR_WUT) | (seconds & RTC_WUTR_WUT);
  RTC->CR = (RTC->CR & ~RTC_CR_WUCKSEL) | (RTC_CR_WUCKSEL_2 /* 10x */);
  RTC->CR |= RTC_CR_WUTE;

  RTC->CR |= RTC_CR_WUTIE;

  // clear wakeup timer flag
  RTC->ISR &= ~(RTC_ISR_ALRBF | RTC_ISR_ALRAF | RTC_ISR_WUTF | RTC_ISR_TAMP1F |
                      RTC_ISR_TSOVF | RTC_ISR_TSF);

  // lock RTC regs
  RTC->WPR = 0xFF;

  /* Enter low power mode */
  //PWR->CR |= PWR_CR_LPSDSR;
  //PWR->CR &= ~PWR_CR_PDDS; // stop (rather than standby)

  /* clear PDDS and LPDS bits */
  PWR->CR &= ~(PWR_CR_PDDS | PWR_CR_LPSDSR);

  /* set LPDS and clear  */
  PWR->CR |= (PWR_CR_LPSDSR | PWR_CR_CSBF | PWR_CR_CWUF);
  PWR->CR |= PWR_CR_ULP;

  /* enable wakeup pin */
  PWR->CSR |= PWR_CSR_EWUP1;

  for(int i = 0; i < 100; i++) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
  SCB->SCR |= SCB_SCR_SLEEPDEEP;
  for(int i = 0; i < 100; i++) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
  wake_reason = 0;
  __WFI();
  __disable_irq();
  SCB->SCR &= ~SCB_SCR_SLEEPDEEP;
  PWR->CR |= PWR_CR_CWUF;
  PWR->CR |= PWR_CR_CSBF;
  stm32_clock_init();
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  __enable_irq();

  if (periph) {
    lp_restore();
    palInit(&pal_default_config);
  }

  RTC_Init();
  ADC_Reinit();
  DbgConsoleReInit();

}


void stopMode() {
  palEnableLineEvent(WAKEUP_LINE, PAL_EVENT_MODE_FALLING_EDGE); /* NC */

  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

  /* debugging */
  // DBGMCU->CR |= DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STANDBY;

  /* clear PDDS and LPDS bits */
  PWR->CR &= ~(PWR_CR_PDDS | PWR_CR_LPDS);

  /* set LPDS and clear  */
  PWR->CR |= PWR_CR_LPDS;

  /* enable wakeup pin */
  PWR->CSR |= PWR_CSR_EWUP;

  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  __DSB();
  __WFI();

  chSysLock();
  palDisableLineEventI(WAKEUP_LINE);

  SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

  PWR->CR |= PWR_CR_CWUF;
  PWR->CR |= PWR_CR_CSBF;

  stm32_clock_init();
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

  chSysUnlock();
}

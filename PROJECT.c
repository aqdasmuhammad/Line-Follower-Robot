#define TM_BASE_1							0x40031000
#define TM_BASE_2							0x40032000


#define SYS_RCGC_GPIO_CLK_R 	*((volatile unsigned long*)0x400FE108)
#define RCGC_TIMER_R 					*((volatile unsigned long*)0x400FE604)
#define GPTM_CONFIG_R 				*( volatile long *)( TM_BASE_1 + 0x000 )
#define GPTM_TA_MODE_R 				*( volatile long *)( TM_BASE_1 + 0x004 )
#define GPTM_CONTROL_R 				*( volatile long *)( TM_BASE_1 + 0x00C )
#define GPTM_TA_IL_R 					*( volatile long *)( TM_BASE_1 + 0x028 )
#define GPTM_TA_MATCH_R 			*( volatile long *)( TM_BASE_1 + 0x030 )

#define GPTM_CONFIG_R2 				*( volatile long *)( TM_BASE_2 + 0x000 )
#define GPTM_TA_MODE_R2 			*( volatile long *)( TM_BASE_2 + 0x004 )
#define GPTM_CONTROL_R2				*( volatile long *)( TM_BASE_2 + 0x00C )
#define GPTM_TA_IL_R2			    *( volatile long *)( TM_BASE_2 + 0x028 )
#define GPTM_TA_MATCH_R2		  *( volatile long *)( TM_BASE_2 + 0x030 )

#define GPIO_PORTA_DATA_R 		*((volatile unsigned long*)0x4000407C)
#define GPIO_PORTF_DATA_R 		*((volatile unsigned long*)0x4002501F)
#define GPIO_PORTA_DIR_R 			*((volatile unsigned long*)0x40004400)
#define GPIO_PORTF_DIR_R 			*((volatile unsigned long*)0x40025400)
#define GPIO_PORTA_DEN_R 			*((volatile unsigned long*)0x4000451C)
#define GPIO_PORTF_DEN_R 			*((volatile unsigned long*)0x4002551C)
#define GPIO_PORTF_AFSEL_R 		*((volatile unsigned long*)0x40025420)
#define GPIO_PORTF_PCTL_R 		*((volatile unsigned long*)0x4002552C)

#define CLOCK_ENABLE 					0x21
#define PORTA_PIN							0x1F
#define	PORTF_PIN							0x1F

#define SYS_CLOCK_FREQUENCY 	16000000
#define TIM_16_BIT_CONFIG 		0x00000004 // 16- bit 
#define TIM_PERIODIC_MODE 		0x00000002 // Periodic 
#define TIM_A_ENABLE 					0x00000001 // Timer 
#define TIM_PWM_MODE 					0x0000000A // Timer 
#define TIM_CAPTURE_MODE 			0x00000004 // Timer
#define TIM_A_INTERVAL 				16000 // 1k
#define TIM_A_MATCH 					8000 // 50% Duty Cycle

void Timer1A_Init ( void )
{
	// Enable the clock for port F and Timer1
	SYS_RCGC_GPIO_CLK_R |= CLOCK_ENABLE;
	RCGC_TIMER_R |= 0x02;
	// Configure PortF pin 2 as Timer1 A output
	GPIO_PORTF_AFSEL_R |= 0x00000008 ;
	GPIO_PORTF_PCTL_R  |= 0x00000700 ;  
	GPIO_PORTF_DEN_R 	 |= 0x00000008 ;
	// Enable the clock for Timer 1
	GPTM_CONTROL_R &= ~( TIM_A_ENABLE ); // disable timer 1 A
	// Timer1 A configured as 16- bit timer
	GPTM_CONFIG_R |= TIM_16_BIT_CONFIG ;
	// Timer1 A in periodic timer , edge count and PWM mode
	GPTM_TA_MODE_R |= TIM_PWM_MODE ;
	GPTM_TA_MODE_R &= ~( TIM_CAPTURE_MODE );
	// Make PWM frequency 1 kHz using reload value of 16000
	GPTM_TA_IL_R = TIM_A_INTERVAL ;
	// Configure PWM duty cycle value ( should be less than 16000)
	GPTM_TA_MATCH_R = TIM_A_MATCH ;
	// Enable timer1 A
	GPTM_CONTROL_R |= TIM_A_ENABLE ; 
}

void Timer2A_Init ( void )
{
	// Enable the clock for port F and Timer1
	SYS_RCGC_GPIO_CLK_R |= CLOCK_ENABLE;
	RCGC_TIMER_R |= 0x02;
	
	// Configure PortF pin 2 as Timer1 A output
	GPIO_PORTF_AFSEL_R |= 0x00000004 ;
	GPIO_PORTF_PCTL_R  |= 0x00000700 ;  
	GPIO_PORTF_DEN_R 	 |= 0x00000004 ;
	// Enable the clock for Timer 1
	GPTM_CONTROL_R2 &= ~( TIM_A_ENABLE ); // disable timer 1 A
	// Timer1 A configured as 16- bit timer
	GPTM_CONFIG_R2 |= TIM_16_BIT_CONFIG ;
	// Timer1 A in periodic timer , edge count and PWM mode
	GPTM_TA_MODE_R2 |= TIM_PWM_MODE ;
	GPTM_TA_MODE_R2 &= ~( TIM_CAPTURE_MODE );
	// Make PWM frequency 1 kHz using reload value of 16000
	GPTM_TA_IL_R2 = TIM_A_INTERVAL ;
	// Configure PWM duty cycle value ( should be less than 16000)
	GPTM_TA_MATCH_R2 = TIM_A_MATCH ;
	// Enable timer1 A
	GPTM_CONTROL_R2 |= TIM_A_ENABLE ; 
}

int main ( void )
{
	
	while (1) 
	{
		Timer1A_Init (); // Initialize the timer
	 // Timer2A_Init (); // Initialize the timer
	}
}
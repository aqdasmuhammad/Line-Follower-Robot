#define TM_BASE			0x40031000


#define SYS_RCGC_GPIO_CLK_R 			*((volatile unsigned long*)0x400FE108)
#define RCGC_TIMER_R 				      *((volatile unsigned long*)0x400FE604)

#define GPTM_CONFIG_R 						*( volatile long *)( TM_BASE + 0x000 )
#define GPTM_CONTROL_R					  *( volatile long *)( TM_BASE + 0x00C )

#define GPTM_TA_MODE_R 						*( volatile long *)( TM_BASE + 0x004 )
#define GPTM_TA_IL_R 							*( volatile long *)( TM_BASE + 0x028 )
#define GPTM_TA_MATCH_R 					*( volatile long *)( TM_BASE + 0x030 )

#define GPTM_TA_MODE_R2 					*( volatile long *)( TM_BASE + 0x008 )
#define GPTM_TA_IL_R2							*( volatile long *)( TM_BASE + 0x02C )
#define GPTM_TA_MATCH_R2		  		*( volatile long *)( TM_BASE + 0x034 )

#define GPIO_PORTA_DATA_R 				*((volatile unsigned long*)0x4000407C)
#define GPIO_PORTF_DATA_R 				*((volatile unsigned long*)0x40025030)
#define GPIO_PORTA_DIR_R 					*((volatile unsigned long*)0x40004400)
#define GPIO_PORTF_DIR_R 					*((volatile unsigned long*)0x40025400)
#define GPIO_PORTA_DEN_R 					*((volatile unsigned long*)0x4000451C)
#define GPIO_PORTF_DEN_R 					*((volatile unsigned long*)0x4002551C)
#define GPIO_PORTF_AFSEL_R 				*((volatile unsigned long*)0x40025420)
#define GPIO_PORTF_PCTL_R 				*((volatile unsigned long*)0x4002552C)

#define CLOCK_ENABLE 							0x21
#define PORTA_PIN									0x1F
#define	PORTF_PIN									0x0C

#define SYS_CLOCK_FREQUENCY 			16000000
#define TIM_16_BIT_CONFIG 				0x00000004 // 16- bit 
#define TIM_PERIODIC_MODE 				0x00000002 // Periodic 
#define TIM_A_ENABLE 							0x00000101 // Timer 
#define TIM_PWM_MODE 							0x0000000A // Timer 
#define TIM_CAPTURE_MODE 					0x00000004 // Timer
#define TIM_A_INTERVAL 						16000 // 1k
#define TIM_A_MATCH 							8000 // 50% Duty Cycle

void Timer1_Init ( void )
{
	// Enable the clock for port F and Timer1
	SYS_RCGC_GPIO_CLK_R 	|=	 CLOCK_ENABLE;
	RCGC_TIMER_R 					|= 	 0x02;
	
	
	// Configure PortF pin 2 as Timer1 A output
	GPIO_PORTF_AFSEL_R 		|=   0x0000000C ;
	GPIO_PORTF_PCTL_R     |=   0x00007700 ;  
	GPIO_PORTF_DEN_R 	    |=   0x0000000C ;
	
	
	// Enable the clock for Timer 1
	GPTM_CONTROL_R 				&=   ~( TIM_A_ENABLE ); // disable timer 1
	// Timer1 configured as 16- bit timer
	GPTM_CONFIG_R 				|=   TIM_16_BIT_CONFIG ;
	
	
	// TIMER 1-A: BLUE
	// Timer1 A in periodic timer , edge count and PWM mode
	GPTM_TA_MODE_R 				|=   TIM_PWM_MODE ;
	GPTM_TA_MODE_R        &=   ~( TIM_CAPTURE_MODE );
	// Make PWM frequency 1 kHz using reload value of 16000 for TIMER 1-A
	GPTM_TA_IL_R          =    TIM_A_INTERVAL ;
	// Configure PWM duty cycle value ( should be less than 16000) for TIMER 1-A
	GPTM_TA_MATCH_R 			=    TIM_A_MATCH ;
	
	
	// TIMER 1-B: GREEN
	// Timer1 B in periodic timer , edge count and PWM mode
	GPTM_TA_MODE_R2 			|=   TIM_PWM_MODE ;
	GPTM_TA_MODE_R2			  &=   ~( TIM_CAPTURE_MODE );
	// Make PWM frequency 1 kHz using reload value of 16000 for B
	GPTM_TA_IL_R2 				=    TIM_A_INTERVAL ;
	// Configure PWM duty cycle value ( should be less than 16000) for B
	GPTM_TA_MATCH_R2 			=    TIM_A_MATCH ;
	
	
	// Enable timer1
	GPTM_CONTROL_R |= TIM_A_ENABLE ; 
}


int main ( void )
{
	
	while (1) 
	{
		Timer1_Init (); // Initialize the timer
	}
}

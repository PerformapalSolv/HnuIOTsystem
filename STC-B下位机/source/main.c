#include "STC15F2K60S2.H"
#include "sys.H"
#include "displayer.H"
#include "beep.h"
#include "adc.h"
#include "hall.h"
#include "vib.h"
#include "key.h"
#include "uart1.h"
code unsigned long SysClock=11059200;
 
#ifdef _displayer_H_ 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01,0x76,0x38};   
	             /* ??:   0    1    2    3    4    5    6    7    8    9    10     11	 12   13   14   15  */
                 /* ??:   0    1    2    3    4    5    6    7    8    9    (?)   ?-  ?-  ?-   H    L  */ 
 

unsigned char pos[4];
unsigned char mat[2]={0xaa,0x55};
unsigned char msg[6]={0xa5};
unsigned char key1[1]={0x01};
unsigned int light_intensity;
unsigned int light_sum;
char gewei;
char shiwei;
char baiwei;

unsigned char key3[2]={0x03,0x33};
unsigned char keyup[1]={0x04};
unsigned char keydown[1]={0x05};
unsigned char keycenter[1]={0x06};
void myHall_callback()
{ 
	if( GetHallAct() == enumHallGetClose) 
		{	
			SetBeep(1000,20);
			msg[4]=0x01;
		}else{
			msg[4]=0x00;
		}
	
}

void myVib_callback()
{ 
	if(GetVibAct()==enumVibQuake){
		msg[5]=0x01;
	}
}
/*void myKN_callback(){
		if(GetAdcNavAct(enumAdcNavKeyUp)== enumKeyPress||GetAdcNavAct(enumAdcNavKeyLeft)  == enumKeyPress)
			Uart1Print(&keyup,1);
	if(GetAdcNavAct(enumAdcNavKeyDown)== enumKeyPress||GetAdcNavAct(enumAdcNavKeyRight) == enumKeyPress)
			Uart1Print(&keydown,1);
	if(GetAdcNavAct(enumAdcNavKeyCenter)== enumKeyPress)		
	{
		Uart1Print(&keycenter,1);
	}
	if(GetAdcNavAct(enumAdcNavKey3) == enumKeyPress){
		 Uart1Print(&key3,2);
	}
}*/
void myKN_callback(){
	SetBeep(1000,10);
	if(GetAdcNavAct(enumAdcNavKeyCenter)== enumKeyPress)		
	{
		msg[5]=0x00;
	}
}
void Per100ms_displayer(){
	light_sum+=GetADC().Rop;
	gewei = (GetADC().Rop % 10);
  shiwei = (GetADC().Rop/ 10) % 10;
  baiwei = (GetADC().Rop / 100) % 10;
	if(GetADC().Rop>100){
		Seg7Print(msg[5],10,10,10,10,baiwei,shiwei,gewei);
	}
	else{
		Seg7Print(msg[5],10,10,10,10,10,shiwei,gewei);
	}
	if(msg[5])SetBeep(1000,50);
}

void do_1S(){
	light_intensity=light_sum/10;
	light_sum=0;
	msg[1]=(light_intensity/ 100) % 10;
	msg[2]=(light_intensity / 10) % 10;
	msg[3]=light_intensity % 10;
	Uart1Print(&msg,6);
}
int main(){
	DisplayerInit(); 
	SetDisplayerArea(0,7);
	Seg7Print(msg[5],10,10,10,10,10,10,10);
	LedPrint(0);
	BeepInit();
	AdcInit(ADCexpEXT);
	HallInit();
	VibInit();
	Uart1Init(1200); 
	SetUart1Rxd(pos,4,mat, 2);
	
	
	SetEventCallBack(enumEventNav, myKN_callback);
	SetEventCallBack(enumEventSys100mS, Per100ms_displayer);
	SetEventCallBack(enumEventSys1S, do_1S);
	SetEventCallBack(enumEventHall, myHall_callback);
	SetEventCallBack(enumEventVib , myVib_callback);
  MySTC_Init();
  while(1){
     MySTC_OS();
	}		
}
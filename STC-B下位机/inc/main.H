#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "key.h"
#include "adc.h"
#include "uart1.h"
#include "displayer.H" 
#include "DS1302.h"
#include "beep.h"

//必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致
code unsigned long SysClock=11059200;  
#ifdef _displayer_H_                          //??????????(????????,?????????) 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ??:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ??:   0   1    2    3    4     5    6    7   8    9    A     B    C    D     E      F           */ 
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80,  
             /* ????     0         1         2         3         4         5         6         7         8         9        */
													0x3F,0x37,0x71 };
												// o     n    f
#endif
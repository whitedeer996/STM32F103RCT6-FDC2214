#ifndef __FDC2214_H
#define __FDC2214_H

#include <sys.h>

#define FDC_Address_W (0x54)
#define FDC_Address_R  (0x55)			


extern u32 C_CHO_data_final;
			
void FDC_write_reg(u8 addr,u16 value);  
void FDC_Start(void);
u16 FDC_read_reg(u8 addr);
u8 FDC_read_reg_high(u8 addr);
u8 FDC_read_reg_low(u8 addr);

int FDC_CNum_To_PaperNum(u32 CNum);
 
#endif

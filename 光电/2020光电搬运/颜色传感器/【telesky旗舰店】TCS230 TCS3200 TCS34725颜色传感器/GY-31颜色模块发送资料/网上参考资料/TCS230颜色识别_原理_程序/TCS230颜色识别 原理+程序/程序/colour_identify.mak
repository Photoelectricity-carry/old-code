CC = iccavr
CFLAGS =  -IC:\icc\include\ -e -DATMEGA -DATMega128  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\icc\lib\ -g -ucrtatmega.o -bfunc_lit:0x8c.0x20000 -dram_end:0x10ff -bdata:0x100.0x10ff -dhwstk_size:16 -beeprom:1.4096 -fihx_coff -S2
FILES = colour_identify.o 

colour_identify:	$(FILES)
	$(CC) -o colour_identify $(LFLAGS) @colour_identify.lk   -lcatmega
colour_identify.o: C:/icc/include/iom128v.h C:/icc/include/macros.h C:\DOCUME~1\Administrator\桌面\程序/12864.h C:/icc/include/iom128v.h C:/icc/include/macros.h C:/icc/include/BIT.h C:/icc/include/RD_UseBITs.h C:/icc/include/RD_MacroAndConst.h\
 C:/icc/include/macros.h
colour_identify.o:	C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c
	$(CC) -c $(CFLAGS) C:\DOCUME~1\Administrator\桌面\程序\colour_identify.c

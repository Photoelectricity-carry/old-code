NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   008C   0072 =    114. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       008C  __idata_start
       00FE  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00FE   07D4 =   2004. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       007F  __text_start
       007F  __start
       009F  _exit
       00A0  _delay_us
       00B4  _delay_ms
       00C8  _Sendbyte
       00EC  _Receivebyte
       0120  _Checkbusy
       0126  _Writecommand
       013D  _Writedata
       0154  _Locate_x_y
       017E  _Display_x_y_symbol
       0191  _Write_string
       01A1  _Display_x_y_data
       01D7  _LcmClearTXT
       01E7  _Init_12864
       01F5  _int2_init
       01FB  _timer1_init
       0202  _port_init
       0206  _main
       0238  _interrupt_int2
       024A  _interrupt_timer1
       03FA  mod16u
       03FC  div16u
       03FD  xdiv16u
       0416  pop_gset2
       0419  pop_gset3
       041C  push_gset5
       041E  push_gset4
       0420  push_gset3
       0422  push_gset2
       0424  push_gset1
       0427  pop_gset1
       0428  pop
       043B  push_lset
       0452  pop_lset
       0469  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100   0072 =    114. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  _AC_TABLE
       0100  __data_start
       0120  _red
       0121  _blue
       0122  _green
       0123  _flag
       0124  _i
       0125  _j
       0126  _data
       012B  _counter
       0172  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   003C =     60. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\icc\lib\crtatmega.o	[ crtatmega.s ]
colour_identify.o	[ colour_identify.c ]
<library>	[ div16u.s, gpop2.s, gpop3.s, gpush.s, lpush.s ]

User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x8c
data = 0x100
eeprom:1.4096


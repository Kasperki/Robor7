Project:      output/RobottiProjekti
Build Number: 0
Date:         Fri Feb 14 15:29:42 2014
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0150   006E =    110. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0150  _LEFTFOW
       0152  _LEFTBACK
       0154  _RIGHTFOW
       0156  _RIGHTBACK
       0158  LoadConfigTBL_robottiprojekti_Bank0
       018F  LoadConfigTBL_robottiprojekti_Bank1
       01BE  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   01BE   012C =    300. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       01BE  LoadConfigTBL_robottiprojekti_Ordered
       0283  _LoadConfigInit
       0283  LoadConfigInit
       0293  _LoadConfig_robottiprojekti
       0293  LoadConfig_robottiprojekti
       02EA  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   02EA   033C =    828. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       02EA  _PWM8_VASEN_ISR
       02EB  _PWM8_VASEN_EnableInt
       02EB  PWM8_VASEN_EnableInt
       02EF  _PWM8_VASEN_DisableInt
       02EF  PWM8_VASEN_DisableInt
       02F3  PWM8_VASEN_Start
       02F3  _PWM8_VASEN_Start
       02F7  _PWM8_VASEN_Stop
       02F7  PWM8_VASEN_Stop
       02FB  _PWM8_VASEN_WritePeriod
       02FB  PWM8_VASEN_WritePeriod
       02FE  _PWM8_VASEN_WritePulseWidth
       02FE  PWM8_VASEN_WritePulseWidth
       0301  bPWM8_VASEN_ReadPulseWidth
       0301  PWM8_VASEN_bReadPulseWidth
       0301  _bPWM8_VASEN_ReadPulseWidth
       0301  _PWM8_VASEN_bReadPulseWidth
       0304  _PWM8_VASEN_bReadCounter
       0304  _bPWM8_VASEN_ReadCounter
       0304  bPWM8_VASEN_ReadCounter
       0304  PWM8_VASEN_bReadCounter
       032D  _PWM8_OIKEA_ISR
       032E  _PWM8_OIKEA_EnableInt
       032E  PWM8_OIKEA_EnableInt
       0332  _PWM8_OIKEA_DisableInt
       0332  PWM8_OIKEA_DisableInt
       0336  PWM8_OIKEA_Start
       0336  _PWM8_OIKEA_Start
       033A  PWM8_OIKEA_Stop
       033A  _PWM8_OIKEA_Stop
       033E  _PWM8_OIKEA_WritePeriod
       033E  PWM8_OIKEA_WritePeriod
       0341  _PWM8_OIKEA_WritePulseWidth
       0341  PWM8_OIKEA_WritePulseWidth
       0344  bPWM8_OIKEA_ReadPulseWidth
       0344  _bPWM8_OIKEA_ReadPulseWidth
       0344  PWM8_OIKEA_bReadPulseWidth
       0344  _PWM8_OIKEA_bReadPulseWidth
       0347  PWM8_OIKEA_bReadCounter
       0347  _PWM8_OIKEA_bReadCounter
       0347  _bPWM8_OIKEA_ReadCounter
       0347  bPWM8_OIKEA_ReadCounter
       0370  _LCD_PrCString
       0370  LCD_PrCString
       0382  LCD_HEX_STR
       0392  LCD_PrHexByte
       0392  _LCD_PrHexByte
       03A5  LCD_PrHexInt
       03A5  _LCD_PrHexInt
       03AC  LCD_PrString
       03AC  _LCD_PrString
       03B6  _LCD_Write_Data
       03B6  LCD_Write_Data
       03B6  LCD_WriteData
       03B6  _LCD_WriteData
       03CA  _LCD_Control
       03CA  LCD_Control
       0471  LCD_Init
       0471  LCD_Start
       0471  _LCD_Start
       0471  _LCD_Init
       04DD  LCD_ROW_OFFSET
       04E1  LCD_Position
       04E1  _LCD_Position
       04ED  LCD_Delay50uTimes
       04ED  _LCD_Delay50uTimes
       04F3  LCD_Delay50u_Table
       04FB  LCD_Delay50u
       04FB  _LCD_Delay50u
       050F  LCD_DrawBG
       0535  _LCD_DrawBG
       055E  LCD_DrawVBG
       058B  _LCD_DrawVBG
       05BB  LCD_InitVBG
       05BB  _LCD_InitVBG
       05E8  LCD_BG_TYPE1
       05EF  LCD_BG_TYPE2
       05F6  LCD_InitBG
       05F6  _LCD_InitBG
       0626  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0626   042D =   1069. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0626  _main
       0626  __text_start
       06F5  _InitPWM
       0756  _MoveForward
       07BE  _MoveBackward
       0826  _Stop
       0833  _TurnLeft
       0869  _TurnRight
       08D6  _itoa
       0A53  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0000   0006 =      6. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __rZ
       0001  __rY
       0002  __rX
       0003  __r3
       0004  __r1
       0005  __r0
       0006  __virtual_registers_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0006   0003 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0006  _Port_2_Data_SHADE
       0006  _NO_SHADOW
       0006  Port_2_Data_SHADE
       0006  NO_SHADOW
       0007  Port_2_DriveMode_0_SHADE
       0007  _Port_2_DriveMode_0_SHADE
       0008  _Port_2_DriveMode_1_SHADE
       0008  Port_2_DriveMode_1_SHADE
       0009  __ramareas_end
       0009  __InterruptRAM_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   00D7 =    215. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       00D4  _bGetPowerSetting
       00D4  bGetPowerSetting

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
obj/motorcontrol.o	[ motorcontrol.c ]
<library>	[ pwm8_vasenint.asm, pwm8_vasen.asm, pwm8_oikeaint.asm, pwm8_oikea.asm, psocconfigtbl.asm, psocconfig.asm ]
[ lcd.asm, rZ.asm, rY.asm, rX.asm, r3.asm, r1.asm, r0.asm, divmodu_16x16_16_util.asm, i_div16_block_util.asm ]
[ itoa.s ]

Area Definitions

-blit:0x150.0x3fff
-bdata:0.0xff
-rwh:SSCParmBlk:0xf7.0xff


# MCU name
MCU = WB32F3G71

# Bootloader selection
# BOOTLOADER = stm32duino

MCU_LDSCRIPT = WB32F3G71x9
BOOTLOADER = custom

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

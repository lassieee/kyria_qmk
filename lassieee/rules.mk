CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
MOUSEKEY_ENABLE = no   # Mouse keys
OLED_ENABLE = yes      # Enables the use of OLED displays
OLED_DRIVER = ssd1306  # Use specific OLED driver
ENCODER_ENABLE = no    # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes  # Enables keyboard RGB underglow
TAP_DANCE_ENABLE = yes # Enables TapDance
BOOTMAGIC_ENABLE = no  # Enables Bootmagic Lite
SPLIT_KEYBOARD = yes   # Enables split-keyboard mode
LTO_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled_utils.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += encoder_utils.c
endif

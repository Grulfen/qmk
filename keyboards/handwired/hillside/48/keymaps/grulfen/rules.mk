OLED_ENABLE = no
OLED_DRIVER = SSD1306      # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enable the use of one or more encoders
RGBLIGHT_ENABLE = no       # Disable keyboard RGB underglow

COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

SRC += features/casemodes.c
SRC += features/oneshot.c
SRC += features/swapper.c

# Compiler and Flags
COMMON_OBJECTS = main.o
CPU = msp430g2553
CC = msp430-elf-gcc

#CFLAGS = -mmcu=msp430g2553 -Wall -I../timerLib  # Include timerLib headers
CFLAGS = -mmcu=${CPU} -I../H -Wall -I../timerLib
#CC = msp430-elf-gcc
AS = msp430-elf-as

# Paths

TIMERLIB = ../timerLib

# LDFLAGS = -L$(TIMERLIB) -lTimer  # Link with timerLib
#LDSCRIPT = /opt/ti/msp430_gcc/include/msp430g2553.ld  # uPDATE THIS PATH IF NECESSARY
LDFLAGS = -L$(TIMERLIB) -L/opt/ti/msp430_gcc/include -T/opt/ti/msp430_gcc/include/msp430g2553.ld





# Source Files

SRC = main.c toggle_buzzer_state.s $(TIMERLIB)/libTimer.a

OBJ = $(SRC:.c=.o)

TARGET = led_toggle.elf



# Default rule: Compile and link

all: $(TARGET)



$(TARGET): $(SRC)

	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)



# Flash the program onto the MSP430

load: $(TARGET)

	msp430loader.sh $(TARGET)



# Clean compiled files

clean:

	rm -f $(TARGET) $(OBJ)


# Makefile for the LibreEMS host-based tests

CC = gcc
CCFLAGS = -g 
LDFLAGS = -lcmocka -g0
TARGET = LibreTests
INSTALL_PREFIX = $(PREFIX)

SRCS = cmockaTests.c \
       ../main/printf.c \
       ../main/debugging.c \
       ../main/commsCore.c \
       ../main/commsISRs.c \
       ../main/init.c \
       ../main/flashWrite.c \
       ../main/plotOutputs.c \
       ../main/dataAcquisition.c \
       floatingPointCalcs.c \
       ../main/dataCalculation.c \
       ../main/globals.c \
       ../main/globalConstants.c \
       ../main/utils.c \
       ../main/libreMath.c \
       ../main/tableLookup.c \
       ../main/blockDetailsLookup.c \
       ../main/Config.c \
       ../main/GPIO.c \
       emulatedRegisters.c \
       ../main/commsUtils.c \
       ../main/tableDescriptors.c \
       ../main/derivedVarsDescriptor.c \
       ../main/fieldDescriptor.c \
       ../main/keyUserVarsDescriptor.c \
       ../main/coreVarsDescriptor.c \
       ../main/decoderStatsDescriptor.c \
       ../main/dataLookup.c \
       ../main/mathFunctions.c \
       ../main/engineAngleDecoders/Crank8x_Cam1x.c

all : ${TARGET}

${TARGET}: $(SRCS)
	$(CC) $(CFLAGS) -o ${TARGET} $(SRCS) $(LDFLAGS) -D FIRMWARE_BUILD_DATE="NOT_DEFINED" -D PRELIM_CONFIG="UNIT_TESTS" -D FIRMWARE_VERSION="UNIT_TEST_BUILD" -D HOST_TESTS=1 -D CONFIG=SEANKR1_ID \
    -D BASE_FILE_NAME=\"CMOCKA\"

clean:
	rm -f *.o ${TARGET}

install: ${TARGET}
	@echo "Nothing to install"
    
.PHONY: install

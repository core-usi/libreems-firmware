# Top level convenience make file

# Detect windows, set variables to handle platform differences
ifdef ComSpec
VAR_SET = SET
SPECIAL_QUOTE = "
PATHSEP = \\
DESCEND = cd src$(PATHSEP)main
else
VAR_SET = export
SPECIAL_QUOTE = '
PATHSEP = /
DESCEND = cd src$(PATHSEP)main
endif


Help:
	@echo
	@echo "######################## Welcome to LibreEMS! ########################"
	@echo
	@echo "To build, choose a target from the below list and type 'make target'!"
	@echo "For example, to build blank unconfigured firmware type 'make BLANK'"
	@echo "Note: For BenchTest to work you MUST build using the BENCHTEST target!"
	@echo "Advanced users can find more options available in the src/main directory!"
	@echo
	@echo "Options:"
	@echo
	@make -qp | awk -F':' $(SPECIAL_QUOTE)/^[a-zA-Z0-9][^$$#\/\t=]*:([^=]|$$)/ {split($$1,A,/ /);for(i in A)print A[i]}$(SPECIAL_QUOTE)

TEST_AND_SAVE_ALL:
	$(DESCEND) && ..$(PATHSEP)..$(PATHSEP)bin$(PATHSEP)testclibuilds.bash

BLANK:
	$(DESCEND) && make clean s19

SPECIAL: # Can use a dependency here instead. 
	$(DESCEND) && make clean EvenTeeth-Distributor-4of6and1

# Other special builds
BENCHTEST: 
	$(VAR_SET) CLIFLAGS="DEFAULT" CFLAGS="-DBENCHTEST=1" && $(DESCEND) && make clean BenchTest 
DEFAULT: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean DEFAULT
TRUCK: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean MitsiAndMazda-CAS-4and1
HOTEL: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean HallOrOptical-Distributor-4of69
PRESTO: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean EvenTeeth-Cam-24and1
SEANKLT1: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean GM-LT1-CAS
SEANKR1: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean SEANKR1
SEANKHAYABUSA: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean SEANKHAYABUSA
MAZDAVVT: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean MAZDAVVT
FORD4600: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean FORD4600-32V
FORDV10: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean FORDV10
SBC383MALCOM: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean SBC383MALCOM
SNOTROCKET: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean EvenTeeth-Cam-24and1
SPUDMN: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean MissingTeeth-Crank-8minus1
SLATER: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean MissingTeeth-Crank-12minus1
PETERJSERIES: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean JSeries-12CrankWith6-2Cam
DEUCECOUPE: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean EvenTeeth-Cam-6and1
DEUCES10: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean EvenTeeth-Cam-4and1
PETERTRUCK: 
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean MissingTeeth-Cam-12minus1
JUSTINMIATA:
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean Cam12x-1-12x-1_Cam1x
MITSU4G63:
	$(VAR_SET) CLIFLAGS="$@" && $(DESCEND) && make clean MITSU4G63

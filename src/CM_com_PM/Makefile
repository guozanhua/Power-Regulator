CC=gcc
CFLAGS+= -L . -lnetlayer
OBJECTS=PM_test.o CM_test.o CMPM_cm_agent.o CMPM_pm_agent.o
OBJECTS_CM=CM_test.o CMPM_cm_agent.o
OBJECTS_PM=PM_test.o CMPM_pm_agent.o
BIN=PM_test CM_test

$(BIN):$(OBJECTS)
	$(CC) $(OBJECTS_CM) $(CFLAGS) -o CM_test
	$(CC) $(OBJECTS_PM) $(CFLAGS) -o PM_test
PM_test.o:PM_test.c CMPM_pm_agent.h NetLayer.h
	$(CC) -c PM_test.c
CMPM_pm_agent.o:CMPM_pm_agent.c CMPM_pm_agent.h NetLayer.h
	$(CC) -c CMPM_pm_agent.c
CM_test.o:CM_test.c CMPM_cm_agent.h NetLayer.h
	$(CC) -c CM_test.c 
CMPM_cm_agent.o:CMPM_cm_agent.c CMPM_cm_agent.h NetLayer.h
	$(CC) -c CMPM_cm_agent.c
clean:
	rm $(BIN) $(OBJECTS)

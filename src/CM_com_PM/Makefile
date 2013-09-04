CC=gcc
CFLAGS+= -L . -lnetlayer
OBJECTS=PM_test.o CM_test.o CM_server.o PM_client.o
OBJECTS_CM=CM_test.o CM_server.o
OBJECTS_PM=PM_test.o PM_client.o
BIN=PM_test CM_test

$(BIN):$(OBJECTS)
	$(CC) $(OBJECTS_CM) $(CFLAGS) -o CM_test
	$(CC) $(OBJECTS_PM) $(CFLAGS) -o PM_test
PM_test.o:PM_test.c PM_client.h NetLayer.h
	$(CC) -c PM_test.c
PM_client.o:PM_client.c PM_client.h NetLayer.h
	$(CC) -c PM_client.c
CM_test.o:CM_test.c CM_server.h NetLayer.h
	$(CC) -c CM_test.c 
CM_server.o:CM_server.c CM_server.h NetLayer.h
	$(CC) -c CM_server.c
clean:
	rm $(COMMAND) $(OBJECTS)

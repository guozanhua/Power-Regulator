CC=gcc
CFLAGS+=
OBJECTS=test_client.o test_server.o NetLayer_Client.o NetLayer_Server.o NetLayer_General.o
OBJECTS_CLIENT=test_client.o NetLayer_Client.o NetLayer_General.o
OBJECTS_SERVER=test_server.o NetLayer_Server.o NetLayer_General.o
COMMAND=test_client test_server

$(COMMAND):$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS_CLIENT) -o test_client
	$(CC) $(CFLAGS) $(OBJECTS_SERVER) -o test_server
test_client.o : test_client.c NetLayer.h
	$(CC) $(CFLAGS) -c test_client.c
test_server.o : test_server.c NetLayer.h
	$(CC) $(CFLAGS) -c test_server.c
NetLayer_Client.o : NetLayer.h NetLayer_Client.c
	$(CC) $(CFLAGS) -c NetLayer_Client.c
NetLayer_Server.o : NetLayer.h NetLayer_Server.c
	$(CC) $(CFLAGS) -c NetLayer_Server.c
NetLayer_General.o : NetLayer.h NetLayer_General.c
	$(CC) $(CFLAGS) -c NetLayer_General.c

clean:
	rm $(OBJECTS) $(COMMAND)

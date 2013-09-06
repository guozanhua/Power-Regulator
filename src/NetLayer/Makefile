CC=gcc
CFLAGS+=
OBJECTS=NetLayer_Client.o NetLayer_Server.o NetLayer_General.o
LIB=libnetlayer.a

$(LIB):$(OBJECTS)
	ar -r $(LIB) $(OBJECTS)
	cp NetLayer.h ../CM_com_PM/
	cp $(LIB)     ../CM_com_PM/
	cp NetLayer.h ../PM_com_VM/
	cp $(LIB)     ../PM_com_VM/
NetLayer_Client.o : NetLayer.h NetLayer_Client.c
	$(CC) $(CFLAGS) -c NetLayer_Client.c
NetLayer_Server.o : NetLayer.h NetLayer_Server.c
	$(CC) $(CFLAGS) -c NetLayer_Server.c
NetLayer_General.o : NetLayer.h NetLayer_General.c
	$(CC) $(CFLAGS) -c NetLayer_General.c

clean:
	rm $(OBJECTS) $(LIB)
	rm ../CM_com_PM/NetLayer.h
	rm ../CM_com_PM/$(LIB)
	rm ../PM_com_VM/NetLayer.h
	rm ../PM_com_VM/$(LIB)

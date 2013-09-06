CC=gcc
CFLAGS+= -L . -lnetlayer
BIN= PM_test VM_test
OBJECTS=PM_test.o VM_test.o PMVM_pm_agent.o PMVM_vm_agent.o
OBJECTS_PM= PM_test.o PMVM_pm_agent.o
OBJECTS_VM= VM_test.o PMVM_vm_agent.o

$(BIN):$(OBJECTS)
	$(CC) $(OBJECTS_PM) $(CFLAGS) -o PM_test
	$(CC) $(OBJECTS_VM) $(CFLAGS) -o VM_test
PM_test.o: PM_test.c PMVM_pm_agent.h
	$(CC) -c PM_test.c
VM_test.o: VM_test.c PMVM_vm_agent.h
	$(CC) -c VM_test.c
PMVM_pm_agent.o: PMVM_pm_agent.c PMVM_pm_agent.h PMVM_share.h NetLayer.h
	$(CC) -c PMVM_pm_agent.c
PMVM_vm_agent.o: PMVM_vm_agent.c PMVM_vm_agent.h PMVM_share.h NetLayer.h
	$(CC) -c PMVM_vm_agent.c
clean:
	rm $(OBJECTS) $(BIN)
	

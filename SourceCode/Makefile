TARGET:=Manager
OBJS:=main.o FullTime.o Building.o DormArea.o Manager.o Date.o

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$*.o:$%.c
	$(CXX) -c $^ -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)

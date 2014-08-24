TARGET=signal-games

$(TARGET):
	g++ -I. -o $(TARGET) $(TARGET).cpp
clean:
	rm -f $(TARGET)

start: $(TARGET)
	./$(TARGET) &
kill:
	killall -15 $(TARGET)

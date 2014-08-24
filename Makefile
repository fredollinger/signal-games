TARGET=signal-games

all: clean $(TARGET)

$(TARGET):
	g++ -I. -o $(TARGET) $(TARGET).cpp
clean:
	rm -f $(TARGET)

start: $(TARGET)
	./$(TARGET) &
kill:
	rm -rf /tmp/log
	killall -15 $(TARGET)
signal:
	./send-usr2-signal.sh
edit:
	vim handle-signal-close-log.h signal-games.cpp 

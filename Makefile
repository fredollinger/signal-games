TARGET=signal-games
CXX=g++
WARN= -Werror -pedantic -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

all: clean $(TARGET)

$(TARGET):
	$(CXX) $(WARN) -I. -o $(TARGET) $(TARGET).cpp
clean:
	rm -f $(TARGET)

start: $(TARGET)
	./$(TARGET) &
kill:
	rm -rf /tmp/log
	killall -15 $(TARGET)

stop: kill

signal:
	./send-usr2-signal.sh
edit:
	vim handle-signal-close-log.h signal-games.cpp 

TARGET = pcap-test

all: $(TARGET)

$(TARGET): main.o utils.o
	g++ -o pcap-test main.o utils.o -lpcap

main.o: pcap-test.c utils.h structure.h
	g++ -c pcap-test.c -o main.o

utils.o: utils.c structure.h utils.h
	g++ -c utils.c -o utils.o

clean:
	rm -f $(TARGET)
	rm -f *.o
#./avrgcc/bin/avr-gcc.exe -c -mmcu=atmega328p pitches.h
#./avrgcc/bin/avr-gcc.exe -c -mmcu=atmega328p stylophone.c
#./avrgcc/bin/avr-gcc.exe -mmcu=atmega328p stylophone.o pitches.o
#./avrgcc/bin/avr-objcopy.exe -O ihex -j .text -j .text a.out a.hex
#./avrdude-v7.1-windows-x64/avrdude.exe -C avrdude-v7.1-windows-x64/avrdude.conf -v -p atmega328p -c stk500v1 -P COM6 -b 19200 -U lfuse:w:0xF2:m

stylophone: StylophoneSolderingWorkshop.ino.hex
	./avrdude-v7.1-windows-x64/avrdude.exe -C avrdude-v7.1-windows-x64/avrdude.conf -v -p atmega328p -c stk500v1 -P COM6 -b 19200 -U flash:w:StylophoneSolderingWorkshop.ino.hex:i

clean:
	#del a.hex
	#del a.out
	#del simonSays.o
	#del random.o
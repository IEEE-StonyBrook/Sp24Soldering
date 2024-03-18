stylophone: StylophoneSolderingWorkshop.ino.hex
	./avrdude-v7.1-windows-x64/avrdude.exe -C avrdude-v7.1-windows-x64/avrdude.conf -p atmega328 -c stk500v1 -P COM6 -b 19200 -U lfuse:w:0xFF:m
	./avrdude-v7.1-windows-x64/avrdude.exe -C avrdude-v7.1-windows-x64/avrdude.conf -v -p atmega328 -c stk500v1 -P COM6 -b 19200 -U flash:w:StylophoneSolderingWorkshop.ino.hex:i

clean:

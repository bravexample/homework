all:
	gcc -o hw0401 hw0401.c
	gcc -o hw0402 hw0402.c
	gcc -o hw0403 hw0403.c
	gcc -o hw0404 hw0404.c
	gcc -o hw0405 hw0405.c -lcurl -lxml2 -I/usr/include/libxml2
	gcc -o hw0406 hw0406.c

clean:
	rm -rf hw0401 hw0402 hw0403 hw0404 hw0405 hw0406

first:
	./hw0401 -t 2447

second:
	./hw0402

third:
	./hw0403

fourth:
	./hw0404

fifth:
	./hw0405 -s 2357.TW -i date.json -o price.json

six:
	./hw0406
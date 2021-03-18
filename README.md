# Projekt 2 - Arytmetyka liczb zespolonych

##Budowanie programu
Projekt zawiera pliki cmake które generują odpowiednie foldery i pliki Makefile.

Aby zbudować projekt należy wpisać w terminal:	

	$ mkdir build && cd build
	
	$ cmake ..

Wygeneruje to nam 2 pliki Makefile:

* build/Makefile: tworzący program complex_run
* build/tst/Makefile: tworzący program complex_tst

### complex_run
Program należy odpalić z flagą (latwy | trudny) aby skorzystać z przygotowanych plików sprawdzających.\
Na przykład:
	
	./complex_run latwy


### complex_tst
Program zawiera 14 testów dla klas complex, testujący wszystkie metody klasy oraz ich przypadki graniczne.

	./complex_tst

Po którym odpaleniu ma pokazać poprawność 14 testów i ogólną oceną:

	[ PASSED ] 14 tests.


## Uwagi


### Klasa complex
Została napisana jako szablon klasy co wymusza przetrzymywanie definicji i deklaracji w jednym pliku.

#### round_complex
Są to dwie przeciążone metody statyczne służące do zaokrąglania liczb prostych oraz liczb zespolonych do 4 miejsc po przecinku.

#### istream & ostream
Strumienie obsługują wyjątkowe przypadki takie jak:

* gdy real = 0 i imag = 0 (przykład: (0))
* gdy real = 0 (przykład: (4i))
* gdy real = 0 i imag = 1 (przykład: (i))
* gdy real = 0 i imag = -1 (przykład: (-i))
* gdy real != 0 i imag = 0 (przykład: (2))
* gdy real = 0 i imag != {-1, 0, 1} (przykład: (-3.123i))
* przypadek standardowy (przykład: (-123.123 + 321.321i))

### Klasa database
Klasa automatycznie otwiera i czyta wyrażenia urojone z plików.\
Klasa przy wczytywaniu sprawdza poprawność wyrażeń i razie błędu wypisuje błąd na 'stderr'.

## Struktura repozytorium

&nbsp;&nbsp; [src](src/) - folder z plikami źródłowymi\
&nbsp;&nbsp; ├── [main.cpp](src/main.cpp) - główny plik main programu\
&nbsp;&nbsp; └── [database.cpp](src/database.cpp) - plik źródłowy dla klasy database\
&nbsp;&nbsp; [inc](inc/)-- folder z plikami nagłówkowymi\
&nbsp;&nbsp; ├── [complex.h](inc/complex.h) - plik zawierający szablon klasy complex\
&nbsp;&nbsp; └── [database.h](inc/database.h) - plik nagłówkowy klasy database\
&nbsp;&nbsp; [tst](tst/) - zawiera pliki źródłowe testów\
&nbsp;&nbsp; ├── [CMakeLists.txt](tst/CMakeLists.txt) - cmake generujący makefile dla programu complex_tst\
&nbsp;&nbsp; ├── [complex-test.cpp](tst/complex-test.cpp) - plik zawierający testy dla klasy complex\
&nbsp;&nbsp; └── [main.cpp](tst/main.cpp) - plik main dla programu complex_tst\
&nbsp;&nbsp; [lib](lib/) - zawiera biblioteke googletest\
&nbsp;&nbsp; └── [googletest-master](lib/googletest-master/) - folder z biblioteką googletest\
&nbsp;&nbsp; [dtb](dtb/) - zawiera pliki z wyrażeniami dla liczb urojonych\
&nbsp;&nbsp; ├── [latwe.dat](dtb/latwe.dat) - plik z łatwymi wyrażeniami\
&nbsp;&nbsp; └── [trudne.dat](dtb/trude.dat) - plik z trudnymi wyrażeniami\
&nbsp;&nbsp; [man](man/) - instrukcje do zadania oraz inne pomoce naukowe\
&nbsp;&nbsp; [CMakeLists.txt](CMakeLists.txt) - cmake generujący makefile dla programu complex_run\
&nbsp;&nbsp; [.gitignore](.gitignore)  - plik określający, które pliki mają być ignorowane przez Gita\

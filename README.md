# volleyball-simulator
**volleyball-simulator** to prosty w użyciu program symulujący wyniki siatkówki.

## Zawartość folderu programu:

***folder results*** - Folder z plikami które mieszczą wyniki danych spotkań. W nazwie pliku jest zapisana godzina i minuta symulacji, aby zminimalizować ryzyko kolizji nazw przy kilkukrotnej symulacji tych samych drużyn.
***folder src*** - Folder z kodem źrodłowym programu. <br>
***plik teams.csv*** - Plik bez którego program poprawnie nie działa. Zawiera on informacje o wszystkich drużynach dostępnych w grze.
***plik config.csv*** - Plik zawierający informacje o opcjach z menu.
- **Jak wpisać drużyny do teams.csv?** <br>
*<nazwa-drużyny>,<umiejętności od 1 do 120>*<br>
Każdą wartość oddzielamy przecinkiem, a każdą drużynę piszemy od entera. <br><br>
***Przykład:*** <br>
Norwegia,73 <br>
Francja,88 <br>
Bułgaria,64 <br>

Jeśli umiejętności nie mieszczą się w zakresie, automatycznie jest dobierana wartość 1 lub 120.

**plik volleyball.exe** - plik wykonywalny programu.

## Opcje w menu gry:
- Symuluj mecz
- Drużyny (Można tam dodawać, edytować i usuwać drużyny z poziomu programu.)
- Ustawienia (Można tutaj ustawić np. czy drużyny mają się automatycznie sortować, lub czy wyniki mają być automatycznie zapisywane w pliku.)

*W pliku teams.csv od razu są przykładowe drużyny, ale nie znam się bardzo na siatkówce więc zachęcam do wpisania własnych.*

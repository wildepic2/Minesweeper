1. Projektname: Minesweeper

2. Kurze Beschreibung der Idee (2-5 Sätze):
Die Idee war einfach minesweeper nachzu programmieren wie z.b. microsoft minesweeper.
Wenn man auf eine Bombe klick sollte man verlieren und wenn man auf alle Bomben eine Flage platziert sollte man gewinnen.

   
3. Beschreibung des 2D-Arrays (Datentyp, Größe, Bedeutung der Werte):
Wir haben mehrere 2D-arrays; a. bool isCovered[fieldSize][fieldSize]; b. bool isBomb[fieldSize][fieldSize]; c. bool isFlag[fieldSize][fieldSize]; d. int fieldValue[fieldSize][fieldSize];
Sie haben alle die fieldSize welche 10 ist.
a. bool isCovered[fieldSize][fieldSize]; Datentyp bool. Es schaut ob ein feld noch nicht geöffnet wurde (true) oder geöffnet ist (false).
b. bool isBomb[fieldSize][fieldSize]; Datentyp bool. Es schaut ob sich dort eine Bombe befindet (true) oder nicht (false).
c. bool isFlag[fieldSize][fieldSize]; Datentyp bool. Schaut ob sich dort eine Flage platziert wurde (true) oder nicht (false).
d. int fieldValue[fieldSize][fieldSize]; Datentyp int. Speichert die Zahlen wie viele Bomben auf dem Umfeld eines Feldes befindet wenn sich 2 Bomben im Umfeld befinden ist der Wert dieses Felds 2.

4. Steuerung (welche Tasten/Mausaktionen was machen):
Mit der linke Maustaste kannst du ein noch nicht enthülltes feld oder ein Feld wo keine Flage steht enthüllen.
Mit der rechten Maustaste kannst du eine Flage platzieren wenn du denkst das dort sich eine Mine befindet oder auch eine Flage wieder aufheben.
Mit der leertaste startes du das Spiel und kannst es neu staten wenn du verloren oder gewonnen hast.

5. Verwendeter String und 1D-Array (kurz benennen):
Der 1D-array welchen wir verwendet haben ist bool isBombFields[8];. Es ist da für die Berechnung der Zahlen.

6. Liste der Funktionen:
initGame() → lädt alle Texturen
a. Menü Funktionen:

mainMenu() → Zeichnet das Hauptmenü
endGame() → Zeigt GAME OVER oder YOU WON

b. Zeichnen Funktionen:

drawField() → Zeichnet alles zusammen
drawGrass() → Zeichnet alle verdeckten Felder
drawBomb() → Zeichnet alle Bomben
drawNumber() → Zeichnet die Zahlen
drawFlag() → Zeichnet Flaggen

c. Einzelne Feldzeichnungen Funktionen:

grassField(int x, int y) → Zeichnet Grasfeld
explodedField(int x, int y) → Zeichnet Explosion
flagField(int x, int y) → Zeichnet Flagge
numberField(int x, int y, int number) → Zeichnet Zahl

d. Spiellogik Funktionen:

playerInput() → Linksklick/Rechtsklick
generateBombs() → Platziert Bomben zufällig
calculateNumbers() → Berechnet Nachbarbomben
wonOrLoose() → Prüft ob du Verloren oder Gewonnen hast
resetGame() → Setzt Spiel zurück
resetGrass() → Verdeckt alle Felder neu
öffneLeereFelder(int x, int y) → Öffnet automatisch zusammenhängende leere Felder und Stoppt bei Zahlen, Bomben oder bereits offenen Feldern
leereFelderZählen(int x, int y, bool visited[][]) → Zählt wie groß ein zusammenhängendes leeres Gebiet ist und Nutzt visited damit Felder nicht doppelt gezählt werden
größtesFeldÖffen() → Sucht das größte leere Gebiet und Öffnet dieses Gebiet automatisch beim Spielstart

e. Texturen laden Funktionen: (laden einfache die Texturen)

initGrassTexture()
initExplodedTexture()
initNumber0Texture()
initNumber1Texture()
initNumber2Texture()
initNumber3Texture()
initNumber4Texture()
initNumber5Texture()
initFlagTexture()


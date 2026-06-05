1. Projektname:
mini-Minesweeper

2. Kurze Beschreibung der Idee (2-5 Sätze):
Die Idee war einfach minesweeper nachzu programmieren wie z.b. microsoft minesweeper.
Wenn man auf eine Bombe klick sollte man verlieren und wenn man auf alle Bomben eine Flage platziert sollte man gewinnen.

   
3. Beschreibung des 2D-Arrays (Datentyp, Größe, Bedeutung der Werte):
Wir haben mehrere 2D-arrays:1. bool isCovered[fieldSize][fieldSize]; 2. bool isBomb[fieldSize][fieldSize]; 3. bool isFlag[fieldSize][fieldSize]; 4. int fieldValue[fieldSize][fieldSize];
Sie haben alle die fieldSize wleche 10 ist.
1. bool isCovered[fieldSize][fieldSize]; Datentyp bool. Es schaut ob ein feld noch nicht geöffnet wurde (true) oder geöffnet ist (false).
2. bool isBomb[fieldSize][fieldSize]; Datentyp bool. Es schaut ob sich dort eine Bombe befindet (true) oder nicht (false).
3. bool isFlag[fieldSize][fieldSize]; Datentyp bool. Schaut ob sich dort eine Flage platziert wurde (true) oder nicht (false).
4. int fieldValue[fieldSize][fieldSize]; Datentyp int. Speichert die Zahlen wie viele Bomben auf dem Umfeld eines Feldes befindet wenn sich 2 Bomben im Umfeld befinden ist der Wert dieses Felds 2.

4. Steuerung (welche Tasten/Mausaktionen was machen):
Mit der linke Maustaste kannst du ein noch nicht enthülltes feld oder ein Feld wo keine Flage steht enthüllen.
Mit der rechten Maustaste kannst du eine Flage platzieren wenn du denkst das dort sich eine Mine befindet oder auch eine Flage wieder aufheben.
Mit der leertaste startes du das Spiel und kannst es neu staten wenn du verloren oder gewonnen hast.

5. Verwendeter String und 1D-Array (kurz benennen):
Der 1D-array welchen wir verwendet haben ist bool isBombFields[8];. Es ist da für die Berechnung der Zahlen.

6. Liste der Funktionen:
initGame() → lädt alle Texturen
1. Menü Funktionen:
mainMenu() → Zeichnet das Hauptmenü
endGame() → Zeigt GAME OVER oder YOU WON
2. Zeichnen Funktionen:
drawField() → Zeichnet alles zusammen
drawGrass() → Zeichnet alle verdeckten Felder
drawBomb() → Zeichnet alle Bomben
drawNumber() → Zeichnet die Zahlen
drawFlag() → Zeichnet Flaggen
3. Einzelne Feldzeichnungen Funktionen:
grassField(int x, int y) → Zeichnet Grasfeld
explodedField(int x, int y) → Zeichnet Explosion
flagField(int x, int y) → Zeichnet Flagge
numberField(int x, int y, int number) → Zeichnet Zahl
4. Spiellogik Funktionen:
playerInput() → Linksklick/Rechtsklick
generateBombs() → Platziert Bomben zufällig
calculateNumbers() → Berechnet Nachbarbomben
wonOrLoose() → Prüft Gewinn/Verlust
resetGame() → Setzt Spiel zurück
resetGrass() → Verdeckt alle Felder neu
5. Texturen laden Funktionen:
initGrassTexture()
initExplodedTexture()
initNumber0Texture()
initNumber1Texture()
initNumber2Texture()
initNumber3Texture()
initNumber4Texture()
initNumber5Texture()
initFlagTexture()


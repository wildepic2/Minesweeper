# Minesweeper

Ein einfaches **Minesweeper-Spiel**, geschrieben in **C** mit der Grafikbibliothek **raylib**.

Ziel des Projekts ist es, das klassische Minesweeper-Spielprinzip nachzubauen, wie man es zum Beispiel von Microsoft Minesweeper kennt. Der Spieler muss sichere Felder aufdecken, Bomben vermeiden und verdächtige Bombenfelder mit Flaggen markieren.

Wenn der Spieler auf eine Bombe klickt, verliert er das Spiel. Wenn alle sicheren Felder geöffnet wurden, gewinnt der Spieler.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/F1F61XISYB)

---

## Inhaltsverzeichnis

- [Über das Projekt](#über-das-projekt)
- [Spielprinzip](#spielprinzip)
- [Steuerung](#steuerung)
- [Projektstruktur](#projektstruktur)
- [Technische Details](#technische-details)
- [Spielzustände](#spielzustände)
- [Spielfeld und Arrays](#spielfeld-und-arrays)
- [2D-Arrays](#2d-arrays)
- [1D-Array](#1d-array)
- [Funktionenübersicht](#funktionenübersicht)
- [Texturen](#texturen)
- [Build-Voraussetzungen](#build-voraussetzungen)
- [Build-Anleitung](#build-anleitung)
- [GitHub Actions](#github-actions)
- [Assets](#assets)
- [Gewinnen und Verlieren](#gewinnen-und-verlieren)
- [Besonderheiten](#besonderheiten)
- [Zusammenfassung](#zusammenfassung)

---

## Über das Projekt

**Minesweeper** ist ein kleines Spielprojekt, bei dem das klassische Minesweeper-Spiel umgesetzt wurde.

Die Idee war, Minesweeper ähnlich wie bekannte Versionen, zum Beispiel Microsoft Minesweeper, nachzuprogrammieren.

Das Spiel besteht aus einem festen Spielfeld. Auf diesem Spielfeld werden zufällig Bomben platziert. Der Spieler muss Felder öffnen, Zahlen richtig deuten und Bomben mithilfe von Flaggen markieren oder vermeiden.

Im Hauptmenü werden der Spieltitel, die Steuerung und die Autoren angezeigt.

Autor-Anzeige im Spiel:

```text
By Raphael Botond Jonas
```

---

## Spielprinzip

Das Spiel funktioniert nach dem bekannten Minesweeper-Prinzip:

1. Das Spiel wird über das Hauptmenü gestartet.
2. Der Spieler deckt Felder auf.
3. Zahlen zeigen an, wie viele Bomben sich in der direkten Umgebung eines Feldes befinden.
4. Vermutete Bomben können mit Flaggen markiert werden.
5. Wird eine Bombe aufgedeckt, ist das Spiel verloren.
6. Sind alle sicheren Felder geöffnet, ist das Spiel gewonnen.

Die Bomben werden zufällig platziert. Dafür wird beim Start des Spiels eine Zufallsbasis mit der aktuellen Zeit gesetzt.

---

## Steuerung

| Eingabe | Aktion |
|---|---|
| **Leertaste** | Spiel starten oder nach Gewinn/Verlust neu starten |
| **Linke Maustaste** | Ein verdecktes Feld aufdecken, wenn dort keine Flagge steht |
| **Rechte Maustaste** | Eine Flagge setzen oder wieder entfernen |

### Weitere Steuerungsregeln

- Ein Feld mit Flagge kann nicht mit der linken Maustaste geöffnet werden.
- Eine Flagge kann nur auf einem verdeckten Feld gesetzt werden.
- Wenn keine Flaggen mehr übrig sind, kann keine weitere Flagge gesetzt werden.
- Durch erneutes Rechtsklicken auf eine Flagge wird sie wieder entfernt.

---

## Projektstruktur

```text
Minesweeper/
├── .github/
│   └── workflows/
│       └── build.yml
├── assets/
├── src/
│   └── main.c
├── CMakeLists.txt
└── README.md
```

### Wichtige Ordner und Dateien

| Pfad | Beschreibung |
|---|---|
| `src/main.c` | Hauptdatei des Spiels |
| `assets/` | Enthält Texturen und andere Spieldateien |
| `CMakeLists.txt` | CMake-Konfiguration zum Bauen des Projekts |
| `.github/workflows/build.yml` | GitHub-Actions-Workflow zum automatischen Bauen und Verpacken |
| `README.md` | Dokumentation des Projekts |

---

## Technische Details

| Kategorie | Wert |
|---|---|
| Projektname | `Minesweeper` |
| Fenstertitel | `MINESWEEPER` |
| Programmiersprache | C |
| C-Standard | C23 |
| Grafikbibliothek | raylib |
| raylib-Version | 5.5 |
| Build-System | CMake |
| CMake-Version | 4.2 |
| Spielfeldgröße | `10 x 10` |
| Anzahl Bomben | `11` |
| Maximale Anzahl Flaggen | `11` |
| Fenstergröße | `500 x 500` Pixel |
| Feldgröße | `50 x 50` Pixel |
| Ziel-FPS | `60` |

---

## Spielzustände

Das Spiel verwendet verschiedene Zustände, um Menü, Spiel und Endbildschirm zu trennen.

| Zustand | Bedeutung |
|---|---|
| `MAIN_MENU` | Hauptmenü wird angezeigt |
| `PLAYING` | Das Spiel läuft |
| `GAME_OVER` | Der Endbildschirm wird angezeigt |

Das Spiel startet im Zustand `MAIN_MENU`.

---

## Spielfeld und Arrays

Das Spielfeld besteht aus einem festen Raster mit:

```c
10 x 10
```

Feldern.

Jedes Feld kann verschiedene Zustände haben:

- verdeckt
- aufgedeckt
- Bombe
- Flagge
- Zahl

Diese Informationen werden mit mehreren Arrays gespeichert.

---

## 2D-Arrays

Das Projekt verwendet mehrere 2D-Arrays.

Alle wichtigen Spielfeld-Arrays besitzen die Größe:

```c
fieldSize x fieldSize
```

Da `fieldSize` den Wert `10` hat, ergibt sich daraus ein Spielfeld von:

```c
10 x 10
```

### Übersicht der 2D-Arrays

| Array | Datentyp | Beschreibung |
|---|---|---|
| `isCovered[fieldSize][fieldSize]` | `bool` | Speichert, ob ein Feld noch verdeckt ist |
| `isBomb[fieldSize][fieldSize]` | `bool` | Speichert, ob sich auf einem Feld eine Bombe befindet |
| `isFlag[fieldSize][fieldSize]` | `bool` | Speichert, ob auf einem Feld eine Flagge gesetzt wurde |
| `fieldValue[fieldSize][fieldSize]` | `int` | Speichert die Anzahl der Bomben in der Umgebung eines Feldes |

---

### `isCovered`

```c
bool isCovered[fieldSize][fieldSize];
```

Dieses Array speichert, ob ein Feld noch verdeckt oder bereits geöffnet ist.

| Wert | Bedeutung |
|---|---|
| `true` | Das Feld ist noch verdeckt |
| `false` | Das Feld ist bereits geöffnet |

---

### `isBomb`

```c
bool isBomb[fieldSize][fieldSize];
```

Dieses Array speichert, ob sich auf einem Feld eine Bombe befindet.

| Wert | Bedeutung |
|---|---|
| `true` | Auf dem Feld befindet sich eine Bombe |
| `false` | Auf dem Feld befindet sich keine Bombe |

---

### `isFlag`

```c
bool isFlag[fieldSize][fieldSize];
```

Dieses Array speichert, ob auf einem Feld eine Flagge gesetzt wurde.

| Wert | Bedeutung |
|---|---|
| `true` | Auf dem Feld befindet sich eine Flagge |
| `false` | Auf dem Feld befindet sich keine Flagge |

---

### `fieldValue`

```c
int fieldValue[fieldSize][fieldSize];
```

Dieses Array speichert, wie viele Bomben sich um ein Feld herum befinden.

Beispiel:

Wenn sich um ein Feld zwei Bomben befinden, wird dort folgender Wert gespeichert:

```c
2
```

---

## 1D-Array

Das Projekt verwendet außerdem ein 1D-Array:

```c
bool isBombFields[8];
```

Dieses Array wird zur Berechnung der Zahlen auf den Feldern verwendet.

Es überprüft die acht Nachbarfelder eines Feldes:

- links
- rechts
- oben
- unten
- links oben
- rechts oben
- links unten
- rechts unten

Dadurch kann gezählt werden, wie viele Bomben sich direkt um ein Feld herum befinden.

---

## Funktionenübersicht

Das Projekt ist in mehrere Funktionsbereiche aufgeteilt:

- Initialisierung
- Menü
- Zeichnen
- Spiellogik
- Eingabe
- Texturen laden

---

### Initialisierung

| Funktion | Beschreibung |
|---|---|
| `initGame()` | Lädt alle benötigten Texturen |
| `resetGame()` | Setzt das gesamte Spiel zurück |
| `resetGrass()` | Verdeckt alle Felder erneut |

---

### Menü-Funktionen

| Funktion | Beschreibung |
|---|---|
| `mainMenu()` | Zeichnet das Hauptmenü |
| `endGame()` | Zeigt den Endbildschirm mit Gewinn- oder Verlustmeldung |

---

### Zeichen-Funktionen

| Funktion | Beschreibung |
|---|---|
| `drawField()` | Zeichnet das komplette Spielfeld |
| `drawGrass()` | Zeichnet alle verdeckten Felder |
| `drawBomb()` | Zeichnet Bomben, wenn sie aufgedeckt wurden |
| `drawNumber()` | Zeichnet die Zahlenfelder |
| `drawFlag()` | Zeichnet alle gesetzten Flaggen |

---

### Einzelne Feld-Zeichenfunktionen

| Funktion | Beschreibung |
|---|---|
| `grassField(int x, int y)` | Zeichnet ein verdecktes Feld |
| `explodedField(int x, int y)` | Zeichnet ein explodiertes Bombenfeld |
| `flagField(int x, int y)` | Zeichnet eine Flagge |
| `numberField(int x, int y, int number)` | Zeichnet ein Zahlenfeld |

---

### Spiellogik-Funktionen

| Funktion | Beschreibung |
|---|---|
| `playerInput()` | Verarbeitet Maus- und Tasteneingaben während des Spiels |
| `generateBombs()` | Platziert Bomben zufällig auf dem Spielfeld |
| `calculateNumbers()` | Berechnet die Zahlen für alle Felder |
| `wonOrLoose(int caseOfCall)` | Prüft, ob das Spiel gewonnen oder verloren wurde |
| `oeffneLeereFelder(int x, int y)` | Öffnet zusammenhängende leere Felder automatisch |
| `leereFelderZaehlen(int x, int y, bool visited[fieldSize][fieldSize])` | Zählt die Größe eines zusammenhängenden leeren Bereichs |
| `groeßtesFeldOeffnen()` | Sucht den größten leeren Bereich und öffnet ihn beim Spielstart automatisch |

---

## Texturen

Das Spiel verwendet mehrere Texturen aus dem Ordner:

```text
assets/minesweeper_tiles/
```

### Verwendete Texturdateien

| Datei | Bedeutung |
|---|---|
| `masked_tile.png` | Verdecktes Feld |
| `tile_exploded.png` | Explodierte Bombe |
| `revealed_tile.png` | Leeres aufgedecktes Feld |
| `revealed_tile_1.png` | Aufgedecktes Feld mit Zahl 1 |
| `revealed_tile_2.png` | Aufgedecktes Feld mit Zahl 2 |
| `revealed_tile_3.png` | Aufgedecktes Feld mit Zahl 3 |
| `revealed_tile_4.png` | Aufgedecktes Feld mit Zahl 4 |
| `revealed_tile_5.png` | Aufgedecktes Feld mit Zahl 5 |
| `masked_tile_flag_blue.png` | Feld mit Flagge |

Alle Texturen werden auf eine Größe von `50 x 50` Pixel angepasst.

---

## Build-Voraussetzungen

Zum Bauen des Projekts werden folgende Programme benötigt:

- C-Compiler
- CMake
- Git
- raylib-Abhängigkeiten

Die Bibliothek **raylib 5.5** wird automatisch über CMake heruntergeladen.

Unter Linux werden zusätzlich einige Systembibliotheken benötigt, zum Beispiel für Audio, Fenster, Mauszeiger, OpenGL und X11.

---

## Build-Anleitung

### 1. Repository klonen

```bash
git clone <repository-url>
cd Minesweeper
```

### 2. Projekt konfigurieren

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

### 3. Projekt bauen

```bash
cmake --build build --config Release
```

### 4. Spiel starten

Unter Linux:

```bash
./build/Minesweeper
```

Unter Windows:

```bash
build/Release/Minesweeper.exe
```

Unter macOS:

```bash
./build/Minesweeper
```

---

## Compiler-Warnungen

Beim Bauen werden Compiler-Warnungen aktiviert.

| Compiler | Warnoptionen |
|---|---|
| MSVC | `/W4` |
| Andere Compiler | `-Wall -Wextra -Wpedantic` |

---

## GitHub Actions

Das Projekt enthält einen GitHub-Actions-Workflow, der das Spiel automatisch baut und verpackt.

Der Workflow wird ausgeführt bei:

- Pushes auf den Branch `master`
- Pull Requests auf den Branch `master`

Der Workflow läuft auf:

- Ubuntu
- Windows
- macOS

Dabei werden folgende Schritte ausgeführt:

1. Repository auschecken
2. CMake 4.2 einrichten
3. Linux-Abhängigkeiten installieren, falls der Build auf Linux läuft
4. Projekt mit CMake konfigurieren
5. Projekt bauen
6. Einen `dist`-Ordner erstellen
7. Die ausführbare Datei in den `dist`-Ordner kopieren
8. Den `assets`-Ordner kopieren, falls er vorhanden ist
9. Das fertige Paket als Artefakt hochladen

Die Artefakte werden ungefähr so benannt:

```text
minesweeper-linux-v<run_number>
minesweeper-windows-v<run_number>
minesweeper-macos-v<run_number>
```

---

## Assets

Das Spiel verwendet den Ordner:

```text
assets/
```

Dort liegen die Texturen für:

- verdeckte Felder
- aufgedeckte Felder
- Zahlenfelder
- Bomben
- Flaggen

Beim Bauen wird der `assets`-Ordner automatisch neben die ausführbare Datei kopiert, damit das Spiel die Texturen laden kann.

---

## Gewinnen und Verlieren

### Verlieren

Der Spieler verliert, wenn er ein Feld aufdeckt, auf dem sich eine Bombe befindet.

Danach werden alle Felder aufgedeckt und der Endbildschirm zeigt:

```text
GAME OVER
```

---

### Gewinnen

Der Spieler gewinnt, wenn alle sicheren Felder geöffnet wurden.

Danach werden alle Felder aufgedeckt und der Endbildschirm zeigt:

```text
YOU WON!
```

---

## Besonderheiten

Das Spiel öffnet beim Start automatisch das größte leere Feldgebiet.

Dadurch beginnt das Spiel nicht mit einem komplett geschlossenen Feld, sondern direkt mit einem geöffneten Bereich.

Außerdem werden zusammenhängende leere Felder automatisch geöffnet, ähnlich wie im klassischen Minesweeper.

Bomben werden zufällig erzeugt. Wenn zufällig ein Feld ausgewählt wird, auf dem bereits eine Bombe liegt, wird erneut ein Feld gesucht. Dadurch wird verhindert, dass zwei Bomben auf demselben Feld liegen.

---

## Zusammenfassung

Dieses Projekt ist eine einfache Minesweeper-Umsetzung in **C** mit **raylib**.

Es enthält:

- ein Hauptmenü
- einen Spielzustand für Menü, Spiel und Endbildschirm
- ein 10x10-Spielfeld
- 11 zufällig platzierte Bomben
- maximal 11 Flaggen
- ein Flaggen-System
- Schutz davor, markierte Felder versehentlich zu öffnen
- Zahlenberechnung für Nachbarbomben
- automatische Öffnung leerer Felder
- automatische Öffnung des größten leeren Bereichs beim Spielstart
- Gewinn- und Verlustprüfung
- Texturen für Felder, Zahlen, Bomben und Flaggen
- automatisches Kopieren des `assets`-Ordners
- Compiler-Warnungen
- automatischen Build über GitHub Actions für Linux, Windows und macOS

## Hinweis für macOS

Auf macOS sollte das Spiel über das Terminal gestartet werden und nicht direkt per Doppelklick.

Der macOS-Build funktioniert, wenn man zuerst in den Ordner mit der ausführbaren Datei und dem `assets`-Ordner wechselt und das Spiel dann über die Kommandozeile startet:

bash cd path/to/minesweeper-macos ./Minesweeper

Beim direkten Doppelklick kann es passieren, dass das Spiel den `assets`-Ordner nicht findet.
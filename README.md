## Ziel des Projektes

Ziel des Projektes ist es ein Buchstabenspiel in C zu erstellen. Hierbei soll man ein zufälliges Wort einer festen Länge eraten. Man gibt dazu Wörter/andere Buchstabenkombos ein und das Spiel sagt einem, wie viele Buchstaben auf der korrekten Position oder im Wort sind. Wenn man das Wort innerhalb von 10 Versuchen erraten hat, hat man gewonnen.

Für das Wortspiel ist eine Wortliste nötig. Um während der Laufzeit nicht unnötig in der Wortliste nach Wörtern der korrekten Länge zu suchen, soll hier aus der alten eine neue Liste mit nur Wörtern der korrekten Länge erzeugt werden.

## Nutzung

Den Code mit einem Compiler (beispielsweise gcc) kompilieren. Sollte die Wordliste ("Output.txt") nicht vorhanden sein oder sollten sie die Länge der Worte verändern wollen, muss makeWordList.c ausgeführt werden.

Zum Spielen des Wortspieles muss Wordgame.c ausgeführt werden.

## Weitere Voraussetzungen
1. Die Länge des Wortes soll vom Benutzer festgelegt werden können
2. Gegeben ist eine txt Datei, welche Hunderttausende Wörter unterschiedlicher Länge hat. Wörter sind (größtenteils) einzeln mit Zusatzdaten in einer Zeile gegeben. Zusatzdaten, sowie unbrauchbare Daten sollen nicht in der Wortliste vorkommen
3. Das Buchstabenspiel soll so gut optimiert sein, dass der Nutzer keine Wartezeiten hat. Die Mindestvoraussetzung ist ein Laptop, der bei mir Zuhause rumliegt :D
4. Der Code zum Generieren der Wortliste muss nicht super optimiert/schnell sein, da der Code nur ein/zweimal läuft, um die neue Datei zu erstellen. 
5. Wörter mit selteneren Buchstaben ("ß, ö, é") nutzen stattdessen ihre alternative Schreibweise ("ss, oe, e"). Beispiel (groß -> gross, über -> ueber)
6. Abhängig von welchem Text Encoding genutzt wird, sind die Kodierungen von den Charakterzeichen anders. Dieses Programm geht von Unicode (UTF-8) aus

## Probleme

### Buchstabenspiel

- Der Input wird noch nicht gefiltert. Man kann noch Buchstaben eingeben, die nicht im Wort vorkommen können

### Erstellung der Wortliste

- Manche Wörter stehen mir anderen in der selben Zeile, getrennt mit , / ( ). Diese Werden momentan ausgeschlossen

## Acknowledgements

#### Wortgrundformenliste

Korpusbasierte Wortgrundformenliste DeReWo, \
v-ww-bll-320000g-2012-12-31-1.0, mit Benutzerdokumentation, \
http://www.ids-mannheim.de/derewo, \
© Institut für Deutsche Sprache,  \
Programmbereich Korpuslinguistik, \
Mannheim, Deutschland, 2013.

Parser
======
Anfragen an die Datenbank werden in SQL formuliert und als Zeichenkette eingegeben.
Das Parsen von Anfragen erfolgt dabei in zwei Schritten:

- Lexikalische Analyse
- Syntaktische Analyse

Bei der lexikalischen Analyse wird die Eingabe durch Anwendung regulärer Ausdrücke zunächst in einen Token-Strom
umgewandelt. Dieser wird anschließend durch einen Recursive descent parser ohne Backtracking auf korrekte Syntax
geprüft. Das Ergebnis der Parse-Phase ist eine abstrakte Repräsentation der Anfrage.

Die abstrakte Abfrage enthält:

- den Typ der Abfrage (Abruf, Einfügen, Löschen von Einträgen, Erstellen einer Tabelle)
- die Namen der Tabellen von denen Einträge abgefragt werden
- die Namen der Spalten die projeziert werden
- eine (aus mehreren Teilbedingungen zusammengesetzte) Selektions-Bedingung

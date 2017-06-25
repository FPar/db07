Plan
====

Es können zwei Arten von Plänen unterschieden werden: Pläne, die Daten Abfragen und Pläne,
die Daten ändern. Im Rahmen dieses Projektes wurde der Plan für ``SELECT``- und
``Insert``-Abfragen implementiert.

Alle Pläne, bei denen Daten gelesen werden sollen, greifen dafür auf einen Exeuction Tree
aus einzelnen Nodes zu. Dieser wird vom Optimizer generiert und liefert einen linearen
Datenstrom.

Nodes
-----

Nachfolgend eine Auflistung implementierter Nodes.

Table Scan
++++++++++

Dieser Node iteriert durch eine Tabelle vom Anfang bis zum Ende und kann dabei nach Einträgen
filtern, welche eine bestimmte Bedinungung erfüllen. Die Bedingung liegt selbst in Form eines
Matching Baums vor, welcher auf Grundlage des Typesystems Werte des gleichen Datentypes
vergleichen kann.

Hash Match
++++++++++

Um zwei Tabellen miteinander zu verknüpfen, kann naiv das kartesische Produkt der beiden
Tabellen gebildet werden und dieses mit einer Verknüpfungsbedingung auf das gewünschte
Ergebnis reduziert werden. Eine effizientere Variante, welche von diesem Node umgesetzt
wird, ist das Hashen des Schlüssels der ersten Tabelle und dann für jeden Eintrag in
der zweiten Tabelle über den Schlüsselhash den zugehörigen Eintrag in der ersten Tabelle
zuzuordnen und zu verknüpfen. Das Hash Match führt diese Operation über zwei beliebige
untergeordnete Nodes durch.

Insert data node
++++++++++++++++

Dieser Node wird für das Einfügen von Daten verwendet und liefert Einträge basierend
auf einer in-Memory Collection.

SELECT
------

Ein ``SELECT``-Plan besteht aus drei Komponenten: der Root-Node eines Execution Trees,
eine Projektions-Instruktion und ein Ziel, an welches die abgefragten Daten übergeben
werden. Die Tabellenbeschreibung der Projektions-Definition wird aus der Tabellenbeschreibung
des Root Nodes des Execution Trees und einer Liste von Spaltennamen gebildet. Damit kann die
Projektion als letzter Schritt auf jeden beliebigen Query angewendet werden.

INSERT
------

Ein ``INSERT``-Plan fügt Daten, welche von einem Execution-Tree bereitgestellt werden, in
eine beliebige Tabelle (wenn die Tabellen-Definition es zulässt) ein. Für reguläre ``INSERT``-
Abfragen stellt ein Insert data node die zu einfügenden Daten bereit. Aber auch komplexere
Abfragen könnten durchgeführt werden, wenn Daten aus einer anderen Tabelle eingefügt werden
sollen.

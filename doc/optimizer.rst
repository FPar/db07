Optimizer
=========

Vom Parser wird die Art der Anfrage erwartet und die
entsprechenden Daten wie betroffene Tabelle und Spalten.

Es gibt eine Liste von Conditions und eine Liste mit den boolischen Ausdrücken.
Anhand der Indizes werden die Conditions mit den boolischen Ausdrücken
verbunden.

Mithilfe des Table Scans und der Projektion wird ein select plan erstellt.
Der Table Scan wird die angefragte Tabelle übergeben und die Root Condition.
Die Liste der selektierten Spalten werden in der Projektion angegeben.

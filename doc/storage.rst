Data Store
==========
- Die Daten werden abgespeichert in einem B+Tree. 
- Dabei handelt es sich um einen vollständig balancierten Baum. 
- Die Daten sind in den Leafnodes enthalten. Jedes Leafnode enthält vier Datensätze.
- Es wird im voraus schon festgelegt wie viele Elemente in einem Knoten enthalten sein darf. In Aktuelle Implementierung enthält jeder Knoten vier keys und fünf Pointer auf seine Kindelemente
- Bereits beim Löschen und Einfügen wird der Baum balanciert. 
- Durch das Balancieren wächst der Baum erst nach dem kompletten Füllen einer Breitenebene um eine Ebene in die Tiefe. Dadurch werden Operationen wie der IndexScan stark beschleunigt.

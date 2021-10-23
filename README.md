# PROVA FINALE DI ALGORITMI E PRINCIPI DELL'INFORMATICA (API) A.A. 2019/2020
Scopo del progetto è quello di implmentare un semplice editor di testo ispirato all'editor Unix [ed](https://it.wikipedia.org/wiki/Ed_(Unix)).

## COMANDI DISPONIBILI
Segue una breve descrizione dei comandi disponibili per l'editor:
* __(ind1,ind2)c__: cambia il testo presente alle righe comprese tra ind1 ed ind2 (estremi inclusi).
* __(ind1,ind2)d__: cancella le righe comprese tra ind1 ed ind2 (estremi inclusi), spostando verso l’alto le righe successive a quella di indirizzo ind2 (se ce ne sono).
* __(ind1,ind2)p__: stampa le righe comprese tra ind1 ed ind2 (o tra ind1 e la fine del testo se ind2 non corrisponde ad alcun indirizzo nel testo).
* __(numero)u__: effettua l’annullamento (undo) di un numero di comandi (c o d) pari a quello specificato tra parentesi tonde (laddove numero `e un intero strettamente maggiore di zero).
* __(numero)r__: annulla l’effetto di undo per un numero di comandi pari a numero a partire dalla versione corrente (funzione di redo). 
* __q__: termina l’esecuzione dell’editor.

## ESECUZIONE DEL PROGRAMMA
Eseguire il file Codice.exe oppure compilare ed eseguire il file Codice.c.

## MAGGIORI INFORMAZIONI
Ulteriori informazioni sulla specifica e sui comandi sono disponibili nel file [Specifica](https://github.com/DavideFoini/PROGETTO-API-2019-2020/blob/main/Specifica.pdf).

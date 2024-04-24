# Parsificazione e gestione delle date

<!-- ```cpp -->
La libreria mette a disposizione del programmatore una struct `DateTime`, volta a gestire date che includono l'ora.

Essa contiene i seguenti campi:
```cpp
// La zona UTC corrente.
int TimeZone = +0;

// Il timestamp UNIX.
double TimeStamp;

/// Il giorno del mese (1-31).
unsigned int Day;

/// Il numero del mese (1-12).
unsigned int Month;

/// L'anno.
unsigned int Year;

/// Le ore (0-23).
unsigned int Hours;

/// I minuti.
unsigned int Minutes;

/// I secondi.
unsigned int Seconds;

/// I millisecondi.
unsigned int Milliseconds;

/// Il giorno dell'anno (0-366).
unsigned int DayOfYear;

/// Il giorno della settimana (0-6).
unsigned int WeekDay;
```

## Inizializzazione di un oggetto `DateTime`
Gli oggetti di tipo `DateTime` possono essere inizializzati in tre modi:

1. **Con il costruttore vuoto.** In questo modo l'oggetto farà riferimento alla data e ora corrente, e al fuso orario corrente
```cpp
DateTime dt = DateTime();
```
2. **Con un Timestamp UNIX passato al costruttore.**

**N.B.** Il timestamp UNIX non include informazioni sul fuso orario, che andrà quindi settato successivamente (Di default è a zero, fuso orario di Greenwich).

```cpp
DateTime dt = DateTime(1603640983);
dt.TimeZone = +1;
```

3. **Creando un timestamp UNIX utilizzando il metodo `DateTime::GetTimeStamp()`**

```cpp
DateTime dt = DateTime::GetTimeStamp(2023, 06, 21, 23, 30, 42, 0);
dt.TimeZone = +2;
```

4. **Parsificando una stringa ISO.**
Il parser supporta stringhe ISO in tutti i formati, sia che contengano esclusivamente la data sia che contengano data e ora, fuso orario incluso.

Esempi:
 - `2022-08-28`
 - `2022-08-28T21:45:31`
 - `2022-08-28T21:45:31.123`
 - `2022-08-28T21:45:31+02:00`
 - `2022-08-28T21:45:31.123+02:00`

```cpp
DateTime dt = DateTime::ParseISO("2022-08-28");
```

## Conversione in stringa dell'oggetto

Al contrario, per convertire l'oggetto DateTime in una stringa, esistono diversi metodi:

```cpp
DateTime dt = DateTime::GetTimeStamp(2023, 06, 21, 23, 30, 42, 0);
dt.TimeZone = +2;

dt.ToDateString(); // 21/06/2023
dt.ToTimeString(); // 23:30:42
dt.ToISOString(); // 2023-06-21T23:30:42+02:00
```
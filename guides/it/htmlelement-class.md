## La classe `HTMLElement` e le sue derivate

La classe `HTMLElement` è alla base di ogni metodo della libreria che manipola il *DOM*. Un'istanza di questa classe rappresenta un puntatore a un oggetto grafico del documento, come può essere un paragrafo, un div, eccetera. La classe fornisce metodi e proprietà che permettono di modificare dinamicamente l'oggetto puntato. Da `HTMLElement` derivano altre classi che rappresentano elementi DOM più specifici (ad esempio `HTMLButtonElement`) e che dispongono di proprietà e metodi aggiuntivi e specifici.

Di seguito vengono elencate e descritte tutte le proprietà e i metodi della classe, insieme con i suoi costruttori e il suo distruttore.

### Costruttori e distruttore di `HTMLElement`

-   **Costruttore** (data una query CSS e un documento padre)
    ```cpp
    HTMLElement(const char* CSS_QUERY, HTMLDocument doc = document);
    ```
    L'utilizzo di questo costruttore crea una nuova istanza di classe che punta al primo elemento selezionato dalla query CSS passata come primo parametro. &Egrave; inoltre possibile specificare il documento dove la ricerca dell'elemento va effettuata. Di default, fa riferimento al documento corrente (`document`). 

    > **N.B.** Nel caso in cui l'elemento selezionato non esistesse, l'interprete JavaScript mostrerà un errore in console del tipo:  
`Cannot read properties of undefined.`

- **Costruttore** (dato il tipo di elemento da creare, il suo ID e il documento di destinazione)
  ```cpp
  HTMLElement(const char* TAGNAME, const char* ID, HTMLDocument doc = document);
  ```
  Al contrario del costruttore precedente, questo permette di creare un nuovo elemento. &Egrave; necessario specificare il tipo di elemento (es. `"table"`, `"button"`) ed un suo ID univoco.

    > **N.B.** Una volta richiamato questo costruttore, l'elemento verrà solo creato come oggetto in memoria, ma NON ancora accodato alla pagina. Per aggiungere l'elemento alla pagina, sarà necessaria una chiamata a `document.Append`.

- **Distruttore**
  ```cpp
  ~HTMLElement();
  ```
  Il distruttore di classe viene automaticamente richiamato quando l'oggetto non è più necessario. &Egrave; anche possibile richiamare manualmente il distruttore.

    > **N.B.** Il distruttore distrugge l'oggetto che punta all'elemento. Non rimuove l'elemento dalla pagina.

    > Per evitare che il puntatore venga distrutto automaticamente, settare la proprietà `Destroyable` a `false`.

### Metodi e operatori di `HTMLElement`

- **Metodo `Append()`**
  ```cpp
  el.Append("TESTO");
  el.Append(&ALTRO_ELEMENTO);
  ```
  Permette di aggiungere in coda all'elemento o un testo o un altro `HTMLElement`.

- **Operatore `<<`**
  ```cpp
  el << "TESTO";
  el << &ALTRO_ELEMENTO;
  ```
  Equivale al `.Append()`.

    > **N.B.** Quando si aggiunge un'elemento ad un altro, esso va sempre passato per referenza utilizzando l'operatore di *referenziazione* (`&`)

- **Metodi `setProperty()` e `getProperty()`**
  ```cpp
  void setProperty(const char* key, const char* value);
  char* getProperty(const char* key);
  ```
  Impostano o restituiscono il valore di una proprietà dell'oggetto puntato.

- **Metodi `setAttribute()` e `getAttribute()`**
  ```cpp
  void setAttribute(const char* key, const char* value);
  char* getAttribute(const char* key);
  ```
  Impostano o restituiscono il valore di un attributo HTML dell'oggetto puntato.

- **Metodi `setStyleProperty()` e `getStyleProperty()`**
  ```cpp
  void setStyleProperty(const char* key, const char* value);
  char* getStyleProperty(const char* key);
  ```
  Impostano o restituiscono il valore di una proprietà CSS dell'oggetto puntato.

- **Metodo `addEventListener()`**
  ```cpp
  void addEventListener(const char* eventname, void(*handler)(HTMLElement&));
  ```
  Associa un'handler a un evento (come `click`, `load` eccetera). L'handler può essere una *lambda* oppure una funzione classica. Il primo parametro dell'handler, di tipo `HTMLElement&`, rappresenta il sender. 

  *Esempio con lambda:*
  ```cpp
  el.addEventListener("click", [](HTMLElement& sender) {
    // Codice eseguito al click
  });
  ```
  *Esempio con funzione classica:*
  ```cpp
  void btnProva_Click(HTMLElement& sender) {
    // Codice eseguito al click
  }

  el.addEventListener("click", btnProva_Click);
  ```

### Proprietà di `HTMLElement`

- **Array associativo `attributes[]`**
  ```cpp
  char* attributes[const char* key];
  ```
  Permette l'accesso agli attributi dell'elemento. Equivale all'utilizzo di `setAttribute` e `getAttribute`.

  *Esempio:*
  ```cpp
  el.attributes["src"] = "https://example.com/my_img.jpg";
  ```

- **Array associativo `style[]`**
  ```cpp
  char* style[const char* key];
  ```
  Permette l'accesso alle proprietà CSS dell'elemento. Equivale all'utilizzo di `setStyleProperty` e `getStyleProperty`.

  *Esempio:*
  ```cpp
  el.style["display"] = "none";
  ```

- `Destroyable` (`bool`)  
  Specifica se l'elemento dovrà essere deallocato dal distruttore quando non più necessario. Di default è impostato a `true`.

- `Exists` (`bool`)  
  Indica se l'elemento specificato effettivamente esiste nel DOM.

- `id`  
  Rappresenta l'attributo *id* dell'elemento, cioè un identificatore univoco all'interno dell'albero DOM.

- `innerHTML`  
  Rappresenta la stringa HTML contenuta all'interno dell'elemento.

- `outerHTML`  
  Stringa HTML rappresentante l'elemento e il suo contenuto.

- `innerText`  
  Rappresenta il testo contenuto all'interno dell'elemento.

- `outerText`  
  Rappresenta il testo contenuto all'interno dell'elemento. La differenza rispetto a innerText è che, quando usata come setter, rimpiazza l'elemento.

- `textContent`  
  Stringa che rappresenta il testo contenuto nell'elemento.

- `nodeName`  
  Corrisponde al tipo di tag dell'elemento, oppure a `#text` o `#comment` se il nodo è un nodo di testo o un commento.

- `nodeType`  
  Corrisponde al tipo di nodo. Utile nella gestione dell'XML.

- `nodeName`  
  Se il nodo è un nodo di testo o un commento, ne restituisce il valore. Utile nella gestione dell'XML.

- `lang`  
  Specifica il linguaggio in cui il testo dell'elemento è scritto.

- `title`  
  Specifica il testo del tooltip visualizzato di default quando ci si porta con il mouse sull'elemento.

- `scrollTop`  
  Specifica la distanza a cui l'utente è arrivato a scorrere da cima elemento.

- `scrollLeft`  
  Specifica la distanza a cui l'utente è arrivato a scorrere dalla destra dell'elemento.

- `scrollWidth`  
  Specifica la larghezza dell'elemento che si può scorrere.

- `scrollHeight`  
  Specifica l'altezza dell'elemento che si può scorrere.

- `dir`  
  Specifica la direzione del testo (`rtl`, `ltr`).

- `className`  
  Specifica il nome della classe CSS associata all'elemento.

- `contentEditable`  
  Specifica se il contenuto dell'elemento è modificabile.

- `accessKey`  
  Specifica il tasto che, premuto in combinazione con **`ALT`**, attiva l'elemento.

### Eventi dell'`HTMLElement`
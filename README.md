**Dinamica in un biliardo triangolare**

**Riccardo Grandicelli** 

**1. Introduzione** 

Il  programma  intende  simulare  il  movimento  di  un  oggetto  all’interno  di  un  biliardo triangolare, così come descritto nelle istruzioni che ci sono state fornite [1]. La particella che si muove all’interno del biliardo può urtare le due pareti (quella superiore e quella inferiore) e prosegue il suo moto finché non esce dal biliardo dalla parete di destra o da quella di sinistra (in quest’ultimo caso la particella viene contata come non uscita dal biliardo). Gli urti con le pareti sono supposti elastici. 

Il programma fornisce posizione finale e angolo di uscita dal biliardo della particella. È possibile sia determinare le coordinate finali di una singola particella, con coordinate di partenza  fornite  dall’utente,  sia  determinare  le  coordinate  finali  di  un  certo  numero  di particelle, con coordinate di partenza generate casualmente seguendo una distribuzione gaussiana. 

Il programma può infine calcolare media, deviazione standard, coefficiente di simmetria (indice  di  simmetria  di  Fischer)  e  di  appiattimento  (indice  di  curtosi  di  Pearson)  delle distribuzioni di posizione e angolo finali delle particelle generate casualmente. 

In allegato ho aggiunto una macro di ROOT che permette di visualizzare graficamente la distribuzione di posizione e angolo, sia iniziali che finali. 

**2. Classi, metodi e funzioni** 

Le classi, i metodi e le funzioni implementate per la risoluzione del problema sono state divise in tre namespaces: 

- Gen: contiene i function objects 
- Stats: contiene le classi e i metodi per il calcolo delle statistiche delle distribuzioni finali di posizione e angolo delle particelle 
- Ric: contiene tutti gli altri metodi, classi e funzioni utili alla risoluzione del problema 
**A. Namespace Ric** 

Qui sono implementate le classi Point, Line e Particle: 

- **Point:** è una coppia di double che definiscono le coordinate x e y di un punto nello spazio bidimensionale** 
- L’**operatore !=** serve per definire l’uguaglianza tra due punti. Poiché è difficile usare l’operatore == per i double, tale operatore != considera uguali due punti se la differenza tra le x e la differenza tra le y sono entrambe, in valore assoluto, minori di 0.001 (cioè praticamente uguali a 0)** 
- **Line:** rappresenta una retta nello spazio bidimensionale, nella forma  + + = 0 La scelta di utilizzare i parametri a, b e c per definire una retta (anziché usare coefficiente angolare e intercetta) è dovuto al fatto che ciò pone meno problemi nel caso in cui dovesse essere definita una retta parallela all’asse y.** 
- La  retta  può  essere  inizializzata  mediante  tre  costruttori:  il  primo  utilizza coefficiente angolare e intercetta, il secondo due punti nello spazio, e il terzo una particella (che, come illustrerò in seguito, è definita in base a un punto e all’angolo con l’asse x, parametri sufficienti per definire una retta)** 
- I metodi **m** e **q** restituiscono rispettivamente coefficiente angolare e intercetta, mentre il metodo **set\_new** serve per modificare a, b e c, partendo da una particella (in pratica è un costruttore per una retta già inizializzata)** 
- **Particle:**  definisce  una  particella  nel  biliardo,  caratterizzata  da  una  posizione  e dall’angolo formato dalla sua velocità con l’asse x.** 
- Il modulo della velocità non è stato inserito in quanto è irrilevante ai fini di determinare  la  posizione  finale  della  particella  (visto  che  non  è  presente l’attrito, e che gli urti sono elastici).** 
- L’angolo può essere compreso tra -90° e 90° (in radianti). Nel costruttore non c’è nessun controllo su questa invariante di classe, ma nel codice ogni volta in cui viene inizializzata una particella si controlla che il valore dell’angolo sia nell’intervallo appena definito.** 
- I metodi **set\_position** e **set\_angle** servono a modificare angolo e posizione della particella, mentre i metodi **rotate\_forward** e **rotate\_backward** ruotano la velocità della particella rispettivamente in senso antiorario o orario, di un angolo compreso tra 0° e 90°. Il funzionamento di questi metodi è spiegato in Appendice 1.** 

Sempre nel namespace Ric sono definite le funzioni intsec, ort e find\_angle 

- **Intsec:** restituisce il punto di intersezione tra due rette. 
- **Ort:** data una retta e un punto, la funzione trova la perpendicolare alla retta passante per quel punto, sfruttando il fatto che il prodotto tra i coefficienti angolare di due rette perpendicolari è -1. 
- **Find\_angle:** trova l’angolo acuto compreso tra due rette. Il suo funzionamento è spiegato in Appendice 2. 
**B. Namespace Gen** 

Qui sono definite le classi (function objects) PartG e PartM: 

- **PartG:** serve per generare posizioni e angoli iniziali delle particelle. Si inizializza con i parametri della distribuzione gaussiana della posizione iniziale in y (la posizione di partenza in x è 0) e i parametri della distribuzione gaussiana dell’angolo iniziale. L’**operatore  ()**  permette  di  generare  particelle  casualmente  seguendo  tali distribuzioni gaussiane. La generazione viene ripetuta fino a quando la particella generata non ha y compresa tra -r1 e r1 e angolo compreso tra -90° e 90°. 
- **PartM:** serve per trovare la posizione e l’angolo finali di una particella. Si inizializza con i parametri che definiscono il biliardo (r1, r2 e l). L’**operatore ()** prende in input una particella e ne cambia posizione e angolo portandola dalla sua configurazione iniziale a quella finale. Nel paragrafo 3 è spiegato il metodo utilizzato per trovare la configurazione finale.** 

**C. Namespace Stats**

Qui sono definite le classi Statistics e Sample: 

- **Statistics:** è un insieme di quattro double: media, deviazione standard, coefficiente di simmetria e di appiattimento 
- **Sample:**  definisce  un  campione  di  particelle.  Una  variabile  Sample  può  essere inizializzata con un vettore di Particle. 
- Il metodo **statistics\_y** permette di calcolare, e di salvare in una variabile Statistics, le statistiche relative alle posizioni in y delle particelle contenute nella variabile Sample. 
- Il metodo **statistics\_ang** permette di calcolare le statistiche relative agli angoli delle particelle nella variabile Sample, nello stesso modo in cui sono calcolate le statistiche per le posizioni in y. 
**3. Come trovare la configurazione finale delle particelle** 

L’operatore () del function object PartM permette di trovare la posizione e l’angolo di uscita di una particella, tramite il seguente procedimento: 

1. Vengono generate le variabili Line *upborder*, *downborder*, *leftborder* e *rightborder* (i quattro bordi del biliardo), mentre la variabile Line *go* viene inizializzata a partire da posizione e angolo della particella da muovere (*go* indica la direzione del moto della particella).  Vengono  inoltre  inizializzate  le  variabili  Line  *down\_perp*  e  *up\_perp*, rispettivamente le perpendicolari al bordo inferiore e superiore (che non dipendono dal punto di impatto della particella) 
1. Inizia ora un ciclo while, nel quale a ogni iterazione *go* viene intersecata con i quattro bordi. Chiaramente solo due delle intersezioni saranno interne ai bordi del biliardo, di cui una è la posizione attualmente occupata dalla particella e l’altra il punto d’impatto della particella con il biliardo.* 
1. Le quattro condizioni if successive servono proprio per vedere quale dei quattro bordi del biliardo urta la particella, controllando che tale punto d’impatto sia diverso dalla posizione attualmente occupata dalla particella. A seconda del bordo colpito, la particella ha quattro possibilità:* 
- Se vengono urtati il bordo superiore o inferiore, la funzione **find\_angle** trova l’angolo tra *go* e la perpendicolare al bordo colpito. A questo punto il metodo **rotate\_forward** ruota l’angolo della particella di un angolo pari a quello appena trovato, in senso antiorario.  Se  ora  l’angolo  della  particella  corrisponde  a  quello  di  *up\_perp*  o *down\_perp*  (ossia  l’arcotangente  del  loro  coefficiente  angolare),  la  rotazione  è avvenuta nel senso corretto, quindi viene effettuata un’altra rotazione. Se invece i due angoli non corrispondono, viene effettuata per tre volte una rotazione in senso orario con il metodo **rotate\_backward**. In entrambi i casi, l’angolo della particella dopo le rotazioni è il suo angolo finale in seguito all’urto. Il punto d’impatto diventa dunque la nuova posizione della particella e i membri privati di go vengono aggiornati ai nuovi metodi privati della particella.* 
- Se viene urtato il bordo a destra o a sinistra, la particella è uscita dal biliardo. Posizione e angolo della particella vengono aggiornati al punto d’impatto finale, e il ciclo termina.* 

**4\. Funzione main** 

La funzione main del programma attende un comando dall’utente: tale comando può essere soltanto uno dei seguenti caratteri: ‘m’, ‘a’, ‘s’ e ‘q’. 

- ‘m’ consente di trovare la configurazione finale di una singola particella: il programma chiede  in  input  all’utente  alcuni  dati  relativi  al  biliardo  e  allo  stato  iniziale  della particella, poi calcola posizione e angolo finale (se la particella riesce a uscire dal biliardo, altrimenti viene visualizzato un messaggio di errore). 
- ‘a’ seguito da un numero intero n genera n particelle in modo pseudocasuale e ne trova  la  configurazione  finale. Tutti  i  dati  relativi  al  biliardo  e  ai  parametri  della distribuzione gaussiana di posizione e angolo iniziali delle particelle vengono letti dal programma dal file “input.txt”. In tale file i dati vanno inseriti nel seguente ordine: 
- r1 
- r2 
- l 
- media y iniziale 
- sigma y iniziale 
- media angolo iniziale 
- sigma angolo iniziale 

Il  programma  salva  le  configurazioni  iniziali  delle  particelle  generate  nel  file “outinit.txt” e le configurazioni finali nel file “outfin.txt”. La configurazione finale viene salvata soltanto se la particella esce dal biliardo (dal bordo di destra). Il programma informa comunque l’utente di quante particelle non escono dal biliardo. 

- ‘s’ permette il calcolo delle statistiche, sia per la distribuzione delle particelle in input che per quella delle particelle in output. Prima di utilizzare questo comando bisogna generare un certo numero di simulazioni del moto con il comando ‘a’. I dati salvati in “outinit.txt” e “outfin.txt” verranno anche salvati in due vettori, rispettivamente *input* e *output*. Tali vettori saranno usati per estrarre i dati di cui calcolare le statistiche (con i metodi statistics\_y e statistics\_ang). 
- ‘q’ permette di uscire dal programma. 

**Bibliografia**

[1] Repository Github per il corso di Programmazione per la Fisica [https://github.com/Programmazione-per-la-Fisica/progetto2022/blob/main/biliardo.md ](https://github.com/Programmazione-per-la-Fisica/progetto2022/blob/main/biliardo.md)

**Appendice A: metodi rotate\_forward e rotate\_backward di Particle** 

Il metodo **rotate\_forward** della classe Particle riceve in input un angolo da 0 a 90°, e ruota la direzione del moto della particella in senso antiorario di tale angolo (ossia somma l’angolo in input all’angolo della particella). Nel caso in cui la direzione del moto della particella formi con l’asse x un angolo ottuso, l’angolo che deve avere la particella è il corrispondente angolo acuto negativo (l’angolo della particella con l’asse x va da -90° a 90°). Quindi, se a seguito della rotazione l’angolo della particella supera i 90°, rotate\_forward sottrae 180° a tale angolo, in modo da ottenere un angolo acuto negativo. 

Il metodo **rotate\_backward** è identico, ma la rotazione avviene all’indietro (l’angolo in input viene sottratto), e se l’angolo ottenuto è inferiore a -90°, rotate\_backward aggiunge 180°, in modo da avere un angolo acuto positivo. 

**Appendice B: funzione find\_angle**

La funzione **find\_angle** trova l’angolo acuto positivo tra due rette (ossia due variabili Line fornite in input). L’angolo compreso tra due rette è la differenza tra gli angoli che queste rette formano con l’asse x (angolo che può andare da 0 a 180°). 

L’angolo che una retta forma con l’asse x è l’arcotangente del suo coefficiente angolare. Se tale angolo è però ottuso, l’arcotangente del coefficiente angolare è il corrispondente angolo acuto negativo. Per questo, se il coefficiente angolare della retta è negativo, find\_angle aggiunge 180° a tale angolo, trovando così il corrispondente angolo ottuso positivo. 

Una volta trovati gli angoli che le due rette formano con l’asse, la funzione calcola il valore assoluto della loro differenza, che corrisponde all’angolo compreso tra le due rette. Tale angolo può essere acuto o ottuso, ma la funzione cerca l’angolo acuto. Per questo, se l’angolo è ottuso, la funzione restituisce l’angolo supplementare all’angolo così trovato. 

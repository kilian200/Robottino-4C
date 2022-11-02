# Robottino-4C
Robottino per la classe 4C del Maxwell

Implementa la ricezione di pacchetti UDP dal modulo WiFi (ESP01) configurato come Access Point, e l'inoltro del contenuto (testo) al monitor seriale collegato all'Arduino.

## Procedura di invio
1. usare applicazione "UDP Monitor" (per Android) su telefonino
2. inserire Indirizzo IP dell'Access Point (192.168.4.1) e la porta del UDP Server (4567)
3. inserire testo
4. inviare testo (premendo l'appostio pulsante offerto dall'APP)

Risultato: Monitor Seriale dovrebbe mostrare il testo inviato

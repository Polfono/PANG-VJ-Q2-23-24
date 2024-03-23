# PANG-VJ-Q2-23-24

--- Nom i cognoms dels integrats del grup ---

Fonoyet González, Pol
Parra Ordorica, Gorka

--- Funcionalitats implementades ---

4 pantalles -> Menú principal -> Jugar -> Instruccions -> Crèdits

17 nivells amb configuracions diferents (Blocs, bombolles, música, localitat, etc.)

Bombolles amb gravetat que reboten amb l'escenari i els blocs

Ganxo amb col·lisions amb bombolles i blocs

5 Power-ups, la probabilitat d'aparèixer en destruir una bombolla és del 10%
-> Dinamita, separa totes les bombolles fins a la mida més petita
-> Congelar el temps, durant 5 segons les bombolles no es mouran ni et faran mal
-> Invencibilitat, et dona un escut que et fa resistent a un impacte de bombolla.
-> Temps lent, redueix un 25% la velocitat de moviment de les bombolles
-> Vida extra, afegeix una vida al jugador (Aquest power-up no està al joc original, ha estat afegit per millorar la jugabilitat)

27 Objectes de menjar
-> Apareix un objecte de menjar entre els 10 i 30 primers segons de cada nivell
-> La puntuació que atorga consumir cada objecte de menjar pot anar entre 500 i 50000 depenent la seva raresa

Puntuació
-> Destruir bombolles (segons la seva mida descendent 50, 100, 150, 200)
-> Fer combos de destruir bombolles de la mateixa mida (x2, x4, x8 màxim)
-> Destruir un bloc destructible (500)
-> Consumir objecte de menjar (de 500 a 50000 depenent l'objecte)
-> Temps restant en acabar nivell (x100 del temps restant)

El jugador pot pujar i baixar escales

El jugador rellisca sobre superficies gelades

El jugador perd una vida si el temps del nivell arriba a 0 o és impactat per una bombolla, si no li queden vides perd la partida.

Interfície gràfica que mostra el temps restant, la puntuació acumulada, les vides restants i el nivell en el qual es troba el jugador.

Tecles per saltar contingut
-> Power-ups: 'T' Dinamita, 'Y' Congelar el temps, 'U' Invencibilitat, 'I' Temps lent, 'O' Vida extra
-> Pantalles concretes:
---> '1', '2', '3' ... '9' per saltar al respectiu nivell (No hi ha tecles concretes per nivells posteriors)
---> Alternativament 'N' per anar al següent nivell 'B' per anar a l'anterior
-> Activar/desactivar el God mode 'G' que et faci invulnerable

So
-> Música al menú
-> Música diferent per a cada nivell
-> Efectes especials per a perdre la partida, trencar blocs, ser impactat, agafar un objecte, destruir bombolles,
destruir escut, seleccionar opció, disparar ganxo, completar nivell...

Animacions i transicions en destruir blocs, destruir bombolles, disparar ganxo, finalitzar power-up, moviment de personatge, obtenir puntuació, transició entre nivells i game over, etc.

--- Instruccions del joc ---

Per moure's al menú principal s'utilitzen les fletxes d'adalt i avall '↓' '↑', per seleccionar una opció 'ENTER'.

L'objectiu del joc és aconseguir una alta puntuació i avançar pels diferents nivells.

Per completar un nivell s'haurà d'eliminar totes les bombolles d'aquest. Per a aconseguir-ho, el jugador pot disparar un ganxo amb la tecla 'S' i moure's amb les fletxes '←' '→' '↓' '↑'. Quan el ganxo col·lisiona amb una bombolla, aquesta explota i es divideix en dues bombolles més petites. Les bombolles més petites de totes no es divideixen.

La puntuació es pot aconseguir de diferents maneres, com ara destruir bombolles o consumir menjar.

# Evolution Simulator

As each epoch ends, observe the evolution of a wide variety of species as they struggle to live and consume as much food as they can.

### Rules

- Each species has a set of attributes that determine its behaviour.
- The world is a 2D grid of cells, with each cell representing either a piece of food, an individual or nothing.
- The goal of each species is to consume as much food as possible. Different species have different food requirements for surviving to the next epoch.
- Each epoch, each individual moves randomly, each step being in one of the 8 directions (up, down, left, right, up-left, up-right, down-left, down-right).
- If an individual moves on a cell with food, it consumes it and gets one step closer to fulfilling its food requirement.
- If an individual moves on a cell with a suitor of its type, they mate and produce between 1 and 5 offspring.
- Otherwise, if two individuals meet, both of them continue their movement.
- At the end of each epoch, if an individual has not fulfilled its food requirement, it dies.
- To compute the next generation, the fitness of each species is computed, taking into account the number of individuals of that species spawned at the beginning of the epoch and the number of individuals that survived.
- The fitness of each species is used to determine the number of individuals of that species that will be spawned in the next epoch.
- The simulation pauses automatically when an epoch ends. It can be restarted by the user by pressing the space bar, if they want to observe the evolution of the species in the next epoch.
- The types of individuals that can be spawned are the following:
  - **Keystone's**: they don't have any special abilities, but they need a small quantity of food.
  - **RedBull's**: they are very fast, but they need to eat a lot of food.
  - **Ascendant's**: limited at the beginning, but they get stronger once they eat the first time.
  - **Clairvoyant's**: they can see the food in the cells around them, but they need a large quantity of food.
  - **Suitor's**: they want to mate with a specific type of individual to produce more of their kind.
  
### Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [x] definirea a minim 3-4 clase folosind compunere
- [x] constructori de inițializare
- [x] pentru o clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [x] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [x] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese
- [x] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` exemple de date de intrare de la tastatură (dacă există)
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa de mai sus, constructori virtuali (clone)
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] smart pointers
  - [x] `dynamic_cast`
- [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim 2 clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor, `try`/`catch` în `main`
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] la sfârșit: commit separat cu adăugarea unei noi derivate fără a modifica restul codului
- [ ] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
  - Singleton - clasa Game
  - Factory - clasa CellFactory
  - Strategy - clasa FightingStrategy (**TODO**)
- [x] o funcție șablon (template) cu sens; minim 2 instanțieri
- [x] o clasă șablon cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit

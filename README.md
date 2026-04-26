## A projekt célja
A beadandó célja egy 3D-s adatábrázoló program elkészítése,
amely egy hagyományos adatbázist egy bejárható, futurisztikus városként mutat be.
A program nemcsak vizuálisan érdekes, hanem egy oktató jellegű minijátékot is
tartalmaz, amellyel alapvető adatbázis-lekérdezéseket lehet gyakorolni interaktív módon.

## Hogyan képzelem el a programot

### A látványvilág
A program egy sötét, mátrix hangulatú virtuális térben játszódik.
A talaj egy végtelennek tűnő, világító neonrács, amely megadja a digitális
hálózat alaphangulatát.
A teret köd (fog) teszi atmoszferikussá, a sötét hátteret 
pedig dinamikus, állítható fényforrás világítja meg.

### Az adatok megjelenítése
A térben lévő adatokat 3D-s tornyok vagy oszlopok jelképezik, amelyek egy virtuális várost alkotnak.
* **Fizikai méret:** A tornyok magassága az adott adat értékétől függ. Egy nagyobb szám automatikusan magasabb épületet eredményez.
* **Színkódolás:** A normál, hétköznapi adatok hűvös kék színben világítanak, míg a kiugró értékeket vagy rendszerhibákat meleg, például piros vagy lüktető szín jelzi.
* **Textúra:** Az oszlopokon egy animált, lefelé folyó digitális "Mátrix kód" látható.
* **Lebegés:** Az oszlopok nem a talajon állnak, hanem a levegőben lebegnek.(ütközés még nincs megoldva)

### Interakció és játékmenet (A minijáték)
A városban elszórva találhatók speciális, "titkosított" adatcsomópontok, amelyeket egyedi, lüktető animáció jelöl a térben. 
* **A cél:** A játékos feladata felkutatni 3 ilyen kiemelt csomópontot.
* **A feladat:** Ha a drónnal elég közel repül egy ilyen ponthoz, az **F** gombbal elindul a hackelés. Ekkor egy grafikus terminál ablak ugrik fel a képernyőn egy SQL feladvánnyal.
* **A megoldás:** A játékosnak a billentyűzet **1, 2 vagy 3** gombjaival kell kiválasztania a helyes SQL Injection kódot a terminálon látható opciók közül.
* **A visszajelzés:** Sikeres hackelés esetén a Progress Bar (folyamatjelző) növekszik, és az oszlop zöldre vált. Ha mind a 3 célpont megvan, a rendszer "megtisztul" és kék színben ragyog fel.

### Interakció és játékmenet (A minijáték)
A városban elszórva találhatók speciális, "titkosított" adatcsomópontok, amelyeket egyedi szín jelöl a térben. 
* **A cél:** A játékos feladata felkutatni ezeket a csomópontokat.
* **A feladat:** Ha a drónnal elég közel repül egy ilyen ponthoz, elindul a "feltörés" ha az akció gombot megnyomjuk(f). A program mögött futó fekete terminál ablakban (parancssorban) megjelenik egy kérdés vagy szituáció.
* **A megoldás:** A játékosnak egy valódi adatbázis-lekérdező parancsot (SQL kódot) kell begépelnie a terminálba.(ez volt a cél ezt nem sikerült megvalósítani még)<span style="color:red"> **jelenleg az 1,2,3 gombokkal lehet a válaszokat kiválasztani válaszokat a felugró ablak esetén**</span> 
* **A visszajelzés:** Ha a beírt kód helyes, a rendszer engedélyezi a hozzáférést, és a 3D-s térben a torony színt vált, jelezve a sikeres feltörést. Hibás kód esetén a rendszer megtagadja a hozzáférést.

## Irányítás (Controls)
* **W, A, S, D:** Mozgás (előre, balra, hátra, jobbra)
* **Q, E:** Emelkedés és süllyedés
* **Egér (bal gomb lenyomva):** Körbenézés
* **F:** Hackelés megkezdése a célpontnál
* **1, 2, 3:** Választás a hacker terminálon
* **Numpad + / - :** Fényerő növelése és csökkentése
* **F1:** Súgó ablak megjelenítése

## Hogyan futtassa (How to run)

A projekt fordításához és futtatásához kövesse az alábbi lépéseket:

Győződjön meg róla, hogy minden szükséges fájl megvan hozzá.

Be sure to have all the needed files.

1. **Nyisson egy terminált** a projekt főkönyvtárában (az `assignment` mappában, ahol a `Makefile` is található).
2. **Fordítás:** Adja ki a következő parancsot a forráskód lefordításához:
   ```bash
    make
    main.exe
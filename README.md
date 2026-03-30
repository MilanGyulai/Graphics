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

### Az adatok megjelenítése
A térben lévő adatokat 3D-s tornyok vagy oszlopok jelképezik, amelyek egy virtuális várost alkotnak.
* **Fizikai méret:** A tornyok magassága az adott adat értékétől függ. Egy nagyobb szám automatikusan magasabb épületet eredményez.
* **Színkódolás:** A normál, hétköznapi adatok hűvös kék színben világítanak, míg a kiugró értékeket vagy rendszerhibákat meleg, például piros vagy lüktető szín jelzi.

### A bejárás és mozgás
A felhasználó egy lebegő, repülő drón szerű kameráján keresztül szemléli és járja be a világot.
Szabadon tud manőverezni az adatblokkok között: képes előre-hátra mozogni, oldalazni, emelkedni,
süllyedni és bármilyen irányba körbenézni.

### Interakció és játékmenet (A minijáték)
A városban elszórva találhatók speciális, "titkosított" adatcsomópontok, amelyeket egyedi szín jelöl a térben. 
* **A cél:** A játékos feladata felkutatni ezeket a csomópontokat.
* **A feladat:** Ha a drónnal elég közel repül egy ilyen ponthoz, elindul a "feltörés" folyamat. A program mögött futó fekete terminál ablakban (parancssorban) megjelenik egy kérdés vagy szituáció.
* **A megoldás:** A játékosnak egy valódi adatbázis-lekérdező parancsot (SQL kódot) kell begépelnie a terminálba. 
* **A visszajelzés:** Ha a beírt kód helyes, a rendszer engedélyezi a hozzáférést, és a 3D-s térben a torony színt vált, jelezve a sikeres feltörést. Hibás kód esetén a rendszer megtagadja a hozzáférést.

## Hogyan futtassa (How to run)

A projekt fordításához és futtatásához kövesse az alábbi lépéseket:

Győződjön meg róla, hogy minden szükséges fájl megvan hozzá.

Be sure to have all the needed files.

1. **Nyisson egy terminált** a projekt főkönyvtárában (az `assignment` mappában, ahol a `Makefile` is található).
2. **Fordítás:** Adja ki a következő parancsot a forráskód lefordításához:
   ```bash
    make
    main.exe
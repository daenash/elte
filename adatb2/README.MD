# Adatbázisok 2.

*Gyakorlatvezető: Nikovits Tibor*<br>
*2019 tavasz*

Használt nyelv: **SQL**<br>
ELTE adatbázis: **Aramis**

### **SSH TUNNEL**<br>
Az adatbázis nem az egyetemi hálózaton való eléréséhez SSH tunnelt kell létrehoznunk. Ennek segítségével egy lokális porton keresztül ssh titkosítással tudunk csatlakozni az ELTE szerverére. Különböző felületeken különböző módon kell létrehozni.

**MAC OS**:<br>
Egy egyszerű terminál ablakot nyitunk, és az alábbi kódot használjuk, ahol a: 

- `4444` a lokális portunk
- `aramis.inf.elte.hu:1521` az aramis adatbázis elérhetősége a szerveren
- `caesar_kod` a caesar bejelentkezőnk

```
ssh -N -L 4444:aramis.inf.elte.hu:1521 caesar_kod@caesar.elte.hu
```

## Gyakorlatok és házi feladatok

- [1. gyakorlat feladatok és megoldások](gyakorlatok/gyak_1.sql)
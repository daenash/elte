-- Nikovits tanár úr feladatai
-- Készítette: Gutai Dénes

-- 4. gyakorlat

select dnev, rowid from nikovits.dolgozo;

-- smith rowid-ja: AAATuHAACAAAAI7AAA
select * from nikovits.dolgozo where ROWID=chartorowid('AAATuHAACAAAAI7AAA');

-- Extensek kiírása
select * from dba_extents where owner = 'NIKOVITS'
and segment_name ='CIKK' and segment_type='TABLE';

-- King rowidjából kinyerhető adatok
SELECT dnev, dbms_rowid.rowid_object(ROWID) adatobj, 
        dbms_rowid.rowid_relative_fno(ROWID) fajl,
        dbms_rowid.rowid_block_number(ROWID) blokk,
        dbms_rowid.rowid_row_number(ROWID) sor
FROM nikovits.dolgozo WHERE dnev = 'KING';

-- Hány különböző blokkban tárolódnak a cikk tábla rekordjai
SELECT distinct dbms_rowid.rowid_object(ROWID) adatobj, 
        dbms_rowid.rowid_relative_fno(ROWID) fajl,
        dbms_rowid.rowid_block_number(ROWID) blokk
FROM nikovits.cikk;
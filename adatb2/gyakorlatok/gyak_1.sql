-- Nikovits tanár úr feladatai
-- Készítette: Gutai Dénes

-- 1. gyakorlat

-- Adatbázis objektumok

-- 1. feladat
-- Kinek a tulajdonában van a DBA_TABLES nevű nézet (illetve a DUAL nevű tábla)? (owner)
select distinct owner from dba_objects
where object_name = 'DBA_TABLES' or object_name='DUAL';

-- 2. feladat
-- Kinek a tulajdonában van a DBA_TABLES nevű szinonima (illetve a DUAL nevű)? (owner)
select distinct owner from dba_synonyms
where synonym_name = 'DBA_TABLES' or synonym_name = 'DUAL';

-- 3. feladat
-- Milyen típusú objektumai vannak az orauser nevű felhasználónak az adatbázisban? (object_type)
select distinct object_type from dba_objects
where upper(owner) = 'ORAUSER';

-- 4. feladat
-- Hány különböző típusú objektum van nyilvántartva az adatbázisban? (darab)
select count(distinct object_type) "Különböző objektumoktípusok" from dba_objects;

-- 5. feladat
-- Melyek ezek a típusok? (object_type)
select distinct object_type from dba_objects;

-- 6. feladat
-- Kik azok a felhasználók, akiknek több mint 10 féle objektumuk van? (owner)
select owner from dba_objects
group by owner
having count(*) > 10;

-- 7. feladat
-- Kik azok a felhasználók, akiknek van triggere és nézete is? (owner)
select distinct owner from dba_objects 
where upper(object_type) = 'TRIGGER'
intersect
select distinct owner from dba_objects
where upper(object_type) = 'VIEW';

-- 8. feladat
-- Kik azok a felhasználók, akiknek van nézete, de nincs triggere? (owner)
select distinct owner from dba_objects
where upper(object_type) = 'VIEW'
minus
select distinct owner from dba_objects
where upper(object_type) = 'TRIGGER';

-- 9. feladat
-- Kik azok a felhasználók, akiknek több mint 40 táblájuk, de maximum 37 indexük van? (owner)
select owner from dba_objects
where upper(object_type) = 'VIEW'
group by owner
having count(*) > 40
intersect
select owner from dba_objects
where upper(object_type) = 'INDEX'
group by owner
having count(*) <= 37;

-- 10. feladat
-- Melyek azok az objektum típusok, amelyek tényleges tárolást igényelnek,
-- vagyis tartoznak hozzájuk adatblokkok? (object_type)
select distinct object_type from dba_objects
where data_object_id is not null;

-- 11. feladat
-- Melyek azok az objektum típusok, amelyek nem igényelnek tényleges tárolást, vagyis nem
-- tartoznak hozzájuk adatblokkok? (object_type)
select distinct object_type from dba_objects
where data_object_id is null;

-- 12. feladat
-- Keressük meg az utóbbi két lekérdezés metszetét. (object_type)
select distinct object_type from dba_objects
where data_object_id is not null
intersect
select distinct object_type from dba_objects
where data_object_id is null;

-- Táblák oszlopai

-- 13. feladat
-- Hány oszlopa van a nikovits.emp táblának? (darab)
select count(*) "Táblák száma" from dba_tab_columns
where table_name = 'EMP' and owner = 'NIKOVITS';

-- 14. feladat
-- Milyen típusú a nikovits.emp tábla 6. oszlopa? (data_type)
select data_type from dba_tab_columns
where table_name = 'EMP' and owner = 'NIKOVITS' and column_id = 6;

-- 15. feladat
-- Adjuk meg azoknak a tábláknak a tulajdonosát és nevét, amelyeknek van 'Z' betűvel
-- kezdődő oszlopa. (owner, table_name)
select distinct owner, table_name from dba_tab_columns
where column_name like 'Z%';

-- 16. feladat
-- Adjuk meg azoknak a tábláknak a tulajdonosát és nevét, amelyeknek legalább 8 
-- darab dátum tipusú oszlopa van. (owner, table_name)
select owner as o1, table_name as t1
from dba_tab_columns
where data_type = 'DATE'
group by owner, table_name
having count(*) > 8;

-- 17. feladat
-- Adjuk meg azoknak a tábláknak a tulajdonosát és nevét, amelyeknek 1. es 4. oszlopa is
-- VARCHAR2 tipusú, az oszlop hossza mindegy. (owner, table_name)
select owner, table_name from dba_tab_columns
where data_type = 'VARCHAR2' and column_id = 1
intersect
select owner, table_name from dba_tab_columns
where data_type = 'VARCHAR2' and column_id = 4;


-- PL/SQL

-- Írjunk meg egy PLSQL procedúrát, amelyik a paraméterül kapott karakterlánc alapján 
-- kiírja azoknak a tábláknak a nevét és tulajdonosát, amelyek az adott karakterlánccal 
-- kezdődnek.

SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE table_print(p_kar VARCHAR2) 
IS
BEGIN
    dbms_output.put_line('Tulajdonos, Táblanév');
    FOR table_row IN (
        select owner as o, table_name as t from dba_tables
        where upper(table_name) like upper(p_kar)||'%'
    )
    LOOP
        dbms_output.put_line(table_row.o || ', ' || table_row.t);
    end LOOP;
END;
/

EXECUTE table_print('DOL');


-- Házi feladat
-- Írjunk meg egy plsql procedúrát, amelyik a paraméterül kapott táblára kiírja 
-- az őt létrehozó CREATE TABLE utasítást. 

-- Teszt tábla
CREATE TABLE tipus_proba(
c10 CHAR(10) DEFAULT 'bubu',
vc20 VARCHAR2(20),
nc10 NCHAR(10), 
nvc15 NVARCHAR2(15),
blo BLOB,
clo CLOB,
nclo NCLOB,
num NUMBER,
num10_2 NUMBER(10,2), 
num10 NUMBER(10) DEFAULT 100,
flo FLOAT,
bin_flo binary_float DEFAULT '2e+38', 
bin_doub binary_double DEFAULT 2e+40,
dat DATE DEFAULT TO_DATE('2007.01.01', 'yyyy.mm.dd'),
rid ROWID
);

-- Procedúra létrehozása / felülírása
CREATE OR REPLACE PROCEDURE cr_tab(p_owner VARCHAR2, p_tabla VARCHAR2) 
IS
output_string varchar2(1000) := '';
row_count NUMBER(20) := 0;
BEGIN
    -- Kiválasztjuk hány sora van a táblának, hogy tudjuk mikor nem kell már vesszővel elválasztani az oszlopokat
    select count(*) into row_count from dba_tab_columns
    where upper(table_name) = upper(p_tabla)
    and upper(owner) = upper(p_owner);

    -- Elkezdjük kiírni az utasítást
    dbms_output.put_line('CREATE TABLE ' || p_tabla || '(');

    -- Végigiterálunk a megtalált tábla oszlopain növekvő sorrendben
    FOR c IN (
        select column_name as c_name, data_type as c_type, data_default as c_default, data_length as c_length, column_id as c_id
        from dba_tab_columns
        where upper(table_name) = upper(p_tabla)
        and upper(owner) = upper(p_owner)
        order by column_id
    )
    LOOP
        output_string := lower(c.c_name) || ' ' || upper(c.c_type) || '(' || c.c_length || ')';

        -- Ha van DEFAULT érték, akkor hozzáadjuk
        IF c.c_default is not null THEN
            output_string := output_string || ' DEFAULT ' || c.c_default;
        END IF;
        
        -- Ha nem az utolsó sor, vesszővel elválasztjuk őket
        IF c.c_id < row_count THEN
            output_string := output_string || ',';
        END IF;
        
        dbms_output.put_line(output_string);
    end LOOP;
    dbms_output.put_line(');');
END;
/

-- A procedúra futtatása
-- EXECUTE cr_tab('NEPTUN_KÓD','tipus_proba');
EXECUTE cr_tab('jag5ds','tipus_proba');

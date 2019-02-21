-- 2. gyakorlat

-- Hozzunk létre egy szekvenciát, amelyik az osztály azonosítókat fogja generálni
-- a számunkra. Minden osztály azonosító a 10-nek többszöröse legyen.
drop sequence osztaly_azon;
CREATE SEQUENCE osztaly_azon
    start with 10
    increment by 10;

-- osztály tábla
drop table osztaly;
create table osztaly(
    nev varchar2(30),
    azon number primary key
);

-- dolgozó tábla
drop table dolgozo;
create table dolgozo(
    nev Varchar2(30),
    oazon number,
    foreign key (oazon) references osztaly(azon)
);

insert into osztaly values('osztaly1',osztaly_azon.nextval);
insert into dolgozo values('béla1',osztaly_azon.currval);

insert into osztaly values('osztaly2',osztaly_azon.nextval);
insert into dolgozo values('béla2',osztaly_azon.currval);
insert into dolgozo values('géza2',osztaly_azon.currval);
insert into dolgozo values('károly2',osztaly_azon.currval);

insert into osztaly values('osztaly3',osztaly_azon.nextval);
insert into dolgozo values('károly3',osztaly_azon.currval);
insert into dolgozo values('géza3',osztaly_azon.currval);

select * from osztaly o,dolgozo d where o.azon = d.oazon;
 
 
-- adatbáziks linkek
drop database link ullman;
CREATE DATABASE LINK ullman CONNECT TO jag5ds IDENTIFIED BY jag5ds
USING 'ullman.inf.elte.hu:1521/ullman';

select orszag.nev
from NIKOVITS.VILAG_ORSZAGAI@ullman orszag, NIKOVITS.FOLYOK folyo
where folyo.nev='Duna'
and folyo.orszagok like '%'||orszag.tld||'%';


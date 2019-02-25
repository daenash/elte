-- Nikovits tanár úr feladatai
-- Készítette: Gutai Dénes

-- 3. gyakorlat

-- Adattárolással kapcsolatos fogalmak

-- 1.
-- ...
-- ...


-- 9.
-- foglalt méret
select count(*), sum(e.bytes) 
from DBA_DATA_FILES f, DBA_EXTENTS e
where f.file_id = e.file_id and f.file_name like '%users02.dbf';


-- szabad méret
select count(*), sum(e.bytes) 
from DBA_DATA_FILES f, dba_free_space e
where f.file_id = e.file_id and f.file_name like '%users02.dbf';


-- százalékos szabad méret
select round((sum(e.bytes) / f.bytes),2) * 100
from DBA_DATA_FILES f, DBA_EXTENTS e
where f.file_id = e.file_id and f.file_name like '%users02.dbf'
group by f.bytes;

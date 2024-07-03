drop view if exists venditearticolo;
create view venditearticolo (articolomusicale, somma) as
select pa.articolomusicale, sum(pa.prezzotot) as somma -- prezzi delle vendite di febbraio per articolo
from (select cat.articolomusicale, reg.quantita * cat.prezzo as prezzotot -- prezzi per vendita di ogni articolo
		from (select * -- vendite di febbraio
				from scontrino as s
				where s.data >= '2024-02-01' and s.data <= '2024-02-29') as vf, registro as reg, catalogo as cat
		where vf.data = reg.datascontrino and vf.ora = reg.orascontrino and reg.catalogo = cat.articolomusicale) as pa
group by pa.articolomusicale;

select prod.artista	
from (select va.articolomusicale, va.somma -- articolo musicale con somma massima		
		from venditearticolo as va
		where va.somma = (select max(somma) from venditearticolo)) as art, produzione as prod
where art.articolomusicale = prod.articolomusicale

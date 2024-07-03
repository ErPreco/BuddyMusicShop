select ed.nome, count(*) as numerovinili
from vinile as vin, articolomusicale as am, etichettadiscografica as ed
where vin.articolomusicale = am.codicearticolo and am.etichettadiscografica = ed.nome
group by ed.nome
order by numerovinili desc

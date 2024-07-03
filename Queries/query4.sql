select sco.cliente, sum(cat.prezzo) spesatotale
from scontrino as sco, registro as reg, catalogo as cat
where sco.data = reg.datascontrino and sco.ora = reg.orascontrino and reg.catalogo = cat.articolomusicale and
        sco.cliente is not null
group by sco.cliente
having sum(cat.prezzo) > 100
order by spesatotale desc
select gen.tipo as genere, count(*) as quantita
from scontrino as sco, registro as reg, catalogo as cat, articolomusicale as am, genere as gen
where sco.data = reg.datascontrino and sco.ora = reg.orascontrino and reg.catalogo = cat.articolomusicale and
        cat.articolomusicale = am.codicearticolo and am.genere = gen.tipo
group by gen.tipo
order by quantita desc

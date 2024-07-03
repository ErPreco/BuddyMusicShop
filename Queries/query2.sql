select codicearticolo, descrizione, etichettadiscografica, codicebundle
from (select *
        from evento
        where data = (select min(data) from evento where numeroarticolivenduti is null)) as prossimoevento
    join articolomusicale on prossimoevento.genere = articolomusicale.genere
order by etichettadiscografica desc

select producer.nome, producer.cognome, cdsel.etichettadiscografica
from (select *
		from articolomusicale as am join cd on am.codicearticolo = cd.articolomusicale
		where am.nome = 'Golden Hour') as cdsel, produzione, artista as art, collaborazione as collab, producer
where cdsel.codicearticolo = produzione.articolomusicale and produzione.artista = art.nomearte and
		art.nomearte = collab.artista and collab.producer = producer.codicefiscale
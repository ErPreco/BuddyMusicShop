drop index if exists data_scontrino_idx_btree;
drop index if exists ora_scontrino_idx_hash;
drop index if exists data_registro_idx_hash;
drop index if exists ora_registro_idx_hash;
drop index if exists catalogo_registro_idx_hash;
drop index if exists articolomusicale_catalogo_idx_hash;

create index data_scontrino_idx_btree on scontrino(data);
create index ora_scontrino_idx_hash on scontrino using hash(ora);
create index data_registro_idx_hash on registro using hash(datascontrino);
create index ora_registro_idx_hash on registro using hash(orascontrino);
create index catalogo_registro_idx_hash on registro using hash(catalogo);
create index articolomusicale_catalogo_idx_hash on catalogo using hash(articolomusicale);

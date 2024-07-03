drop table if exists EtichettaDiscografica cascade;
drop table if exists Genere cascade;
drop table if exists Settore cascade;
drop table if exists ArticoloMusicale cascade;
drop table if exists Vinile cascade;
drop table if exists CD cascade;
drop table if exists CassettaAudio cascade;
drop table if exists Artista cascade;
drop table if exists Produzione cascade;
drop table if exists Producer cascade;
drop table if exists Collaborazione cascade;
drop table if exists Evento cascade;
drop table if exists Catalogo cascade;
drop table if exists Cliente cascade;
drop table if exists Prenotazione cascade;
drop table if exists Ordine cascade;
drop table if exists Scontrino cascade;
drop table if exists Registro cascade;

drop type if exists giriVinile;
drop type if exists condizioneVinile;
drop type if exists formatoLogicoCD;
drop type if exists formatoCassettaAudio;
drop type if exists nastroCassettaAudio;

drop domain if exists uint;
create domain uint as smallint check (value >= 0);

create table Genere (
	tipo varchar(12) primary key
);

create table EtichettaDiscografica (
	nome varchar(40) primary key,
	sede varchar(20) not null
);

create table Settore (
	etichettaDiscografica varchar(40) references EtichettaDiscografica(nome) on update cascade on delete no action,
	genere varchar(12) references Genere(tipo) on update no action on delete no action,
	primary key(etichettaDiscografica, genere)
);

create table ArticoloMusicale (
	codiceArticolo char(8) primary key,
	nome varchar(50) not null,
	descrizione varchar(200) not null,
	genere varchar(12) not null references Genere(tipo) on update no action on delete no action,
	etichettaDiscografica varchar(40) references EtichettaDiscografica(nome) on update cascade on delete no action,
	codiceBundle char(8) references ArticoloMusicale(codiceArticolo) on update cascade on delete set null
);

create type giriVinile as enum ('33', '45');
create type condizioneVinile as enum ('pessimo', 'buono', 'ottimo');
create table Vinile (
	articoloMusicale char(8) primary key references ArticoloMusicale(codiceArticolo) on update no action on delete no action,
	giri giriVinile not null,
	condizioneCopertina condizioneVinile not null,
	condizioneDisco condizioneVinile not null
);

create type formatoLogicoCD as enum ('CD-Audio', 'ISO 9660', 'Apple-ISO (HFS)');
create table CD (
	articoloMusicale char(8) primary key references ArticoloMusicale(codiceArticolo) on update no action on delete no action,
	rpm uint not null,
	formatoLogico formatoLogicoCD not null
);

create type formatoCassettaAudio as enum ('C46', 'C60', 'C90', 'C120');
create type nastroCassettaAudio as enum ('IEC I', 'IEC II', 'IEC III', 'IEC IV');
create table CassettaAudio (
	articoloMusicale char(8) primary key references ArticoloMusicale(codiceArticolo) on update no action on delete no action,
	formato formatoCassettaAudio not null,
	tipoNastro nastroCassettaAudio not null
);

create table Artista (
	nomeArte varchar(30) primary key,
	nome varchar(15),
	cognome varchar(15),
	nazionalita varchar(3) not null
);

create table Produzione (
	articoloMusicale char(8) references ArticoloMusicale(codiceArticolo) on update no action on delete no action,
	artista varchar(30) references Artista(nomeArte) on update cascade on delete no action,
	primary key(articoloMusicale, artista)
);

create table Producer (
	codiceFiscale char(16) primary key,
	nome varchar(15) not null,
	cognome varchar(15) not null,
	etichettaDiscografica varchar(40) references EtichettaDiscografica(nome) on update cascade on delete no action
);

create table Collaborazione (
	artista varchar(30) references Artista(nomeArte) on update cascade on delete no action,
	producer char(16) references Producer(codiceFiscale) on update no action on delete no action,
	primary key(artista, producer)
);

create table Evento (
	data date primary key,
	genere varchar(12) not null references Genere(tipo) on update no action on delete no action,
	sconto numeric not null check (sconto > 0 and sconto <= 1),
	numeroArticoliVenduti uint
);

create table Catalogo (
	articoloMusicale char(8) primary key references ArticoloMusicale(codiceArticolo) on update no action on delete no action,
	quantita uint not null,
	prezzo numeric not null,
	quantitaArrivo uint not null,
	prezzoAcquisto numeric not null
);

create table Cliente (
	email varchar(40) primary key,
	nome varchar(15) not null,
	numeroTelefono char(10) not null
);

create table Prenotazione (
	data date,
	ora time,
	cliente varchar(40) references Cliente(email) on update cascade on delete cascade,
	acconto numeric not null,
	primary key(data, ora)
);

create table Ordine (
	data date,
	ora time,
	catalogo char(8) references Catalogo(articoloMusicale) on update no action on delete no action,
	quantita uint not null,
	primary key(data, ora, catalogo),
	foreign key(data, ora) references Prenotazione(data, ora) on update no action on delete cascade
);

create table Scontrino (
	data date,
	ora time,
	cliente varchar(40) references Cliente(email) on update cascade on delete set null,
	primary key(data, ora)
);

create table Registro (
	dataScontrino date,
	oraScontrino time,
	catalogo char(8) references Catalogo(articoloMusicale) on update no action on delete no action,
	quantita uint not null,
	primary key(dataScontrino, oraScontrino, catalogo),
	foreign key(dataScontrino, oraScontrino) references Scontrino(data, ora) on update no action on delete cascade
);

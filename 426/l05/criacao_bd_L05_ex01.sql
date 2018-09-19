/*
*
* Lista 05 exercicio 1
* Bruno Ferrero
*
*/


-- psql l05e01

-- a)
create domain tipo_cpf as numeric (11,0);
create domain tipo_nusp as numeric (9,0);
create domain tipo_codigo as varchar (7);

create table PESSOA (
    nusp tipo_nusp,
    nome varchar (50) NOT NULL,
    cpf tipo_cpf unique NOT NULL,
    primary key (nusp)
    );

create table PROFESSOR (
    nusp tipo_nusp unique,
    sala integer NOT NULL,
    foreign key (nusp) references PESSOA (nusp)
    );

create table ALUNO (
    id_aluno integer,
    primary key (id_aluno)
);

create table ALUNO_REGULAR (
    nusp_aluno tipo_nusp,
    curso varchar (50) NOT NULL DEFAULT 'Bacharelado em Computação',
    nusp_prof tipo_nusp,
    id_aluno integer NOT NULL,
    CONSTRAINT Ch_id foreign key (id_aluno) references ALUNO (id_aluno),
    CONSTRAINT Ch_nusp foreign key (nusp_aluno) references PESSOA (nusp),
    CONSTRAINT Ch_prof foreign key (nusp_prof) references PROFESSOR (nusp)
    );

create table ALUNO_ESPECIAL (
    id_aluno integer,
    email varchar (50),
    foreign key (id_aluno) references ALUNO (id_aluno)
    );

create table DISCIPLINA (
    codigo tipo_codigo,
    nome varchar (50) NOT NULL,
    primary key (codigo)
    );

create table PRE_REQUISITO (
     cod_disc tipo_codigo,
     cod_disc_pre_requisito tipo_codigo,
     CONSTRAINT Ch_disc foreign key (cod_disc) references DISCIPLINA (codigo),
     CONSTRAINT Ch_disc_pre foreign key (cod_disc_pre_requisito) references DISCIPLINA (codigo)
     );

create table MINISTRA (
    nusp_prof tipo_nusp,
    cod_disc tipo_codigo,
    semestre_ano varchar(7) DEFAULT '01_0000',
    primary key (nusp_prof,cod_disc,semestre_ano),
    foreign key (nusp_prof) references PROFESSOR (nusp),
    foreign key (cod_disc) references DISCIPLINA (codigo)
    );

create table MATRICULA (
    nusp_prof tipo_nusp,
    cod_disc tipo_codigo,
    semestre_ano varchar(7) DEFAULT '01_0000',
    id_aluno integer,
    frequencia integer 
	CHECK (frequencia >= 0 AND frequencia <= 100),
    nota integer
	CHECK (nota >= 0 and nota <= 10),
    situacao varchar(14)  NOT NULL 
    	CHECK ((situacao='aprovado' AND frequencia >= 75 AND nota >= 5) OR situacao='reprovado' OR situacao='em recuperacao' )
    );

-- b)
alter table MATRICULA add column dtMatricula date;

-- c)
alter table MATRICULA add constraint ChP primary key (nusp_prof,cod_disc,semestre_ano,id_aluno);
alter table MATRICULA add constraint ChE foreign key (nusp_prof,cod_disc,semestre_ano) references MINISTRA;

-- d)
alter table ALUNO_REGULAR alter column curso drop DEFAULT;

/*
*
* Lista 05 exercicios 2 e 3
* Bruno Ferrero
*
*/

-- psql CooperAgri 

-- Exercício 2

-- a) Liste os nomes dos restaurantes que ficam em Santo André.
select nomer from restaurante where cidader='Santo André'; 

-- b) Liste todas as informacoes dos produtos cujo nome comecam com a letra 'c' e cujo o preco do por quilo e inferior a R$3,00
select * from produto where nomep like 'c%' and precoquilo < 3;

-- c) Liste os codigos dos agricultores que ja entregaram produtos para o restaurante RU-USP.
select distinct coda from entrega 
	where codr in 
	(select codr from restaurante where nomer='RU-USP');

-- d) Liste os nomes dos produtos que ja foram alguma vez entregues por um agricultor de Mogi das Cruzes.
select nomep from produto 
	where codp in 
	(select codp from entrega where coda in 
		(select coda from agricultor where cidadea='Mogi das Cruzes'));

-- e) Liste os codigos dos agricultores que ja entregaram batatas e tambem ja entregaram cebolas.
(select coda from entrega where codp in (
	select codp from produto where nomep='batata'))
INTERSECT
(select coda from entrega e2 where codp in (
	select codp from produto where nomep='cebola'));

-- f) Liste os codigos dos agricultores que ja entregaram batatas, mas nunca entregaram cebolas.
(select coda from entrega where codp in (
	select codp from produto where nomep='batata'))
EXCEPT
(select coda from entrega e2 where codp in (
	select codp from produto where nomep='cebola'));

-- g) Liste todas as triplas (codigo do agricultor, codigo do produto, codigo restaurante) extraidas de Entrega tais que o agricultor e o restaurante estejam na mesma cidade.
select coda,codp,codr from entrega where coda in 
	(select coda from agricultor where cidadea in 
		(select cidader from restaurante)
	);

-- h) Obtenha o numero total de restaurantes ja supridos pelo agricultor “Machado de Assis”.
select distinct count(codr) from entrega where coda in 
    (select coda  from agricultor where nomea='Machado de Assis');

-- i) Liste os nomes das cidades onde ao menos um agricultor ou um restaurante esteja localizado.
(select cidadea from agricultor)
union
(select cidader from restaurante);

-- j) Obtenha o numero de produtos que sao fornecidos ou por um agricultor de Sao Paulo ou para um restaurante em Sao Paulo.
select distinct count(codp) from entrega where coda in 
    (select coda from agricultor where cidadea='São Paulo') 
    or codr in 
        (select codr from restaurante where cidader='São Paulo');

-- k) Obtenha pares do tipo (codigo do agricultor, codigo do produto) tais que o agricultor indicado nunca tenha fornecido o produto indicado.
select coda, codp, coda, codp from entrega; -- incompleta

-- l) Obtenha os codigos dos produtos e suas respectivas quantidades medias por entrega para os produtos que sao fornecidos em uma quantidade media por entrega superior a 30 quilos.
select codp, avg(qtdequilos) media from entrega 
	group by codp having avg(qtdequilos)>30;

-- m) Obtenha o(s) nome(s) dos produtos mais fornecidos a restaurantes (ou seja, os produtos dos quais as somas das quantidades ja entregues e a maior possivel).
select codp, sum(qtdequilos) soma_kg from entrega group by codp order by soma_kg desc limit 1;

-- n) Obtenha o nome do(s) agricultor(es) que fez(fizeram) a entrega de produtos mais antiga registrada no BD.
select nomea from agricultor where coda in (
	select coda from entrega order by dataentrega limit 2);

-- o) Liste os nomes dos produtos que sao oferecidos a todos os restaurantes do BD. Ou seja, um produto nao deve aparecer na lista se houver um restaurante que nunca o tenha recebido.

-- p) Liste todos os pares possiveis do tipo (i,j) tal que i e o nome de um agricultor, j é o nome de um restaurante e i já entregou um produto para j. Mas atencao: o nome de todos os agricultores cadastrados no BD deve aparecer no conjunto resposta. Se um agricultor nunca fez uma entrega, entao o seu nome deve vir acompanhado de NULL no conjunto resposta.
select agricultor.nomea, sub.nomer from agricultor natural left outer join 
    (select agricultor.nomea, restaurante.nomer from entrega, agricultor, restaurante 
    where entrega.coda=agricultor.coda and entrega.codr = restaurante.codr) as sub;

-- Exercício 3

-- a) Insira no BD um novo agricultor de codigo 111, que possui nome “Fulano de Tal” e cuja cidade nao se sabe qual e.
insert into Agricultor values (111, 'Fulano de Tal');

-- b)Reduza em 15% o preco por quilo de todas as variedades de tomate presentes na tabela Produto (ou seja, de todos os produtos cujo nome comeca com a palavra “tomate”).
update produto set precoquilo=precoquilo*0.85 where nomep like 'tomate%';

-- c) Remova no BD todos os produtos que nunca foram entregues a nenhum restaurante.
delete from produto where codp in (
	(select codp from produto) 
	except 
	(select codp from entrega));

-- d) Insira no BD o seguinte fato: o agricultor de codigo 111 forneceu ao RU-USP na data de hoje 50 kg de cada um dos produtos que tem preco menor que R$ 2,00.
insert into entrega (
	select 111 as CodA, CodP, 3005 as CodR, current_timestamp as DataEntrega,50 as QtdeQuilos 
	from produto where precoquilo < 2);

clear all; close all; clc;

%caso01.dat
in = fopen('caso01.dat', 'w');
a = [12 -51 4; 6 167 -68; -4 24 -41];
n=length(a);
fprintf (in, '%d %d\n', n, n);
for i=1:n
    for j=1:n
        fprintf (in, '%d %d %5.4f\n', i-1,j-1, a(i,j));
    end
end

b = [1 1 1];
for i=1:n
    fprintf (in, '%d %5.4f\n', i-1, b(i));
end
fclose(in);

%caso02.dat
clear all; close all;
n = 100;
x = randi([-1000 1000],n,n);
Q = orth(x);
R = triu(randn(n));
a = Q*R;
b=randi([1 100], n,1);

in = fopen('caso02.dat', 'w');
fprintf (in, '%d %d\n', n, n);
for i=1:n
    for j=1:n
        fprintf (in, '%d %d %5.4f\n', i-1,j-1, a(i,j));
    end
end

for i=1:n
    fprintf (in, '%d %5.4f\n', i-1, b(i));
end
fclose(in);

%caso03.dat
clear all; close all;
n = 1000;
x = randi([-1000 1000],n,n);
Q = orth(x);
R = triu(randn(n));
a = Q*R;
b = randi([1 100], n,1);

in = fopen('caso03.dat', 'w');
fprintf (in, '%d %d\n', n, n);
for i=1:n
    for j=1:n
        fprintf (in, '%d %d %5.4f\n', i-1,j-1, a(i,j));
    end
end

for i=1:n
    fprintf (in, '%d %5.4f\n', i-1, b(i));
end
fclose(in);

%polinomio: f(t)
clear all; close all;
m=100;
n=2;
t=linspace(1,50,m);
f = 3.5 + 2.7.*t;
ruido = randn (1,m); 
b = f + ruido;
s = ones (m,1);
a = [s t'];

in = fopen('caso04.dat', 'w');
fprintf (in, '%d %d\n', m, n);
for i=1:m
    for j=1:n
        fprintf (in, '%d %d %5.4f\n', i-1,j-1, a(i,j));
    end
end

for i=1:m
    fprintf (in, '%d %5.4f\n', i-1, b(i));
end
fclose(in);

p = 3.317559 + 2.707609.*t;

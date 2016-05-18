#!/usr/bin/perl -w

use strict;

my (%pontos, %saldoGols);
my ($paisA, $paisB);
while (<>)
{
    chomp $_;
    my @linha = split " x ", $_;
    my @timeA = split " ", $linha[0];
    my @timeB = split " ", $linha[1];
    my $golsA = pop @timeA;
    my $golsB = shift @timeB;
    $paisA = join " ", @timeA;
    $paisB = join " ", @timeB;

    if (!defined $pontos{$paisA}) {
        $pontos{$paisA} = 0;
        $saldoGols{$paisA} = 0;
    }
    if (!defined $pontos{$paisB}) {
        $pontos{$paisB} = 0;
        $saldoGols{$paisB} = 0;
    }
    if ($golsA > $golsB) {
        $pontos{$paisA} += 3;
    }
    elsif ($golsA == $golsB) {
        $pontos{$paisA} += 1;
        $pontos{$paisB} += 1;
    }
    else {
         $pontos{$paisB} += 3;
    }
    $saldoGols{$paisA} += ($golsA - $golsB);
    $saldoGols{$paisB} += ($golsB - $golsA);
}

my @paises = sort {$pontos{$a} <=> $pontos{$b}} keys %pontos;
foreach my $chave (reverse @paises) {
    print $chave . " " . $pontos{$chave} . " " . $saldoGols{$chave} . "\n";
}



#!/usr/bin/perl -w


# usando regex

use strict;

my (%pontos, %saldoGols);
my ($paisA, $paisB, $golsA, $golsB);
while (<>)
{
    chomp $_;
    if ($_ =~ /([A-Za-z\sA-Za-z]+)(\s\d+)\s(\w?).*(\d+)\s([A-Za-z\s]+)/) {
        $paisA = $1; 
        $paisB = $5;
        $golsA = $2;
        $golsB = $4;
    }
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
    elsif ($golsB > $golsA) {
         $pontos{$paisB} += 3;
    }
    $saldoGols{$paisA} += ($golsA - $golsB);
    $saldoGols{$paisB} += ($golsB - $golsA);
}
my @paises = sort {$pontos{$a} <=> $pontos{$b}} keys %pontos;
foreach my $chave (reverse @paises) {
    print $chave . " " . $pontos{$chave} . " " . $saldoGols{$chave} . "\n";
}




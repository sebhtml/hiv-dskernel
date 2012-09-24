#!/usr/bin/perl
use warnings;
use strict;

my $file= $ARGV[0] ;
print( $file."\n");

open(FILE,$file);

my %distribution=();
while(<FILE>){
	my $line=$_;
	my @fields=split("\t",$line);
	my $sequence=$fields[2];
	my $length=length($sequence);
	$distribution{$length}++;

}

close(FILE);

my @lengths=keys(%distribution);

for(my $i=0;$i<@lengths;$i++){
	my $length=$lengths[$i];
	my $density=$distribution{$length};
	print $length." ".$density."\n";
}

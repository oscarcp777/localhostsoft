#! /usr/bin/perl
sub saludo{
	print "@_";
}
&saludo("Hola mundo","feo\n");
sub Suma
{
$Total="aca se usa \n"
}
# Llamada a la subrutina con 2 parámetros.
print &Suma (2,3);

exit 1;
print "holamundo \n";
$var=12122122;
print "$var \n";
@num=(1,9);

@animal=("hola","chau","adios",@num);
push(@animal,"mundo cruel");
print "@animal\n";
$sale=pop(@animal);
print "$sale\n";
unshift(@animal,"caballo");
$sale=shift(@animal);
print "$sale\n";
print "$#animal\n";

foreach $iter (@animal){
	print "que hay : $iter\n";
}
%hash=(1,"lunes1",2,"lunes2",3,"lunes3",4,"lunes4",5,"lune5",6,"lunes6");
%hash2=(lunes1 =>2,lunes2=>3,lunes3=>4,lunes4=>5,lune5=>6,lunes6=>7);

print "$hash{5}\n";
print "$hash2{lunes1}\n";
$hash2{lunes1}="100";
print "$hash2{lunes1}\n";
delete $hash{1};
print values(%hash2);
print "\n";
print sort(keys(%hash2));

print each(%hash);

$existe=exists $hash{4};
print "existe  $existe\n";
$existe=defined $hash2{lunes1};
print "#"x30;
print "\n";
 foreach $iter (keys %hash){
 	print "$iter : $hash{$iter} \n";
 }
 $cadena="hola este mundo cruel ";
 
 if($cadena =~ /^hola|este/){
 	print "encontro la palabra\n";
 } 
 if($cadena =~ /mund?/){
 	print "encontro la palabra\n";
 } 
$_="el oso es peresoso";
if(/oso/){
	print "encontro la palabra oso \n";
}
s/oso/asa/g;
print "$_\n";

$registro="oscar,caceres,paredes,Av entre rios 1629,93862910,2303930303030,uml";
@campos=split(/,/,$registro);
foreach $campo (@campos){
	print "$campo\n";
}
$reg=join("|",@campos);
open(ARCH,">>empleados.txt");
 print ARCH "$reg\n";
 close(ARCH);
 open(ARCH,"empleados.txt");
 @registros=<ARCH>;
foreach $reg (@registros){
	print "$reg";
}
 close(ARCH);
 
 

 
 


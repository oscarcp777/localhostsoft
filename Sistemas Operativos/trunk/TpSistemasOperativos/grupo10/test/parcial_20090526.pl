#! /usr/bin/perl
$cantArg=4;
if($cantArg < 3){
	die "error en la cantidad de parametros \n";
	exit 1;
}
$arch="datos.prd"; ##$ARGV[0];
$separador=";";#$ARGV[1];
$posCantidad=4;#$ARGV[2];
$posProducto=5;#$ARGV[3];
if($posCantidad == $posProducto || $posCantidad <= 0 || $posProducto <= 0){
	die "error pocisiones de cantidad y producto invalidas \n";
	exit 2;
}
open FILE, "<", $arch or die "no se pudo abrir el archivo o no existe \n";
@registros=<FILE>;
if($#registros == -1){
	die " archivo vacio \n";
}
$reg=$registros[0];
chop($reg);
@campos=split /$separador/,$reg;
$cantCampos=$#campos +1;
print "cantidad $cantCampos $posCantidad  $posProducto \n";
if($cantCampos <= 1){
	die "menor cantidad de campos que los permitidos \n";
}
if(( $cantCampos < $posCantidad ) || ($cantCampos < $posProducto )){
	die "error en la posicion de cantidad y producto \n";
}
close(FILE);
print "Escriba el nombre del archivo de salida : \n";
$nombreOuput="salida";#<STDIN>;
chop($nombreOuput);
$nombreOuput="$nombreOuput.sal";
%hashProd_cant=();
open OUPUT, ">",$nombreOuput or die $/;
foreach $reg (@registros){
	chop($reg);
    @campos=split /$separador/,$reg;
    $producto=$campos[$posProducto-1];
    $cantidad=$campos[$posCantidad-1];
    $hashProd_cant{$producto} +=$cantidad;
   	print "$producto $cantidad \n";
}
foreach $key (sort(keys(%hashProd_cant))){
	print "con esta clave $key : $hashProd_cant{$key} \n";
}
close(OUPUT);
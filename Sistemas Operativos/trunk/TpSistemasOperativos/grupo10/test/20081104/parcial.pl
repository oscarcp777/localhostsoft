#! /usr/bin/perl
#El Fondo Monetario Internacional recibe informes de los organismos internacionales de crédito 
#(BID, Banco Mundial, etc) en donde se indican todos los préstamos otorgados en cada país. 
#Código de País,Código de prestamo, Fecha de disponibilidad, Monto del Préstamo, Fecha de caducidad
#Ej: 613,ANR-1208,20070220,1200000,20090220#
#Ej: 613,ANR-OCQR,20061103,3000000,20091103
#Los campos de los registros están separados por , En ambas fechas el formato es aaaammdd
#Si el archivo lo envía el BID, el nombre del archivo es BIDnnn, donde nnn es un número de 3 dígitos secuencial.
#Si el archivo lo envía el Banco MUndial, el nombre es BMnnn, donde nnn es un número de 3 dígitos secuencial.
#Se pide:
#Desarrollar un comando perl que reciba como parámetro el nombre del archivo que se quiere procesar (parámetro obligatorio) 
#y un código de país (parámetro opcional). Si el código de país no se ingresa, tomar como valor de defecto el 613 
#que corresponde a Argentina y grabe un archivo de salida (informe.txt) con la siguiente información:
#“Totales de préstamos puestos a disponbilidad por el (BID o BM según corresponda) en (nombre del país)”
#“año xxxa u$s aaaa (suma de los montos de préstamos con fecha de disponibilidad en el año xxxa) dólares”
#“año xxxb u$s bbbb (suma de los montos de préstamos con fecha de disponibilidad en el año xxxb) dólares”
#etc.
#Condiciones de resolución
#Es obligariorio el uso de funciones perl para separar y cortar los campos de los registros 
#(NO USAR EXPRESIONES REGULARES en reemplazo de estas funciones)
#Es olbigatorio esl uso de una estructura de hash para efectuar la suma de los préstramos por año. 
#El campo año es el que se debe emplear como clave y el campo monto es el que se debe acumular.
#Validar el nombre del archivo de entrada de acuerdo al formato especificado.  XXX YA ESTA XXXX
#Si el archivo de entrada no existe, mostrar en pantalla un mensaje de error.  XXX YA ESTA XXXX
#Validar el parámetro opcional si este es ingresado empleando la tabla de paises.tab XXX YA ESTA XXXX
#Si el archivo de salida existe solocitar al ususario que ingrese un nuevo nombre de archivo de salida XXX YA ESTA XXXX
#Cuando termina de procesar el archivo y graba la salida, terminar el programa
#Estructura de paises.tab (1 a n registros):
#Codigo de Pais;Nombre (separador es punto y coma)
#Ej: 613;Argentina
#Ej: 815;Perú
$fileOuput="informe.txt";
$codigoPais=613;
$nombrePais="Argentina";
$cantArg=2;#$ARGV;
if($cantArg < 1 ){
	die "	ERROR: menor cantidad de parametros que los pedidos \n";
}
if($cantArg >= 2){
	$codigoPais=613;#$ARGV[1];
	$encontro=0;
	open(PAISES,"paises.tab");
	@registros=<PAISES>;
	foreach $reg (@registros){
		@campos=split /;/,$reg;
		if($codigoPais eq $campos[0]){
			$nombrePais=$campos[1];
			print " encontro $nombrePais\n";
			$encontro=1;
			last;
		}
	}
	if($encontro == 0){
		die "no existe el pais en el archivo maestro de paises\n";
	}
}
$fileInput="BID123";#$ARGV[0];

@campos=split //,$fileInput;
$cant=@campos;
$banco="no encontrado";
print "\n";
if($cant == 5 || $cant == 6){
     if($fileInput =~ /^BM[0-9][0-9][0-9]$|^BID[0-9][0-9][0-9]$/){
	    open FILE,"<",$fileInput or die "ERROR: no existe el archivo \n";
	    $banco=substr($fileInput,0,$cant-3);
	    print " $banco \n";
       }
       else{
	    die "nombre archivo invalido \n";
       }
}else{
	die "nombre archivo invalido \n";
}
if(open OUPUT,"<",$fileOuput){
	print "El nonbre del archivo de salida \"informes.txt\" ya existe ingrese uno nuevo : ";
	$fileOuput=<STDIN>;
	chop($fileOuput);
}
open OUPUT,">",$fileOuput or die "error al abrir archivo\n";

print OUPUT "Totales de préstamos puestos a disponbilidad por el ($banco) en $nombrePais";
@registros=<FILE>;
%hash_anio_monto=();
foreach $reg (@registros){
	@campos=split /,/,$reg;
	$monto=$campos[3];
	$anio=substr($campos[2],0,4);
	$hash_anio_monto{$anio}+=$monto;
}
foreach $reg (sort(keys(%hash_anio_monto))){
	print OUPUT "$reg;$hash_anio_monto{$reg}\n";
}












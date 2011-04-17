#!/usr/bin/perl
# Comando "reporte"
# Output
# 	 Log $grupo/logdir/reporte.log
#	 Listados $grupo/datadir/list/<nombre listado>.<id>
#	 Archivo de Modificaciones de Contratos $grupo/datadir/new/MODIF.<pais>
#
# Input
#	Archivo de Contratos de Préstamos Personales $grupo/datadir/new/CONTRAT.<pais>
#	Archivo Maestro Préstamos Personales Impagos $grupo/datadir/mae/PPI.mae
#	Tabla de Paises y Sistemas $grupo/conf/p-s.tab

# Chquear que las variables de ambiente estén inicializadas
$envcheck = `envcheck.sh`;
if ($envcheck eq 1) {`glog.sh "Reporte" E "El ambiente no está inicializado"`; exit 1;}

# Chequear que no hayan otros comandos ejecutándose
if (`obtpid.sh iniciar.sh`){`glog.sh "Reporte" E "Está corriendo el comando INICIAR"`; exit 2;}
if (`obtpid.sh detectar.sh`){`glog.sh "Reporte" E "Está corriendo el comando DETECTAR"`; exit 2;}
if (`obtpid.sh interprete.sh`){`glog.sh "Reporte" E "Está corriendo el comando INTERPRETE"`; exit 2;}
if (`obtpid.sh reporte.sh`){`glog.sh "Reporte" E "Está corriendo el comando REPORTE"`; exit 2;}

# Variables
$error=1;
$grupo=$ENV{"GRUPO"};
$data=$ENV{"DATADIR"};
$rutaps="$grupo/conf/p-s.tab";
$rutappi="$grupo/$data/mae/PPI.mae";
$rutacontract="$grupo/$data/new/CONTRACT."; #Cuando se sepa el pais se le agrega a la variable
$rutalistado="$grupo/$data/list/list"; #Cuando se sepan el pais y el id se le agregan a la variable
$rutamodif="$grupo/$data/new/MODIF."; #Cuando se sepa el pais se le agrega a la variable
$sano="SANO";
$dudoso="DUDOSO";
$consultaa=0; $consultab=0; $consultac=0; $consultad=0; $consultae=0; $consultaf=0;

# Chequear si existe p-s.tab
if ((! -e $rutaps) && (! -r $rutaps)){`glog.sh "Reporte" E "El archivo p-s.tab no existe o no se puede leer"`; exit 3;}

# Funcion que guarda el listado de un tipo de consulta
sub grabarlistado{
	$rutalistadoaux="${rutalistado}@_[0]";
	@archivos = <$rutalistadoaux.*>;
	if (!@archivos) {$id=0;} else {$id=@archivos;}
	$rutalistadoaux="$rutalistadoaux.$id";
	open(output_listado,">$rutalistadoaux");
	$parametros = @_;
	for ($i=1;$i<$parametros;$i++){
		print output_listado "$i-@_[$i]";
	}
	close(output_listado);
	`glog.sh "Reporte" I "Se guardó el listado de la consulta en $rutalistadoaux"`;
}

# Menú
sub menu {
	print "Seleccione el/los tipos de consulta que desea realizar.\n";
	print "Para ello ingrese por teclado la/s letra/s correspondiente/s a cada consulta y luego presione enter.\n";
	print "a: Contratos Comunes Sanos con Idéntico Monto Restante\n";
	print "b: Contratos Comunes Dudosos con Idéntico Monto Restante\n";
	print "c: Contratos Comunes Sanos con Diferente Monto Restante\n";
	print "d: Contratos Comunes Dudosos con Diferente Monto Restante\n";
	print "e: Contratos Comunes con Diferente Estado e Idéntico Monto Restante\n";
	print "f: Contratos Comunes con Diferente Estado y Diferente Monto Restante\n";
	print "Consultas seleccionadas: ";
}

# Selección de consultas
system("clear");
print "Comando de reporte\n\n";
&menu;

while ($error){	
	$opciones=<STDIN>; chomp($opciones); $opciones = lc $opciones;
	$opciones =~ s/[^a-zA-Z]//g;
	$opciones = uc $opciones;
	if ($opciones =~ m/[^ABCDEF]/) {
		$error=1;
		system("clear");
		print "Ingresó una opción que no es válida.\n\n";
		&menu;
	} else {$error=0;}
	if (!$error){
		if ($opciones =~ m/[A]/) {$consultaa=1;} else {$consultaa=0;}
		if ($opciones =~ m/[B]/) {$consultab=1;} else {$consultab=0;}
		if ($opciones =~ m/[C]/) {$consultac=1;} else {$consultac=0;}
		if ($opciones =~ m/[D]/) {$consultad=1;} else {$consultad=0;}
		if ($opciones =~ m/[E]/) {$consultae=1;} else {$consultae=0;}
		if ($opciones =~ m/[F]/) {$consultaf=1;} else {$consultaf=0;}
	}
}
`glog.sh "Reporte" I "Se eligieron los tipos de consulta: $opciones"`;

# Parametros
$pais; $sistema; $anio; $mes;
$aceptado="No";
$mensajelog="Se eligieron los parametros:";
while ($aceptado ne "Si"){
	system("clear");
	print "A continuación se pedirán los parámetros para la consulta.\n";

	$paisVal=0;
	while (!$paisVal) { #Chequear que sea un pais valido
		print "Ingrese el id del pais: ";
		$pais=<STDIN>; chomp($pais);
		while (!$pais){
			print "No ingresó un pais y este parametro es obligatorio. Ingrese el id del pais nuevamente: ";
			$pais=<STDIN>; chomp($pais);
		}

		open(input_tab,"<$rutaps");
		while ($linea=<input_tab>){
			chomp($linea);
			if ($linea){
				@campos_tab=split("-",$linea);
				if ($pais eq @campos_tab[0]){
					$paisVal=1;
				}
			}
		}
		close(input.tab);
		if (!$paisVal){
			print "Ingreso un id de pais inexistente\n";
		}	
	}

	$sistVal=0;
	while (!$sistVal) { #Chequear que sea un sistema valido
		print "\nIngrese el id del sistema. Este campo es opcional, si no desea seleccionar un sistema no ingrese nada y presione enter: ";
		$sistema=<STDIN>; chomp($sistema);
		
		if (!$sistema){
			$sistVal=1;
		}
		else{
			open(input_tab,"<$rutaps");
			while ($linea=<input_tab>){
				chomp($linea);
				if ($linea){
					@campos_tab=split("-",$linea);
					if ($sistema eq @campos_tab[2]){
						$sistVal=1;
					}
				}
			}
			close(input.tab);
		}
		if (!$sistVal){
			print "Ingreso un id de sistema inexistente";
		}
	}
	
	print "\nIngrese el año. Este campo es opcional, si no desea especificar un año no ingrese nada y presione enter: ";
	$anio=<STDIN>; chomp($anio);
	while ($anio!="" && ($anio<2000 || $anio>2010)) { #Chequear que se elija un año valido? o se haya dejado en blanco
		print "Ingresó una año inválido. Ingrese un número de año o deje en blanco y presione enter: ";
		$anio=<STDIN>; chomp($anio);
	}

	if ($anio) {
		print "\nHa especificado un año, si desea consultar un mes en particular escriba el número de mes y presiones enter. Si no desea especificar un mes no ingrese nada y presione enter: ";
		$mes=<STDIN>; chomp($mes);
		while ($mes!="" && ($mes<1 || $mes>12)) { #Chequear que se elija un año valido? o se haya dejado en blanco
			print "Ingresó una mes inexistente. Ingrese un número entre 1 o 12 o deje en blanco y presione enter: ";
			$mes=<STDIN>; chomp($mes);
		}
	} else { $mes="";}
	
	print "\nLos parametros ingresados son:\n";
	print "Pais: $pais\n";
	print "Sistema: ";
	if ($sistema) {print "$sistema\n";} else {print "No se ingresó ningún sistema\n";}
	print "Año: ";
	if ($anio) {print "$anio\n";} else {print "No se ingresó ningún año\n";}
	print "Mes: ";
	if ($mes) {print "$mes\n";} else {print "No se ingresó ningún mes\n";}

	print "\n¿Es correcta esta información?: ";
	$aceptado=<STDIN>; chomp($aceptado); $aceptado = ucfirst $aceptado;
	if ($aceptado eq "S") {$aceptado="Si";}
}
close(input_tab);

# Log
$mensajelog="$mensajelog $pais";
if ($sistema) {$mensajelog="$mensajelog $sistema";}
if ($anio) {$mensajelog="$mensajelog $anio";}
if ($mes) {$mensajelog="$mensajelog $mes";}
`glog.sh "Reporte" I "$mensajelog"`;

# Opciones
$aceptado="No";
while ($aceptado ne "Si"){
	system("clear");
	print "A continuación se le pedirá que elija las opciones de guardado para los resultados de la consulta.\n";
	print "¿Desea guardar el listado generado por la consulta?: ";
	$glistado=<STDIN>; chomp($glistado); $glistado = ucfirst $glistado;
	while ($glistado ne "S" && $glistado ne "Si" && $glistado ne "N" && $glistado ne "No") {
		print "Ingresó una opción invalida, indique si desea guardar o no el listado generado por la consulta: ";
		$glistado=<STDIN>; chomp($glistado); $glistado = ucfirst $glistado;
	}
	if ($glistado eq "S") {$glistado="Si";}
	if ($glistado eq "N") {$glistado="No";}

	print "\n¿Desea guardar el archivo de modificaciones de contratos?: ";
	$gmodif=<STDIN>; chomp($gmodif); $gmodif = ucfirst $gmodif;
	while ($gmodif ne "S" && $gmodif ne "Si" && $gmodif ne "N" && $gmodif ne "No") {
		print "Ingresó una opción invalida, indique si desea guardar o no el archivo de modificaciones: ";
		$gmodif=<STDIN>; chomp($gmodif); $gmodif = ucfirst $gmodif;
	}
	if ($gmodif eq "S") {$gmodif="Si";}
	if ($gmodif eq "N") {$gmodif="No";}
	
	print "\nLas opciones ingresadas son:\n";
	print "Guardar listado: $glistado\n";
	print "Guardar archivo de modificaciones: $gmodif\n";

	print "\n¿Es correcta esta información?: ";
	$aceptado=<STDIN>; chomp($aceptado); $aceptado = ucfirst $aceptado;
	if ($aceptado eq "S") {$aceptado="Si";}
}

# Log
$mensajelog="Se eligió";
if ($glistado eq "No"){$mensajelog="$mensajelog no";}
$mensajelog="$mensajelog guardar el listado";
`glog.sh "Reporte" I "$mensajelog"`;
$mensajelog="Se eligió";
if ($gmodif eq "No"){$mensajelog="$mensajelog no";}
$mensajelog="$mensajelog guardar el el archivo de modificaciones";

# Imprimo encabezados
system("clear");
printf("%-20s%-6s%-8s%-6s%-6s%-20s%-10s%-20s\n","FUENTE","PAIS","SISTEMA","ANIO","MES","NUMERO DE CONTRATO","ESTADO","MONTO RESTANTE");

# Imprimo la fuente
printf("%-20s","ARCHIVO MAESTRO");
print("\n");

#Chequear si existen PPI.mae y CONTRACT.$pais
if (-e $rutappi && -r $rutappi){open(input_mae,"<$rutappi");
} else {`glog.sh "Reporte" E "El archivo PPI.mae no existe o no se puede leer"`; exit 4;}

$rutacontract="$rutacontract$pais";
if (-e "$rutacontract" && -r "$rutacontract"){open(input_pais,"<$rutacontract");
} else {`glog.sh "Reporte" E "El archivo CONTRACT.$pais no existe o no se puede leer"`;	exit 5;}

# Cargo el número de contrato y el monto restante en un hash y en otro hash el número y el estado
%mt_restante_mae;
%estado_mae;

while ($linea=<input_mae>){
	chomp($linea);
	$linea =~ s/,/./g; #perl usa punto para la parte decimal en vez de la coma
	if ($linea){
		@campos_mae=split("-",$linea);
		if (@campos_mae[0] eq $pais &&(@campos_mae[6] eq $sano || @campos_mae[6] eq $dudoso)){
			$mt=(@campos_mae[10]+@campos_mae[11]+@campos_mae[12]-@campos_mae[14]);
			$mt_restante_mae{@campos_mae[7]}=$mt;
			$estado_mae{@campos_mae[7]}=@campos_mae[6];
			if (($pais == @campos_mae[0]) && (($sistema && $sistema == @campos_mae[1]) || !$sistema) && ((($anio && $anio == @campos_mae[2]) && (($mes && $mes == @campos_mae[3]) || !$mes)) || !$anio)){
				printf("%-20s%-6s%-8s%-6s%-6s%-20s%-10s%15s\n","",@campos_mae[0],@campos_mae[1],@campos_mae[2],@campos_mae[3],@campos_mae[7],@campos_mae[6],$mt_restante_mae{@campos_mae[7]});
			}
		}
	}
}
close(imput_mae);

$cantSanosIgualMonto=0;
$totalSanosIgualMonto=0;

$cantDudososIgualMonto=0;
$totalDudososIgualMonto=0;

$cantSanosDistintoMonto=0;
$totalSanosDistintoMontoContrato=0;
$totalSanosDistintoMontoMaestro=0;

$cantDudososDistintoMonto=0;
$totalDudososDistintoMontoContrato=0;
$totalDudososDistintoMontoMaestro=0;

$cantSanoDudosoIgualMonto=0;
$totalSanoDudosoIgualMonto=0;

$cantDudosoSanoIgualMonto=0;
$totalDudosoSanoIgualMonto=0;

$cantSanoDudosoDistintoMonto=0;
$totalSanoDudosoDistintoMontoContrato=0;
$totalSanoDudosoDistintoMontoMaestro=0;

$cantDudosoSanoDistintoMonto=0;
$totalDudosoSanoDistintoMontoContrato=0;
$totalDudosoSanoDistintoMontoMaestro=0;

@contratos_modif; #Para guardar el numero de contrato de los contratos que van a MODIF
@listado; #Para guardar las lineas del listado, y poder imprimirlo y guardarlo
@modif; #Para guardar las lineas que van a guardarse en MODIF

# Imprimo la fuente
printf("%-20s","ARCHIVO CONTRATO");
print("\n");
while ($linea=<input_pais>){
	chomp($linea);
	$linea =~ s/,/./g;
	if ($linea){
		@campos_pais=split("-",$linea);

		if ((($sistema && $sistema == @campos_pais[0]) || !$sistema) && ((($anio && $anio == @campos_pais[1]) && (($mes && $mes == @campos_pais[2]) || !$mes)) || !$anio) ){
			
			printf("%-20s%-6s%-8s%-6s%-6s%-20s%-10s%15s\n","",$pais,@campos_pais[0],@campos_pais[1],@campos_pais[2],@campos_pais[3],@campos_pais[5],@campos_pais[11]);

			if ($consultaa==1){
				if((@campos_pais[5]eq$sano) && ($estado_mae{@campos_pais[3]}eq$sano) && ($mt_restante_mae{@campos_pais[3]}eq@campos_pais[11])) {
					$cantSanosIgualMonto++;
					$totalSanosIgualMonto+=@campos_pais[11];
				}
			};

			if ($consultab==1){
				if((@campos_pais[5]eq$dudoso) && ($estado_mae{@campos_pais[3]}eq$dudoso) && ($mt_restante_mae{@campos_pais[3]}eq@campos_pais[11])) {
					$cantDudososIgualMonto++;
					$totalDudososIgualMonto+=@campos_pais[11];
				}
			};

			if ($consultac==1){
				if ((@campos_pais[5]eq$sano) && ($estado_mae{@campos_pais[3]}eq$sano)  && ($mt_restante_mae{@campos_pais[3]}ne@campos_pais[11])) {
					$cantSanosDistintoMonto++;
					$totalSanosDistintoMontoContrato+=@campos_pais[11];
					$totalSanosDistintoMontoMaestro+=$mt_restante_mae{@campos_pais[3]};
					push(@contratos_modif,@campos_pais[3]);
				}
			};

			if ($consultad==1){
				if((@campos_pais[5]eq$dudoso) && ($estado_mae{@campos_pais[3]}eq$dudoso) && ($mt_restante_mae{@campos_pais[3]}ne@campos_pais[11])) {
					$cantDudososDistintoMonto++;
					$totalDudososDistintoMontoContrato+=@campos_pais[11];
					$totalDudososDistintoMontoMaestro+=$mt_restante_mae{@campos_pais[3]};
				}
			};

			if (($consultae==1) && ($mt_restante_mae{@campos_pais[3]}eq@campos_pais[11])){
				if ((@campos_pais[5]eq$sano) && ($estado_mae{@campos_pais[3]}eq$dudoso)) {
					$cantSanoDudosoIgualMonto++;
					$totalSanoDudosoIgualMonto+=@campos_pais[11];
				} else {
					if ((@campos_pais[5]eq$dudoso) && ($estado_mae{@campos_pais[3]}eq$sano)){
						$cantDudosoSanoIgualMonto++;
						$totalDudosoSanoIgualMonto+=@campos_pais[11];
						push(@contratos_modif,@campos_pais[3]);
					}
				}
			};

			if (($consultaf==1) && ($mt_restante_mae{@campos_pais[3]}ne@campos_pais[11])){
				if ((@campos_pais[5]eq$sano) && ($estado_mae{@campos_pais[3]}eq$dudoso)){
					$cantSanoDudosoDistintoMonto++;
					$totalSanoDudosoDistintoMontoContrato+=@campos_pais[11];
					$totalSanoDudosoDistintoMontoMaestro+=$mt_restante_mae{@campos_pais[3]};
				} else {
					if ((@campos_pais[5]eq$dudoso) && ($estado_mae{@campos_pais[3]}eq$sano)){
						$cantDudosoSanoDistintoMonto++;
						$totalDudosoSanoDistintoMontoContrato+=@campos_pais[11];
						$totalDudosoSanoDistintoMontoMaestro+=$mt_restante_mae{@campos_pais[3]};
						push(@contratos_modif,@campos_pais[3]);
					}
				}
			};
		}
	}
}
close(input_pais);

# Imprimo los encabezados de las consultas
print("\n\n");
push(@listado,sprintf("%-34s%-20s%-18s%-17s%-17s%-20s%-20s\n","CONSULTA","PARAMETROS","CANT. CONTRATOS","EST. CONTRATO","EST. MAESTRO","MT. RT. CONTRATO","MT. RT. MAESTRO"));

if ($consultaa==1) {
	push(@listado,sprintf("%-34s%-15s%15s%16s%16s%21s%21s\n","a-Sanos de igual monto","$pais $sistema $anio $mes",$cantSanosIgualMonto,$sano,$sano,$totalSanosIgualMonto,$totalSanosIgualMonto));
};

if ($consultab==1) {
	push(@listado,sprintf("%-34s%-15s%15s%16s%16s%21s%21s\n","b-Dudosos de igual monto","$pais $sistema $anio $mes",$cantDudososIgualMonto,$dudoso,$dudoso,$totalDudososIgualMonto,$totalDudososIgualMonto));
};

if ($consultac==1) {
	push(@listado,sprintf("%-34s%-15s%15s%16s%16s%21s%21s\n","c-Sanos de distinto monto","$pais $sistema $anio $mes",$cantSanosDistintoMonto,$sano,$sano,$totalSanosDistintoMontoContrato,$totalSanosDistintoMontoMaestro));
};

if ($consultad==1) {
	push(@listado,sprintf("%-34s%-15s%15s%16s%16s%21s%21s\n","d-Dudosos de distinto monto","$pais $sistema $anio $mes",$cantDudososDistintoMonto,$dudoso,$dudoso,$totalDudososDistintoMontoContrato,$totalDudososDistintoMontoMaestro));
};

if ($consultae==1) {
	push(@listado,sprintf("%-34s%-15s%15s%16s%16s%21s%21s\n","e-Distinto estado, igual monto","$pais $sistema $anio $mes",$cantSanoDudosoIgualMonto,$sano,$dudoso,$totalSanoDudosoIgualMonto,$totalSanoDudosoIgualMonto));
	push(@listado,sprintf("%-49s%15s%16s%16s%21s%21s\n","",$cantDudosoSanoIgualMonto,$dudoso,$sano,$totalDudosoSanoIgualMonto,$totalDudosoSanoIgualMonto));
};

if ($consultaf==1) {
	push(@listado,sprintf("%-34s%-15s%15s%16s%16s%21s%21s\n","f-Distinto estado, distinto monto","$pais $sistema $anio $mes",$cantSanoDudosoDistintoMonto,$sano,$dudoso,$totalSanoDudosoDistintoMontoContrato,$totalSanoDudosoDistintoMontoMaestro));
	push(@listado,sprintf("%-49s%15s%16s%16s%21s%21s\n","",$cantDudosoSanoDistintoMonto,$dudoso,$sano,$totalDudosoSanoDistintoMontoContrato,$totalDudosoSanoDistintoMontoMaestro));
};

print @listado;


if ($glistado eq "Si"){
	mkdir "$grupo/$data/list/";
	if ($consultaa eq 1) {&grabarlistado("A","@listado[0]","@listado[1]");}
	if ($consultab eq 1) {&grabarlistado("B","@listado[0]","@listado[2]");}
	if ($consultac eq 1) {&grabarlistado("C","@listado[0]","@listado[3]");}
	if ($consultad eq 1) {&grabarlistado("D","@listado[0]","@listado[4]");}
	if ($consultae eq 1) {&grabarlistado("E","@listado[0]","@listado[5]","@listado[6]");}
	if ($consultaf eq 1) {&grabarlistado("F","@listado[0]","@listado[7]","@listado[8]");}
};

if ($gmodif eq "Si"){
	#genero las lineas del listado con @contratos_modif
	$contratos = join("-",@contratos_modif);
	open(input_mae,"<$rutappi");
	while ($linea=<input_mae>){
		chomp($linea);
		if ($linea){
			@campos = split("-",$linea);
			$numero = @campos[7];
			if (@campos[0] eq $pais && $contratos =~ m/$numero/) {
				$linea = substr($linea,2);
				$linea = "$linea\n";
				push(@modif,$linea);
			}
		}
	}
	$rutamodif = "$rutamodif$pais";
	#guardo el listado en el archivo
	open(output_modif,">$rutamodif");
	print output_modif @modif;
	close(output_modif);
	`glog.sh "Reporte" I "Se guardó el archivo de modificaciones en $rutamodif"`;
};


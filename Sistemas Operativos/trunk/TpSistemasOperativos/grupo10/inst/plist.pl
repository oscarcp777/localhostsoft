#! /usr/bin/perl

#Los parametros seran ingresados en el siguiente orden :
# 1) archivo/s beneficiario/s nuevos 
# 2) Agencia/s
# 3) Beneficio/s
# 4) -t :salida por pantalla
#    -d :salida por archivo
#    -td o dt: Tanto por archivo como por pantalla
#    Si no ingresamos ninguna opcion por defecto mostrara por #pantalla unicamente
# 5) -c : imprimir matriz de provincia/beneficio y lista beneficiarios
#     si no ponemos nada por defecto solo mostrara la lista de beneficiarios 
# 6) Si la opcion 5 fue ingresada, tambien se podra filtrar por estado, ingresado en cada caso : .-ea : Solo los aprobados
#      .-ep : Solo los pendientes
#      .-er : Solo los rechazados		 	
 
#ARGUMENTOS
my $arch_Beneficiarios = $ARGV[0];
my $agencias = $ARGV[1]; 
my $beneficios = $ARGV[2];
my $opcionSalida = $ARGV[3];
my $opcionListaMatriz = $ARGV[4];
my $filtroPorEstado = $ARGV[5];

#HASH
my %matriz;
my %beneficios;
my $file;
my @files;
my @listaBenficiarios;

#PATH
my $dir_Actual = $DATADIR; 
$dir_log=$ENV{"LOGDIR"};
my $log ='./gralog.sh';
$dirName =$ENV{"DATADIR"};
my $dirSalidaArchivo =$ENV{"CURRDIR"}."/list";
my $ardestino = 'plist';
my $salidaPorArchivo = '>'.$ENV{"CURRDIR"}.'/list/';

#----------------------------CABECERA---------------------------------

sub getCabecera(){
	
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
	$year += 1900;
	$mon ++; 
	$hora = "$hour:$min:$sec";
	$fecha= "$mday/$mon/$year";
	my $usuario = `echo \$LOGNAME | tr -d '\n'`;
	
	push(@cabecera,$hora);
	push(@cabecera,$fecha);
	push(@cabecera,$usuario);
	push(@cabecera,$arch_Beneficiarios);
	push(@cabecera,$agencias);
	push(@cabecera,$beneficios);
	push(@cabecera,$opcionSalida);
	push(@cabecera,$opcionListaMatriz);
	push(@cabecera,$filtroPorEstado);

	return @cabecera;
	
}

#-----------------------------------IMPRESION-------------------------

sub imprimirInfo
{
	
	my $con_Matriz = shift;
	my $matriz =shift;
	my $beneficios = shift;
	my $longitudListaBenef = @listaBenficiarios;
	
	printf("\n%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n\n",$cabecera[0],$cabecera[1],$cabecera[2],$cabecera[3],$cabecera[4],$cabecera[5],$cabecera[6],$cabecera[7],$cabecera[8]);
	printf("\n%-10s%-10s%-10s%-15s%-20s%-12s%-10s\n","APELLIDO","BENEFICIO","AGENCIA","CUIL","PROVINCIA","ESTADO","FECHA_EFECT_ALTA");
	for($i=0;$i<$longitudListaBenef;$i++) {	
		printf("%-10s%-10s%-10s%-15s%-20s%-12s%-10s\n",@listaBenficiarios[$i],@listaBenficiarios[$i+1],@listaBenficiarios[$i+2],@listaBenficiarios[$i+3],@listaBenficiarios[$i+4],@listaBenficiarios[$i+5],@listaBenficiarios[$i+6]);
	$i+=7;
	}
	print "\n\t\t\t";
	if($conMatriz){

	   foreach $llaveBeneficio (keys %{$beneficios}){
		printf("%-4s\t",$llaveBeneficio);	
	   }
	   printf("%-17s","TOTAL BENEFICIARIOS");
	   print "\n";

	   foreach $llave (keys %{$matriz}){
		if(! ($llave eq 'totalBeneficiario') && !($llave eq 'total') ){	         
		   printf ("%-17s\t",$llave);			  
		   foreach $llave2 (keys %{$beneficios}){
		      printf("%-s\t", ${$matriz->{$llave}}{$llave2});
	    	   }
		 printf ("%-d\n",${$matriz->{$llave}}{'totalBeneficiario'});
		}
           }
				
	#Muestra el total de beneficiarios por beneficios(por columna)	
	print "ToltaBeneficiario\t";
	foreach $llaveBeneficio (keys %{$beneficios}){
		printf("%-d\t",${$matriz->{'totalBeneficiario'}}{$llaveBeneficio});
	}
		printf("%-d",${$matriz->{$llave}}{'total'});
		print "\n\n";	
	}
		

}

#-------------------------------------ESCRIBIR EN ARCHIVO-----------------------------------

sub escribirEnArchivo{
	
my $conMatriz = shift;
my $matriz = shift;
my $beneficios = shift;
my @secuencias;
my $secuencia=0;
my $longitudListaBenef = @listaBenficiarios;
my @secuenciasEncontradas;
my $long;

if(! -e $dirSalidaArchivo){
	mkdir $dirSalidaArchivo;
}

opendir(DIR,$dirSalidaArchivo)|| `$log "listaBeneficiarios" A "No se puede leer el directorio $dirSalidaArchivo"`;

while($filename=readdir(DIR)){
	push(@secuenciasEncontradas,$filename);
}
closedir(DIR);

@secuenciasEncontradas = grep(/plist\.[0-9]*/,@secuenciasEncontradas);
$long =@secuenciasEncontradas;
for($i=0;$i<$long;$i++){
  @secuenciasEncontradas[$i] =~s/plist.//;
}

@secuenciasEncontradas = sort {$a <=> $b } @secuenciasEncontradas;
@secuenciasEncontradas = reverse(@secuenciasEncontradas);

$secuencia =  @secuenciasEncontradas[0];


if($secuencia > 0){
	$secuencia ++;
}else{
	$secuencia =1;
}

$rutaArchivo = ">>".$dirSalidaArchivo."/plist.".$secuencia;
open(PLIST,$rutaArchivo);
	printf PLIST "\n%-8s%-4s%-8s%-10s%-10s%-10s%-10s%-10s%-10s\n\n",$cabecera[0],$cabecera[1],$cabecera[2],$cabecera[3],$cabecera[4],$cabecera[5],$cabecera[6],$cabecera[7],$cabecera[8];

	printf PLIST "\n%-10s%-10s%-10s%-15s%-20s%-12s%-10s\n","APELLIDO","BENEFICIO","AGENCIA","CUIL","PROVINCIA","ESTADO","FECHA_EFECT_ALTA";
	for($i=0;$i<$longitudListaBenef;$i++) {	
		printf PLIST "%-10s%-10s%-10s%-15s%-20s%-12s%-10s\n",@listaBenficiarios[$i],@listaBenficiarios[$i+1],@listaBenficiarios[$i+2],@listaBenficiarios[$i+3],@listaBenficiarios[$i+4],@listaBenficiarios[$i+5],@listaBenficiarios[$i+6];
	$i+=7;
	}
	print PLIST "\n\t\t\t";
	if($conMatriz){

	   foreach $llaveBeneficio (keys %{$beneficios}){
		printf PLIST "%-4d\t",$llaveBeneficio;	
	   }
	   printf PLIST "%-17s","TOTAL BENEFICIARIOS";
	   print PLIST "\n";

	   foreach $llave (keys %{$matriz}){
		if(! ($llave eq 'totalBeneficiario') && !($llave eq 'total')){	         
		   printf PLIST "%-17s\t",$llave;			  
		   foreach $llave2 (keys %{$beneficios}){
		      printf PLIST "%-d\t", ${$matriz->{$llave}}{$llave2};
	    	   }
		 printf PLIST "%-d\n",${$matriz->{$llave}}{'totalBeneficiario'};
		}
           }

	#Muestra el total de beneficiarios por beneficios(por columna)	
	print PLIST "ToltaBeneficiario\t";
	foreach $llaveBeneficio (keys %{$beneficios}){
		printf PLIST "%-d\t",${$matriz->{'totalBeneficiario'}}{$llaveBeneficio};
	}
		printf PLIST "%-d",${$matriz->{$llave}}{'total'};
		print PLIST "\n\n";	
	}
close(PLIST);
}

#----------------------------------------------|-----------------------------------------

sub listar(@encontrados,$filtroPorEstado){

	
	my @listaBeneficiarios;
	my @listaBeneficiariosTemp;
	foreach $nombreArch (@encontrados){
		$ruta = $dirName."/".$nombreArch;
		open(OUT,$ruta);
		while($linea=<OUT>){			
			push(@listaBeneficiariosTemp,$linea);
		}
		close(OUT);		
	}

	if($filtroPorEstado eq "-ea"){
		$filtroPorEstado="aprobado";
	}elsif($filtroPorEstado eq "-ep"){
		$filtroPorEstado="pendiente";
	}elsif($filtroPorEstado eq "-er"){
		$filtroPorEstado ="rechazado";
	}else{
		$filtroPorEstado ='.*';
	}		
	
	
	
	@listaBeneficiarios = grep(/$agencias,.*,.*,.*,.*,.*,.*,.*,.*,.*,$beneficios,.*,.*,$filtroPorEstado,.*,.*,.*,.*,.*/,@listaBeneficiariosTemp);

	my @listafinal;
	foreach $linea (@listaBeneficiarios){
		@registro = split(/,/,$linea);
		push(@listafinal,@registro[5]);
		push(@listafinal,@registro[10]);
		push(@listafinal,@registro[0]);
		push(@listafinal,@registro[2]);
		push(@listafinal,@registro[9]);
		push(@listafinal,@registro[13]);
		push(@listafinal,@registro[12]);
		push(@listafinal,"\n");	
	}
	return @listafinal;	
}
#-------------------------------RELLENAR -------------------------------------------------------
sub rellenarMatriz{
	
	my $beneficios = shift;
	my $matriz = shift;
	  
	foreach $llaveBeneficios (keys %{$beneficios}){	   
	foreach $llaveProvincia (keys %{$matriz}){
		if(!exists(${$matriz->{$llaveProvincia}}{$llaveBeneficios}))
		{
		    ${$matriz->{$llaveProvincia}}{$llaveBeneficios} = 0;		 	
		}	
	    }		
	}
}

#------------------------------------CALCULO TOTAL----------------------------------------------

sub calcularTotal{


	my $beneficios = shift;
	my $matriz     = shift;	
	my $total=0;
	#Total beneficiario por provincia
	foreach $llaveProvincia (keys %{$matriz}){
		my $totalBeneficiario=0;		
		foreach $llaveBeneficio (%{$beneficios}){
			$totalBeneficiario += ${$matriz->{$llaveProvincia}}{$llaveBeneficio};			
		}
		$total+=$totalBeneficiario;
		${$matriz->{$llaveProvincia}}{'totalBeneficiario'} = $totalBeneficiario ;	
	}
	
	#total beneficiario por beneficio
	foreach $llaveBeneficio (keys %{$beneficios}){
		my $totalBenefirioPorBeneficio=0;		
		foreach $llaveProvincia (keys %{$matriz}){
		
			$totalBenefirioPorBeneficio += ${$matriz->{$llaveProvincia}}{$llaveBeneficio};	
		}
		${$matriz->{'totalBeneficiario'}}{$llaveBeneficio} = $totalBenefirioPorBeneficio
	}

	${$matriz->{$llaveProvincia}}{'total'} = $total; 
}


#-------------------------------MATRIZ DE CONTROL-----------------------------------------------

sub matrizControl{


$longitud = @listaBenficiarios;
$offset = 8;	
$contador = 0;	
my $beneficios = shift;
my $matriz = shift;
while($contador < $longitud){		
	$offset_Beneficio = $contador + 1;		
	$offset_Provincia = $contador + 4;	
	$llave_Beneficio  = @listaBenficiarios[$offset_Beneficio];
	$llave_Provincia  = @listaBenficiarios[$offset_Provincia];
	if(!exists($beneficios{$llave_Beneficio})){
		$beneficios->{$llave_Beneficio}=1;
			
	}		
 	
	if(!exists($matriz->{$llave_Provincia})){
	
		${$matriz->{$llave_Provincia}}{$llave_Beneficio}=1;		
	}else{
		if(!exists(${$matriz->{$llave_Provincia}}{$llave_Beneficio})){
		
		${$matriz->{$llave_Provincia}}{$llave_Beneficio}=1;		
	}else{
		${$matriz->{$llave_Provincia}}{$llave_Beneficio}+=1;				
	}	
	}
	$contador = $contador + 8;
}
	rellenarMatriz($beneficios,$matriz);
	calcularTotal($beneficios,$matriz);	
}

#--------------------------PRINCIPAL-----------------------------------------------------------#

#validacion de parametros

if($ENV{"GRUPO"} eq ""){
	exit 0;
}

if($beneficios eq ""){
	$beneficios = '.*';
}

if( $agencias eq ""){
	 $agencias='.*';
}
#Se listan todos los archivos del directorio data


opendir(DIR,$dirName)|| `$log "listaBeneficiarios" E "error al abrir el directorio\n"`;

while($filename=readdir(DIR)){
	push(@files,$filename);
}
closedir(DIR);

#Se busca de la lista de archivos encontrados aquellos que coincidan con los nobres de archivos pasados por parametro 

@encontrados = grep(/$arch_Beneficiarios/,@files);
 
if(@encontrados==0)
{
	`$log "listaBeneficiarios" I "NO SE ENCONTRO NINGUN ARCHIVO DE BENEFICIARIOS\n"`;
	
}else{
	@listaBenficiarios = listar(@encontrados,$filtroPorEstado);
	my $cantArchivosEncontrados = @encontrados;
	my $canBenefEncontrados = @listaBenficiarios; 	
		
	`$log "listaBeneficiarios" I "Numero de archivos benef encontrados (sin filtrar) :$canBenefEncontrados\n"`;	
	`$log "listaBeneficiarios" I "Numero de beneficiarios encontrados (filtrado) :$canBenefEncontrados\n"`;	
	
	$conMatriz = false;
	@cabecera = getCabecera();
	#--------------------VALIDANDO Y GENERANDO LISTA - MATRIZ----------------
	if($opcionListaMatriz eq "-c")
	{
		matrizControl(\%beneficios,\%matriz);
		$conMatriz	 = true;	
	} 		
	#-----------------------------SALIDA-----------------------------------	

	#EN ARCHIVO plist.<secuencia>
	if($opcionSalida eq '-d')
	{
		escribirEnArchivo($conMatriz,\%matriz,\%beneficios);
	}

	#POR ARCHIVO Y PANTALLA
	elsif($opcionSalida eq '-td' | $opcionSalida eq '-dt')
	{
		escribirEnArchivo($conMatriz,\%matriz,\%beneficios);
		imprimirInfo($conMatriz,\%matriz,\%beneficios);
	}else{
		imprimirInfo($conMatriz,\%matriz,\%beneficios);
	}	 				 	
}	
#close(LOG);

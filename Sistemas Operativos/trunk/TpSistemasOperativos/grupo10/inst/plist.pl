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
 
#argumentos archivo benef, agencia y beneficios


my $arch_Beneficiarios = $ARGV[0];
my $agencias = $ARGV[1]; 
my $beneficios = $ARGV[2];
my $opcionSalida = $ARGV[3];
my $opcionListaMatriz = $ARGV[4];
my %matriz;
my %beneficios;
my $file;
my @files;
my $dir_Actual = './grupo10/data/'; 
my $log ='>>.grupo10/data/log.txt';
my $dirName ='./grupo10/data/';
my $dirSalidaArchivo ='./grupo10/list';
my $ardestino = 'plist';
my $salidaPorArchivo = '>./grupo10/list/';
my @listaBenficiarios;

#----------------------------CABECERA---------------------------------

sub getCabecera(){
	
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
	$year += 1900;
	$mon +=2; 
	$mday -=20;
	$hour -=6;
	$min  -=29;
	$hora = "$hour:$min:$sec";
	$fecha= "$mday/$mon/$year";
	
	push(@cabecera,"  ");	
	push(@cabecera,$hora);
	push(@cabecera,"     ");	
	push(@cabecera,$fecha);
	push(@cabecera,"     ");
	push(@cabecera,$arch_Beneficiarios);
	push(@cabecera,"     ");	
	push(@cabecera,$agencias);
	push(@cabecera,"     ");
	push(@cabecera,$beneficios);

	return @cabecera;
	
}

#-----------------------------------IMPRESION-------------------------

sub imprimirInfo
{
	
	my $con_Matriz = shift;
	my $matriz =shift;
	my $beneficios = shift;
	
	print "@cabecera\n";
	print "@listaBenficiarios\n";
	if($conMatriz){
	   foreach $llave (keys %{$matriz}){
	   	 	    
		if(! ($llave eq 'totalBeneficiario')){	         
		   print $llave;			  
		   foreach $llave2 (keys %{$beneficios}){
		      print "       ".${$matriz->{$llave}}{$llave2}; 
	    	   }
		 print "\n";
		}
           }				
	#Muestra el total de beneficiarios por beneficios(por columna)	
	print "ToltaBeneficiario   ";
	foreach $llaveBeneficio (keys %{$beneficios}){
		print ${$matriz->{'totalBeneficiario'}}{$llaveBeneficio}."       ";
	}
		
		
	}
		

}
#-----------------------------ESCRIBIR EN ARCHIVO---------------------

sub escribirEnArchivo{
	
my $conMatriz = shift;
my $matriz = shift;
my $beneficios = shift;
my $secuencia=0;

$secuencia = `ls "./EjemplosPerl/list" | grep ".*plist.[1-9]" | sort -r | sed s/$ardestino.// | head -n 1`;
print $ultimaSecuencia;
if($secuencia > 0){
	$secuencia ++;
}else{
	$secuencia =1;
}
$rutaArchivo = ">>".$dirSalidaArchivo."/plist.".$secuencia;
print $rutaArchivo;
open(PLIST,$rutaArchivo);
print "@cabecera\n";
print PLIST "@listaBenficiarios\n";

if($conMatriz){
	   foreach $llave (keys %{$matriz}){
		 if(! ($llave eq 'totalBeneficiario')){	   
	   	 print PLIST $llave;	    
	         foreach $llave2 (keys %{$beneficios}){
		      print PLIST "       ".${$matriz->{$llave}}{$llave2}; 
	    	 }
		 print PLIST "\n";
		 }
           }				
	}
	#Muestra el total de beneficiarios por beneficios(por columna)	
	print "ToltaBeneficiario   ";
	foreach $llaveBeneficio (keys %{$beneficios}){
		print ${$matriz->{'totalBeneficiario'}}{$llaveBeneficio}."       ";
	}
close(PLIST);
}

#---------------------------------LISTAR------------------------------

sub listar(@encontrados,$dir_Actual){

	
	my @listaBeneficiarios;
	my @listaBeneficiariosTemp;
	foreach $nombreArch (@encontrados){
		$ruta = $dir_Actual.$nombreArch;
		open(OUT,$ruta);
		while($linea=<OUT>){			
			push(@listaBeneficiariosTemp,$linea);
		}
		close(OUT);		
	}
	
	@listaBeneficiarios = grep(/$agencias,.*,.*,.*,.*,.*,.*,.*,.*,.*,$beneficios,.*,.*,.*,.*,.*,.*,.*,.*/,@listaBeneficiariosTemp);
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
#-------------------------------RELLENAR -
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

#------------------------------------CALCULO TOTAL--------------------

sub calcularTotal{


	my $beneficios = shift;
	my $matriz     = shift;	

	#Total beneficiario por provincia
	foreach $llaveProvincia (keys %{$matriz}){
		my $totalBeneficiario=0;		
		foreach $llaveBeneficio (%{$beneficios}){
			$totalBeneficiario += ${$matriz->{$llaveProvincia}}{$llaveBeneficio};			
		}
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
	$beneficios->{'totalBeneficiario'}=1;
}


#-------------------------------MATRIZ DE CONTROL---------------------

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

#--------------------------PRINCIPAL---------------------------------#

#validacion de parametros
if($beneficios eq ""){
	$beneficios = '.*';
}

if( $agencias eq ""){
	 $agencias='.*';
}
#Se listan todos los archivos del directorio data
opendir(DIR,$dirName)||die "error al abrir el directorio\n";
while($filename=readdir(DIR)){
	push(@files,$filename);
}
closedir(DIR);

#Se busca de la lista de archivos encontrados aquellos que coincidan con los nobres de archivos pasados por parametro 

@encontrados = grep(/$arch_Beneficiarios/,@files);
 
if(@encontrados==0)
{
	open(LOG,$log);
	print LOG "NO SE ENCONTRO NINGUN ARCHIVO DE BENEFICIARIOS";
	close(LOG);
}else{
	@listaBenficiarios = listar(@encontrados,$dir_Actual);
	@cabecera = getCabecera();
	
	push(@cabecera,$opcionListaMatriz);
	push(@cabecera,$opcionSalida);
	
	$conMatriz = false;
	
	if($opcionListaMatriz eq "-c")
	{
		matrizControl(\%beneficios,\%matriz); 
		$conMatriz	 = true;	
	}	
	if($opcionSalida eq '-t')
	{
		imprimirInfo($conMatriz,\%matriz,\%beneficios);
	}
	if($opcionSalida eq '-d')
	{
		escribirEnArchivo($conMatriz,\%matriz,\%beneficios);
	}
	if($opcionSalida eq '-td' | $opcionSalida eq '-dt')
	{
		escribirEnArchivo($conMatriz,\%matriz,\%beneficios);
		imprimirInfo($conMatriz,\%matriz,\%beneficios);
	}	 				 	
}	


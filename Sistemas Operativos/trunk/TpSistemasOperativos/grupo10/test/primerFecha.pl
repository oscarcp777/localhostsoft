#!usr/bin/perl

# Parametros
# 1.Zona
# 2.Plan

# Ejemplo corrida ./primerFecha.pl Zona_1 Plan_A


$zona=$ARGV[0];
$plan=$ARGV[1];

if($#ARGV+1 <2)
{
	die "Menos de dos parametros, ejecucion fallida";
}

# Validar Plan
open(PLAN,"plan.tab");
@planes=<PLAN>;
foreach $regPlan (@planes){
	@campos=split(",",$regPlan);
	if($campos[0] eq $plan){
		$descripcion=$campos[1];
	}
}
unless($descripcion){
	die "El plan $plan no existe";
}

# Archivos a procesar
opendir(DIR,".") || die "No se puede leer el directorio actual";

while($arch=readdir(DIR)){
	if($arch =~ /^benef/)
	{
		push(@archivos,$arch);
	}
	
}
closedir(DIR);
# Recorro archivos de beneficiarios
foreach $nombreArchivo (@archivos)
{
	open(ARCH,$nombreArchivo) || die "No se pudo abrir el archivo $nombreArchivo";
	@registros=<ARCH>;
	# Recorro registros de ese archivo
	foreach $registro (@registros)
	{
		@campos=split(",",$registro);
		# Valido que se cumplan filtros zona y plan indicados
		if ($campos[1] eq $zona && $campos[2] eq $plan)
		{
			# Calcular Montos por Oficina
			$montos{$campos[0]}+=$campos[5];
		}
	}
	close(ARCH);
}

print "Ingrese nombre archivo de salida...\n";
$archSalida=<STDIN>;
chop($archSalida);

if(open (SALIDA,"$archSalida")){
	print "El archivo de salida existe, desea sobreescribirlo(SI/NO)?\n";
	$resp=<STDIN>;
	chop($resp);
	if($resp eq "SI"){
		close(SALIDA);
		open (SALIDA,">$archSalida");
	}else{
		close(SALIDA);
		die "Ejecucion finalizada, no se realizaron cambios";
	}
}else{
	open (SALIDA,">$archSalida");
}



# Recorro hash y grabo resultados
foreach $registro (keys %montos)
{
	print SALIDA "$registro,$montos{$registro}\n";
	if ($montos{$registro}<=1000){
		print "Para el plan \"$descripcion\" en la zona $zona, la oficina $registro no supero los \$1000\n";
	}
}

close(SALIDA); 


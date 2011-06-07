#! /usr/bin/perl
$cant=$ARGV;
if($cant < 1){
	die "Error en la cantidad  de parametros";
}
$zona="capital";#$ARGV[0];
$plan=210;#$ARGV[1];
print "$zona $plan \n";
print "\n";
opendir(RAIZ,".");
%hashOficinaMonto=();
while($arch=readdir(RAIZ)){
	
	if($arch =~ /^benef*/){
		open FILE, "<",$arch or die "error no se pudo abirir el arhcivo";
		@registros=<FILE>;
		foreach $reg (@registros){
			@campos=split /,/,$reg;
			$oficina=$campos[0];
			$monto=$campos[5];
			if($campos[1] eq $zona && $campos[2] eq $plan){
			$hashOficinaMonto{$oficina}+=$monto;
		    }
			
		}
		close(FILE);
	}
	
}
$descripcion="";
open FILE3,"<","plan1.tb" or die "mal";
@registros=<FILE3>;
foreach $reg (@registros){
	@campos=split /,/,$reg;
	if("$plan" eq $campos[0]){
		$descripcion=$campos[1];
	}
}
print "escriba archivos de salida : ";
$arch2=<STDIN>;
chop($arch2);
if(-e $arch2){
	print "el archivo ya existe desea sobreescribirlo s/n :";
	$result=<STDIN>;
	chop($result);
	if("$result" eq "s"){
		open FILE3,">",$arch2 or die "error";
		close(FILE3);
	}
	if("$result" eq "n"){
		die "se sale sin hacer nada";
	}
}
open FILE2,">>",$arch2 or die "error";
foreach $key (sort(keys(%hashOficinaMonto))){
	    print FILE2 "$key,$hashOficinaMonto{$key}\n";
	    if($hashOficinaMonto{$key} <= 1000){
	    	print "Para el plan \"$descripcion\" en la zona $zona la oficina $key no supero los \$1000 \n";
	    }
}
close(FILE2);
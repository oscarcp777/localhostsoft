#!/usr/bin/perl

# PARCIAL 24/05/2005
# ARGUMENTOS
#  1.Parámetro 3: Nombre del archivo de ENTRADA
#  2.Parámetro 2: Ubicación del campo cliente
#  3.Parámetro 1: Ubicación del campo monto
#  4.Parámetro 4: Nombre del archivo de SALIDA

#ejemplo ./saca_saldo_doni 2 1 pagos.txt saldos.txt


# Hash con los saldos clientes, clave=cliente, valor=saldo
#%saldos;



if($#ARGV+1 != 4)
{
	die "Cantidad parametros incorrecta"
}



$montoUbic=$ARGV[0];
$cliUbic=$ARGV[1];
$archEntrada=$ARGV[2];
$archSalida=$ARGV[3];

open(ENTRADA,$archEntrada) || die "El archivo de entrada no existe";
open(SALIDA,">$archSalida");

@registros=<ENTRADA>;

if($#registros <=0)
{
	die "El campo de entrada esta vacio";
}

@campos=split(",",$registros[0]);
$numeroCampos=$#campos+1;

if($montoUbic<1 || $montoUbic>$numeroCampos)
{
	die "La ubicacion del monto es invalida";
} 	
if($cliUbic<1 || $cliUbic>$numeroCampos)
{
	die "La ubicacion del cliente es invalida";
}

foreach $registro (@registros)
{
	@campos=split(",",$registro);
	$cliente= $campos[$cliUbic-1];
	$monto= $campos[$montoUbic-1];
	unless($saldos{$cliente})
	{
		$saldos{$cliente}=$monto;
	}else
	{
		$saldos{$cliente}= $saldos{$cliente} + $monto;
	}
	
}


foreach $registro (keys %saldos)
{
	print SALIDA "$registro;$saldos{$registro}\n"
}

close (SALIDA);
close (ENTRADA);

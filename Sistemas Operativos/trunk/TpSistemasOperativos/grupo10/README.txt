Pasos a seguir para instalar el software:

1) Copiar el archivo TPSistemasOp.tgz en un directorio de su PC . Dicho directorio lo llamaremos "<DirInstalacion>" de ahora en mas

2) Descomprimir TPSistemasOp.tgz en el direcotrio que lo copio. 
Esto puede realizarlo desde una consola con el comando: "tar xzvf TPSistemasOp.tgz"

3)La accion 2 le generara la siguiente estructura de directorio
    <DirInstalacion>    |
		     	|-grupo10 |
			          |-inst

 +---------------------------------------------------------------------------------------------+
 | IMPORTANTE: Es necesario que esta estructura este creada para poder realizar la instalación.|
 |	      Cualquier archivo o directorio faltante no permitira continuar la instalación    	   |
 +---------------------------------------------------------------------------------------------+

4) Defina la variable $GRUPO con la ruta del directorio donde copio el archivo TPSistemasOp.tgz. Esto es con la ruta de  <DirInstalacion>
   Esto lo puede realizar desde una consola de la siguiente manera: "export GRUPO=<DirInstalacion>"
   EJ:  Si copio TPSistemasOp.tgz en "/home/user/"
	En la consola debo escribir "export GRUPO=/home/user/"
   +----------------------------------------------------------------------------------------+
   |IMPORTANTE:  Si no realiza el paso 4) el programa no se podra instalar		    		|		 
   |		 El directorio debe terminar con "/" como en el ejemplo GRUPO="/home/user/" 	|
   +----------------------------------------------------------------------------------------+
 

5) Dirijase al directorio <DirInstalacion>/grupo05/inst/ y ejecute el comando instula.sh desde una consola 
   de la siguiente forma "./instula.sh"
   +-------------------------------------------------------------------------------------+
   |IMPORTANTE: La ejecucion de instalar.sh debe ser como se muestra "./instalar.sh".	 |
   |		De lo contrario la instalacion NO sera exitosa		 						 |	
   +-------------------------------------------------------------------------------------+

Para correr el software:

1) Ingresar a la carpeta <DirInstalacion>/grupo10/bin por consola o la carpeta que se haya seleccionado como destino de ejecutables

2) Llamar a iniciar.sh con el comando ". ./iniciar.sh"
Ej: >. ./iniciar.sh




#include "archivo.hpp"
#include <string.h>

Archivo::Archivo(unsigned int longitud, const std::string& nombre_archivo) throw(): Almacenamiento(longitud), nombre_archivo(nombre_archivo)
{
}

Archivo::Archivo(unsigned int longitud, const std::string& nombre_archivo, Esquema::puntero esquema, std::list<Clave::puntero>& listaClaves) throw(): Almacenamiento(longitud)
{
    //seteo nombres de archivo y de archivoHeader
    this->nombre_archivo = nombre_archivo;
    this->nombre_archivo_header = nombre_archivo;
    this->nombre_archivo_header.append(".hdr");

    //creo archivo y archivoHeader
    std::fstream archivoDatos(nombre_archivo.c_str(), std::ios_base::out);
    std::fstream archivoHeader(this->nombre_archivo_header.c_str(), std::ios_base::out);

    //persisto esquemas y claves
    Archivo::escribirHeaderModoTexto(archivoHeader, esquema, listaClaves);
}

Archivo::Archivo(unsigned int longitud, const std::string& nombre_archivo, Esquema::puntero esquema, EsquemaBloque::puntero esquemaBloque, std::list<Clave::puntero>& listaClaves) throw(): Almacenamiento(longitud)
{
    //seteo nombres de archivo y de archivoHeader
    this->nombre_archivo = nombre_archivo;
    this->nombre_archivo_header = nombre_archivo;
    this->nombre_archivo_header.append(".hdr");
    this->nombre_archivo_esquemaBloque = nombre_archivo;
    this->nombre_archivo_esquemaBloque.append(".blq");

    //creo archivo y archivoHeader
    std::fstream archivoDatos(nombre_archivo.c_str(), std::ios_base::out);
    std::fstream archivoHeader(this->nombre_archivo_header.c_str(), std::ios_base::out);
    std::fstream archivoEsquemaBloque(this->nombre_archivo_esquemaBloque.c_str(), std::ios_base::out);

    //persisto esquemas y claves
    Archivo::escribirHeaderModoTexto(archivoHeader, esquema, listaClaves);
    Archivo::escribirEsquemaBloqueModoTexto(archivoEsquemaBloque, esquemaBloque);
}



Archivo::~Archivo() throw() {
	this->cerrar();
	this->archivoHeader.close();
}

void Archivo::crearModoTexto(const std::string& nombre_archivo, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw() {
	std::fstream archivoTemporal(nombre_archivo.c_str(), std::ios_base::out);
	Archivo::escribirHeaderModoTexto(archivoTemporal, esquema, listaClaves);
}

void Archivo::crearModoBinario(const std::string& nombre_archivo, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw() {
	std::fstream archivoTemporal(nombre_archivo.c_str(), std::ios_base::out | std::ios_base::binary);
	Archivo::escribirHeaderModoBinario(archivoTemporal, esquema, listaClaves);
}

void Archivo::escribirHeaderModoTexto(std::fstream& archivoTemporal, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw() {
	if (archivoTemporal.is_open()) {
		// Persisto el esquema
		Esquema::iterador_campos actual_campo_esquema = esquema->primer_campo();
		Esquema::iterador_campos fin_campo_esquema = esquema->ultimo_campo();
		unsigned int cantidad_campos_esquema = esquema->cantidad_campos();

		// Persisto cantidad de campos del esquema
		archivoTemporal << cantidad_campos_esquema << " ";
		// Persisto cada campo
		while (actual_campo_esquema != fin_campo_esquema) {
			unsigned int longitud_campo_esquema = actual_campo_esquema->first.size();
			TipoCampo tipo_campo_esquema = actual_campo_esquema->second;
			archivoTemporal << longitud_campo_esquema << " ";
			archivoTemporal << actual_campo_esquema->first << " ";
			archivoTemporal << tipo_campo_esquema << " ";
			++actual_campo_esquema;
		}

		// Persisto las claves
		std::list<Clave::puntero>::const_iterator actual_clave = listaClaves.begin();
		std::list<Clave::puntero>::const_iterator fin_clave = listaClaves.end();
		unsigned int cantidad_claves = listaClaves.size();

		// Persisto cantidad de claves
		archivoTemporal << cantidad_claves << " ";
		while (actual_clave != fin_clave) {
			const Clave::puntero elemento_actual = *actual_clave;
			Clave::iterador_campos_constante actual_campo_clave = elemento_actual->primer_campo();
			Clave::iterador_campos_constante fin_campo_clave = elemento_actual->ultimo_campo();
			unsigned int cantidad_campos_clave = elemento_actual->cantidad_campos();

			// Persisto cantidad de campos
			archivoTemporal << cantidad_campos_clave << " ";
			while (actual_campo_clave != fin_campo_clave) {
				unsigned int longitud_campo_clave = actual_campo_clave->size();
				archivoTemporal << longitud_campo_clave << " ";
				archivoTemporal << *actual_campo_clave << " ";
				++actual_campo_clave;
			}
			++actual_clave;
		}
		// Cierro archivo temporal
		archivoTemporal.close();
	}
}

void Archivo::escribirEsquemaBloqueModoTexto(std::fstream& archivoEsquemaBloque, EsquemaBloque::puntero esquemaBloque)
{
    if(archivoEsquemaBloque.is_open())
    {
        //almaceno la cantidad de bloques
        archivoEsquemaBloque << esquemaBloque->GetCantidadDeBloques() << " ";

        //guardo el espacio ocupado por cada bloque
        for(EsquemaBloque::iterador it = esquemaBloque->primerCampo(); it != esquemaBloque->ultimoCampo(); it++)
            archivoEsquemaBloque << it->second << " ";

        archivoEsquemaBloque.close();
    }
}

void Archivo::LeerHeaderBloque()
{
    this->archivoEsquemaBloque.close();
    this->archivoEsquemaBloque.open(this->nombre_archivo_esquemaBloque.c_str());
    if (!this->archivoEsquemaBloque.is_open())
	{
		this->archivoEsquemaBloque.open(this->nombre_archivo_esquemaBloque.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
		this->archivoEsquemaBloque.close();
		this->archivoEsquemaBloque.open(this->nombre_archivo_esquemaBloque.c_str());
	}

    char linea[256];
    char *a, *b;
    char cantidadBloques[4];
    char espacioOcupado[4];

    this->archivoEsquemaBloque.read(linea, 256);

    a = linea;
    b = cantidadBloques;
    while ( *a!=' ' && *a!='\0')
    {
        *b = *a;
        b++;
        a++;
    }
    *b='\0';
    a++;

    this->esquemaBloque = new EsquemaBloque(atoi(cantidadBloques));

    for(int i = 0; i < this->esquemaBloque->GetCantidadDeBloques(); i++)
    {
        b = espacioOcupado;
        while ( *a!=' ' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;
        this->esquemaBloque->SetEspacioOcupado(i, atoi(espacioOcupado));
        *espacioOcupado = '\0';
    }

	this->archivoEsquemaBloque.close();

}

void Archivo::ActualizarEsquemaBloque(EsquemaBloque::puntero esquemaBloque)
{
    this->esquemaBloque = esquemaBloque;
    this->archivoEsquemaBloque.open(this->nombre_archivo_esquemaBloque.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
    this->escribirEsquemaBloqueModoTexto(this->archivoEsquemaBloque, this->esquemaBloque);
    this->archivoEsquemaBloque.close();
}

void Archivo::LeerHeader()
{
    this->archivoHeader.close();
	this->archivoHeader.open(this->nombre_archivo_header.c_str());
	if (!this->archivoHeader.is_open())
	{
		this->archivoHeader.open(this->nombre_archivo_header.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
		this->archivoHeader.close();
		this->archivoHeader.open(this->nombre_archivo_header.c_str());
	}
	leerHeaderModoTexto();
	this->archivoHeader.close();
}

void Archivo::leerHeaderModoTexto() throw()
{
	if (this->archivoHeader.is_open()) {
		// Creo esquema
		this->esquema = new Esquema();
		 int cantidad_campos_esquema;
		// Leo cantidad de campos esquema
		this->archivoHeader >> cantidad_campos_esquema;

		for (int contador = 0; contador < cantidad_campos_esquema; ++contador) {
			unsigned int longitud_campo_esquema;
			std::string campo_esquema;
			unsigned int tipo_campo_esquema;
			this->archivoHeader >> longitud_campo_esquema;
			this->archivoHeader >> campo_esquema;
			this->archivoHeader >> tipo_campo_esquema;
			this->esquema->agregar_campo(campo_esquema, (TipoCampo) tipo_campo_esquema);
		}

		 int cantidad_claves;
		this->archivoHeader >> cantidad_claves;

		for (int contador = 0; contador < cantidad_claves; ++contador) {
			 int cantidad_campos_clave;
			this->archivoHeader >> cantidad_campos_clave;
			Clave::puntero clave_actual = new Clave();
			for (int contadorInterno = 0; contadorInterno < cantidad_campos_clave; ++contadorInterno) {
				unsigned int longitud_campo_clave;
				std::string campo_clave;
				this->archivoHeader >> longitud_campo_clave;
				this->archivoHeader >> campo_clave;
				clave_actual->agregar_campo(campo_clave);
			}
			this->listaClaves.push_back(clave_actual);
		}
		this->offset_header = this->archivoHeader.tellg();
	}
}

void Archivo::escribirHeaderModoBinario(std::fstream& archivoTemporal, Esquema::puntero esquema, const std::list<Clave::puntero>& listaClaves) throw() {
        if (archivoTemporal.is_open()) {
                // Persisto el esquema
                Esquema::iterador_campos actual_campo_esquema = esquema->primer_campo();
                Esquema::iterador_campos fin_campo_esquema = esquema->ultimo_campo();
                unsigned int cantidad_campos_esquema = esquema->cantidad_campos();

                // Persisto cantidad de campos del esquema
                archivoTemporal.write((char*)&cantidad_campos_esquema, sizeof(cantidad_campos_esquema));
                // Persisto cada campo
                while (actual_campo_esquema != fin_campo_esquema) {
                        unsigned int longitud_campo_esquema = actual_campo_esquema->first.size();
                        TipoCampo tipo_campo_esquema = actual_campo_esquema->second;
                        archivoTemporal.write((char*)&longitud_campo_esquema, sizeof(longitud_campo_esquema));
                        archivoTemporal.write(actual_campo_esquema->first.c_str(), longitud_campo_esquema);
                        archivoTemporal.write((char*)&tipo_campo_esquema, sizeof(tipo_campo_esquema));
                        ++actual_campo_esquema;
                }

                // Persisto las claves
                std::list<Clave::puntero>::const_iterator actual_clave = listaClaves.begin();
                std::list<Clave::puntero>::const_iterator fin_clave = listaClaves.end();
                unsigned int cantidad_claves = listaClaves.size();

                // Persisto cantidad de claves
                archivoTemporal.write((char*)&cantidad_claves, sizeof(cantidad_claves));
                // Persisto cada clave
                while (actual_clave != fin_clave) {
                        const Clave::puntero elemento_actual = *actual_clave;
                        Clave::iterador_campos_constante actual_campo_clave = elemento_actual->primer_campo();
                        Clave::iterador_campos_constante fin_campo_clave = elemento_actual->ultimo_campo();
                        unsigned int cantidad_campos_clave = elemento_actual->cantidad_campos();

                        // Persisto cantidad de campos clave
                        archivoTemporal.write((char*)&cantidad_campos_clave, sizeof(cantidad_campos_clave));
                        while (actual_campo_clave != fin_campo_clave) {
                                unsigned int longitud_campo_clave = actual_campo_clave->size();
                                archivoTemporal.write((char*) &longitud_campo_clave, sizeof(longitud_campo_clave));
                                archivoTemporal.write(actual_campo_clave->c_str(), longitud_campo_clave);
                                ++actual_campo_clave;
                        }
                        ++actual_clave;
                }
                // Cierro el archivo temporal
                archivoTemporal.close();
        }
}

void Archivo::leerHeaderModoBinario() throw() {

}

std::list<Clave::puntero> Archivo::obtener_claves() const throw() {
	return this->listaClaves;
}

void Archivo::establecer_nombre_archivo(const std::string& nombre_archivo) throw() {
	this->nombre_archivo = nombre_archivo;
}

std::string Archivo::obtener_nombre_archivo() const throw() {
	return this->nombre_archivo;
}

void Archivo::abrirModoTexto() throw() {
	this->archivo.close();
	this->archivo.open(this->nombre_archivo.c_str());
	if (!this->archivo.is_open()) {
		this->archivo.open(this->nombre_archivo.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::app);
		this->archivo.close();
		this->archivo.open(this->nombre_archivo.c_str());
	}
	//this->leerHeaderModoTexto();
}

void Archivo::abrirModoBinario() throw() {
	this->archivo.close();
	this->archivo.open(this->nombre_archivo.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::binary);
	if (!this->archivo.is_open()) {
		this->archivo.open(this->nombre_archivo.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::app);
		this->archivo.close();
		this->archivo.open(this->nombre_archivo.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::binary);
	}
	//this->leerHeaderModoBinario();
}

void Archivo::cerrar() throw() {
	this->archivo.close();
}

bool Archivo::escribir(const char* bytes, unsigned int posicion) throw() {
	unsigned int offset = posicion * this->obtener_longitud_en_bytes();
	this->archivo.seekp(offset, std::ios_base::beg);
	this->archivo.write(bytes, this->obtener_longitud_en_bytes());
	bool exitoso = this->archivo.good();

	if (!exitoso) {
		this->archivo.clear();
	}
	return exitoso;
}

bool Archivo::escribir(const char* bytes, unsigned int posicion, unsigned int tamanio) throw() {
	unsigned int offset = posicion * this->obtener_longitud_en_bytes();
	this->archivo.seekp(offset, std::ios_base::beg);
	this->archivo.write(bytes, tamanio);
	bool exitoso = this->archivo.good();

	if (!exitoso) {
		this->archivo.clear();
	}
	return exitoso;
}

bool Archivo::leer(char* bytes, unsigned int posicion) throw() {
	unsigned int offset = posicion * this->obtener_longitud_en_bytes();
	this->archivo.seekg(offset, std::ios_base::beg);
	this->archivo.read(bytes, this->obtener_longitud_en_bytes());
	bool exitoso = this->archivo.good();

	if (!exitoso) {
		this->archivo.clear();
	}
	return exitoso;
}

bool Archivo::leer(char* bytes, unsigned int posicion, unsigned int tamanio) throw() {
	unsigned int offset = posicion * this->obtener_longitud_en_bytes();
	this->archivo.seekg(offset, std::ios_base::beg);
	this->archivo.read(bytes, tamanio);
	bool exitoso = this->archivo.good();

	if (!exitoso) {
		this->archivo.clear();
	}
	return exitoso;
}

bool Archivo::agregar(char* bytes) throw() {
	this->archivo.seekp(0, std::ios_base::end);
	this->archivo.write(bytes, this->obtener_longitud_en_bytes());
	bool exitoso = this->archivo.good();

	if (!exitoso) {
		this->archivo.clear();
	}
	return exitoso;
}

unsigned int Archivo::obtener_cantidad_registros() throw() {
	this->archivo.seekp(0, std::ios_base::end);
	unsigned int posicion = this->archivo.tellp();
	unsigned int cantidad_registros = posicion / this->obtener_longitud_en_bytes();
	return cantidad_registros;
}


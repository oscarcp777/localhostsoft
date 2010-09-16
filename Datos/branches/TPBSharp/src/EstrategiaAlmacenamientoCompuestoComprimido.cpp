#include "EstrategiaAlmacenamientoCompuestoComprimido.hpp"
#include <iostream>

EstrategiaAlmacenamientoCompuestoComprimido::EstrategiaAlmacenamientoCompuestoComprimido(ComparadorClave::puntero comparadorClave)
{
    this->comparadorClave = comparadorClave;
    this->esquemaBloque = NULL;
}

EstrategiaAlmacenamientoCompuestoComprimido::~EstrategiaAlmacenamientoCompuestoComprimido() throw()
{
}

bool EstrategiaAlmacenamientoCompuestoComprimido::Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    //chequeo si el almacenamiento es de tipo archivo para chequear que este abierto antes de continuar
    Archivo::puntero archivo = almacenamiento;
    if(archivo != NULL)
    {
        archivo->cerrar();
        archivo->abrirModoBinario();
    }

    this->esquemaBloque = almacenamiento->GetEsquemaBloque();
    int espacioOcupado = esquemaBloque->GetEspacioOcupado(posicion);

    Registro::puntero registro = componente;
    BloqueCompresor::puntero blq_cmp;

    ///OJO: leer bloque seria
    char* bytesBloque = new char[almacenamiento->obtener_longitud_en_bytes()];
    blq_cmp = new BloqueCompresor( almacenamiento->GetEsquema(), registro->obtener_clave_primaria() , almacenamiento->obtener_longitud_en_bytes());

    if(almacenamiento->leer(bytesBloque, posicion))
        blq_cmp->establecer_datos_comprimidos(bytesBloque, espacioOcupado);

    int cantidadReg = blq_cmp->cantidad_componentes();

    if ( blq_cmp->puede_agregar_componente( registro ) )
            blq_cmp->agregar_componente( registro );
    else
        return false;

    const char * bytes = blq_cmp->obtener_datos_comprimidos();

    bool exitoso = archivo->escribir( bytes, posicion);
    int longitudOcupada = blq_cmp->obtener_longitud_ocupada();

    if(exitoso)
    {
        this->esquemaBloque->SetEspacioOcupado(posicion, longitudOcupada);
        ///PROBAR: haciendo esto aca funciona bien???? asi no seria necesario andar haciendo a cada rato luego de escribir
        almacenamiento->ActualizarEsquemaBloque(this->esquemaBloque);
    }

    if(archivo != NULL)
        archivo->cerrar();

    delete[] bytes;
    return exitoso;
}

Componente::puntero EstrategiaAlmacenamientoCompuestoComprimido::Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave)
{
    Archivo::puntero archivo = almacenamiento;
    if(archivo != NULL)
    {
        archivo->cerrar();
        archivo->abrirModoBinario();
    }
    //obtengo los esquemas
    Esquema::puntero esquema = almacenamiento->GetEsquema();
    this->esquemaBloque = almacenamiento->GetEsquemaBloque();

    //creo el bloque compresor
    BloqueCompresor::puntero blq_cmp = new BloqueCompresor(esquema, clave, almacenamiento->obtener_longitud_en_bytes());

    char* bytesBloque = new char[almacenamiento->obtener_longitud_en_bytes()];

    //leo los bytes comprimidos y devuelvo el bloque compresor
    if(almacenamiento->leer(bytesBloque, posicion))
    {
        blq_cmp->establecer_datos_comprimidos( bytesBloque, this->esquemaBloque->GetEspacioOcupado(posicion));
        int cantidadReg = blq_cmp->cantidad_componentes();

        BloqueCompresor::iterador_componentes_constante actualComponente = blq_cmp->primer_componente();
        BloqueCompresor::iterador_componentes_constante finComponente = blq_cmp->ultimo_componente();

        while(actualComponente != finComponente)
        {
            RegistroLongitudVariable::puntero registro = *actualComponente;
            if ( comparadorClave->es_igual(clave, registro, this->registroAuxiliar) )
            {
                delete[] bytesBloque;
                return registro;
            }
            actualComponente++;
        }
    }
    delete[] bytesBloque;
    return NULL;
}

int EstrategiaAlmacenamientoCompuestoComprimido::AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    Registro::puntero registro = componente;
    Archivo::puntero archivo = almacenamiento;
    if(archivo != NULL)
    {
        archivo->cerrar();
        archivo->abrirModoBinario();
    }

    this->esquemaBloque = almacenamiento->GetEsquemaBloque();
    Esquema::puntero esquema = almacenamiento->GetEsquema();

    std::string registroComprimido = BloqueCompresorHelper::comprimir_registro(esquema, registro);
    int longitudComprimidaRegistro = registroComprimido.length();
    int espacioOcupado = 0;
    int posicion = -1;
    int longitudEnBytes = almacenamiento->obtener_longitud_en_bytes();

    for(int i = 0; i < this->esquemaBloque->GetCantidadDeBloques(); i++)
    {
        espacioOcupado = this->esquemaBloque->GetEspacioOcupado(i);
        if(espacioOcupado + longitudComprimidaRegistro <= longitudEnBytes)
        {
            posicion = i;
            break;
        }
    }

    if(posicion > -1 && this->Escribir(posicion, componente, almacenamiento))
        return posicion;
    return -1;
}

EsquemaBloque::puntero EstrategiaAlmacenamientoCompuestoComprimido::GetEsquemaBloque()
{
    return this->esquemaBloque;
}

ComparadorClave::puntero EstrategiaAlmacenamientoCompuestoComprimido::GetComparador()
{
    return this->comparadorClave;
}

void EstrategiaAlmacenamientoCompuestoComprimido::SetRegistroConDatosClave(Registro::puntero registroAuxiliar)
{
    this->registroAuxiliar = registroAuxiliar;
}

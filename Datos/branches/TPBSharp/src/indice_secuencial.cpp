#include "indice_secuencial.hpp"

IndiceSecuencial::IndiceSecuencial(ComparadorClave::puntero comparador)
{
    this->comparador = comparador;
}

IndiceSecuencial::~IndiceSecuencial() throw()
{
}

Registro::puntero IndiceSecuencial::Buscar(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    switch(archivo->GetTipoAlmacenamiento())
    {
        case Bloques:
        {
            return this->BuscarPorBloque(archivo, registroAuxiliar, clave);
            break;
        }
        case Registros:
        {
            return this->BuscarPorRegistro(archivo, registroAuxiliar, clave);
            break;
        }
        case Texto:
        {
            return this->BuscarPorTexto(archivo, registroAuxiliar, clave);
            break;
        }
         case Compresor:
        {
            return this->BuscarPorCompresor(archivo, registroAuxiliar, clave);
            break;
        }
        default:
            return 0;
            break;
    }
}

Registro::puntero IndiceSecuencial::Buscar(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    switch(buffer->GetTipoAlmacenamiento())
    {
        case Bloques:
        {
            return this->BuscarPorBloque(buffer, registroAuxiliar, clave);
        }
        case Registros:
        {
            return this->BuscarPorRegistro(buffer, registroAuxiliar, clave);
            break;
        }
        case Texto:
        {
            return this->BuscarPorTexto(buffer, registroAuxiliar, clave);
            break;
        }
        case Compresor:
        {
            return this->BuscarPorCompresor(buffer, registroAuxiliar, clave);
            break;
        }
        default:
            return 0;
            break;
    }

}

Registro::puntero IndiceSecuencial::BuscarPorRegistro(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    archivo->cerrar();
    archivo->abrirModoBinario();
    int cantidadRegistros = archivo->obtener_cantidad_registros();
    Esquema::puntero esquema = archivo->GetEsquema();
    Registro::puntero registro;
    CampoStream::puntero bufferStream = new CampoStream();
    char* bytes = new char[archivo->obtener_longitud_en_bytes()];

    EstrategiaAlmacenamientoRegistros::puntero estrategia = new EstrategiaAlmacenamientoRegistros();
    for(int i = 0; i < cantidadRegistros; i++)
    {
        registro = estrategia->Leer(i, archivo, clave);
        if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
        {
            archivo->cerrar();
            return registro;
        }
    }

    archivo->cerrar();
    delete[] bytes;
    return 0;
}

Registro::puntero IndiceSecuencial::BuscarPorRegistro(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    Esquema::puntero esquema = buffer->GetEsquema();
    RegistroLongitudFija::puntero registro = new RegistroLongitudFija(clave, buffer->obtener_longitud_en_bytes());
    CampoStream::puntero bufferStream = new CampoStream();
    char* bytes = new char[buffer->obtener_longitud_en_bytes()];

    EstrategiaAlmacenamientoRegistros::puntero estrategia = new EstrategiaAlmacenamientoRegistros();

    for(Buffer::iterador itBuffer = buffer->primero(); itBuffer != buffer->ultimo(); itBuffer++)
    {
        registro = estrategia->Leer(itBuffer->first, buffer, clave);
        if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
            return registro;
    }

    delete[] bytes;
    return 0;
}

Registro::puntero IndiceSecuencial::BuscarPorBloque(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    archivo->cerrar();
    archivo->abrirModoBinario();

    //esquemas
    Esquema::puntero esquema = archivo->GetEsquema();
    EsquemaBloque::puntero esquemaBloque = archivo->GetEsquemaBloque();

    RegistroLongitudVariable::puntero registro;
    CampoStream::puntero bufferStream = new CampoStream();

    //auxiliares
    char* bytes = new char[archivo->obtener_longitud_en_bytes()];
    bool encontrado = false;
    int posicion = 0;
    int espacioOcupado = 0;

    EstrategiaAlmacenamientoBloques::puntero estrategia = new EstrategiaAlmacenamientoBloques(this->comparador);
    estrategia->set_por_buffer(false);
    estrategia->SetRegistroConDatosClave(registroAuxiliar);
    for(int i = 0; i < esquemaBloque->GetCantidadDeBloques(); i++)
    {
        if(esquemaBloque->GetEspacioOcupado(i) != 0)
        {
            registro = estrategia->Leer(i, archivo, clave);
            if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
            {
                archivo->cerrar();
                return registro;
            }
        }
    }

    archivo->cerrar();

    delete[] bytes;
    return 0;
}

Registro::puntero IndiceSecuencial::BuscarPorBloque(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    //esquemas
    Esquema::puntero esquema = buffer->GetEsquema();
    EsquemaBloque::puntero esquemaBloque = buffer->GetEsquemaBloque();

    RegistroLongitudVariable::puntero registro;
    CampoStream::puntero bufferStream = new CampoStream();

    //auxiliares
    char* bytes = new char[buffer->obtener_longitud_en_bytes()];
    bool encontrado = false;
    int posicion = 0;
    int espacioOcupado = 0;

    EstrategiaAlmacenamientoBloques::puntero estrategia = new EstrategiaAlmacenamientoBloques(this->comparador);
    estrategia->set_por_buffer(true);
    estrategia->SetRegistroConDatosClave(registroAuxiliar);
    for(int i = 0; i < esquemaBloque->GetCantidadDeBloques(); i++)
    {
        if(esquemaBloque->GetEspacioOcupado(i) != 0)
        {
            registro = estrategia->Leer(i, buffer, clave);
            if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
                return registro;
        }
    }

    delete[] bytes;
    return 0;
}

Registro::puntero IndiceSecuencial::BuscarPorTexto(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    archivo->cerrar();
    archivo->abrirModoTexto();
    int cantidadRegistros = archivo->obtener_cantidad_registros();
    Esquema::puntero esquema = archivo->GetEsquema();
    Registro::puntero registro;
    CampoStream::puntero bufferStream = new CampoStream();
    char* bytes = new char[archivo->obtener_longitud_en_bytes()];

    EstrategiaAlmacenamientoTexto::puntero estrategia = new EstrategiaAlmacenamientoTexto();
    for(int i = 0; i < cantidadRegistros; i++)
    {
        Registro::puntero registro = estrategia->Leer(i, archivo, clave);
        if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
        {
            archivo->cerrar();
            return registro;
        }
    }
    return 0;
}

Registro::puntero IndiceSecuencial::BuscarPorTexto(Buffer::puntero buffer, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    Esquema::puntero esquema = buffer->GetEsquema();
    RegistroLongitudFija::puntero registro = new RegistroLongitudFija(clave, buffer->obtener_longitud_en_bytes());
    CampoStream::puntero bufferStream = new CampoStream();
    char* bytes = new char[buffer->obtener_longitud_en_bytes()];

    EstrategiaAlmacenamientoTexto::puntero estrategia = new EstrategiaAlmacenamientoTexto();

    for(Buffer::iterador itBuffer = buffer->primero(); itBuffer != buffer->ultimo(); itBuffer++)
    {
        Registro::puntero registro = estrategia->Leer(itBuffer->first, buffer, clave);
        if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
            return registro;
    }

    delete[] bytes;
    return 0;
}

Registro::puntero IndiceSecuencial::BuscarPorCompresor(Archivo::puntero archivo, Registro::puntero registroAuxiliar, Clave::puntero clave)
{
    archivo->cerrar();
    archivo->abrirModoBinario();

    //esquemas
    Esquema::puntero esquema = archivo->GetEsquema();
    EsquemaBloque::puntero esquemaBloque = archivo->GetEsquemaBloque();

    RegistroLongitudVariable::puntero registro;
    CampoStream::puntero bufferStream = new CampoStream();

    //auxiliares
    char* bytes = new char[archivo->obtener_longitud_en_bytes()];
    bool encontrado = false;
    int posicion = 0;
    int espacioOcupado = 0;

    EstrategiaAlmacenamientoCompuestoComprimido::puntero estrategia = new EstrategiaAlmacenamientoCompuestoComprimido(this->comparador);
    estrategia->set_por_buffer(false);
    estrategia->SetRegistroConDatosClave(registroAuxiliar);
    for(int i = 0; i < esquemaBloque->GetCantidadDeBloques(); i++)
    {
        if(esquemaBloque->GetEspacioOcupado(i) != 0)
        {
            registro = estrategia->Leer(i, archivo, clave);
            if(registro != NULL && this->comparador->es_igual(clave, registro, registroAuxiliar))
            {
                archivo->cerrar();
                return registro;
            }
        }
    }

    archivo->cerrar();

    delete[] bytes;
    return 0;
}

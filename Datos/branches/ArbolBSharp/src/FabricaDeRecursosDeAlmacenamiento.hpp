#ifndef FABRICADERECURSOSDEALMACENAMIENTO_HPP
#define FABRICADERECURSOSDEALMACENAMIENTO_HPP

#include "EstrategiaAlmacenamiento.hpp"
#include "almacenamiento.hpp"
#include "componentecompuesto.hpp"
#include "componente.hpp"


class FabricaDeRecursosDeAlmacenamiento
{
    public:
        /**
        Constructor de la clase FabricaDeRecursosDeAlmacenamiento.
        */
        FabricaDeRecursosDeAlmacenamiento();
        /**
        Destructor virtual de la clase FabricaDeRecursosDeAlmacenamiento.
        */
        virtual ~FabricaDeRecursosDeAlmacenamiento();
        /**
        Se crea un recurso de almacenamiento en buffer.
        */
        void RecursoDeAlmacenamientoEnBuffer(EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Almacenamiento* almacenamiento, ComponenteCompuesto* compuesto, Componente* componente);
        /**
        Se crea un recurso de almacenamiento en un archivo.
        */
        void RecursoDeAlmacenamientoEnArchivo(EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Almacenamiento* almacenamiento, ComponenteCompuesto* compuesto, Componente* componente);
        /**
        Se crea un recurso de almacenamiento en buffer y en un archivo.
        */
        void RecursoDeAlmacenamientoEnArchivoConBuffer(EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Almacenamiento* almacenamiento, ComponenteCompuesto* compuesto, Componente* componente);

    protected:

    private:
};

#endif // FABRICADERECURSOSDEALMACENAMIENTO_HPP

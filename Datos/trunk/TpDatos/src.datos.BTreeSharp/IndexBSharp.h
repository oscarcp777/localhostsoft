/*
 * IndexBSharp.h
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#ifndef INDEXBSHARP_H_
#define INDEXBSHARP_H_
#include "ContainerInsertion.h"
#include "InternalNode.h"
#include "LeafNode.h"
#include "../src.datos.models/Registry.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../src.datos.storage/FreeBlockController.h"

#include <string>
#include <list>
class IndexBSharp {
public:
	IndexBSharp(const std::string& nameFile,unsigned int sizeBlock,int typeElement);
	virtual ~IndexBSharp();
	int getLongBytes();
	/**
	 * Agrega un registro en el indice b sharp.
	 */
	 void addRegistry(Registry* registry) throw();
	/**
	 * Remueve un registro en el indice b sharp.
	 */
	 void deleteRegistry(Registry* registry) throw();
	/**
	 * Busca un registro en el indice b sharp.
	 */
	 Registry* searchRegistry(Registry* registry) throw();
	/**
	 * Imprime el arbol en el stream de salida pasado por parametro.
	 */
	void print(std::ostream& streamSalida) throw();
private:
	/**
	 * lee de la posicion de  disco el numero de bloque pasado por parametro
	 */
	Node* readNode(unsigned int pos) throw() ;
	/**
	 *
	 */
	Node* readNodeBytes(Buffer* buffer) throw();
	/**
	 *Lee y desenpaqueta un nodo interno de disco
	 */
	Node* readInternalNodeBytes(Buffer* buffer) throw();
	/**
	 * Lee y desenpaqueta un nodo hoja de disco
	 */
	Node* readLeafNodeBytes(Buffer* buffer) throw();
		/**
		 * Crea el bloque raiz del indice b sharp.
		 */
		void createBlockRoot() throw();
		/**
		 * Lee el bloque raiz del indice b sharp.
		 */
		void readBlockRoot() throw();
		/**
		 * Escribe el bloque raiz del indice b sharp.
		 */
		void writeBlockRoot() throw();
		/**
		 * Maneja el sobreflujo al dividirse el nodo raiz del indice b sharp.
		 */
		void splitLeafRoot(ContainerInsertion* container, Registry* registry) throw();

		void splitInternalRoot(ContainerInsertion* container) throw();
		/**
		 * Inserta un registro en un bloque externo.
		 * @param leafNode - El bloque externo donde insertar el registro.
		 * @param container - El registro a insertar.
		 * @param resultado - El resultado de la insercion del registro en el bloque externo.
		 * @return boolean - Retorna true si hubo division del bloque externo.
		 */
		int insertLeafNode(LeafNode* leafNode,Registry* registry,ContainerInsertion* container,unsigned int brotherNode) throw();
		/**
		 * Inserta un registro en un bloque externo no lleno.
		 * @param LeafNode - El bloque externo donde insertar el registro.
		 * @param Registry - El registro a insertar.
		 */
		void insertLeafNodeNotFull(LeafNode* leafNode,Registry* registry) throw();
		/**
		 * Inserta un registro en un bloque externo lleno.
		 * @param leafNode - El bloque externo donde insertar el registro.
		 * @param registry - El registro a insertar.
		 * @param container - El resultado de insercion del registro en el bloque externo.
		 */
		void insertLeafNodeFull(LeafNode* leafNode,LeafNode* brotherNode,Registry* registry,ContainerInsertion* container) throw();
		/**
		 * Inserta un registro en un bloque interno.
		 * @param internalNode - El bloque interno donde insertar el registro.
		 * @param registry - El registro con la clave a insertar.
		 * @param container - El resultado de la insercion del registro en el bloque interno.
		 * @preturn boolean - Retorna true si hubo division del bloque interno.
		 */
		int insertInternalNode(InternalNode* internalNode,Registry* registry,ContainerInsertion* container,unsigned int brotherBlock,Registry* fatherRegistry) throw();
		/**
		 * Inserta un registro en un bloque interno no lleno.
		 * @param internalNode - El bloque interno donde insertar el registro.
		 * @param registry - El registro con la clave a insertar.
		 */
		void insertInternalNodeNotFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock) throw();
		/**
		 * Inserta un registro en un bloque interno lleno.
		 * @param internalNode - El bloque interno donde insertar el registro.
		 * @param registry - El registro con la clave a insertar.
		 * @param resultado - El resultado de insercion del registro en el bloque interno.
		 */
		void insertInternalNodeFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock,ContainerInsertion* container) throw();
		/**
		 * Busca la posicion de insercion hoja para el registro dado.
		 * @param registry - El registro a insertar en el bloque externo.
		 * @param primer_registro - Iterador al primer registro del bloque externo.
		 * @return unsigned int - La posicion de insercion externa para el registro dado.
		 */
		unsigned int searchPositionInsertLeafNode(Registry* registry, list<Registry*>::iterator IteratorBegin, list<Registry*>::iterator IteratorEnd) throw();
		/**
		 * Busca la posicion de insercion interna para el registro dado.
		 * @param registry - El registro a insertar en el bloque interno.
		 * @param primer_registro - Iterador al primer registro del bloque interno.
		 * @param unsigned int - La posicion de insercion interna para el registro dado.
		 */
		unsigned int searchPositionInsertInternalNode(Registry* registry, list<Registry*>::iterator IteratorBegin, list<Registry*>::iterator IteratorEnd) throw();
		/**
		 * Busca la rama por la cual insertar o buscar un registro.
		 */
		int searchBranch(InternalNode* internalNode,Registry* registry) throw();
		/**
		 * Estrae la clave de un registro al momento de hacer un split de un bloque hoja.
		 */
		Registry* extractKey(Registry* registry) throw();
		/**
		 * Busca un registro en un bloque externo devolviendo el registro coincidente.
		 * @param registry - El registro a buscar en el bloque externo.
		 * @return registry::puntero - El registro encontrado, o NULL si no se encontro.
		 */
		Registry* searchLeafNode(LeafNode* leafNode,Registry* registry) throw();
		/**
		 * Busca un registro en un bloque interno devolviendo el registro coincidente.
		 * @param registro - El registro a buscar en el bloque interno.
		 * @return Registro::puntero - El registro encontrado, o NULL si no se encontro.
		 */
		Registry*  searchInternalNode(InternalNode* internalNode,Registry* registry) throw();
		/**
		 * Imprime recursivamente el arbol en el strema de salida.
		 */
		void printRecursive(Node* currentNode, std::ostream& streamSalida, unsigned int level) throw();
		/**
		 * Imprime un registro en la salida.
		 */
		void printRegistry(Registry* registry, std::ostream& streamSalida) throw();
		/**
		 *escribwe un bloque en disco
		 */
		void writeBlock(Node* node,int position=-1) throw();
		void advanceListPointer(list<Registry*>::iterator& iterator,unsigned int countAdvance);
		void advanceVectorPointer(vector<int>::iterator& iterator,unsigned int countAdvance);
		void mergeComponentList(list<Registry*> &listRegistry, list<Registry*> &listLeftNode,list<Registry*> &listRightNode);
		void mergeBranchList(std::vector<int> &listBranch,std::vector<int> &listLeftNode,std::vector<int> &listRightNode);
		bool balanceLeafNode(Registry* reg, LeafNode* actualNode, LeafNode* brotherNode,ContainerInsertion* container)throw();
		bool balanceInternalNode(InternalNode* internalNode, InternalNode* brotherNode, ContainerInsertion* container, Registry* fatherReg) throw();
		/**
		 * Almacena la longitud de los bloques del indice b sharp.
		 */
		unsigned int sizeBlock;
		/**
		 * clase para cargar los bytes del bloque
		 */
		Buffer* buffer;
		/**
		 * Almacena el archivo del indice b sharp.
		 */
	    BinaryFile* binaryFile;
		/**
		 * Almacena la estrategia de espacio libre b sharp.
		 */

		FreeBlockController* freeBlockController;

		/**
		 * Almacena el type del indice b sharp.
		 */
		int typeElement;
		/** lista de registros temporales
		 *
		 */
		list<Registry*> listRegistry;
		/**
		 * lista de ramas temporal
		 */
		std::vector<int> branchList;
		/**
		 * Almacena el bloque raiz del indice b sharp.
		 */
		Node*  rootNode;
};

#endif /* INDEXBSHARP_H_ */

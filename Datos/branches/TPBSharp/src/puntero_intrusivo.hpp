#ifndef PUNTERO_INTRUSIVO_HPP
#define PUNTERO_INTRUSIVO_HPP

#include<typeinfo>
#include<cstddef>

/**
 * Definicion de la clase PunteroIntrusivo que incrementa el contador de
 * referencia de punteros al crearse / copiarse y decrementa al destruirse
 * liberando el puntero cuando el contador de referencias llega a cero.
 */
template<class T>
class PunteroIntrusivo {
    template<class Y> friend class PunteroIntrusivo;
	public:
		/**
		 * Constructor de la clase PuntroIntrusivo.
		 * @param puntero - El puntero a encapsular.
		 */
		PunteroIntrusivo(T* puntero = NULL) throw();
		/**
		 * Constructor de la clase PunteroIntrusivo.
		 * @param puntero - El puntero a encapsular.
		 */
		template<class Y>
		PunteroIntrusivo(Y* puntero = NULL) throw();
		/**
		 * Constructor copia de la clase PunteroIntrusivo.
		 * @param copia - El puntero a copiar.
		 */
		PunteroIntrusivo(const PunteroIntrusivo<T>& copia) throw();
		/**
		 * Constructor copia de la clase PunteroIntrusivo.
		 * @param copia - El puntero a copiar.
		 */
		template<class Y>
		PunteroIntrusivo(const PunteroIntrusivo<Y>& copia) throw();
		/**
		 * Destructor virtual de la clase PunteroIntrusivo.
		 */
		virtual ~PunteroIntrusivo() throw();
		/**
		 * Operador de asignacion de la clase PunteroIntrusivo.
		 * @param puntero - El puntero a asignar.
		 */
		PunteroIntrusivo<T>& operator = (T* puntero) throw();
		/**
		 * Operador de asignacion de la clase PunteroIntrusivo.
		 * @param puntero - El puntero a asignar.
		 */
		template<class Y>
		PunteroIntrusivo<T>& operator = (Y* puntero) throw();
		/**
		 * Operador de asignacion de la clase PunteroIntrusivo.
		 * @param copia - El puntero a copiar.
		 */
		PunteroIntrusivo<T>& operator = (const PunteroIntrusivo<T>& copia) throw();
		/**
		 * Operador de asignacion de la clase PunteroIntrusivo.
		 * @param copia - El puntero a copiar.
		 */
		template<class Y>
		PunteroIntrusivo<T>& operator = (const PunteroIntrusivo<Y>& copia) throw();
		/**
		 * Operador de comparacion de la clase PunteroIntrusivo.
		 * @param puntero - El puntero a comparar.
		 */
		bool operator == (T* puntero) const throw();
		/**
		 * Operador de comparacion de la clase PunteroIntrusivo.
		 * @param puntero - El puntero a comparar.
		 */
		bool operator == (const PunteroIntrusivo<T>& puntero) const throw();
		/**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator != (T* puntero) const throw();
                /**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator != (const PunteroIntrusivo<T>& puntero) const throw();
		/**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator >= (T* puntero) const throw();
                /**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator >= (const PunteroIntrusivo<T>& puntero) const throw();
		/**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator <= (T* puntero) const throw();
                /**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator <= (const PunteroIntrusivo<T>& puntero) const throw();
		/**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator > (T* puntero) const throw();
                /**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator > (const PunteroIntrusivo<T>& puntero) const throw();
		/**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator < (T* puntero) const throw();
                /**
                 * Operador de comparacion de la clase PunteroIntrusivo.
                 * @param puntero - El puntero a comparar.
                 */
                bool operator < (const PunteroIntrusivo<T>& puntero) const throw();
		/**
		 * Operador de desreferenciacion de la clase PunteroInterno.
		 * @return El puntero interno desreferenciado.
		 */
		T& operator * () throw();
		/**
		 * Operador de desreferenciacion de la clase PunteroInterno.
		 * @return El puntero interno desreferenciado.
		 */
		const T& operator * () const throw();
		/**
		 * Operador de indireccion de la clase PunteroInterno.
		 * @return El puntero interno de la clase PunteroInterno.
		 */
		T* operator -> () throw();
		/**
		 * Operador de indireccion de la clase PunteroInterno.
		 * @return El puntero interno de la clase PunteroInterno.
		 */
		const T* operator -> () const throw();
		/**
		 * Obtiene el puntero interno.
		 */
		T* obtener_puntero() throw();
		/**
		 * Obtiene el puntero interno.
		 */
		const T* obtener_puntero() const throw();
		/**
		 * Castea el puntero a otro tipo, lanza excepcion si no se puede realizar el cast.
		 */
		template<class Y>
		PunteroIntrusivo<Y> castear_puntero() const throw(std::bad_cast&);
	private:
		/**
		 * Atacha a el puntero incrementando su contador de referencias.
		 */
		void atachar(T* puntero) throw();
		/**
		 * Desatacha a el puntero decrementando su contador de referencias.
		 */
		void desatachar() throw();
		/**
		 * Asigna el puntero destaachando el puntero actual y atachando al nuevo puntero.
		 */
		void asignar(T* puntero) throw();
		/**
		 * Almacena el puntero interno.
		 */
		T* punteroInterno;
};

template<class T>
PunteroIntrusivo<T>::PunteroIntrusivo(T* puntero) throw() {
	this->atachar(puntero);
}

template<class T>
PunteroIntrusivo<T>::PunteroIntrusivo(const PunteroIntrusivo<T>& copia) throw() {
	this->atachar(copia.punteroInterno);
}

template<class T>
template<class Y>
PunteroIntrusivo<T>::PunteroIntrusivo(Y* puntero) throw() {
	this->atachar(dynamic_cast<T*>(puntero));
}

template<class T>
template<class Y>
PunteroIntrusivo<T>::PunteroIntrusivo(const PunteroIntrusivo<Y>& copia) throw() {
	this->atachar(dynamic_cast<T*>(copia.punteroInterno));
}

template<class T>
PunteroIntrusivo<T>::~PunteroIntrusivo() throw() {
	this->desatachar();
}

template<class T>
PunteroIntrusivo<T>& PunteroIntrusivo<T>::operator = (T* puntero) throw() {
	this->asignar(puntero);
	return (*this);
}

template<class T>
template<class Y>
PunteroIntrusivo<T>& PunteroIntrusivo<T>::operator = (Y* puntero) throw() {
	this->asignar(dynamic_cast<T*>(puntero));
	return (*this);
}

template<class T>
PunteroIntrusivo<T>& PunteroIntrusivo<T>::operator = (const PunteroIntrusivo<T>& copia) throw() {
	this->asignar(copia.punteroInterno);
	return (*this);
}

template<class T>
template<class Y>
PunteroIntrusivo<T>& PunteroIntrusivo<T>::operator = (const PunteroIntrusivo<Y>& copia) throw() {
	this->asignar(dynamic_cast<T*>(copia.punteroInterno));
	return (*this);
}

template<class T>
bool PunteroIntrusivo<T>::operator == (T* puntero) const throw() {
	return this->punteroInterno == puntero;
}

template<class T>
bool PunteroIntrusivo<T>::operator == (const PunteroIntrusivo<T>& puntero) const throw() {
	return this->punteroInterno == puntero.punteroInterno;
}

template<class T>
bool PunteroIntrusivo<T>::operator != (T* puntero) const throw() {
        return this->punteroInterno != puntero;
}

template<class T>
bool PunteroIntrusivo<T>::operator != (const PunteroIntrusivo<T>& puntero) const throw() {
        return this->punteroInterno != puntero.punteroInterno;
}

template<class T>
bool PunteroIntrusivo<T>::operator >= (T* puntero) const throw() {
        return this->punteroInterno >= puntero;
}

template<class T>
bool PunteroIntrusivo<T>::operator >= (const PunteroIntrusivo<T>& puntero) const throw() {
        return this->punteroInterno >= puntero.punteroInterno;
}

template<class T>
bool PunteroIntrusivo<T>::operator <= (T* puntero) const throw() {
        return this->punteroInterno <= puntero;
}

template<class T>
bool PunteroIntrusivo<T>::operator <= (const PunteroIntrusivo<T>& puntero) const throw() {
        return this->punteroInterno <= puntero.punteroInterno;
}

template<class T>
bool PunteroIntrusivo<T>::operator > (T* puntero) const throw() {
        return this->punteroInterno > puntero;
}

template<class T>
bool PunteroIntrusivo<T>::operator > (const PunteroIntrusivo<T>& puntero) const throw() {
        return this->punteroInterno > puntero.punteroInterno;
}

template<class T>
bool PunteroIntrusivo<T>::operator < (T* puntero) const throw() {
        return this->punteroInterno < puntero;
}

template<class T>
bool PunteroIntrusivo<T>::operator < (const PunteroIntrusivo<T>& puntero) const throw() {
        return this->punteroInterno < puntero.punteroInterno;
}

template<class T>
T& PunteroIntrusivo<T>::operator * () throw() {
	return *(this->punteroInterno);
}

template<class T>
const T& PunteroIntrusivo<T>::operator * () const throw() {
	return *(this->punteroInterno);
}

template<class T>
T* PunteroIntrusivo<T>::operator -> () throw() {
	return this->punteroInterno;
}

template<class T>
const T* PunteroIntrusivo<T>::operator -> () const throw() {
	return this->punteroInterno;
}

template<class T>
T* PunteroIntrusivo<T>::obtener_puntero() throw() {
    return this->punteroInterno;
}

template<class T>
const T* PunteroIntrusivo<T>::obtener_puntero() const throw() {
    return this->punteroInterno;
}

template<class T>
void PunteroIntrusivo<T>::atachar(T* puntero) throw() {
	this->punteroInterno = puntero;
	if (this->punteroInterno != NULL) {
		this->punteroInterno->incrementar_contador_referencias();
	}
}

template<class T>
void PunteroIntrusivo<T>::desatachar() throw() {
	if (this->punteroInterno != NULL) {
		this->punteroInterno->decrementar_contador_referencias();
		if (this->punteroInterno->obtener_contador_referencias() == 0) {
			delete this->punteroInterno;
			this->punteroInterno = NULL;
		}
	}
}

template<class T>
void PunteroIntrusivo<T>::asignar(T* puntero) throw() {
	this->desatachar();
	this->atachar(puntero);
}

#endif /** PUNTERO_INTRUSIVO_HPP */


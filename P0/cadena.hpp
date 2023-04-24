

#ifndef _CADENA_HPP_
#define _CADENA_HPP_

#include <iostream>
#include <cstring>
#include <stdexcept>

class Cadena {
    public:
        //Constructores
        explicit Cadena (size_t tam=0, char c=' ');
        Cadena(const Cadena& cad); //Ctor. de copia
        Cadena(const char* cad); //Ctor. de conversión

        //Operador de asignación
        Cadena& operator =(const Cadena& cad);

        //Operador de conversión Cadena -> const char*
        explicit operator const char*() const;

        //Método Observador
        size_t length() const noexcept; //Devuelve longitud (obviando "\0")
        
        //Operador de Concatenación de Cadenas
        Cadena& operator +=(const Cadena& cad);

        //Operadores de Índice
        char& operator[](size_t i);
        const char& operator[](size_t i) const;

        char& at(size_t i);
        const char& at(size_t i) const;

        //Función de Subcadena
        Cadena substr(size_t i, size_t tam) const;

        //Destructor
        ~Cadena();

    private:
        char* s_;
        size_t tam_;

};

//Operadores Lógicos
bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator !=(const Cadena& cad1, const Cadena& cad2);
bool operator <(const Cadena& cad1, const Cadena& cad2);
bool operator >(const Cadena& cad1, const Cadena& cad2);
bool operator <=(const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const Cadena& cad2);

//Concatenación de cadenas (+)
Cadena operator +(const Cadena& cad1, const Cadena& cad2);

/////////////////// MÉTODOS INLINE ///////////////////

inline size_t Cadena::length() const noexcept{return tam_;}

inline char& Cadena::operator[](size_t i){return s_[i];}

inline const char& Cadena::operator[](size_t i) const {return s_[i];}

inline Cadena::operator const char*() const {return s_;}

inline bool operator ==(const Cadena& cad1, const Cadena& cad2)
{
    return !strcmp((const char*)cad1, (const char*)cad2);
}

inline bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
    return strcmp((const char*)cad1, (const char*)cad2);
}

inline bool operator <(const Cadena& cad1, const Cadena& cad2)
{
    return (strcmp((const char*)cad1, (const char*)cad2) < 0);
}

inline bool operator >(const Cadena& cad1, const Cadena& cad2)
{
    return cad2 < cad1;
}

inline bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad2 < cad1);
}

inline bool operator >=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad1 < cad2);
}

#endif
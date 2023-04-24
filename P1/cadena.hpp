

#ifndef _CADENA_HPP_
#define _CADENA_HPP_

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iterator>
#include <string>

using namespace std;

class Cadena {
    public:
        //Constructores
        explicit Cadena (size_t tam=0, char c=' ');
        Cadena(const char* cad); //Ctor. de conversión
        Cadena(const Cadena& cad); //Ctor. de copia
        Cadena(Cadena&& cad); //Ctor. de movimiento
        
        //Operadores de asignación
        Cadena& operator =(const Cadena& cad);
        Cadena& operator =(Cadena&& cad);
        Cadena& operator =(const char* cad);

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

        //Iteradores
        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator <iterator> reverse_iterator; 
        typedef std::reverse_iterator <const_iterator> const_reverse_iterator;
        iterator begin() const;
        iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

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

//Operadores de Flujo
ostream& operator <<(ostream& os, const Cadena& cad); //Inserción
istream& operator >>(istream& is, Cadena& cad); //Extraccion

/////////////////// MÉTODOS INLINE ///////////////////

inline size_t Cadena::length() const noexcept {return tam_;}

inline char& Cadena::operator[](size_t i) {return s_[i];}

inline const char& Cadena::operator[](size_t i) const {return s_[i];}

inline Cadena::operator const char*() const 
{
    if (s_==nullptr)
        return "";
    else
        return s_;
}

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

inline ostream& operator <<(ostream& os, const Cadena& cad)
{
    os<<(const char*)cad;
    return os;
}

inline istream& operator >>(istream& is, Cadena& cad)
{
    char buffer[33]=""; //Máximo 32 caracteres (Importante "")
    is.width(33);
    is>>buffer;
    cad=Cadena{buffer};
    
    return is;
}

inline Cadena::iterator Cadena::begin() const {return s_;}

inline Cadena::iterator Cadena::end() const {return s_+tam_;}

inline Cadena::const_iterator Cadena::cbegin() const {return s_;}

inline Cadena::const_iterator Cadena::cend() const {return s_+tam_;}

inline Cadena::reverse_iterator Cadena::rbegin() const noexcept
{
    return reverse_iterator(end());
}

inline Cadena::reverse_iterator Cadena::rend() const noexcept
{ 
    return reverse_iterator(begin()); 
}

inline Cadena::const_reverse_iterator Cadena::crbegin() const noexcept
{
    return const_reverse_iterator(end());
}

inline Cadena::const_reverse_iterator Cadena::crend() const noexcept
{ 
    return const_reverse_iterator(begin()); 
}

// Especialización de la plantilla std ::hash<Key> para definir la función hash a usar
// en contenedores desordenados de Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std.
    template <> // Es una especializaci ón de una plantilla para Cadena.
    struct hash<Cadena> { // Es una clase con solo un operador público.
        size_t operator() (const Cadena& cad) const // El operador función.
        {
            hash<string> hs; // Creamos un objeto hash de string.
            auto p{(const char*)(cad)}; // Convertimos Cadena a cadena de bajo nivel.
            string s{p}; // Creamos un string desde la cadena de b. nivel .
            size_t res{hs(s)}; // El hash del string . Como hs.operator()(s);
            return res; // Devolvemos el hash del string.
            // En forma abreviada:
            // return hash<string>{}((const char*)(cad));
        }
    };
}


#endif
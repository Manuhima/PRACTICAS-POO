

#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

/////////////////// CLASE ARTÍCULO ///////////////////

class Articulo{
    public:
        Articulo(const Cadena& ref, const Cadena& tit, const Fecha& fe, double pr, unsigned int st=0);
    
        //Observadores
        const Cadena& referencia() const noexcept;
        const Cadena& titulo() const noexcept;
        const Fecha& f_publi() const noexcept;
        double precio() const noexcept;
        double& precio() noexcept;
        unsigned int stock() const noexcept;
        unsigned int& stock() noexcept;

    private:
        const Cadena referencia_;
        const Cadena titulo_;
        const Fecha f_publi_;
        double precio_;
        unsigned int stock_;
};

/////////////////// MÉTODOS INLINE ///////////////////

inline const Cadena& Articulo::referencia() const noexcept {return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept {return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept {return f_publi_;}
inline double Articulo::precio() const noexcept {return precio_;}
inline double& Articulo::precio() noexcept {return precio_;}
inline unsigned int Articulo::stock() const noexcept {return stock_;}
inline unsigned int& Articulo::stock() noexcept {return stock_;}

//Flujo de Salida
ostream& operator <<(ostream& os, const Articulo& art);

#endif
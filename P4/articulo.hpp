

#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

#include <iostream>
#include <iomanip>
#include <set>

using namespace std;

/////////////////// CLASE AUTOR ///////////////////

class Autor{
    public:
        Autor(const Cadena& nom, const Cadena& apell, const Cadena& dir);
        const Cadena& nombre() const noexcept;
        const Cadena& apellidos() const noexcept;
        const Cadena& direccion() const noexcept;

    private:
        const Cadena nombre_;
        const Cadena apellidos_;
        const Cadena dirrecion_;
};

inline const Cadena& Autor::nombre() const noexcept {return nombre_;}
inline const Cadena& Autor::apellidos() const noexcept {return apellidos_;}
inline const Cadena& Autor::direccion() const noexcept {return dirrecion_;}

/////////////////// CLASE ARTÍCULO ///////////////////

class Articulo{
    public:
        typedef set<Autor*> Autores;

        Articulo(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, double pr);

        //Observadores
        const Autores& autores() const noexcept;
        const Cadena& referencia() const noexcept;
        const Cadena& titulo() const noexcept;
        const Fecha& f_publi() const noexcept;
        double precio() const noexcept;
        double& precio() noexcept;

        virtual void impresion_especifica(ostream& os) const=0;

        class Autores_vacios{};

        virtual ~Articulo() {}

    protected:
        const Autores autores_;
        const Cadena referencia_;
        const Cadena titulo_;
        const Fecha f_publi_;
        double precio_;
};

/////////////////// MÉTODOS INLINE ///////////////////

inline const Articulo::Autores& Articulo::autores() const noexcept {return autores_;}
inline const Cadena& Articulo::referencia() const noexcept {return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept {return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept {return f_publi_;}
inline double Articulo::precio() const noexcept {return precio_;}
inline double& Articulo::precio() noexcept {return precio_;}

//Flujo de Salida
ostream& operator <<(ostream& os, const Articulo& art);

/////////////////// CLASE ARTICULO ALMACENABLE ///////////////////

class ArticuloAlmacenable: public Articulo {
    public:
        ArticuloAlmacenable(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
                            double pr, unsigned int st=0);

        unsigned int stock() const noexcept;
        unsigned int& stock() noexcept;

        virtual ~ArticuloAlmacenable() {}

        //Hereda "virtual void impresion_especifica(ostream& os) const=0" por lo tanto es clase abstracta

    protected:
        unsigned int stock_;
};

inline unsigned int ArticuloAlmacenable::stock() const noexcept {return stock_;}
inline unsigned int& ArticuloAlmacenable::stock() noexcept {return stock_;}

/////////////////// CLASE LIBRO ///////////////////

class Libro: public ArticuloAlmacenable {
    public:
        Libro(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
              double pr, unsigned int pag, unsigned int st=0);

        unsigned int n_pag() const noexcept;

        void impresion_especifica(ostream& os) const;

    protected:
        const unsigned int n_pag_;

};

inline unsigned int Libro::n_pag() const noexcept {return n_pag_;}

/////////////////// CLASE REVISTA ///////////////////

class Revista: public ArticuloAlmacenable {
    public:
        Revista(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
                double pr, unsigned int num, unsigned int per ,unsigned int st=0);

        unsigned int numero() const noexcept;
        unsigned int periodicidad() const noexcept;

        void impresion_especifica(ostream& os) const;

    private:
        unsigned int numero_;
        unsigned int periodicidad_;

};

inline unsigned int Revista::numero() const noexcept {return numero_;}
inline unsigned int Revista::periodicidad() const noexcept {return periodicidad_;}

/////////////////// CLASE LIBRO DIGITAL ///////////////////

class LibroDigital: public Articulo {
    public:
        LibroDigital(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
                     double pr, const Fecha& f_exp);

        const Fecha& f_expir() const noexcept;

        void impresion_especifica(ostream& os) const;

    private:
        const Fecha f_expir_;
};

inline const Fecha& LibroDigital::f_expir() const noexcept {return f_expir_;}


#endif
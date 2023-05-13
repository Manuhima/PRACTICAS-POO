

#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include "cadena.hpp"
#include "tarjeta.hpp"

#include <iostream>      
#include <map>          
#include <unordered_map>
#include <unordered_set> 

using std::map;
using std::unordered_map;
using std::unordered_set;
using std::ostream;

class Tarjeta;
class Numero;
class Articulo;

/////////////////// CLASE CLAVE ///////////////////
class Clave{
    public:
        Clave(const char* psswd="");

        //Observador
        Cadena clave() const noexcept {return clave_;}
        bool verifica(const char* psswd) const;

        enum Razon{CORTA,ERROR_CRYPT};

        class Incorrecta{
            public:
                Incorrecta(Razon r): razon_{r} {}
                Razon razon() const noexcept {return razon_;}
            private:
                Razon razon_;
        };

    private:
        Cadena clave_;
};

/////////////////// CLASE USUARIO ///////////////////

class Usuario{
    public:
        typedef map<Numero,Tarjeta*> Tarjetas;
        typedef unordered_map<Articulo*,unsigned int> Articulos;

        Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& cl);
        
        Usuario(const Usuario&)=delete; //Un usuario no podrá copiarse
        Usuario& operator =(const Usuario&)=delete; //ni asignarse

        class Id_duplicado{
            public:
                Id_duplicado(const Cadena& duplicado): id_dup(duplicado) {}
                Cadena idd() const noexcept {return id_dup;}
            private:
                Cadena id_dup;
        };

        //Observadores
        const Cadena& id() const noexcept;
        const Cadena& nombre() const noexcept;
        const Cadena& apellidos() const noexcept;
        const Cadena& direccion() const noexcept;
        const Tarjetas& tarjetas() const noexcept;
        const Articulos& compra() const noexcept;

        void compra(Articulo& art, unsigned int cant=1);
        void vaciar_carro();
        unsigned int n_articulos() const noexcept;

        void es_titular_de(const Tarjeta& tar);
        void no_es_titular_de(Tarjeta& tar);

        //Flujo de Salida
        friend ostream& operator <<(ostream& os, const Usuario& user);

        ~Usuario();

    private:
        static unordered_set<Cadena> ids;
        const Cadena id_;    
        const Cadena nombre_;
        const Cadena apellidos_;
        const Cadena direccion_;
        Clave contraseña_;
        Tarjetas tarjetas_;
        Articulos carrito_;
};

//Función externa: mostrar_carro()
void mostrar_carro(ostream& os, const Usuario& user);

/////////////////// MÉTODOS INLINE ///////////////////

inline const Cadena& Usuario::id() const noexcept {return id_;}
inline const Cadena& Usuario::nombre() const noexcept {return nombre_;}
inline const Cadena& Usuario::apellidos() const noexcept {return apellidos_;}
inline const Cadena& Usuario::direccion() const noexcept {return direccion_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const noexcept {return tarjetas_;}
inline const Usuario::Articulos& Usuario::compra() const noexcept {return carrito_;}

inline void Usuario::vaciar_carro() {carrito_.clear();}
inline unsigned int Usuario::n_articulos() const noexcept {return carrito_.size();}

#endif
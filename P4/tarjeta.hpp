

#ifndef _TARJETA_HPP_
#define _TARJETA_HPP_

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

#include <set>
#include <iostream>
#include <locale>

using std::set;
using std::endl;
using std::ostream;

class Usuario;

/////////////////// CLASE NÚMERO ///////////////////

class Numero{
    public:
        Numero(const Cadena& num="0");

        //Operador conversión Numero->const char*
        operator const char*() const noexcept;

        enum Razon {LONGITUD,DIGITOS,NO_VALIDO};
        class Incorrecto {
            public:
                Incorrecto(Razon r): razon_{r} {}
                Razon razon() const noexcept {return razon_;}
            private:
                Razon razon_;
        };

    private:
        Cadena numero_;

};

inline Numero::operator const char*() const noexcept {return (const char*)numero_;}

//Operador comparación "menor que"
bool operator <(const Numero& n1, const Numero& n2);

inline bool operator <(const Numero& n1, const Numero& n2)
{
    return (strcmp((const char*)n1, (const char*)n2) < 0);
}

/////////////////// CLASE TARJETA ///////////////////

class Tarjeta{
    public:
        Tarjeta(const Numero& num, Usuario& user, const Fecha& f_cad);

        Tarjeta(const Tarjeta&)=delete; //Una tarjeta no podrá copiarse
        Tarjeta& operator =(const Tarjeta&)=delete; //ni asignarse

        enum Tipo {AmericanExpress,JCB,Maestro,Mastercard,VISA,Otro};

        class Caducada {
            public:
                Caducada(const Fecha& fech): f_cad{fech} {}
                Fecha cuando() const noexcept {return f_cad;}
            private:
                Fecha f_cad;
        };

        class Num_duplicado {
            public:
                Num_duplicado(const Numero& num): dup_{num} {}
                Numero que() const noexcept {return dup_;}
            private:
                Numero dup_;
        };

        class Desactivada {};

        const Numero numero() const noexcept;
        Usuario* titular() const noexcept;
        const Fecha caducidad() const noexcept;
        bool activa() const noexcept;
        Tipo tipo() const noexcept;

        bool activa(bool act) noexcept;

        ~Tarjeta();

    private:
        static set<Numero> numeros;
        const Numero numero_;
        Usuario* const titular_;
        const Fecha caducidad_;
        bool activa_;

        friend class Usuario;
        void anula_titular();
};

//Flujo de Salida
ostream& operator <<(ostream& os, const Tarjeta& tar);
ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo) noexcept;

inline const Numero Tarjeta::numero() const noexcept {return numero_;}
inline Usuario* Tarjeta::titular() const noexcept {return titular_;}
inline const Fecha Tarjeta::caducidad() const noexcept {return caducidad_;}
inline bool Tarjeta::activa() const noexcept {return activa_;}

inline bool Tarjeta::activa(bool act) noexcept {return activa_=act;}

inline void Tarjeta::anula_titular() {activa_=false; const_cast<Usuario*&>(titular_)=nullptr;}

//Operador menor que
bool operator <(const Tarjeta& t1, const Tarjeta& t2);

inline bool operator <(const Tarjeta& t1, const Tarjeta& t2)
{
    return (t1.numero()<t2.numero());
}

#endif
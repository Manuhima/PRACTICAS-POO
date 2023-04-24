

#include "tarjeta.hpp"
#include "usuario.hpp"

#include <locale>
#include <set>
#include <iomanip>

using std::isspace;
using std::isdigit;

std::set<Numero> Tarjeta::numeros;
bool luhn(const Cadena& numero);

/////////////////// NÚMERO ///////////////////

Numero::Numero(const Cadena& num)
{
    Cadena nuevo;
    //Quitamos espacios en blanco
    for (auto it:num) {
        if(!isspace(it)){ 
            if(!isdigit(it)) throw Incorrecto{DIGITOS}; //Comprobamos que todo sean dígitos
            else nuevo += Cadena{1,it}; //Cadena(tam,char)
        }
    }
    //Comprobamos que la longitud este comprendida entre 13 y 19 (incluidos)
    if(nuevo.length()<13 || nuevo.length()>19) throw Incorrecto{LONGITUD};

    //Comprobamos validez con dígito de control
    if(!luhn(nuevo)) throw Incorrecto{NO_VALIDO};

    numero_=nuevo;
}

/////////////////// TARJETA ///////////////////

Tarjeta::Tarjeta(const Numero& num, Usuario& user, const Fecha& f_cad):  
    numero_{num}, titular_{&user}, caducidad_{f_cad}, activa_{true}
{
    //Comprobamos que la caducidad no sea menor a la actual
    if(caducidad_<Fecha{})
        throw Caducada{f_cad};

    //Comprobamos que no existe el número y lo metemos en el set
    typedef set<Numero>::iterator tipoIt;
    std::pair<tipoIt, bool> res = numeros.insert(num); // Insertar el numero num
    if (!res.second) //Inserción fallida
        throw Num_duplicado{num};
    
    titular_->es_titular_de(*this);
}

Tarjeta::Tipo Tarjeta::tipo() const noexcept
{
    switch (numero_[0]) {
        case '3':
            if (numero_[1]=='4' || numero_[1]=='7')
                return AmericanExpress;
            else
                return JCB;
            break;

        case '4':
            return VISA;
            break;

        case '5':
            return Mastercard;
            break;

        case '6':
            return Maestro;
            break;

        default:
            return Otro;
            break;
    }
}

//Operador inserción Tarjeta
ostream& operator <<(ostream& os, const Tarjeta& tar)
{
    os<<tar.tipo()<<endl<<tar.numero()<<endl;

    Cadena facial= tar.titular()->nombre() + Cadena{" "} + tar.titular()->apellidos();
    for (auto& it:facial) it=toupper(it);

    os<<facial;

    os<<endl<<"Caduca: "<<std::setfill('0') << std::setw(2)<<tar.caducidad().mes()
      <<"/"<<std::setw(2)<<tar.caducidad().anno()%100<<endl;

    return os;
}

//Operador inserción Tipo
ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo) noexcept
{
    switch (tipo) {
        case Tarjeta::Tipo::AmericanExpress: os<<"American Express"; break;
        
        case Tarjeta::Tipo::JCB: os<<"JCB"; break;
        
        case Tarjeta::Tipo::Maestro: os<<"Maestro"; break;

        case Tarjeta::Tipo::Mastercard: os<<"Mastercard"; break;

        case Tarjeta::Tipo::VISA: os<<"VISA"; break;

        default: os<<"Tipo indeterminado"; break;
    };

    return os;
}

Tarjeta::~Tarjeta()
{
    if(titular_)
        titular_->no_es_titular_de(*this);
    numeros.erase(numero_);
}
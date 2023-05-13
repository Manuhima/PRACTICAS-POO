

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <random>
#include <time.h>

using namespace std;

unordered_set<Cadena> Usuario::ids;

/////////////////// CLAVE ///////////////////

Clave::Clave(const char* psswd)
{
    if (strlen(psswd)<5)
        throw Incorrecta{CORTA};

    const char* salt_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./";

    char salt[3];
    salt[0]=salt_chars[rand()%strlen(salt_chars)];
    salt[1]=salt_chars[rand()%strlen(salt_chars)];
    salt[2]='\0';

    if (crypt(psswd,salt)==NULL)
        throw Incorrecta{ERROR_CRYPT};
    else
        clave_=crypt(psswd,salt);
}

bool Clave::verifica(const char* psswd) const
{
    psswd=crypt(psswd,(const char*)clave_);
    return psswd==clave_;
}

/////////////////// USUARIO ///////////////////

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& cl):
    id_{id}, nombre_{nom}, apellidos_{apell}, direccion_{dir}, contraseña_{cl}
{
    typedef unordered_set<Cadena>::iterator tipoIt;
    std::pair<tipoIt, bool> res = Usuario::ids.insert(id); // Insertar el identificador id
    if (!res.second) //Inserción fallida
        throw Id_duplicado{id};
}

void Usuario::es_titular_de(const Tarjeta& tar)
{
    if(tar.titular()==this) 
        tarjetas_[tar.numero()] = const_cast<Tarjeta*>(&tar);
}

void Usuario::no_es_titular_de(Tarjeta& tar)
{
    tarjetas_.erase(tar.numero());
    tar.anula_titular();
    tar.activa(true);
}


void Usuario::compra(Articulo& art, unsigned int cant) 
{
    //Miramos si existe
    auto dentro=carrito_.find(&art);
    
    if(dentro==carrito_.end()){//No está dentro del carrito
        if(cant>0)
            carrito_[&art]=cant;

    }else {//Articulo ya en carrito
        if(cant>0)//Actualizamos con la nueva cantidad
            dentro->second=cant;
        else //Borramos articulo
            carrito_.erase(dentro);
    }
}

ostream& operator <<(ostream& os, const Usuario& user)
{
    os<<user.id()<<" ["<<user.contraseña_.clave()<<"] "<<user.nombre_<<" "<<user.apellidos_<<endl
      <<user.direccion_<<endl<<"Tarjetas:"<<endl;

    for (auto& it:user.tarjetas_)
        os<<*it.second<<endl;

    return os;
}

void mostrar_carro(ostream& os, const Usuario& user)
{
    os<<"Carrito de compra de "<<user.id()<<" [Artículos: "<<user.n_articulos()<<"]"<<endl<<" Cant. Artículo"<<endl
      <<"==========================================================="<<endl;
    for (auto it:user.compra())
        os<<"  "<<it.second<<"  "<<*it.first<<endl;

}


Usuario::~Usuario()
{
    for(auto t:tarjetas_) 
        t.second->anula_titular(); 
    ids.erase(id_);
}
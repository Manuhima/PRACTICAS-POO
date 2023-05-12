

#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario& u, Pedido& p)
{
    pedidosUsuario_[&u].insert((Pedido*)&p);
    propietario_[&p]=(Usuario*)&u;
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u)
{
    asocia(u,p);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& u) const noexcept
{
    map<Usuario*,Pedidos>::const_iterator i=pedidosUsuario_.find((Usuario*)&u);

    if (i!=pedidosUsuario_.end()) 
        return i->second;
    else 
        return Pedidos{};

}

const Usuario* Usuario_Pedido::cliente(Pedido& p) const noexcept
{
    map<Pedido*,Usuario*>::const_iterator i=propietario_.find((Pedido*)&p);
    if(i!=propietario_.end())
        return i->second;
    else
        return nullptr;
}
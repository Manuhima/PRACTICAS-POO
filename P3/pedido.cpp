

#include "pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::N_pedidos=1;

Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& user, const Tarjeta& tar, const Fecha& fech):
    num_{N_pedidos}, tarjeta_{&tar}, fecha_{fech}, total_{0.0}
{
    //Excepciones rápidas de comprobar
    if (&user!=tar.titular()) throw Impostor{user};

    if (!tar.activa()) throw Tarjeta::Desactivada{};

    if (tar.caducidad()<fech) throw Tarjeta::Caducada{tar.caducidad()};

    if (user.n_articulos()==0) throw Vacio{user};
    
    for (auto art:user.compra()) {
        if (art.first->stock()<art.second) { //Stock articulos < cantidad en carrito del usuario
            user.vaciar_carro(); //Vaciamos carro
            throw SinStock{*art.first};
        }
    }
    
    for(auto art:user.compra()) {
        p_a.pedir(*art.first,*this,art.first->precio(),art.second); //Enlace pedido-articulo
        total_+=art.first->precio()*art.second;
        art.first->stock()-=art.second; //Actualización stock
    }

    u_p.asocia(user,*this); //Enlace usuario-pedido

    user.vaciar_carro(); //Vaciamos carro una vez hemos hecho los enlaces

    N_pedidos++;
}

ostream& operator <<(ostream& os, const Pedido& ped)
{
    os<<"Núm. pedido: "<<ped.numero()<<std::endl<<"Fecha:       "<<ped.fecha()<<std::endl
      <<"Pagado con:  "<<ped.tarjeta()->tipo()<<" n.º: "<<ped.tarjeta()->numero()<<std::endl
      <<"Importe:     "<<ped.total()<<" €"<<std::endl;

    return os;
}


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

    bool vacio=true;
    for (auto art:user.compra()) { //Bucle para comprobar excepciones
        if (ArticuloAlmacenable* aa=dynamic_cast<ArticuloAlmacenable*>(art.first)) {
            vacio=false; //Si es el almacenable no está vacío
            if (aa->stock()<art.second) { //Stock articulos < cantidad en carrito del usuario
                user.vaciar_carro(); //Vaciamos carro
                throw SinStock{*art.first};
            }

        } else if (LibroDigital* ld=dynamic_cast<LibroDigital*>(art.first)) {
            if (ld->f_expir()>=fecha_) //Si es digital hay que ver que no haya expirado
                vacio=false; 

        } else { //Si no es ninguno entonces lanzamos excepción logic_error
            throw std::logic_error{"Tipo desconocido"};
        }
    }

    if (vacio) throw Vacio{user};

    for (auto art:user.compra()) { //Bucle para comprobar excepciones
        if (ArticuloAlmacenable* aa=dynamic_cast<ArticuloAlmacenable*>(art.first)) {
            p_a.pedir(*aa,*this,aa->precio(),art.second); //Enlace pedido-articulo
            total_+=aa->precio()*art.second;
            aa->stock()-=art.second; //Actualización stock

        } else {
            LibroDigital* ld=dynamic_cast<LibroDigital*>(art.first);
            if (ld->f_expir()>=fecha_) { //Es válido
                p_a.pedir(*ld,*this,ld->precio(),art.second); //Enlace pedido-articulo
                total_+=ld->precio()*art.second; 
            }
            //Si no es válido simplemente no lo mete
        }
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
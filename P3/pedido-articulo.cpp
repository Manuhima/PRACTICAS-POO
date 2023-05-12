

#include "pedido-articulo.hpp"
#include "pedido.hpp"

#include <iostream>
#include <iomanip>

using std::ostream;
using std::fixed;
using std::setprecision;

/////////////////// LINEA PEDIDO ///////////////////

ostream& operator <<(ostream& os, const LineaPedido& lp)
{
    os<<setprecision(2)<<fixed<<lp.precio_venta()<<" €\t"<<lp.cantidad();
    return os;
}

/////////////////// PEDIDO_ARTICULOS ///////////////////

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double pr, unsigned int cnt)
{
    ped_art_[&ped].insert(std::make_pair(&art,LineaPedido{pr,cnt}));
    art_ped_[&art].insert(std::make_pair(&ped,LineaPedido{pr,cnt}));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double pr, unsigned int cnt)
{
    pedir(ped,art,pr,cnt);
}


Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& ped) const noexcept
{
    map<Pedido*,ItemsPedido,OrdenaPedidos>::const_iterator i=ped_art_.find((Pedido*)&ped);

    if (i!=ped_art_.end()) 
        return i->second;
    else 
        return ItemsPedido{};
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art) const noexcept
{
    map<Articulo*,Pedidos,OrdenaArticulos>::const_iterator i=art_ped_.find((Articulo*)&art);

    if (i!=art_ped_.end()) 
        return i->second;
    else 
        return Pedidos{};
}

void Pedido_Articulo::mostrarDetallePedidos(ostream& os) const noexcept
{
    double total=0;
    for(auto it:ped_art_) {
        os<<"Pedido núm. "<<it.first->numero()<<std::endl
          <<"Cliente: "<<it.first->tarjeta()->titular()<<"\t\t Fecha: "<<it.first->fecha()
          <<std::endl<<detalle(*it.first)<<std::endl;
          total+=it.first->total();
    }
    os<<"TOTAL VENTAS\t"<<total<<" €"<<std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(ostream& os) const noexcept
{
    for(auto it:art_ped_) {
        os<<"Ventas de ["<<it.first->referencia()<<"] "<<it.first->titulo()<<std::endl
          <<ventas(*it.first);
    }
}

ostream& operator <<(ostream& os, Pedido_Articulo::ItemsPedido ip)
{
    double total=0;
    os<<"  PVP\tCantidad \tArtículo"<<std::setfill('=')<<std::setw(70)<<std::endl;
    //Imprimir items
    for(auto item:ip) {
        total+=item.second.precio_venta()+item.second.cantidad();
        os<<item.second<<"\t"
          <<"["<<item.first->referencia()<<"] "<<item.first->titulo()<<std::endl;
    }
    os<<std::setfill('=')<<std::setw(70)<<std::endl
      <<"Total   "<<total<<std::endl;

    return os;
}

ostream& operator <<(ostream& os, Pedido_Articulo::Pedidos peds)
{
    double total=0;
    unsigned int cantidad=0;

    os<<"[Pedidos: "<<peds.size()<<"]"<<std::endl
      <<std::setfill('=')<<std::setw(70)<<" "<<std::endl
      <<"  PVP\tCantidad\t\tFecha de venta"<<std::endl
      <<std::setfill('=')<<std::setw(70)<<" "<<std::endl;
    //Imprimir pedidos
    for(auto p:peds) {
        total+=p.second.precio_venta()*p.second.cantidad();
        cantidad+=p.second.cantidad();
        os<<p.second<<"\t\t"<<p.first->fecha()<<std::endl;
    }

    os<<std::setfill('=')<<std::setw(70)<<" "<<std::endl
      <<total<<" €\t\t"<<cantidad<<std::endl;

    return os;
}




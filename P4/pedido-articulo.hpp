

#ifndef _PEDIDO_ARTICULO_HPP_
#define _PEDIDO_ARTICULO_HPP_

#include <iostream>
#include <map>

#include "articulo.hpp"
#include "pedido.hpp"

using std::ostream;
using std::map;

class Pedido;

/////////////////// CLASE LINEA PEDIDO ///////////////////

class LineaPedido {
    public:
        explicit LineaPedido(double pv, unsigned cant=1): precio_venta_{pv}, cantidad_{cant} {}
        double precio_venta() const noexcept;
        unsigned cantidad() const noexcept;

    private:
        double precio_venta_;
        unsigned cantidad_;

};

ostream& operator <<(ostream& os, const LineaPedido& lp);

inline double LineaPedido::precio_venta() const noexcept {return precio_venta_;}
inline unsigned LineaPedido::cantidad() const noexcept {return cantidad_;}


/////////////////// CLASE PEDIDO_ARTICULOS ///////////////////

struct OrdenaArticulos: std::binary_function<Articulo*,Articulo*,bool>{
    bool operator() (const Articulo* art1, const Articulo* art2) const noexcept 
    {return art1->referencia()<art2->referencia();}
};

struct OrdenaPedidos: std::binary_function<Pedido*,Pedido*,bool>{
    bool operator() (const Pedido* ped1, const Pedido* ped2) const noexcept
    {return ped1->numero()<ped2->numero();}
};

class Pedido_Articulo {
    public:
        typedef map<Articulo*,LineaPedido,OrdenaArticulos> ItemsPedido;
        typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        void pedir(Pedido& ped, Articulo& art, double pr, unsigned int cnt=1);
        void pedir(Articulo& art, Pedido& ped, double pr, unsigned int cnt=1);
        ItemsPedido detalle(Pedido& ped) const noexcept;
        Pedidos ventas(Articulo& art) const noexcept;

        void mostrarDetallePedidos(ostream& os) const noexcept;
        void mostrarVentasArticulos(ostream& os) const noexcept;

    private:
        map<Pedido*,ItemsPedido,OrdenaPedidos> ped_art_;
        map<Articulo*,Pedidos,OrdenaArticulos> art_ped_;

};

ostream& operator <<(ostream& os, Pedido_Articulo::ItemsPedido ip);
ostream& operator <<(ostream& os, Pedido_Articulo::Pedidos peds);


#endif
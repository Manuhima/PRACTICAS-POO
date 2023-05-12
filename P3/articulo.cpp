

#include "articulo.hpp"

Articulo::Articulo(const Cadena& ref, const Cadena& tit, const Fecha& fe, double pr, unsigned int st):
        referencia_{ref}, titulo_{tit}, f_publi_{fe}, precio_{pr}, stock_{st} {}

ostream& operator <<(ostream& os, const Articulo& art)
{
    os<<"["<<art.referencia()<<"] \""<<art.titulo()<<"\", "<<art.f_publi().anno()
    <<". "<<setprecision(2)<<fixed<<art.precio()<<" €";
    return os;
}
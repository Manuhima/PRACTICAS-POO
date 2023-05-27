

#include "articulo.hpp"

/////////////////// CLASE ARTÍCULO ///////////////////

Articulo::Articulo(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, double pr):
        autores_{aut},referencia_{ref}, titulo_{tit}, f_publi_{fe}, precio_{pr}
{
    if (aut.empty()) throw Autores_vacios{};
}

ostream& operator <<(ostream& os, const Articulo& art)
{
    os<<"["<<art.referencia()<<"] \""<<art.titulo()<<"\", de ";

    auto a=art.autores().begin();
    os<<(*a)->apellidos();
    a++;
    while(a!=art.autores().end()) {
        os<<", "<<(*a)->apellidos();
        a++;
    }

    os<<". "<<art.f_publi().anno()<<". "<<setprecision(2)<<fixed<<art.precio()<<" €"<<endl<<"\t";
    art.impresion_especifica(os);
    return os;
}

/////////////////// CLASE AUTOR ///////////////////

Autor::Autor(const Cadena& nom, const Cadena& apell, const Cadena& dir): 
        nombre_{nom}, apellidos_{apell}, dirrecion_{dir} {}

/////////////////// CLASE ARTICULO ALMACENABLE ///////////////////

ArticuloAlmacenable::ArticuloAlmacenable(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
                                         double pr, unsigned int st): Articulo{aut,ref,tit,fe,pr}, stock_{st} {}

/////////////////// CLASE LIBRO ///////////////////

Libro::Libro(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
             double pr, unsigned int pag, unsigned int st): ArticuloAlmacenable{aut,ref,tit,fe,pr,st}, n_pag_{pag} {}

void Libro::impresion_especifica(ostream& os) const 
{
    os<<n_pag_<<" págs., "<<stock_<<" unidades.";
}

/////////////////// CLASE REVISTA ///////////////////

Revista::Revista(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
        double pr, unsigned int num, unsigned int per ,unsigned int st): 
            ArticuloAlmacenable{aut,ref,tit,fe,pr,st}, numero_{num}, periodicidad_{per} {}

void Revista::impresion_especifica(ostream& os) const
{
    os<<"Número: "<<numero_<<", Periodicidad: "<<periodicidad_<<" días."<<endl
      <<"\tPróximo número a partir de: "<<f_publi_+periodicidad_<<".";
}
/////////////////// CLASE LIBRO DIGITAL ///////////////////

LibroDigital::LibroDigital(const Autores& aut, const Cadena& ref, const Cadena& tit, const Fecha& fe, 
                           double pr, const Fecha& f_exp): Articulo{aut,ref,tit,fe,pr}, f_expir_{f_exp} {}

void LibroDigital::impresion_especifica(ostream& os) const
{
    os<<"A la venta hasta el "<<f_expir_<<".";
}
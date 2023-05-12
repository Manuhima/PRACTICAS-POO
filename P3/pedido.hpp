

#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_

#include <iostream>

#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "fecha.hpp"
#include "tarjeta.hpp"

using std::ostream;

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
    public:
        Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& user, const Tarjeta& tar, const Fecha& fech=Fecha());

        int numero() const noexcept;
        const Tarjeta* tarjeta() const noexcept;
        const Fecha& fecha() const noexcept;
        double total() const noexcept;
        static int n_total_pedidos() noexcept;

        class Vacio{
            public:
                Vacio(const Usuario& user): user_{&user} {}
                const Usuario& usuario() const noexcept {return *user_;}
            private:
                const Usuario* user_;
        };

        class Impostor{
            public:
                Impostor(const Usuario& user): user_{&user} {}
                const Usuario& usuario() const noexcept {return *user_;}
            private:
                const Usuario* user_;
        };

        class SinStock{
            public:
                SinStock(const Articulo& art): art_{&art} {}
                const Articulo& articulo() const noexcept {return *art_;}
            private:
                const Articulo* art_;
        };

    private:
        static int N_pedidos;
        int num_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
};

inline int Pedido::numero() const noexcept {return num_;}
inline const Tarjeta* Pedido::tarjeta() const noexcept {return tarjeta_;}
inline const Fecha& Pedido::fecha() const noexcept {return fecha_;}
inline double Pedido::total() const noexcept {return total_;}
inline int Pedido::n_total_pedidos() noexcept {return N_pedidos;}

ostream& operator <<(ostream& os, const Pedido& ped);


#endif


#ifndef _USUARIO_PEDIDO_HPP_
#define _USUARIO_PEDIDO_HPP_

#include <map>
#include <set>

using std::set;
using std::map;

class Pedido;
class Usuario;

class Usuario_Pedido {
    public:
        typedef set<Pedido*> Pedidos;
        void asocia(Usuario& u, Pedido& p);
        void asocia(Pedido& p, Usuario& u);
        Pedidos pedidos(Usuario& u) const noexcept;
        const Usuario* cliente(Pedido& p) const noexcept;
    private:
        map<Usuario*,Pedidos> pedidosUsuario_;
        map<Pedido*,Usuario*> propietario_;
};


#endif


#include "cadena.hpp"

/////////////////// CONSTRUCTORES ///////////////////
Cadena::Cadena(size_t tam, char c): s_{new char[tam+1]}, tam_{tam}
{
    for(size_t i=0; i<tam_; i++)
        s_[i]=c;
    s_[tam_]='\0';
}

Cadena::Cadena(const Cadena& cad): s_{new char[cad.tam_ + 1]}, tam_{cad.tam_}
{
    strcpy(s_,cad.s_);
}

Cadena::Cadena(const char* cad): s_{new char[strlen(cad)+1]}, tam_{strlen(cad)}
{
    strcpy(s_,cad);
}

/////////////////// OP. ASIGNACIÓN ///////////////////
Cadena& Cadena::operator =(const Cadena& cad)
{
    if(this!= &cad){ //Evitamos autoasignación
        delete[] s_;
        s_=new char[cad.tam_+1];
        tam_=cad.tam_;
        strcpy(s_,cad.s_);
    }
    return *this;
}

/////////////////// OPS. CONCATENACIÓN ///////////////////
Cadena& Cadena::operator +=(const Cadena& cad)
{
    char* aux=new char[tam_+1];
    strcpy(aux,s_);

    tam_+=cad.tam_;
    
    delete[] s_;
    s_=new char[tam_+1];
    strcpy(s_,aux);

    strcat(s_,cad.s_); 
    delete[] aux;

    return *this;
}

Cadena operator +(const Cadena& cad1, const Cadena& cad2)
{
    Cadena aux(cad1);
    return aux+=cad2;
}

/////////////////// MÉTODOS ATs ///////////////////
char& Cadena::at(size_t i)
{
    if(i<tam_)
        return s_[i]; 
    else
        throw std::out_of_range{"Funcion at(): fuera de limites."};
}

const char& Cadena::at(size_t i) const
{
    if(i<tam_)
        return s_[i];
    else 
        throw std::out_of_range{"Funcion at(): fuera de limites."};
}

Cadena Cadena::substr(size_t i, size_t tam) const
{
    if(i+tam>tam_ || tam>tam_ || i>tam_)
        throw std::out_of_range{"Funcion substr(): fuera de limites."};

    else{
        Cadena aux{tam};
        strncpy(aux.s_,s_+i,tam);
        aux.s_[tam]='\0';
        return aux;
    }
}

/////////////////// DESTRUCTOR ///////////////////
Cadena::~Cadena()
{
    delete[] s_;
    tam_=0;
}



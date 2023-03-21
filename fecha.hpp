

#ifndef _FECHA_HPP_
#define _FECHA_HPP_

#include <ctime>
#include <cstdio>
#include <iostream>
#include <locale>

class Fecha {
    public:
        explicit Fecha(int d=0, int m=0, int a=0); //3,2,1 o ningún parámetro
        Fecha(const Fecha &f)=default; //Ctor de copia (por defecto)
        Fecha(const char* cad); //"dd/mm/aaaa"
        Fecha& operator =(const Fecha&)=default; //Op. asignación (por defecto)
        
        //Operador de conversión Fecha -> const char*
        operator const char*() const;

        //Constantes
        static const int AnnoMinimo=1902;
        static const int AnnoMaximo=2037;

        //Clase Fecha Invalida
        class Invalida{
            public:
                Invalida(const char* inf): info_{inf} {}
                const char* por_que() const;
            private:    
                const char* info_;
        };

        //Observadores
        int dia() const noexcept;
        int mes() const noexcept;
        int anno() const noexcept;

        //Operadores
        Fecha& operator +=(int n);
        Fecha& operator -=(int n);
        Fecha& operator ++();    //++f
        Fecha& operator ++(int); //f++
        Fecha& operator --();    //--f
        Fecha& operator --(int); //f--

        //Operadores Aritméticos
        Fecha operator +(int n) const;
        Fecha operator -(int n) const;
        
        //Destructor
        ~Fecha()=default;

    private:
        int dia_, mes_, anno_;
        void comprueba();
        int ultimo_dia() const;
        std::time_t tiempo_calendario=std::time(nullptr);                   //Lo usamos más adelante
        std::tm* tiempo_descompuesto=std::localtime(&tiempo_calendario);    //en distintas funciones
};

//Operadores Lógicos
bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2); //Antes
bool operator <=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2); //Despues
bool operator >=(const Fecha& f1, const Fecha& f2);

/////////////////// MÉTODOS INLINE ///////////////////

inline const char* Fecha::Invalida::por_que() const {return info_;}

inline int Fecha::dia() const noexcept {return dia_;}

inline int Fecha::mes() const noexcept {return mes_;}

inline int Fecha::anno() const noexcept {return anno_;}

inline bool operator ==(const Fecha& f1, const Fecha& f2)
{
    return (f1.dia()==f2.dia() && f1.mes()==f2.mes() && f1.anno()==f2.anno());
}

inline bool operator !=(const Fecha& f1, const Fecha& f2)
{
    return !(f1==f2);
}

inline bool operator <(const Fecha& f1, const Fecha& f2)
{
    return (f1.anno()<f2.anno() || (f1.anno()==f2.anno() && (f1.mes()<f2.mes() || 
    (f1.mes()==f2.mes() && f1.dia()<f2.dia()))));
}

inline bool operator <=(const Fecha& f1, const Fecha& f2)
{
    return !(f2<f1);
}

inline bool operator >(const Fecha& f1, const Fecha& f2)
{
    return f2<f1;
}

inline bool operator >=(const Fecha& f1, const Fecha& f2)
{
    return !(f1<f2);
}

#endif
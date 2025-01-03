#include "porta.h"

///
/// AS PORTAS
///

/// Porta NOT

//
// FALTA IMPLEMENTAR
//
bool PortaNOT::simular(const std::vector<bool3S>& in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size() == this->Nin_port)
    {
        for(int i=0; i<in_port.size(); ++i)
        {
            prov = ~(in_port[i]);
        }
        out_port = prov;
        return true;
    }
    out_port = prov;
    return false;
}

/// Porta AND

//
// FALTA IMPLEMENTAR
//
bool PortaAND::simular(const std::vector<bool3S>& in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size() == this->Nin_port)
    {
        for(int i=0; i<in_port.size()-1;++i)
        {
            prov = in_port[i]&in_port[i+1];
        }
        out_port = prov;
        return true;
    }
    out_port = prov;
    return false;
}
/// Porta NAND

//
// FALTA IMPLEMENTAR
//

/// Porta OR

//
// FALTA IMPLEMENTAR
//

/// Porta NOR

//
// FALTA IMPLEMENTAR
//

/// Porta XOR

//
// FALTA IMPLEMENTAR
//

/// Porta NXOR

//
// FALTA IMPLEMENTAR
//

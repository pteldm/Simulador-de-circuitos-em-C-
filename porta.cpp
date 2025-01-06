#include "porta.h"

///
/// AS PORTAS
///

/// Porta NOT

//
// FALTA IMPLEMENTAR
//

bool PortaNOT::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != 1) return false;

    setOutput(~in_port.at(0));
    return true;
}

/// Porta AND

//
// FALTA IMPLEMENTAR
//

bool PortaAND::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs() || in_port.size() == 0) return false;

    setOutput(bool3S::TRUE);


    for(int i = 0; i<in_port.size(); i++){
        if(in_port.at(i) == bool3S::FALSE){
            setOutput(bool3S::FALSE);
            break;
        }
        if(in_port.at(i) == bool3S::UNDEF){
            setOutput(bool3S::UNDEF);
        }
    }
    return true;
}



/// Porta NAND

//
// FALTA IMPLEMENTAR
//


bool PortaNAND::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()|| in_port.size() == 0) return false;

    setOutput(bool3S::FALSE);

    for(int i = 0; i<in_port.size(); i++){
        if(in_port.at(i) == bool3S::FALSE){
            setOutput(bool3S::TRUE);
            break;
        }
        if(in_port.at(i) == bool3S::UNDEF){
            setOutput(bool3S::UNDEF);
        }
    }
    return true;
}


/// Porta OR

//
// FALTA IMPLEMENTAR
//


bool PortaOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()|| in_port.size() == 0) return false;

    setOutput(bool3S::FALSE);

    for(int i = 0; i<in_port.size(); i++){
        if(in_port.at(i) == bool3S::TRUE){
            setOutput(bool3S::TRUE);
            break;
        }
        if(in_port.at(i) == bool3S::UNDEF){
            setOutput(bool3S::UNDEF);
        }
    }
    return true;

}

/// Porta NOR


bool PortaNOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()|| in_port.size() == 0) return false;

    setOutput(bool3S::TRUE);

    for(int i = 0; i<in_port.size(); i++){
        if(in_port.at(i) == bool3S::TRUE){
            setOutput(bool3S::FALSE);
            break;
        }
        if(in_port.at(i) == bool3S::UNDEF){
            setOutput(bool3S::UNDEF);
        }
    }
    return true;

}

/// Porta XOR

//
// FALTA IMPLEMENTAR
//

bool PortaXOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()|| in_port.size() == 0) return false;

    bool3S aux;

    if(in_port[0] == bool3S::UNDEF ||  in_port[1] == bool3S::UNDEF){
        setOutput(bool3S::UNDEF);
        return true;
    }

    in_port[0] == in_port[1] ? aux = bool3S::FALSE : aux=bool3S::TRUE;

    if(in_port.size()>2){
        for(int i=2;i<in_port.size(); i++){
            if(in_port[i] == bool3S::UNDEF){
                setOutput(bool3S::UNDEF);
                return true;
            }
            in_port[i] == aux ? aux= bool3S::FALSE : aux=bool3S::TRUE;
        }
    }
    setOutput(aux);
    return true;
}
/// Porta NXOR

//
// FALTA IMPLEMENTAR
//
bool PortaNXOR::simular(const std::vector<bool3S>& in_port) {
    if (in_port.size() != getNumInputs()|| in_port.size() == 0) return false;

    bool3S aux;

    if(in_port[0] == bool3S::UNDEF ||  in_port[1] == bool3S::UNDEF){
        setOutput(bool3S::UNDEF);
        return true;
    }

    in_port[0] == in_port[1] ? aux = bool3S::FALSE : aux=bool3S::TRUE;

    if(in_port.size()>2){
        for(int i=2;i<in_port.size(); i++){
            if(in_port[i] == bool3S::UNDEF){
                setOutput(bool3S::UNDEF);
                return true;
            }
            in_port[i] == aux ? aux= bool3S::FALSE : aux=bool3S::TRUE;
        }
    }
    setOutput(~aux);
    return true;

}

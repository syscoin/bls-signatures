// pk.cpp
#include "bls.hpp"
#include "pk.h"

// Serialize the key into bytes
void* PKSerialize(PublicKey pk) {
    // caller is responsible for freeing this
    uint8_t* buffer = (uint8_t*)malloc(bls::PublicKey::PUBLIC_KEY_SIZE);

    bls::PublicKey* key = (bls::PublicKey*)pk;
    key->Serialize(buffer);

    return (void*)buffer;
}

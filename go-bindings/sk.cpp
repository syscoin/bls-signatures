// sk.cpp
#include <cstring>
#include "bls.hpp"
#include "sk.h"

SecretKey SecretKeyFromSeed(void *p, int size) {
    // caller is responsible for freeing this
    void* skPtr = (bls::PrivateKey*)malloc(bls::PrivateKey::PRIVATE_KEY_SIZE);
    bls::PrivateKey sk = bls::PrivateKey::FromSeed((uint8_t *)p, size);
    memmove(skPtr, (const void*)&sk, bls::PrivateKey::PRIVATE_KEY_SIZE);
    return skPtr;
}

SecretKey SecretKeyFromBytes(void *p, bool modOrder) {
    // debug
    // printf("bls::PrivateKey::PRIVATE_KEY_SIZE = %ld\n", bls::PrivateKey::PRIVATE_KEY_SIZE);
    // printf("sizeof(bls::PrivateKey) = %ld\n", sizeof(bls::PrivateKey));

    // caller is responsible for freeing this
    bls::PrivateKey* skPtr = new bls::PrivateKey(bls::PrivateKey::FromBytes((uint8_t*)p, modOrder));

    // debug, print bytes of key using ptr like in SKserialize
    bls::PrivateKey* kPtr = (bls::PrivateKey*)skPtr;
    auto buf = kPtr->Serialize();
    for (auto &p : buf) {
        printf("p = %d\n", p);
    }

    // debug, show address of ptr before leaving
    printf("skPtr leaving SecretKeyFromBytes = %p\n", skPtr);

    return skPtr;
}

// Serialize the key into bytes
void* SKSerialize(SecretKey sk) {
    bls::PrivateKey* key = (bls::PrivateKey*)sk;

    // debug, show address of ptr when entering, should match above
    printf("key entering SKSerialize = %p\n", key);
    // debug, print bytes of key
    auto buf = key->Serialize();
    for (auto &p2 : buf) {
       printf("p2 = %d\n", p2);
    }

    // caller is responsible for freeing this
    uint8_t* buffer = (uint8_t*)malloc(bls::PrivateKey::PRIVATE_KEY_SIZE);
    key->Serialize(buffer);
    return (void*)buffer;
}

void SecFree(void* p) {
    bls::Util::SecFree(p);
}

// SecretKeyFree frees the memory allocated for the secret key
void SecretKeyFree(SecretKey sk) {
    bls::PrivateKey* key = (bls::PrivateKey*)sk;
    delete key;
}

// Return the public key
PublicKey SKGetPublicKey(SecretKey sk) {
    bls::PrivateKey* key = (bls::PrivateKey*)sk;

    // caller is responsible for freeing this
    bls::PublicKey* pkPtr = new bls::PublicKey(key->GetPublicKey());

    return pkPtr;
}

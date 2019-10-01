// sk.h
#include "pk.h"
#ifdef __cplusplus
#include <stdbool.h>
extern "C" {
#endif

#define SECRET_KEY_SIZE 32

typedef void* SecretKey;
SecretKey SecretKeyFromSeed(void *, int);
SecretKey SecretKeyFromBytes(void *, bool);
void* SKSerialize(SecretKey);
void SecretKeyFree(SecretKey);

void SecFree(void*);

PublicKey SKGetPublicKey(SecretKey);

#ifdef __cplusplus
}
#endif

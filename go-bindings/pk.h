// pk.h
#ifdef __cplusplus
extern "C" {
#endif

#define xPUBLIC_KEY_SIZE 48

typedef void* PublicKey;
void* PKSerialize(PublicKey);
void PublicKeyFree(PublicKey);

#ifdef __cplusplus
}
#endif

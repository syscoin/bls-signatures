package blschia

// #cgo LDFLAGS: -L../build -lbls -lstdc++
// #cgo CXXFLAGS: -std=c++14 -I../src -I../build/contrib/relic/include -I../contrib/relic/include
// #include <stdbool.h>
// #include <stdlib.h>
// #include "sk.h"
import "C"
import "unsafe"
import "runtime"

type GoSecretKey struct {
	sk C.SecretKey
}

// SecretKeyFromSeed creates a new SecretKey object from a seed
func SecretKeyFromSeed(seed []byte) GoSecretKey {
	var ret GoSecretKey

	// convert to C here
	cbytes := C.CBytes(seed)
	defer C.free(cbytes)
	ret.sk = C.SecretKeyFromSeed(cbytes, C.int(len(seed)))
	runtime.SetFinalizer(&ret, func(p *GoSecretKey) { p.Free() })
	return ret
}

// SecretKeyFromBytes creates a new SecretKey object from the raw bytes
func SecretKeyFromBytes(data []byte, modOrder bool) GoSecretKey {
	var ret GoSecretKey

	// convert to C here
	cbytes := C.CBytes(data)
	defer C.free(cbytes)
	ret.sk = C.SecretKeyFromBytes(cbytes, C.bool(modOrder))
	runtime.SetFinalizer(&ret, func(p *GoSecretKey) { p.Free() })
	return ret
}

// Free releases memory allocated by the sk
func (sk GoSecretKey) Free() {
	C.free(unsafe.Pointer(sk.sk))
}

// Serialize returns a byte slice which represents the byte value of the secret
// key
func (sk GoSecretKey) Serialize() []byte {
	// returns a void*, e.g. unsafe.Pointer
	ptr := C.SKSerialize(sk.sk)
	defer C.free(ptr)
	val := C.GoBytes(ptr, C.int(C.SECRET_KEY_SIZE))
	return val
}

func (sk GoSecretKey) PublicKey() GoPublicKey {
	var pk GoPublicKey
	pk.pk = C.SKGetPublicKey(sk.sk)
	runtime.SetFinalizer(&pk, func(p *GoPublicKey) { p.Free() })
	return pk
}

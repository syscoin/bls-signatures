package blschia

// #cgo LDFLAGS: -L../build -lbls -lstdc++
// #cgo CXXFLAGS: -std=c++14 -I../src -I../build/contrib/relic/include -I../contrib/relic/include
// #include <stdlib.h>
// #include "pk.h"
import "C"

type GoPublicKey struct {
	pk C.PublicKey
}

// Free releases memory allocated by the pk
func (pk GoPublicKey) Free() {
	C.PublicKeyFree(pk.pk)
}

// Serialize returns a byte slice which represents the byte value of the public
// key
func (pk GoPublicKey) Serialize() []byte {
	// returns a void*, e.g. unsafe.Pointer
	ptr := C.PKSerialize(pk.pk)
	defer C.free(ptr)
	val := C.GoBytes(ptr, C.int(C.xPUBLIC_KEY_SIZE))
	return val
}

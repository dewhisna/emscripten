// Copyright 2016 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

int main(int argc, char **argv) {
  int fp = atoi(argv[1]);
  printf("fp: %d\n", fp);
  void (*f)(int) = reinterpret_cast<void (*)(int)>(fp);
  f(7);
  EM_ASM({
    removeFunction($0)
  }, f);
#if __wasm__
  // In the wasm backend, we can reuse indexes
  EM_ASM({
    var beforeLength = wasmTable.length;
    for (var i = 0; i < 10; i++) {
      var index = addFunction(function(){}, 'v');
      removeFunction(index);
    }
    assert(wasmTable.length === beforeLength);
  });
#endif
  printf("ok\n");
  return 0;
}

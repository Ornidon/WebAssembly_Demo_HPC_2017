// from https://gist.github.com/kripken/59c67556dc03bb6d57052fedef1e61ab
// compile with: emcc main.c -Os -s WASM=1 -s SIDE_MODULE=1 -o main.wasm
// run with: emrun --port 8080 .
int doubler(int x) {
  return 2 * x;
}
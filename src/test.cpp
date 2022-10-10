include "board.h"
int
main(){
  INITIALIZE_RAYS();
  for(int i = 0; i < 64; i++){
    for(int j = 0; j < 8; j++){
      printBits(sizeof(RAYS[i][j]), RAYS[i][j]);
    }
}
  return 0;
}
void printBits(size_t const size, void const * const ptr)
{
    unsigned char b = (unsigned char) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 0; j < 8; j++) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf("\n");
    }
    puts("");
}

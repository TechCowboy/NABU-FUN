

#define BIN_TYPE BIN_HOMEBREW

#define DISABLE_VDP

#define DISABLE_CURSOR

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <NABU-LIB.h>




    void main(){
      int x;

      initNABULIBAudio();

      puts("");
      puts("This proof on concept");
      puts("application that tests sound");
      puts("options of z88dk library");
      printf("\nVersion 4\n");

      printf("Press any key\n");
      getchar();

      printf("playing sound\n");

      for (x = 0; x < 1000; x++)
      {
        printf("%d\n",x);
        playNoteDelay(0, x, x);
}
printf("Press any key\n");
getchar();
}

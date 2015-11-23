#include <cstdlib>
#include <cstdio>
#include <vector>

int main(int argc, char **argv) {
  size_t size = 10*1024*1024;
  size_t parts = 1;

  if (argc > 1) {
    if (sscanf(argv[1], "%zu", &size) != 1) {
      fprintf(stderr, "failed to parse number: [%s]\n", argv[1]);
      return 1;
    }
  }
  if (argc > 2) {
    if (sscanf(argv[2], "%zu", &parts) != 1) {
      fprintf(stderr, "failed to parse number: [%s]\n", argv[2]);
      return 1;
    }
  }

  std::vector<void*> data;
  printf("allocating %zu parts by %zu\n", parts, size);
  for(size_t i = 0; i < parts; ++i) {
    data[i] = malloc(size);
  }
  printf("releasing resources...");
  for(size_t i = 0; i < parts; ++i) {
    free(data[i]);
  }
  printf("DONE\n");

  return 0;
}

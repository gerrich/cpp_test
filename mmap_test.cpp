#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cstdio> // perror
#include <stdint.h>
#include <stdexcept>

struct mmap_t {
  mmap_t()
    :fd(-1)
    ,data(NULL) {}

  // return 0 on success
  int load(const char *fname) {
    fd = open(fname, O_RDONLY);
    if (fd == -1) {
      throw std::runtime_error("Error opening file for reading");
      return -1;
    }

    struct stat st;
    fstat(fd, &st);
    size = st.st_size;

    data = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
      close(fd);
      throw std::runtime_error("Error mmapping the file");
      return -1;
    }

    return 0;
  }

  // returns 0 on success
  int free() {
    if (munmap(data, size) == -1) {
      throw std::runtime_error("Error un-mmapping the file");
      return -1;
    }
    close(fd);
    return 0;
  }
  int fd;
  void *data;
  size_t size;
};

int main(int argc, char **argv) {
  mmap_t mmap;
  mmap.load(argv[1]);

  size_t base = 6125487138;
  size_t factor = 1223897;
  size_t sum = 56127;
  for (size_t pos = 0; pos < mmap.size; pos += 17) {
    sum = (sum * factor + ((uint8_t*)(mmap.data))[pos]) % base;
  }

  mmap.free();

  printf("check sum: %zu\n", sum);
  return 0;
}

#include "f.h"

int main()
{
    int check_id = 0;
    srand(time(NULL));
    uint32_t valueuncomp = 0, valuecomp = 0, value;
    uint8_t buf[4];
    size_t size, sizeBuf[10];
    uint8_t* val;
    FILE* uncomp = fopen("uncompressed.dat", "wb");
    if (uncomp == NULL) {
        return -1;
    }
    FILE* comp = fopen("compressed.dat", "wb");
    if (comp == NULL) {
        return -1;
    }
    for (int i = 0; i < 1000000; i++) {
        value = generate_number();
        fwrite(&value, sizeof(uint32_t), 1, uncomp);
        size = encode_varint(value, buf);
        fwrite(buf, sizeof(uint8_t), size, comp);
        if (i < 10) {
            sizeBuf[i] = size;
        }
    }
    fclose(uncomp);
    fclose(comp);
    check_id = 0;
    uncomp = fopen("uncompressed.dat", "rb");
    comp = fopen("compressed.dat", "rb");
    for (int i = 0; i < 10; i++) {
        fread(&valueuncomp,
              sizeof(uint8_t),
              sizeof(uint32_t) / sizeof(uint8_t),
              uncomp);
        fread(&valuecomp, sizeof(uint8_t), sizeBuf[i], comp);
        val = &valuecomp;
        valuecomp = decode_varint(&val);
        printf("i = %d\t", i);
        printf("%" PRIu32 "\t", valueuncomp);
        printf("%" PRIu32 "\n", valuecomp);
        check_id++;
    }
}
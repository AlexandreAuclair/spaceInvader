#include "sprite.h"

void save_sprite_pack(const char *filename, Sprite *sprites, word count)
{
    FILE *f;
    dword *offsets;
    int i;

    f = fopen(filename, "wb");

    offsets = (dword *)malloc(sizeof(dword) * count);

    /* write count */
    fwrite(&count, sizeof(word), 1, f);

    /* reserve space for offsets */
    for(i=0;i<count;i++)
    {
        dword zero = 0;
        fwrite(&zero, sizeof(dword), 1, f);
    }

    /* write sprites */
    for(i=0;i<count;i++)
    {
        offsets[i] = ftell(f);

        fwrite(&sprites[i].width, sizeof(byte), 1, f);
        fwrite(&sprites[i].height, sizeof(byte), 1, f);
        fwrite(&sprites[i].size, sizeof(word), 1, f);

        fwrite(sprites[i].data, 1, sprites[i].size, f);
    }

    /* write real offsets */
    fseek(f, sizeof(word), SEEK_SET);

    fwrite(offsets, sizeof(dword), count, f);

    fclose(f);
    free(offsets);
}

Sprite *load_sprite(SpritePack *p, int id)
{
    Sprite *s = (Sprite *)malloc(sizeof(Sprite));

    fseek(p->file, p->offsets[id], SEEK_SET);

    fread(&s->width, sizeof(byte), 1, p->file);
    fread(&s->height, sizeof(byte), 1, p->file);
    fread(&s->size, sizeof(word), 1, p->file);

    s->data = (byte *)malloc(s->size);

    fread(s->data, 1, s->size, p->file);

    return s;
}

SpritePack *open_sprite_pack(const char *filename)
{
    SpritePack *p = (SpritePack *)malloc(sizeof(SpritePack));

    p->file = fopen(filename, "rb");

    fread(&p->count, sizeof(word), 1, p->file);

    p->offsets = (dword *)malloc(sizeof(dword) * p->count);

    fread(p->offsets, sizeof(dword), p->count, p->file);

    return p;
}
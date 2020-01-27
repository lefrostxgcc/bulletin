#ifndef MODEL_PHOTO_COMMON_H
#define MODEL_PHOTO_COMMON_H

struct Model_photo
{
  int id;
  int bull_id;
  char link[256];
  char info[256];
};

struct Model_photoform
{
  void *file;
  size_t file_size;
  char filename[256];
  char link[256];
  char info[256];
};

#endif

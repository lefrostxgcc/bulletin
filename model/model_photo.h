#ifndef MODEL_PHOTO_H
#define MODEL_PHOTO_H

struct Model_photo
{
  int id;
  int bull_id;
  char link[256];
  char info[256];
};

struct Model_photo *select_photos_by_bull_id(int bull_id);

void model_photos_free(struct Model_photo *photos);

#endif

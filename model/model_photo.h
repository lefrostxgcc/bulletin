#ifndef MODEL_PHOTO_H
#define MODEL_PHOTO_H

#include "model_photo_common.h"

struct Model_photo *select_photos_by_bull_id(int bull_id);
void select_model_photo_by_id(struct Model_photo *photo, int id);

void model_photo_set_new(
			 struct Model_photo *photo,
			 const struct Model_photoform *form,
			 int bull_id
			 );

int model_photo_insert(const struct Model_photo *photo);
int model_photo_update_info_by_id(const struct Model_photo *photo);
int model_photo_load_info_by_post(struct Model_photo *photo);
int model_photo_load_id_by_post(struct Model_photo *photo);

void model_photos_free(struct Model_photo *photos);

#endif

#ifndef VIEW_PHOTO_H
#define VIEW_PHOTO_H

#include "../../model/model_photo.h"

void render_photo_index(const char *username,
			const struct Model_photo photos[],
			int bull_id);

void render_photo_add(const char *username, int bull_id);

#endif

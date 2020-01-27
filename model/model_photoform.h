#ifndef MODEL_PHOTOFORM_H
#define MODEL_PHOTOFORM_H

#include <stddef.h>
#include "model_photo_common.h"

enum Photoform_status
  {
   PHOTOFORM_VALID,
   PHOTOFORM_FILE_INVALID_EXTENSION = 1,
   PHOTOFORM_FILE_EMPTY = 1 << 1
  };

enum Photoform_element_index
  {
   PHOTOFORM_FILE_INDEX,
   PHOTOFORM_LINK_INDEX,
   PHOTOFORM_INFO_INDEX,
   PHOTOFORM_ELEMENT_COUNT
  };

int model_photoform_validate(const struct Model_photoform *photoform);

const char **model_photoform_attribute_labels(void);
struct Model_photoform *model_photoform_load_by_post_request(void);
void model_photoform_free(struct Model_photoform *photoform);

#endif

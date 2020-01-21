#ifndef MODEL_PHOTOFORM_H
#define MODEL_PHOTOFORM_H

struct Model_photoform
{
  void *file;
  size_t file_size;
  char filename[256];
  char link[256];
  char info[256];
};

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

#endif

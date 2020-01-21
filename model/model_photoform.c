#include <string.h>
#include <stdbool.h>
#include "model_photoform.h"

static bool ends_with(const char *str, const char *pat)
{
  if (!str || !pat)
    return false;
  const char *s = str + strlen(str);
  const char *p = pat + strlen(pat);
  while (s != str && p != pat)
    if (*--s != *--p)
      return false;
  return p == pat;
}

int model_photoform_validate(const struct Model_photoform *photoform)
{
  int status = PHOTOFORM_VALID;
  if (photoform->file_size == 0)
    status |= PHOTOFORM_FILE_EMPTY;
  if (
      !ends_with(photoform->filename, ".png") &&
      !ends_with(photoform->filename, ".jpg")
      )
    status |= PHOTOFORM_FILE_INVALID_EXTENSION;
  return status;
}

const char **model_photoform_attribute_labels(void)
{
  static const char *labels[PHOTOFORM_ELEMENT_COUNT] =
    {
     [PHOTOFORM_FILE_INDEX] = "Загрузить изображение",
     [PHOTOFORM_LINK_INDEX] = "Ссылка",
     [PHOTOFORM_INFO_INDEX] = "Информация",
    };
  return labels;
}

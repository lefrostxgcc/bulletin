#include <string.h>
#include "model_bulletinsform.h"

int
model_bulletinsform_validate(const struct Model_bulletinsform *bulletinsform)
{
  int status = BULLETINSFORM_VALID;
  if (strlen(bulletinsform->title) == 0)
    status |= EMPTY_BULLETINSFORM_TITLE;
  if (strlen(bulletinsform->info) == 0)
    status |= EMPTY_BULLETINSFORM_INFO;
  if (strlen(bulletinsform->contacts) == 0)
    status |= EMPTY_BULLETINSFORM_CONTACTS;
  if (strlen(bulletinsform->city) == 0)
    status |= EMPTY_BULLETINSFORM_CITY;
  if (bulletinsform->price == 0)
    status |= EMPTY_BULLETINSFORM_PRICE;
  return status;
}

const char **model_bulletinsform_attribute_labels(void)
{
  static const char *labels[BULLETINSFORM_ELEMENT_COUNT] =
    {
     [BULLETINSFORM_TITLE_INDEX] = "Заголовок",
     [BULLETINSFORM_INFO_INDEX] = "Информация",
     [BULLETINSFORM_CONTACTS_INDEX] = "Контакты",
     [BULLETINSFORM_CITY_INDEX] = "Город",
     [BULLETINSFORM_PRICE_INDEX] = "Цена",
    };
  return labels;
}

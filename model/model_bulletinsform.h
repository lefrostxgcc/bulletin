#ifndef MODEL_BULLETINSFORM_H
#define MODEL_BULLETINSFORM_H

enum Bulletinsform_status
  {
   BULLETINSFORM_VALID,
   EMPTY_BULLETINSFORM_TITLE = 1,
   EMPTY_BULLETINSFORM_INFO = 1 << 1,
   EMPTY_BULLETINSFORM_CONTACTS = 1 << 2,
   EMPTY_BULLETINSFORM_CITY = 1 << 3,
   EMPTY_BULLETINSFORM_PRICE = 1 << 4,
  };

enum Bulletinsform_element_index
  {
   BULLETINSFORM_TITLE_INDEX,
   BULLETINSFORM_INFO_INDEX,
   BULLETINSFORM_CONTACTS_INDEX,
   BULLETINSFORM_CITY_INDEX,
   BULLETINSFORM_PRICE_INDEX,
   BULLETINSFORM_ELEMENT_COUNT
  };

struct Model_bulletinsform
{
  char title[256];
  char info[256];
  char contacts[256];
  char city[256];
  double price;
};

int
model_bulletinsform_validate(const struct Model_bulletinsform *bulletinsform);

const char **model_bulletinsform_attribute_labels(void);

int
model_bulletinsform_load_by_post_request(struct Model_bulletinsform *form);

#endif

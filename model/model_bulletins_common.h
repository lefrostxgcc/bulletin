#ifndef MODEL_BULLETINS_COMMON_H
#define MODEL_BULLETINS_COMMON_H

struct Model_bulletins
{
  int id;
  int user_id;
  char date_pub[256];
  char title[256];
  char info[256];
  char contacts[256];
  char city[256];
  double price;
  char status[256];
  int avatar;
  char link[256];
};

struct Model_bulletinsform
{
  char title[256];
  char info[256];
  char contacts[256];
  char city[256];
  double price;
};

#endif

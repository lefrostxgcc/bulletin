#ifndef MODEL_BULLETINS_H
#define MODEL_BULLETINS_H

#include "model_bulletinsform.h"

struct Model_bulletins
{
  int id;
  int user_id;
  char title[256];
  char info[256];
  char contacts[256];
  char city[256];
  double price;
  char status[256];
};

void model_bulletins_set_new(
			    struct Model_bulletins *bulletin,
			    const struct Model_bulletinsform *form,
			    int session_user_id
			    );

int model_bulletins_save(const struct Model_bulletins *bulletin);

#endif

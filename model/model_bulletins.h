#ifndef MODEL_BULLETINS_H
#define MODEL_BULLETINS_H

#include "model_bulletins_common.h"

void model_bulletins_set_new(
			    struct Model_bulletins *bulletin,
			    const struct Model_bulletinsform *form,
			    int session_user_id
			    );

int model_bulletins_insert(const struct Model_bulletins *bulletin);
int model_bulletins_update(const struct Model_bulletins *bulletin);

struct Model_bulletins *
select_bulletins_by_userid_and_status(int user_id, const char *status);

struct Model_bulletins *select_bulletins_by_status(const char *status);

struct Model_bulletins *select_bulletin_by_id(int id);
void model_bulletins_set_public(struct Model_bulletins *bulletin);
void model_bulletins_set_wait(struct Model_bulletins *bulletin);
void model_bulletins_set_delete(struct Model_bulletins *bulletin);
void model_bulletins_free(struct Model_bulletins *bulletin);
int model_bulletins_edit(const struct Model_bulletins *bulletin);
void model_bulletins_update_avatar(const struct Model_bulletins *bulletin);

#endif

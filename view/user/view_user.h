#ifndef VIEW_USER_H
#define VIEW_USER_H

#include "../../model/model_user.h"
#include "../../model/model_userinfo.h"

void render_user_index(const struct Model_user *user,
		       const struct Model_userinfo *userinfo);

#endif

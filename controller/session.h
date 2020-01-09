#ifndef SESSION_H
#define SESSION_H

int session_get_curr_user_id(void);
void session_redirect(const char *url, const char *http_headers);
void unescape_url(char *url);

#endif

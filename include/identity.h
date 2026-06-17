#ifndef IDENTITY_H
#define IDENTITY_H

#include <stdint.h>

#define ID_UID_LEN      32
#define ID_PUBKEY_LEN   32
#define ID_PRIVKEY_LEN  64

typedef struct identity {
    uint8_t uid[ID_UID_LEN];
    uint8_t pubkey[ID_PUBKEY_LEN];
    uint8_t privkey[ID_PRIVKEY_LEN];
} identity_t;

identity_t authenticate(void);

#endif
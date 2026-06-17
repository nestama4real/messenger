#include <stdio.h>
#include <string.h>
#include <sodium.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "identity.h"

#define APP_NAME "messenger"

#define ID_PUB_FILENAME "identity.pub"
#define ID_KEY_FILENAME "identity.key"

#define ID_DIR_REL_PATH ".config/" APP_NAME
#define ID_PUB_REL_PATH ID_DIR_REL_PATH "/" ID_PUB_FILENAME
#define ID_KEY_REL_PATH ID_DIR_REL_PATH "/" ID_KEY_FILENAME

static const char *id_pub_path(void)
{
    static char path[4096];
    const char *home = getenv("HOME");

    if (!home)
        return NULL;

    snprintf(path, sizeof(path), "%s/%s", home, ID_PUB_REL_PATH);
    return path;
}

static const char *id_key_path(void)
{
    static char path[4096];
    const char *home = getenv("HOME");

    if (!home)
        return NULL;

    snprintf(path, sizeof(path), "%s/%s", home, ID_KEY_REL_PATH);
    return path;
}

static int identity_mkdir(void)
{
    char path[4096];
    const char *home = getenv("HOME");

    if (!home)
        return -1;

    snprintf(path, sizeof(path), "%s/%s", home, ID_DIR_REL_PATH);

    mkdir(path, 0700);
    return 0;
}

static int identity_load(identity_t *id)
{
    FILE *f;

    if (!id)
        return -1;

    f = fopen(id_key_path(), "rb");
    if (!f)
        return -1;

    if (fread(id->privkey, 1, ID_PRIVKEY_LEN, f) != ID_PRIVKEY_LEN)
        return fclose(f), -1;

    fclose(f);

    f = fopen(id_pub_path(), "rb");
    if (!f)
        return -1;

    if (fread(id->pubkey, 1, ID_PUBKEY_LEN, f) != ID_PUBKEY_LEN)
        return fclose(f), -1;

    fclose(f);

    crypto_hash_sha256(id->uid, id->pubkey, ID_PUBKEY_LEN);

    return 0;
}

static int identity_save(const identity_t *id)
{
    FILE *f;

    if (!id)
        return -1;

    identity_mkdir();

    f = fopen(id_key_path(), "wb");
    if (!f)
        return -1;

    if (fwrite(id->privkey, 1, ID_PRIVKEY_LEN, f) != ID_PRIVKEY_LEN)
        return fclose(f), -1;

    fclose(f);

    chmod(id_key_path(), 0600);

    f = fopen(id_pub_path(), "wb");
    if (!f)
        return -1;

    if (fwrite(id->pubkey, 1, ID_PUBKEY_LEN, f) != ID_PUBKEY_LEN)
        return fclose(f), -1;

    fclose(f);

    return 0;
}

static void identity_generate(identity_t *id)
{
    if (!id)
        return;

    crypto_sign_keypair(id->pubkey, id->privkey);
    crypto_hash_sha256(id->uid, id->pubkey, ID_PUBKEY_LEN);
}

identity_t authenticate(void)
{
    identity_t id;

    memset(&id, 0, sizeof(id));

    if (identity_load(&id) == 0)
        return id;

    identity_generate(&id);
    identity_save(&id);

    return id;
}

int main(void)
{
    identity_t id;

    if (sodium_init() < 0)
        return 1;

    id = authenticate();

    for (int i = 0; i < ID_PRIVKEY_LEN; i++)
        printf("%02x", id.privkey[i]);
    printf("\n");

    for (int i = 0; i < ID_PUBKEY_LEN; i++)
        printf("%02x", id.pubkey[i]);
    printf("\n");

    for (int i = 0; i < ID_UID_LEN; i++)
        printf("%02x", id.uid[i]);
    printf("\n");

    printf("%s\n", id_key_path());

    return 0;
}
/* crypto.h - ectun crypto wrappers around polarssl */

#ifndef CRYPTO_H
#define CRYPTO_H

#include <polarssl/aes.h>
#include <polarssl/rsa.h>

typedef unsigned char byte;
typedef byte asymm_pubkey[256];
typedef byte asymm_msg[256];
typedef byte nonce[32];
typedef byte symm_key[32];
typedef byte hmac_key[32];
typedef byte hash_val[32];
typedef byte hmac_val[32];

extern void mknonce(nonce n);
extern void randbytes(size_t len, byte *buf);
extern void xorbytes(size_t len, const byte *a, const byte *b, byte *c);

struct symm_ctx {
	aes_context ctx;
	int offset;
	byte block[16];
	byte ctr[16];
};

extern void symm_init(struct symm_ctx *ctx, const symm_key key, int high);
extern void symm_gen(symm_key key);
extern void symm(struct symm_ctx *ctx, size_t sz, const byte *in, byte *out);

extern void hash(size_t sz, const byte *in, hash_val out);
extern void hmac(hmac_key key, size_t sz, const byte *in, hmac_val out);
extern int hmac_ok(hmac_key key, size_t sz, const byte *in);

struct asymm_ctx {
	rsa_context rsa;
};

extern void asymm_init(struct asymm_ctx *ctx);
extern int asymm_gen(struct asymm_ctx *ctx);
extern char *asymm_ukey(struct asymm_ctx *ctx);
extern char *asymm_pkey(struct asymm_ctx *ctx);
extern int asymm_set_ukey(struct asymm_ctx *ctx, char *ukey);
extern int asymm_set_pkey(struct asymm_ctx *ctx, char *pkey);
extern void asymm_write_ukey(struct asymm_ctx *ctx, asymm_pubkey ukey);
extern int asymm_read_ukey(struct asymm_ctx *ctx, const asymm_pubkey ukey);
extern int asymm_encrypt(struct asymm_ctx *ctx, size_t len, const asymm_msg in, asymm_msg out);
extern ssize_t asymm_decrypt(struct asymm_ctx *ctx, size_t len, const asymm_msg in, asymm_msg out);

#endif /* !CRYPTO_H */

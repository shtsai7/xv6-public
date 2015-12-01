typedef uchar uint8_t;
typedef uchar u_int8_t;
typedef ushort uint16_t;
typedef ushort u_int16_t;
typedef uint uint32_t;
typedef uint u_int32_t;
typedef uint size_t;

/* This implementation is adaptable to current computing power.
 * You can have up to 2^31 rounds which should be enough for some
 * time to come.
 */
#define BCRYPT_SALTLEN 16	/* Precomputation is just so nice */
#define BCRYPT_WORDS 6		/* Ciphertext words */
#define BCRYPT_MINBCRYPT_DEFAULT_LOGROUNDS 4	/* we have log2(rounds) in salt */
#define	BCRYPT_HASHLEN (BCRYPT_WORDS * 4)

#define BCRYPT_DEFAULT_LOGR 12

int bcrypt_hashpass(const char *key, const uchar *csalt, uchar *encrypted, uint8_t logr);
int bcrypt_checkpass(const char *pass, const uchar *salt, const uchar *goodhash);
uchar * bcrypt(const char *pass, const uchar *salt);

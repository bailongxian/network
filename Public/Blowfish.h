#ifndef __BLOWFISH_H__	
#define __BLOWFISH_H__	
#define ECB 0 /*default*/  
#define CBC 1  
#define CFB 2  
#define MAX_KEY_SIZE 56  
#define MAX_PBLOCK_SIZE 18	
#define MAX_SBLOCK_XSIZE 4	
#define MAX_SBLOCK_YSIZE 256 

class CBlowfish
{
public:
	CBlowfish() {};
	~CBlowfish() {};

	int Init(unsigned char* unKey, size_t keysize);
	int Encrypt(unsigned char* in, size_t in_size, unsigned char* out, size_t out_size, int iMode);
	int Decrypt(unsigned char* in, size_t in_size, unsigned char* out, size_t out_size, int iMode);

 	struct SBlock
 	{
		unsigned int m_uil;
		unsigned int m_uir;
	};

private:

	void HexStr2CharStr(unsigned char *pszHexStr, int in_size, unsigned char *pucCharStr);
	void CharStr2HexStr(unsigned char *pucCharStr, int in_size, unsigned char *pszHexStr);
	int  DecryptByte(unsigned char *bin, size_t n, unsigned char *bout, int iMode);
	int  EncryptByte(unsigned char *bin, size_t n, unsigned char *bout, int iMode);
	void BlockToBytes(SBlock *b, unsigned char *buf);  
	void EncryptBlock(SBlock *block);  
	void DecryptBlock(SBlock *block); 

private:
	SBlock m_oChain;
	unsigned int m_auiP[MAX_PBLOCK_SIZE];
	unsigned int m_auiS[MAX_SBLOCK_XSIZE][MAX_SBLOCK_YSIZE];
		
};
#endif /*__BLOWFISH_H__*/  

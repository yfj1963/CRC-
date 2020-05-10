struct PasswordMS
{
	int scoped;
	int adjustCount;
};
struct PasswordState
{
    int lastDigitPos;
	int lastLowerLetterPos;
	int lasttouperLetterPos;
	int currentScoped;
	int len;
	int needAdjustCount;
	int dupCount;
};
void setCurrentState(char *c, PasswordState &currentState)
{
	if (isdigit(c))
	{
		currentState.lastDigitPos = i;
	}
	if (isupper(c))
	{
		currentState.lasttouperLetterPos = i;
	}
	if (islower(c))
	{
		currentState.lastLowerLetterPos = i;
	}
	if (i != 0)
	{
		if (c != preC)
		{

		}
	}
}
void anlyzerSmallPasswordInfo(char *pd, int ms, int scoped, PasswordState &currentState, PasswordMS &passwordMS)
{
	int len = currentState.len;
	for (int i = 0; i < len; ++i)
	{
		setCurrentState(pd[i], currentState);
		
    }
}
void anlyzerBigerPasswordInfo(char *pd, int ms, int scoped, PasswordMS &passwordMS)
{

}

void anlyzerPasswordInfo(char *pd, int ms, int scoped)
{
	if (pd == nullptr)
	{
		return;
	}
	int len = strlen(pd);
	PasswordState currentState;
	currentState.currentScoped = scoped;
	if (len < 6)
	{

	}

}

typedef  unsigned char BYTE;
typedef unsigned long long QWORD;
BYTE getBitsMaxLen(QWORD object)
{
	BYTE i = 0;
	BYTE j = 0;
	QWORD temp = 0;
	for (i = 63; i > 0; --i)
	{
		temp = (object >> 1);
		temp = temp & 0x1;
		if (1 == temp && j < 64)
			return 64 - j;
		j++;
	}
	return 0;
}
void transNum2Bits(QWORD object, BYTE len, BYTE *array)
{
	if (array == nullptr) return;

	BYTE i = 0;
	BYTE j = 0;
	QWORD temp = 0;
	
	if (len > 64) return;

	for (i = len; i >= 0 && j <= 64; i--)
	{
		temp = (object >> i);
		temp = temp & 0x1;
		array[j++] = temp;
	}
}
QWORD binTransToInt(BYTE *array, BYTE len, BYTE maxLen)
{
	QWORD sum = 0;
	BYTE i = 0;
	QWORD temp = 0;

	if (maxLen > 64) return 0;

	for (i = len; i < maxLen; i++)
	{
		temp = 0;
		temp = temp | array[i];
		temp = temp << (maxLen - i - 1);
		sum = sum + temp;
	}
	return sum;
}

void caluCrc(BYTE *objectArray, BYTE *divArray, BYTE len)
{
	BYTE flag = 0;
	BYTE i = 0;
	BYTE temp = 0;
	if (objectArray == nullptr || divArray == nullptr) return;
	for (i = 0; i < len;)
	{
		flag = 0;
		if (objectArray[i] == 1)
		{
			for (BYTE j = 32; j >= 0; --j)
			{
				BYTE tempDiv = divArray[j];
				objectArray[i + j] = objectArray[i + j] ^ tempDiv;
				if (objectArray[i + j] == 1)
				{
					temp = i + j;
					flag = 1;
				}
			}
			i = temp;
		}
		if (!flag)
			i++;
	}
}

QWORD getRemainder(QWORD input)
{
	BYTE arraF[64] = { 0 };
	BYTE divarry[33] = { 0 };
	
	BYTE bitNum = getBitsMaxLen(input);

	transNum2Bits(input, bitNum - 1, arraF);
	transNum2Bits(0X104c11db7, 32, divarry);
	caluCrc(arraF, divarry, bitNum);
	return binTransToInt(arraF, bitNum, 32 + bitNum);
}
QWORD getHashId(QWORD input)
{
	QWORD y1 = 0xc704dd78;
	QWORD y2 = getRemainder(input);
	return ~(y1 ^ y2);
}

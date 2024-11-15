#include <bits/stdc++.h>
using namespace std;
#define MP make_pair
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define MAXN 200005
#define MAXM 1000005
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using pdd = pair<double, double>;
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define debug(x) cerr << #x << " = " << x << "\n"
#define int long long

bitset<48> subkey[16];

int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
			 60, 52, 44, 36, 28, 20, 12, 4,
			 62, 54, 46, 38, 30, 22, 14, 6,
			 64, 56, 48, 40, 32, 24, 16, 8,
			 57, 49, 41, 33, 25, 17, 9,  1,
			 59, 51, 43, 35, 27, 19, 11, 3,
			 61, 53, 45, 37, 29, 21, 13, 5,
			 63, 55, 47, 39, 31, 23, 15, 7 };

int IP_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
			  39, 7, 47, 15, 55, 23, 63, 31,
			  38, 6, 46, 14, 54, 22, 62, 30,
			  37, 5, 45, 13, 53, 21, 61, 29,
			  36, 4, 44, 12, 52, 20, 60, 28,
			  35, 3, 43, 11, 51, 19, 59, 27,
			  34, 2, 42, 10, 50, 18, 58, 26,
			  33, 1, 41,  9, 49, 17, 57, 25};

int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12,  4}; 
 
int PC_2[] = {14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32};
 
int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int E[] = {32,  1,  2,  3,  4,  5,
		    4,  5,  6,  7,  8,  9,
		    8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1};
 
int S_BOX[8][4][16] = {
	{  
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},  
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},  
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
	},
	{  
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}  
	}, 
	{  
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}  
	}, 
	{  
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},  
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}  
	},
	{  
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}  
	},
	{  
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}  
	}, 
	{  
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}  
	}, 
	{  
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}  
	} 
};

int P[] = {16,  7, 20, 21,
		   29, 12, 28, 17,
		    1, 15, 23, 26,
		    5, 18, 31, 10,
		    2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25 };

bitset<64> stringToBit(string s){
    bitset<64> res;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            res[(7-i) * 8 + j] = ((s[i] >> (j)) & 1);
        }
    }
    return res;
}

template<int T>
string bitToHex(bitset<T> b){
	string res = "";
	for (int i = T-1; i >= 0; i -= 4){
		int x = 0;
		for (int j = 0; j < 4; j++){
			x += pow(2, 3 - j) * b[i - j];
		}
		if (x == 10)
			res += "A";
		else if (x == 11)
			res += "B";
		else if (x == 12)
			res += "C";
		else if (x == 13)
			res += "D";
		else if (x == 14)
			res += "E";
		else if (x == 15)
			res += "F";
		else
			res += to_string(x);
	}
	return res;
}

template<int T>
void de(bitset<T> b){
	for (int i = 0; i < T; i++){
		cout << b[i];
	}
	cout << "(" << bitToHex<T>(b) << ") ";
}

bitset<32> f(bitset<32> in, bitset<48> k){
    bitset<48> expand;
    for (int i = 0; i < 48; i++){
        expand[i] = in[32 - E[47 - i]];
    }
    expand ^= k;
    bitset<32> res;
    for (int i = 0; i < 48; i += 6){
        int row = 1 * expand[i] + 2 * expand[i + 5], column = 1 * expand[i + 1] + 2 * expand[i + 2] + 4 * expand[i + 3] + 8 * expand[i + 4];
        bitset<4> num(S_BOX[7 - i / 6][row][column]);
        for (int j = 0; j < 4; j++){
            res[i / 6 * 4 + j] = num[j];
        }
    }
    bitset<32> tmp = res;
    for (int i = 0; i < 32; i++){
        res[i] = tmp[32 - P[31 - i]];
    }
    return res;
}

bitset<28> leftShift(bitset<28> key, int shift){
    bitset<28> res = key;
    for (int i = 0; i < 28; i++){
        if (i - shift < 0)
            res[i] = key[i - shift + 28];
        else
            res[i] = key[i - shift];
        
    }
    return res;
}

void keyGenerate(bitset<64> key){
    bitset<56> r_key;
    bitset<28> left, right;
    bitset<48> s_key;
    for (int i = 0; i < 56; i++){
        r_key[i] = key[64 - PC_1[55 - i]];
    }
    for (int r = 0; r < 16; r++){
        for (int i = 0; i < 28; i++){
            right[i] = r_key[i];
            left[i] = r_key[i + 28];
        }
        left = leftShift(left, shiftBits[r]);
        right = leftShift(right, shiftBits[r]);
        for (int i = 0; i < 28; i++){
            r_key[i] = right[i];
            r_key[i + 28] = left[i];
        }
        for (int i = 0; i < 48; i++){
            s_key[i] = r_key[56 - PC_2[47 - i]];
        }
        subkey[r] = s_key;
    }    
}

bitset<64> encrypt(bitset<64> plainText){
    bitset<64> cipher, tmp_cipher, tmp_plain = plainText;
    bitset<32> left;
    bitset<32> right;
    bitset<32> tmp;
    
	for (int i = 0; i < 64; i++){
        plainText[i] = tmp_plain[64 - IP[63 - i]];
    }

    for (int i = 0; i < 32; i++){
        right[i] = plainText[i];
        left[i] = plainText[i + 32];
    }
    for (int i = 0; i < 16;i++){
        tmp = right;
        right = left ^ f(right, subkey[i]);
        left = tmp;
    }

    for (int i = 0; i < 32; i++){
        cipher[i] = left[i];
        cipher[i + 32] = right[i];
    }
    tmp_cipher = cipher;
    for (int i = 0; i < 64; i++){
        cipher[i] = tmp_cipher[64 - IP_1[63 - i]];
    }
    return cipher;

}

signed main()
{
    fastio;
    string plainText, key;
	int t = 5;
	while(t--){
		cin >> key >> plainText;
		bitset<64> b_plainText = stringToBit(plainText), b_key = stringToBit(key), ans;
		keyGenerate(b_key);
		ans = encrypt(b_plainText);
		cout << bitToHex<64>(ans) << "\n";
	}
}

